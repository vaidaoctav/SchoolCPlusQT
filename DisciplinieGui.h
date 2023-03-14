#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "ContractGui.h"
#include "DisciplinaGuiModele.h"
using std::vector;
using std::string;
class DisciplineStoreGUI : public QWidget {
private:

	DisciplinaStore& srv;
	ContractGUI contractWindow{ srv };
	DisciplinaGuiModele modeleWindow{ srv };
	QLabel* lblDenumire = new QLabel{ "Denumire desciplina:" };
	QLabel* lblOre = new QLabel{ "Ore disciplina:" };
	QLabel* lblTip = new QLabel{ "Tip desciplina:" };
	QLabel* lblCadru = new QLabel{ "Cadru disciplina:" };

	QLineEdit* editDenumire;
	QLineEdit* editOre;
	QLineEdit* editTip;
	QLineEdit* editCadru;

	QPushButton* btnAddDisciplina;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSrtOre = new QRadioButton(QString::fromStdString("Ore"));
	QRadioButton* radioSrtDisciplina = new QRadioButton(QString::fromStdString("Disciplina"));
	QPushButton* btnSortDiscipline;
	QLabel* lblFilterCriteria = new QLabel{ "Nr de ore dupa care se filtreaza:" };
	QLineEdit* editFilterOre;
	QPushButton* btnFilterDiscipline;

	QPushButton* btnReloadData;

	QTableWidget* tableDiscipline;
	QPushButton* btnContract;
	QPushButton* btnModel;
	void initializeGUIComponents();

	void connectSignalsSlots();
	void reloadDisciplinaList(vector<Disciplina> songs);
public:
	DisciplineStoreGUI(DisciplinaStore& disciplinaSrv) : srv{ disciplinaSrv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadDisciplinaList(srv.getAllDiscipline());
	}
	void guiAddDisciplina();

};

