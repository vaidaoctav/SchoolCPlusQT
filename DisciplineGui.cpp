#include "DisciplinieGui.h"

void DisciplineStoreGUI::initializeGUIComponents() {

	//impartim fereastra in 2: in stanga, butoane+labels+qlineedits
	//iar in dreapta: tabelul cu discipline

	//"stanga" si "dreapta" pentru ca este QHBoxLayout
	//se adauga componente incepand din stanga, pe orizontala
	//aici: "left" component, then "right" component
	//care la randul lor contin alte componente

	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);


	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editDenumire = new QLineEdit;
	editOre = new QLineEdit;
	editTip = new QLineEdit;
	editCadru = new QLineEdit;

	lyForm->addRow(lblDenumire, editDenumire);
	lyForm->addRow(lblOre, editOre);
	lyForm->addRow(lblTip, editTip);
	lyForm->addRow(lblCadru, editCadru);
	btnAddDisciplina = new QPushButton("Adauga disciplina");
	lyForm->addWidget(btnAddDisciplina);


	//in layout-ul care corespunde partii din stanga a ferestrei
	lyLeft->addWidget(form);


	//Radio Buttons: ne ajuta cand trebuie sa selectam doar o 
	//optiune din mai multe (doar un RadioButton poate fi selectat
	//la un moment dat)


	//vs. CheckBox (see documentation)
	//also see documentation on QGroupBox, QRadioButton pentru detalii

	//cream un GroupBox pentru radiobuttons care corespund 
	

	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSrtOre);
	lyRadioBox->addWidget(radioSrtDisciplina);

	btnSortDiscipline = new QPushButton("Sorteaza discipline");
	lyRadioBox->addWidget(btnSortDiscipline);

	//adaugam acest grup in partea stanga, 
	//dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(groupBox);

	//cream un form pentru filtrarea dupa gen 
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterOre = new QLineEdit();
	lyFormFilter->addRow(lblFilterCriteria, editFilterOre);
	btnFilterDiscipline = new QPushButton("Filtreaza disciplina dupa ore");
	lyFormFilter->addWidget(btnFilterDiscipline);

	lyLeft->addWidget(formFilter);

	//Buton folosit pentru a reincarca datele

	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);


	
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 4;
	this->tableDiscipline = new QTableWidget{ noLines, noColumns };

	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Denumire" << "Ore" << "Tip" << "Cadru";
	this->tableDiscipline->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tableDiscipline->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	btnContract = new QPushButton{ "Open Contract" };
	lyLeft->addWidget(btnContract);
	btnModel= new QPushButton{ "Open Model" };
	lyLeft->addWidget(btnModel);
	lyRight->addWidget(tableDiscipline);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

}
void DisciplineStoreGUI::reloadDisciplinaList(vector<Disciplina> discipline) {
	this->tableDiscipline->clearContents();
	this->tableDiscipline->setRowCount(discipline.size());

	int lineNumber = 0;
	for (auto& disciplina : discipline) {
		this->tableDiscipline->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(disciplina.getDenumire())));
		this->tableDiscipline->setItem(lineNumber, 1, new QTableWidgetItem(QString::number(disciplina.getOre())));
		this->tableDiscipline->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(disciplina.getTip())));
		this->tableDiscipline->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(disciplina.getCadru())));
		lineNumber++;
	}
}

void DisciplineStoreGUI::connectSignalsSlots() {
	QObject::connect(btnAddDisciplina, &QPushButton::clicked, this, &DisciplineStoreGUI::guiAddDisciplina);

	QObject::connect(btnSortDiscipline, &QPushButton::clicked, [&]() {
		if (this->radioSrtOre->isChecked())
			this->reloadDisciplinaList(srv.sortareOre());
		else if (this->radioSrtDisciplina->isChecked())
			this->reloadDisciplinaList(srv.sortareDenumire());
		});

	QObject::connect(btnFilterDiscipline, &QPushButton::clicked, [&]() {
		int nrOre = this->editFilterOre->text().toDouble();
		this->reloadDisciplinaList(srv.filtreazaDiscipline(nrOre));
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadDisciplinaList(srv.getAllDiscipline());
		});
	
	QObject::connect(btnContract, &QPushButton::clicked, [&]() {

		contractWindow.show();
		});
	QObject::connect(btnModel, &QPushButton::clicked, [&]() {

		modeleWindow.show();
		});
}


void DisciplineStoreGUI::guiAddDisciplina() {
	try {
		//preluare detalii din QLineEdit-uri
		string denumire = editDenumire->text().toStdString();
		double ore = editOre->text().toDouble();
		string tip = editTip->text().toStdString();
		string cadru = editCadru->text().toStdString();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		editDenumire->clear();
		editOre->clear();
		editTip->clear();
		editCadru->clear();

		this->srv.addDisciplina(denumire, ore, tip, cadru);
		this->reloadDisciplinaList(this->srv.getAllDiscipline());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Disciplina adaugata cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}


}