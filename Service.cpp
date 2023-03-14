#pragma once
#include "Service.h"
#include <assert.h>
#include <algorithm>
void DisciplinaStore::undo() {
	if (undoActions.empty()) {
		throw RepoException("Nu mai sunt operatii\n");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();

}
void DisciplinaStore::addDisciplina(string denumire, double ore, string tip, string cadru) {
	Disciplina d1{ denumire,ore,tip,cadru };
	val.valideaza(d1);
	repo.store(d1);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, d1));
}
void DisciplinaStore::modificaDisciplina(string newDenumire, double newOre, string newTip, string newCadru)
{
	Disciplina d0 = repo.findByName(newDenumire);
	Disciplina d1{ newDenumire,newOre,newTip,newCadru };
	val.valideaza(d1);
	repo.modifica(newDenumire, newOre, newTip, newCadru);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, d0));
}
void DisciplinaStore::stergereDisciplina(int nrDisciplina)
{
	Disciplina d1;
	vector<Disciplina> v = getAllDiscipline();
	d1.setCadru(v[nrDisciplina].getCadru());
	d1.setDenumire(v[nrDisciplina].getDenumire());
	d1.setOre(v[nrDisciplina].getOre());
	d1.setTip(v[nrDisciplina].getTip());
	repo.stergere(d1);

	undoActions.push_back(std::make_unique<UndoSterge>(repo, d1));
}
vector<Disciplina> DisciplinaStore::filtreazaDiscipline(int nrOre)
{
	const vector<Disciplina>& allDiscipline = getAllDiscipline();
	vector<Disciplina>disciplineFiltrate;
	std::copy_if(allDiscipline.begin(), allDiscipline.end(), back_inserter(disciplineFiltrate),
		[=](const Disciplina& m) {
			return m.getOre() == nrOre;
		});
	return disciplineFiltrate;

}
vector<Disciplina> DisciplinaStore::sortareOre()
{
	vector<Disciplina>sortedCopy{ repo.getAllDiscipline() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpOre);
	return sortedCopy;
}
vector<Disciplina> DisciplinaStore::sortareDenumire()
{
	vector<Disciplina>sortedCopy{ repo.getAllDiscipline() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpDenumire);
	return sortedCopy;
}
void DisciplinaStore::addToContract(string nume) {

	const auto& disciplina = repo.findByName(nume);
	contractCurent.addDisciplinaToContract(disciplina);

}
int DisciplinaStore::addRandomToContract(int howMany) {
	contractCurent.addRandomDisciplina(this->getAllDiscipline(), howMany);
	return contractCurent.getAllDiscipline().size();
}
void DisciplinaStore::emptyContract() {
	contractCurent.emptyContract();
}
const vector<Disciplina>& DisciplinaStore::getDisciplineContract() {
	return contractCurent.getAllDiscipline();
}
void testFiltreazaDiscipline()
{
	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	DisciplinaStore testService{ testRepo,testVal };

	testService.addDisciplina("matematica", 6, "real", "Alexandru");
	testService.addDisciplina("romana", 6, "uman", "Daniel");
	testService.addDisciplina("informatica", 9, "real", "Mihai");
	vector<Disciplina>v = testService.filtreazaDiscipline(6);
	assert(v.size() == 2);
}
void testSortareDiscipline()
{
	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	DisciplinaStore testService{ testRepo,testVal };

	testService.addDisciplina("matematica", 8, "real", "Alexandru");
	testService.addDisciplina("romana", 6, "uman", "Daniel");
	testService.addDisciplina("informatica", 9, "real", "Mihai");
	vector<Disciplina>v = testService.sortareOre();
	Disciplina disciplina1{ "romana", 6, "uman", "Daniel" };
	assert(v[0].getCadru() == disciplina1.getCadru());
	assert(v[0].getOre() == disciplina1.getOre());
	assert(v[0].getTip() == disciplina1.getTip());
	assert(v[0].getDenumire() == disciplina1.getDenumire());
	vector<Disciplina>v1 = testService.sortareDenumire();
	Disciplina disciplina2{ "informatica", 9, "real", "Mihai" };
	assert(v1[0].getCadru() == disciplina2.getCadru());
	assert(v1[0].getOre() == disciplina2.getOre());
	assert(v1[0].getTip() == disciplina2.getTip());
	assert(v1[0].getDenumire() == disciplina2.getDenumire());

}
void testAddService() {
	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	DisciplinaStore testService{ testRepo,testVal };

	testService.addDisciplina("matematica", 7, "real", "Alexandru");
	testService.addDisciplina("romana", 6, "uman", "Daniel");
	testService.addDisciplina("informatica", 9, "real", "Mihai");
	vector<Disciplina>v = testService.getAllDiscipline();
	assert(v.size() == 3);
	try {
		testService.addDisciplina("matematica", 7, "real", "Alexandru");
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		testService.addDisciplina("matematica", 0, "real", "Alexandru");
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		testService.addDisciplina("", 7, "real", "Alexandru");
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Denumirea trebuie sa aiba cel putin 2 caractere.\n");
	}


	try {
		testService.addDisciplina("matematica", 7, "", "Alexandru");
	}
	catch (ValidationException&) {
		assert(true);
	}


	try {
		testService.addDisciplina("matematica", 7, "real", "");
	}
	catch (ValidationException&) {
		assert(true);
	}


}
void testModificaStergeService()
{
	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	DisciplinaStore testService{ testRepo,testVal };
	testService.addDisciplina("matematica", 7, "real", "Alexandru");
	testService.addDisciplina("romana", 6, "uman", "Daniel");
	testService.modificaDisciplina("matematica", 3, "uman", "Andreea");
	const Disciplina& disciplina1{ "matematica", 3, "uman", "Andreea" };
	vector<Disciplina>v = testService.getAllDiscipline();
	assert(testRepo.exists(disciplina1));
	assert(v.size() == 2);
	testService.stergereDisciplina(0);
	assert(testService.getAllDiscipline().size() == 1);

}
void testeService()
{
	testModificaStergeService();
	testAddService();
	testFiltreazaDiscipline();
	testSortareDiscipline();
}
//filtrare nr ore si cadru didactic
//sortare denumire,nr ore,cadru+tip 