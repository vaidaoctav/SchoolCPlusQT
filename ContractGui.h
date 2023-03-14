#pragma once
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include "Service.h"
#include <QMessageBox>
#include <string>
#include <set>
#include <vector>
#include <QDebug>
#include <QPainter>
#include <cstdlib>
using std::to_string;
using std::set;
using std::vector;

class ContractGUI : public QWidget, public Observer {
private:
	DisciplinaStore& srv;
	QHBoxLayout* lyMain;
	QListWidget* disciplinaList;

	QLabel* lblDenumire;
	QLabel* lblCadru;
	QLineEdit* editDenumire;
	QLineEdit* editCadru;

	QPushButton* btnAdd;
	QPushButton* btnGenerate;
	QPushButton* btnEmpty;
	QPushButton* btnExport;
	QPushButton* btnClose;
	QPushButton* btnLabelWindow;
	QPushButton* btnTableWindow;
	QPushButton* btnDrawWindow;


	QLineEdit* editNoSlider;
	QLabel* lblSlider;
	QSlider* sliderGenerate;

	QWidget* widgetDynamic;
	QVBoxLayout* lyBtnDynamic;
	void initGUI();
	void connectSignalsSlots();

	void reloadContract();
	void addToContract();

	//ar trebui ca aceasta metoda sa fie aici sau in service?
	set<string> getGenres(const vector<Disciplina>& contractDiscipline);
	void reloadDynamicButtons();
	
	void update() override {
		reloadContract();
	}

public:
	ContractGUI(DisciplinaStore& disciplinaStore) : srv{ disciplinaStore } {
		initGUI();
		connectSignalsSlots();
		reloadContract();
	}

};


class ContractGUIDraw :public QWidget, public Observer {
private:
	Contract& contract;
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		int x = 10, y = 10 , w = 10;
		for (auto disciplina : contract.getAllDiscipline()) {
			//p.drawRect(x, y, 10, song.getDurata() * 10);
			///x = rand() % 400 + 1;
			//y = rand() % 400 + 1;
			//qDebug() << x << " " << y;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 732, 720);
			QImage image("sun.jpg");

			p.drawRect(x, y, w, disciplina.getOre() * 10);;
			
			x += 40;

		}
	}

	void update() override {
		repaint();
	};
	~ContractGUIDraw() {
		contract.removeObserver(this);
	}

public:
	ContractGUIDraw(Contract& contract) :contract{contract } {
		contract.addObserver(this);
		update();
	};

};

