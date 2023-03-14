#include "repository.h"
#include <assert.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::getline;
using std::stod;
bool DisciplinaRepository::exists(const Disciplina& d) {
	try {
		find(d.getDenumire(), d.getOre(), d.getTip(), d.getCadru());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}
const Disciplina& DisciplinaRepository::find(string denumire, double ore, string tip, string cadru) {
	for (const Disciplina& d : this->allDiscipline) {
		if (d.getDenumire() == denumire && d.getTip() == tip && d.getOre() == ore && d.getCadru() == cadru) {
			return d;
		}
	}
	throw RepoException("Disciplina nu exista");
}
const Disciplina& DisciplinaRepository::findByName(string denumire) {
	for (const Disciplina& d : this->allDiscipline) {
		if (d.getDenumire() == denumire) {
			return d;
		}
	}
	throw RepoException("Disciplina nu exista");
}
void DisciplinaRepository::store(const Disciplina& d) {
	if (exists(d)) {
		throw RepoException("Disciplina cu denumirea " + d.getDenumire() + " si tipul " + d.getTip() + " si numarul de ore " + to_string(d.getOre()) + " si cadrul " + d.getCadru() + " nu exista");
	}
	this->allDiscipline.push_back(d);
}
void DisciplinaRepository::copy(Disciplina& d1, Disciplina& d2)
{
	d1.setCadru(d2.getCadru());
	d1.setOre(d2.getOre());
	d1.setTip(d2.getTip());
	d1.setDenumire(d2.getDenumire());

}
const vector<Disciplina>& DisciplinaRepository::getAllDiscipline() {
	return allDiscipline;
}
void DisciplinaRepository::modifica(string newDenumire, double newOre, string newTip, string newCadru)
{
	bool ok;
	for (int i = 0;i < allDiscipline.size();i++)
		if (allDiscipline[i].getDenumire() == newDenumire)
		{
			ok = true;
			allDiscipline[i].setCadru(newCadru);
			allDiscipline[i].setOre(newOre);
			allDiscipline[i].setTip(newTip);
			allDiscipline[i].setDenumire(newDenumire);
		}
}
void DisciplinaRepository::stergere(Disciplina d1)
{
	int found = 0, index = 0;
	for (Disciplina d : this->allDiscipline)
		if (d.getDenumire() == d1.getDenumire())
		{
			found = 1;
			allDiscipline.erase(allDiscipline.begin() + index);
			break;
		}
		else index++;
	if (found == 0)
		throw RepoException("Disciplina cu numele dat nu exista!\n");
}
void DisciplinaRepositoryFile::loadFromFile() {
	ifstream disciplinaFile(this->filename);
	if (!disciplinaFile.is_open()) {
		throw RepoException("Cannot read from file " + filename);
	}
	string line;
	while (getline(disciplinaFile, line))
	{
		string denumire, tip, cadru;
		double ore;

		stringstream linestream(line);
		string current_item;
		int item_no = 0;

		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0) denumire = current_item;
			if (item_no == 1) ore = stod(current_item);
			if (item_no == 2) tip = current_item;
			if (item_no == 3) cadru = current_item;
			item_no++;
		}
		Disciplina d{ denumire, ore, tip, cadru };

		DisciplinaRepository::store(d);


	}
	disciplinaFile.close();
}

void DisciplinaRepositoryFile::saveToFile() {
	ofstream disciplinaOutput(this->filename);
	if (!disciplinaOutput.is_open())
		throw RepoException("Cannot write to file " + filename);
	for (auto& song : getAllDiscipline()) {
		disciplinaOutput << song.getDenumire() << "," << song.getOre() << ",";
		disciplinaOutput << song.getTip() << "," << song.getCadru() << endl;
	}
	disciplinaOutput.close();
}

void DisciplinaRepositoryFile::store(const Disciplina& s) {

	DisciplinaRepository::store(s);

	saveToFile();

}
void testAddRepo() {
	DisciplinaRepository testRepo;
	Disciplina disciplina1{ "matematica",7,"real","Alexandru" };
	testRepo.store(disciplina1);
	vector<Disciplina> v = testRepo.getAllDiscipline();
	assert(v.size() == 1);

	Disciplina disciplina2{ "matematica",7,"real","Alexandru" };
	try {
		testRepo.store(disciplina2);
	}
	catch (RepoException) {
		assert(true);
	}


}
void testFindRepo() {
	DisciplinaRepository testRepo;

	Disciplina disciplina1{ "matematica",7,"real","Alexandru" };
	Disciplina disciplina2{ "romana",6,"uman","Daniel" };
	Disciplina disciplina3{ "informatica",9,"real","Mihai" };
	testRepo.store(disciplina1);
	testRepo.store(disciplina2);

	assert(testRepo.exists(disciplina1));
	assert(!testRepo.exists(disciplina3));

	auto foundDisciplina = testRepo.find("matematica", 7, "real", "Alexandru");
	assert(foundDisciplina.getDenumire() == "matematica");
	assert(foundDisciplina.getOre() == 7);
	assert(foundDisciplina.getTip() == "real");
	assert(foundDisciplina.getCadru() == "Alexandru");
	try {
		testRepo.find("chimie", 5, "real", "Alexandru");
	}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage() == "Disciplina nu exista");

	}
}

void testeRepo() {
	testAddRepo();
	testFindRepo();
}