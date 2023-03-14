#pragma once
#include "repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Disciplina addedDisciplina;
	DisciplinaRepository& repo;
public:
	UndoAdauga(DisciplinaRepository& repo, const Disciplina& d) : repo{ repo }, addedDisciplina{ d }{}
	void doUndo() override {
		repo.stergere(addedDisciplina);
	}
};
class UndoSterge : public ActiuneUndo {
private:
	Disciplina deletedDisciplina;
	DisciplinaRepository& repo;
public:
	UndoSterge(DisciplinaRepository& repo, const Disciplina& d) : repo{ repo }, deletedDisciplina{ d }{}
	void doUndo() override {
		repo.store(deletedDisciplina);
	}
};
class UndoModifica : public ActiuneUndo {
private:
	Disciplina modifiedDisciplina;
	DisciplinaRepository& repo;
public:
	UndoModifica(DisciplinaRepository& repo, Disciplina& d) : repo{ repo }, modifiedDisciplina{ d }{}
	void doUndo() override {
		repo.modifica(modifiedDisciplina.getDenumire(), modifiedDisciplina.getOre(), modifiedDisciplina.getTip(), modifiedDisciplina.getCadru());
	}
};