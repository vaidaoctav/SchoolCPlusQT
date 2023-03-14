#include "discipline.h"
#include <assert.h>
string Disciplina::getDenumire() const {
	return this->denumire;

}
string Disciplina::getTip() const {
	return this->tip;
}
string Disciplina::getCadru() const {
	return this->cadru;
}
double Disciplina::getOre() const {
	return this->ore;
}
void Disciplina::setDenumire(string newDenumire) {
	this->denumire = newDenumire;

}
void Disciplina::setTip(string newTip) {
	this->tip = newTip;
}
void Disciplina::setCadru(string newCadru) {
	this->cadru = newCadru;
}
void Disciplina::setOre(double newOre) {
	this->ore = newOre;
}
bool cmpOre(const Disciplina& d1, const Disciplina& d2)
{
	return d1.getOre() < d2.getOre();
}
bool cmpDenumire(const Disciplina& d1, const Disciplina& d2)
{
	return d1.getDenumire() < d2.getDenumire();
}
void testGetSet()
{
	Disciplina disciplina1{ "matematica",7,"real","Alexandru" };
	assert(disciplina1.getDenumire() == "matematica");
	assert(disciplina1.getOre() == 7);
	assert(disciplina1.getTip() == "real");
	assert(disciplina1.getCadru() == "Alexandru");
	disciplina1.setDenumire("romana");
	disciplina1.setOre(6);
	disciplina1.setTip("uman");
	disciplina1.setCadru("Daniel");
	assert(disciplina1.getDenumire() == "romana");
	assert(disciplina1.getOre() == 6);
	assert(disciplina1.getTip() == "uman");
	assert(disciplina1.getCadru() == "Daniel");

}
void TesteDomain()
{
	testGetSet();
}
