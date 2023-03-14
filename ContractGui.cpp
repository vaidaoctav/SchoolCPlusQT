#include "ContractGui.h"



void ContractGUI::initGUI() {
	lyMain = new QHBoxLayout{};
	this->setLayout(lyMain);

	QWidget* leftSide = new QWidget{};
	QVBoxLayout* lyLeft = new QVBoxLayout{};
	leftSide->setLayout(lyLeft);

	QWidget* formW = new QWidget{};
	QFormLayout* lyEdits = new QFormLayout{};
	lblDenumire = new QLabel{ "Denumire" };

	editDenumire = new QLineEdit{};


	lblSlider = new QLabel{ "Nr. discipline de generat" };
	editNoSlider = new QLineEdit{};
	lyEdits->addRow(lblDenumire, editDenumire);
	lyEdits->addRow(lblSlider, editNoSlider);
	formW->setLayout(lyEdits);


	btnAdd = new QPushButton{ "Adauga in contract" };
	btnGenerate = new QPushButton{ "Genereaza random" };
	btnEmpty = new QPushButton{ "Goleste contract" };
	btnClose = new QPushButton{ "Close" };


	btnDrawWindow = new QPushButton{ "Fereastra desen" };
	btnDrawWindow->setStyleSheet("background-color: yellow");


	sliderGenerate = new QSlider{};
	sliderGenerate->setMinimum(1);
	sliderGenerate->setMaximum(static_cast<int>(srv.getAllDiscipline().size()));

	lyLeft->addWidget(formW);
	lyLeft->addWidget(btnAdd);
	lyLeft->addWidget(btnGenerate);
	lyLeft->addWidget(btnEmpty);
	lyLeft->addWidget(btnClose);
	lyLeft->addWidget(btnDrawWindow);

	QWidget* rightSide = new QWidget{};
	QVBoxLayout* lyRight = new QVBoxLayout{};
	rightSide->setLayout(lyRight);

	disciplinaList = new QListWidget{};
	disciplinaList->setFixedWidth(320);
	disciplinaList->setSelectionMode(QAbstractItemView::SingleSelection);

	lyRight->addWidget(disciplinaList);

	widgetDynamic = new QWidget{};
	lyBtnDynamic = new QVBoxLayout{};
	widgetDynamic->setLayout(lyBtnDynamic);
	reloadDynamicButtons();

	lyMain->addWidget(leftSide);
	lyMain->addWidget(sliderGenerate);
	lyMain->addWidget(rightSide);
	lyMain->addWidget(widgetDynamic);


}
set<string> ContractGUI::getGenres(const vector<Disciplina>& contractDiscipline) {
	
	set<string> genres;

	for (const auto& d : contractDiscipline) {
		genres.insert(d.getTip());
	}
	return genres;
}
int howManyWithGenre(const vector<Disciplina>& discipline, string genre) {
	int noDiscipline = count_if(discipline.begin(), discipline.end(), [&](Disciplina d) {
		return d.getTip() == genre; });
	return noDiscipline;
}
void clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}
void ContractGUI::reloadDynamicButtons() {
	
	clearLayout(this->lyBtnDynamic);
	const vector<Disciplina>& contractDisciplina = this->srv.getDisciplineContract();
	set<string> genres = this->getGenres(contractDisciplina);

	for (string genre : genres) {
		QPushButton* btn = new QPushButton{ QString::fromStdString(genre) };
		lyBtnDynamic->addWidget(btn);
		int howMany = howManyWithGenre(contractDisciplina, genre);
		//mult mai eficient: puteam sa folosim un dictionar cu cheia = gen, valoare=nr melodii
		//->o singura parcurgere a listei de melodii
		QObject::connect(btn, &QPushButton::clicked, [genre, howMany]() {
			QMessageBox::information(nullptr, "Info", QString::fromStdString("Discipline cu  " + genre + " : " + to_string(howMany)));

			});
	}
	
}
void ContractGUI::connectSignalsSlots() {
	
	srv.getContract().addObserver(this);
	QObject::connect(btnAdd, &QPushButton::clicked, this, &ContractGUI::addToContract);
	QObject::connect(sliderGenerate, &QSlider::sliderReleased, [&]() {
		qDebug() << sliderGenerate->value();
		});
	QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
		int noDiscipline = this->sliderGenerate->value();
		editNoSlider->setText(QString::number(noDiscipline));
		qDebug() << "Cate discipline sa se adauge" << noDiscipline;
		srv.addRandomToContract(noDiscipline);
		this->reloadContract();
		});
	QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
		srv.emptyContract();
		this->reloadContract();
		});
	QObject::connect(btnClose, &QPushButton::clicked, this, &ContractGUI::close);


	QObject::connect(btnDrawWindow, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new ContractGUIDraw{ srv.getContract() };
		drawWindow->show();
		});

	QObject::connect(disciplinaList, &QListWidget::itemSelectionChanged, [&]() {
		auto selItms = disciplinaList->selectedItems();
		for (auto item : selItms) {
			qDebug() << item->text();
			item->setBackground(Qt::green); // sets green background
		}

		});




}


void ContractGUI::reloadContract() {
	
	this->disciplinaList->clear();

	const vector<Disciplina>& discipline = srv.getDisciplineContract();
	for (auto& disciplina : discipline) {
		QString currentItem = QString::fromStdString(disciplina.getDenumire() + "\t" + to_string(disciplina.getOre()) + "\t" + disciplina.getTip() + "\t" + disciplina.getCadru());
		this->disciplinaList->addItem(currentItem);
	}
	reloadDynamicButtons();
	
}


void ContractGUI::addToContract() {
	
	try {
		string denumire = editDenumire->text().toStdString();


		editDenumire->clear();



		this->srv.addToContract(denumire);
		this->reloadContract();

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


