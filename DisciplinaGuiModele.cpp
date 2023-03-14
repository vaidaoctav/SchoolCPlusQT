#include "DisciplinaGuiModele.h"
#include "discipline.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
//#include "MyListModel.h"
#include "MyTableModel.h"
void DisciplinaGuiModele::initGUICmps() {
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	//adaug lista si sub doua butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);

	vl->addWidget(lblCate);

	lstV = new QListView;
	lstV->setUniformItemSizes(true);
	vl->addWidget(lstV);


	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);
	btnSortByOre = new QPushButton("Sort by ore");
	lyBtnsDr->addWidget(btnSortByOre);

	btnSortByDenumire = new QPushButton("Sort by denumire");
	lyBtnsDr->addWidget(btnSortByDenumire);
	vl->addWidget(widBtnDreapta);
	ly->addWidget(widDreapta);

	QWidget* widDreapta2 = new QWidget;
	QVBoxLayout* lyDreapta = new QVBoxLayout;
	widDreapta2->setLayout(lyDreapta);

	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtDenumire = new QLineEdit;
	formLDetalii->addRow(new QLabel("Denumire:"), txtDenumire);
	txtOre = new QLineEdit;
	formLDetalii->addRow(new QLabel("Ore:"), txtOre);
	txtTip = new QLineEdit;
	formLDetalii->addRow(new QLabel("Tip:"), txtTip);
	txtCadru = new QLineEdit;
	formLDetalii->addRow(new QLabel("Cadru:"), txtCadru);

	btnAdd = new QPushButton("Add dicsiplina");
	formLDetalii->addWidget(btnAdd);
	lyDreapta->addWidget(widDetalii);


	ly->addWidget(widDreapta2);

	ly->addWidget(tblV);

}


void DisciplinaGuiModele::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByOre, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortareOre());
		});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByDenumire, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortareDenumire());
		});

	QObject::connect(btnAdd, &QPushButton::clicked, this, &DisciplinaGuiModele::addNewDisciplina);


	//selectia in tabel
	QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tblV->selectionModel()->selectedIndexes().isEmpty()) {
			txtDenumire->setText("");
			txtOre->setText("");
			txtTip->setText("");
			txtCadru->setText("");
			return;
		}
		int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tblV->model()->index(selRow, 0);
		auto cel0Value = tblV->model()->data(cel0Index, Qt::DisplayRole).toString();
		txtDenumire->setText(cel0Value);
		auto cel1Index = tblV->model()->index(selRow, 1);
		auto cel1Value = tblV->model()->data(cel1Index, Qt::DisplayRole).toString();
		txtOre->setText(cel1Value);
		auto cel2Index = tblV->model()->index(selRow, 2);
		auto cel2Value = tblV->model()->data(cel2Index, Qt::DisplayRole).toString();
		txtTip->setText(cel2Value);
		auto cel3Index = tblV->model()->index(selRow, 3);
		auto cel3Value = tblV->model()->data(cel3Index, Qt::DisplayRole).toString();
		txtCadru->setText(cel3Value);
		});
}

void DisciplinaGuiModele::addNewDisciplina() {
	
	ctr.addDisciplina(txtDenumire->text().toStdString(), txtOre->text().toDouble(), txtTip->text().toStdString(),txtCadru->text().toStdString());
		reloadList(ctr.getAllDiscipline());
	

}
void DisciplinaGuiModele::reloadList(std::vector<Disciplina> discipline) {
	lblCate->setText(QString{ "Cate:" } + QString::number(discipline.size()));
	model->setDiscipline(discipline);
}