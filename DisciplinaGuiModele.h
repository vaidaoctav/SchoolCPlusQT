#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtablewidget.h>
#include "Service.h"
#include "discipline.h"
#include <vector>
#include "MyTableModel.h"

class DisciplinaGuiModele : public QWidget {
private:
	DisciplinaStore& ctr;
	MyTableModel* model;
	QLabel* lblCate = new QLabel{ "Cate:" };
	QListView* lstV;

	QTableView* tblV = new QTableView;

	QPushButton* btnSortByOre;
	QPushButton* btnSortByDenumire;

	QLineEdit* txtDenumire;
	QLineEdit* txtOre;
	QLineEdit* txtTip;
	QLineEdit* txtCadru;
	QPushButton* btnAdd;


	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(std::vector<Disciplina> discipline);
	void addNewDisciplina();
public:
	DisciplinaGuiModele(DisciplinaStore& ctr) :ctr{ ctr } {
		initGUICmps();
		model = new MyTableModel{ ctr.getAllDiscipline() };
		lstV->setModel(model);
		tblV->setModel(model);
		connectSignalsSlots();
	}

};