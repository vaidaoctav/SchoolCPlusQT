#include "Contract.h"
using std::shuffle;
void Contract::addDisciplinaToContract(const Disciplina& d) {
	this->contractDiscipline.push_back(d);
}
void Contract::emptyContract() {
	this->contractDiscipline.clear();
}
void Contract::addRandomDisciplina(vector<Disciplina> originalDiscipline, int howMany) {
	shuffle(originalDiscipline.begin(), originalDiscipline.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (contractDiscipline.size() < howMany && originalDiscipline.size() > 0) {
		contractDiscipline.push_back(originalDiscipline.back());
		originalDiscipline.pop_back();
	}
}
const vector<Disciplina>& Contract::getAllDiscipline() {
	return this->contractDiscipline;
}