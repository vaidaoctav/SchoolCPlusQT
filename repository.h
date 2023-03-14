#pragma once
#include "discipline.h"
#include <vector>
#include <string>
using std::vector;
using std::to_string;
/*
Clasa de exceptii specifice Repo
*/
using std::to_string;
class RepoException {
private:
	string errorMsg;
public:
	RepoException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};

class DisciplinaRepository {
private:
	vector<Disciplina> allDiscipline;
public:

	DisciplinaRepository() = default;
	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Repository
	//(in aplicatie avem 1 singur Repo)
	DisciplinaRepository(const DisciplinaRepository& ot) = delete; 


	virtual void store(const Disciplina& s);
	/*
	Returneaza o lista cu toate melodiile
	@return: lista cu melodiile (vector of Song objects)
	*/
	const vector<Disciplina>& getAllDiscipline();

	
	const Disciplina& find(string denumire, double ore, string tip, string cadru);


	bool exists(const Disciplina& s);
	void modifica(string newDenumire, double newOre, string newTip, string newCadru);
	void stergere(Disciplina d1);
	void copy(Disciplina& d1, Disciplina& d2);
	const Disciplina& findByName(string denumire);

};

class DisciplinaRepositoryFile : public DisciplinaRepository {
private:
	string filename;
	/*
	Incarca datele din fisier
	*/
	void loadFromFile();

	void saveToFile();
public:
	DisciplinaRepositoryFile(string fname) :DisciplinaRepository(), filename{ fname } {
		loadFromFile();
	};
	void store(const Disciplina& s) override;
};
void testeRepo();