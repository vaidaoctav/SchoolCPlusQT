#pragma once
#include<string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
class Disciplina {
private:
	string denumire;
	double ore;
	string tip;
	string cadru;

public:
	Disciplina() = default;
	Disciplina(string denumire, double ore, string tip, string cadru) : denumire{ denumire }, ore{ ore }, tip{ tip }, cadru{ cadru }{};
	string getDenumire() const;
	string getTip() const;
	string getCadru() const;
	double getOre() const;
	void setDenumire(string newDenumire);
	void setOre(double newOre);
	void setTip(string newTip);
	void setCadru(string newCadru);
	Disciplina(const Disciplina& ot) :denumire{ ot.denumire }, ore{ ot.ore }, tip{ ot.tip }, cadru{ ot.cadru } {
		//cout << "[Disciplina] Copy constructor called." << endl;
	}
};
bool cmpOre(const Disciplina& d1, const Disciplina& d2);
bool cmpDenumire(const Disciplina& d1, const Disciplina& d2);
void TesteDomain();
