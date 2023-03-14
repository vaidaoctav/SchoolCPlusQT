#pragma once
#include "UI.h"
#include <iostream>
using namespace std;
void ConsoleUI::printMenu() {
	cout << "Comenzi disponibile:" << endl;
	cout << "1. Adauga disciplina" << endl;
	cout << "2. Afiseaza toate disciplinele" << endl;
	cout << "3. Modifica disciplina" << endl;
	cout << "4. Stergere disciplina" << endl;
	cout << "5. Filtreaza Discipline" << endl;
	cout << "6. Sorteaza Discipline " << endl;
	cout << "7. Meniu Contract " << endl;
	cout << "8. Undo" << endl;
	cout << "9. Exit" << endl;
}
void ConsoleUI::printContractMenu() {
	cout << "MENIU Contract" << endl;
	cout << "1. Adauga disciplina in contract" << endl;
	cout << "2. Adauga discipline random in contract" << endl;
	cout << "3. Goleste contract" << endl;
	cout << "4. Afiseaza contract curent" << endl;
	cout << "5. Inapoi la meniul principal" << endl;
}
void ConsoleUI::uiAdd() {
	string denumire, tip, cadru;
	double ore;
	cout << "Denumirea disciplinei este:";
	getline(cin >> ws, denumire);

	cout << "Numarul de ore pe saptamana este:";
	cin >> ore;

	cout << "Tipul disciplinei este:";
	getline(cin >> ws, tip);

	cout << "Cadrul didactic al disciplinei este:";
	getline(cin >> ws, cadru);


	try {
		srv.addDisciplina(denumire, ore, tip, cadru);
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidationException& ve) {
		cout << "Disciplina nu este valida!" << endl;
		cout << ve.getErrorMessages();
	}

}


void ConsoleUI::printAllDiscipline() {
	vector<Disciplina> allDiscipline = srv.getAllDiscipline();
	if (allDiscipline.size() == 0)
		cout << "Nu exista discipline." << endl;
	else
		for (auto d : allDiscipline) {
			cout << "Denumire: " << d.getDenumire() << " | Ore: " << d.getOre() << " | Tip: " << d.getTip() << " | Cadru: " << d.getCadru() << endl;
		}
}
void ConsoleUI::modificaDisciplina() {
	string newDenumire, newTip, newCadru;
	double newOre;
	cout << "Introduceti numele disciplinei care vreti sa il modificati ";
	cin >> newDenumire;
	cout << "Introduceti noul numar de ore,noul tip si noul cadru: \n";
	cin >> newOre;
	cin >> newTip;
	cin >> newCadru;
	srv.modificaDisciplina(newDenumire, newOre, newTip, newCadru);


}
void ConsoleUI::stergereDisciplina() {
	int nrDisciplina;
	cout << "Introduceti numarul disciplinei pe care doriti sa o stergeti ";
	cin >> nrDisciplina;
	srv.stergereDisciplina(nrDisciplina);
}
void ConsoleUI::filtreazaDiscipline()
{
	int nrOre;
	cout << "Introduceti nr de ore dupa care sa se faca filtrarea: ";
	cin >> nrOre;
	for (auto d : srv.filtreazaDiscipline(nrOre))
		cout << "Denumire: " << d.getDenumire() << " | Ore: " << d.getOre() << " | Tip: " << d.getTip() << " | Cadru: " << d.getCadru() << endl;
}
void ConsoleUI::sorteazaDiscipline()
{
	int cmd;
	cout << "1-nr ore,2-denumire";
	cin >> cmd;
	if (cmd == 1)
		for (auto d : srv.sortareOre())
			cout << "Denumire: " << d.getDenumire() << " | Ore: " << d.getOre() << " | Tip: " << d.getTip() << " | Cadru: " << d.getCadru() << endl;
	else
		if (cmd == 2)
			for (auto d : srv.sortareDenumire())
				cout << "Denumire: " << d.getDenumire() << " | Ore: " << d.getOre() << " | Tip: " << d.getTip() << " | Cadru: " << d.getCadru() << endl;
		else
			cout << "Comanda invalida!";
}
void ConsoleUI::uiAddToContract() {
	string nume;
	cout << "Numele disciplinei este:";
	getline(cin >> ws, nume);

	try {
		srv.addToContract(nume);
		cout << "Disciplina s-a adaugat cu succes la contract." << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidationException& ve) {
		cout << "Disciplina nu este valida!" << endl;
		cout << ve.getErrorMessages();
	}
}
void ConsoleUI::uiAddRandomToContract() {
	int howManyToAdd;
	cout << "Cate discipline sa se adauge in contract?";
	cin >> howManyToAdd;


	try {
		int howManyAdded = srv.addRandomToContract(howManyToAdd);
		cout << "S-au adaugat " << howManyAdded << " discipline in contract." << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
}


void ConsoleUI::uiEmptyContract() {
	srv.emptyContract();
	cout << "S-au sters toate disciplinele din contractul curent." << endl;
}
void ConsoleUI::printContract(const vector<Disciplina>& allDiscipline) {

	if (allDiscipline.size() == 0)
		cout << "Nu exista discipline." << endl;
	else {

		for (auto d : allDiscipline) {
			cout << "Denumire: " << d.getDenumire() << " | Ore: " << d.getOre() << " | Tip: " << d.getTip() << " | Cadru: " << d.getCadru() << endl;
		}
	}
}
void ConsoleUI::addDefaultDiscipline() {
	srv.addDisciplina("chimie", 5, "real", "andrei");
	srv.addDisciplina("matematica", 7, "real", "alex");
	srv.addDisciplina("romana", 4, "uman", "andreea");
	srv.addDisciplina("fizica", 6, "real", "remus");

}
void ConsoleUI::undo()
{
	srv.undo();
}
void ConsoleUI::uiContract() {
	int cmd;
	int runningContract = 1;
	while (runningContract) {
		printContractMenu();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAddToContract();
			break;
		case 2:
			uiAddRandomToContract();
			break;
		case 3:
			uiEmptyContract();
			break;

		case 4:
			//printContract(srv.getContract());
			break;
		case 5:
			runningContract = 0;
			break;
		default:
			break;
		}

	}
}
void ConsoleUI::run() {
	int running = 1;
	int cmd;
	//addDefaultDiscipline();
	while (running) {
		printMenu();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAdd();
			break;
		case 2:
			printAllDiscipline();
			break;
		case 3:
			modificaDisciplina();
			break;
		case 4:
			stergereDisciplina();
			break;
		case 5:
			filtreazaDiscipline();
			break;
		case 6:
			sorteazaDiscipline();
			break;
		case 7:
			uiContract();
			break;
		case 8:
			undo();
			break;
		case 9:
			running = 0;
			break;
		default:
			break;
		}

	}
}