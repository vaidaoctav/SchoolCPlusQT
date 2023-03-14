#pragma once
#include "discipline.h"
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock
#include "Observer.h"
using std::vector;
class Contract : public Observable{
private:
	vector<Disciplina> contractDiscipline;
public:
	Contract() = default;
	void addRandomDisciplina(vector<Disciplina> originaDiscipline, int howMany);
	/*
	* Adauga o melodie in playlist
	* @param s: melodia care se adauga (Song)
	*
	* post: melodia va fi adaugata la playlist
	*/
	void addDisciplinaToContract(const Disciplina& d);
	/*
	* Elimina toate melodiile din playlist
	* post: playlist-ul este gol
	*/
	void emptyContract();
	/*
	* Returneaza un vector care contine toate melodiile din playlist
	*/
	const vector<Disciplina>& getAllDiscipline();
};
