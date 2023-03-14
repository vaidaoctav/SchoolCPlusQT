#pragma once
#include "repository.h"
#include "validator.h"
#include "Contract.h"
#include "ReportItem.h"
#include <unordered_map>
#include <functional>
#include "Undo.h"
using std::function;
class DisciplinaStore {
private:
	DisciplinaRepository& repo;
	DisciplinaValidator& val;
	vector<unique_ptr<ActiuneUndo>> undoActions;

	Contract contractCurent;
public:
	DisciplinaStore(DisciplinaRepository& disciplinaRepo, DisciplinaValidator& val) :repo{ disciplinaRepo }, val{ val }{};

	DisciplinaStore(const DisciplinaStore& ot) = delete;
	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Service
	//(in aplicatie avem 1 singur Service)
	//DisciplinaStore(const DisciplinaStore& ot) =delete;





	void addDisciplina(string denumire, double ore, string tip, string cadru);

	void modificaDisciplina(string newDenumire, double newOre, string newTip, string newCadru);
	void stergereDisciplina(int nrDisciplina);
	const vector<Disciplina>& getAllDiscipline() {
		return this->repo.getAllDiscipline();
	}
	vector<Disciplina> filtreazaDiscipline(int nrOre);
	vector<Disciplina> sortareOre();
	vector<Disciplina> sortareDenumire();
	void addToContract(string denumire);
	const vector<Disciplina>& getDisciplineContract();
	void golesteContract();
	int addRandomToContract(int howMany);
	unordered_map<string, ReportItem> Report();
	void emptyContract();
	Contract& getContract() {
		return this->contractCurent;
	}
	void undo();
};
void testAddService();
void testModificaStergeService();
void testeService();
void testFiltreazaDiscipline();
void testSortareDiscipline();