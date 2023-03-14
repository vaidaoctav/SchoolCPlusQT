#pragma once
#include <QAbstractTableModel>
#include "discipline.h"
#include <vector>
#include <qdebug.h>
#include <QBrush>
class MyTableModel :public QAbstractTableModel {
	std::vector<Disciplina> discipline;
public:
	MyTableModel(const std::vector<Disciplina>& discipline) :discipline{ discipline } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return discipline.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::ForegroundRole) {
			Disciplina p = discipline[index.row()];
			if (p.getOre() > 0) {
				return QBrush{ Qt::red };
			}
		}
		if (role == Qt::DisplayRole) {

			Disciplina p = discipline[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getDenumire());
			}
			else if (index.column() == 1) {
				return QString::number(p.getOre());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.getTip());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(p.getCadru());
			}
		}

		return QVariant{};
	}

	void setDiscipline(const std::vector<Disciplina>& discipline) {
		this->discipline = discipline;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};