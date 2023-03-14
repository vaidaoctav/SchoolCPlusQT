#pragma once
#pragma once

#include "discipline.h"
#include "vector.h"
#include <string>
using std::string;
class ValidationException {
	vector<string> errorMsg;
public:
	ValidationException(vector<string> errorMessages) :errorMsg{ errorMessages } {};

	string getErrorMessages() {
		string fullMsg = "";
		for (const string e : errorMsg) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};
class DisciplinaValidator {

public:
	void valideaza(const Disciplina& d) {
		vector<string> errors;
		if (d.getDenumire().length() < 2)
			errors.push_back("Denumirea trebuie sa aiba cel putin 2 caractere.");
		if (d.getTip().length() < 2)
			errors.push_back("Tipul trebuie sa aiba cel putin 2 caractere.");
		if (d.getCadru().length() < 2)
			errors.push_back("Cadrul trebuie sa aiba cel putin 2 caractere.");
		if (d.getOre() < 1 || d.getOre() > 10)
			errors.push_back("Numarul de ore trebuie sa fie intre 1 si 10");

		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};