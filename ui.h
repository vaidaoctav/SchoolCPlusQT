#pragma once
#include "Service.h"
class ConsoleUI {
private:
	DisciplinaStore& srv;
public:
	ConsoleUI(DisciplinaStore& srv) :srv{ srv } {};
	//ConsoleUI(const ConsoleUI& ot) = delete;
	void printMenu();
	void uiAdd();
	void printAllDiscipline();
	void run();
	void modificaDisciplina();
	void stergereDisciplina();
	void filtreazaDiscipline();
	void sorteazaDiscipline();
	void printContractMenu();
	void printContract(const vector<Disciplina>& allDiscipline);
	void uiEmptyContract();
	void uiAddRandomToContract();
	void uiAddToContract();
	void uiContract();
	void addDefaultDiscipline();
	void undo();
};