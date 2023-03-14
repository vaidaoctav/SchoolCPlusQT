#pragma once
#include<iostream>
#include<string>
using namespace std;
class ReportItem {
private:
	string tip;
	int counter;
public:
	ReportItem() = default;
	ReportItem(string tip, int counter) :tip{ tip }, counter{ counter }{};
	string getTip() const;
	int getCounter() const;
	void setTip(string newtip);
	void setCounter(int newcounter);
};
