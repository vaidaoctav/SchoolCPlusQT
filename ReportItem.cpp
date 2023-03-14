#include"ReportItem.h"
string ReportItem::getTip() const {
	return this->tip;
}
int ReportItem::getCounter() const {
	return this->counter;
}
void ReportItem::setTip(string tipnou) {
	this->tip = tipnou;
}
void ReportItem::setCounter(int newcounter) {
	this->counter = newcounter;
}