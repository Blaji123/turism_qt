//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_UNDO_H
#define TURISM_QT_UNDO_H

#include "../domain/Oferta.h"
#include "../repository/AgentieRepo.h"

class ActiuneUndo{
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo{
private:
    Oferta ofertaToBeRemoved;
    AbstractRepo& repo;
public:
    UndoAdauga(AbstractRepo& repo, const Oferta& of):repo{repo}, ofertaToBeRemoved{of}{}
    void doUndo() override{
        repo.deleteRepo(ofertaToBeRemoved.getDenumire());
    }
};

class UndoSterge : public ActiuneUndo{
private:
    Oferta ofertaToBeAdded;
    AbstractRepo& repo;
public:
    UndoSterge(AbstractRepo& repo, const Oferta& of):repo{repo}, ofertaToBeAdded{of}{}
    void doUndo() override{
        repo.addRepo(ofertaToBeAdded);
    }
};

class UndoModifica : public ActiuneUndo{
private:
    Oferta ofertaToBeModifiedBack;
    AbstractRepo& repo;
public:
    UndoModifica(AbstractRepo& repo, const Oferta& of):repo{repo}, ofertaToBeModifiedBack{of}{}
    void doUndo() override{
        repo.deleteRepo(ofertaToBeModifiedBack.getDenumire());
        repo.addRepo(ofertaToBeModifiedBack);
    }
};

#endif //TURISM_QT_UNDO_H
