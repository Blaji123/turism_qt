//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_AGENTIEREPO_H
#define TURISM_QT_AGENTIEREPO_H

#include "../domain/Oferta.h"
#include "MyList.h"
#include <utility>
#include <vector>
#include <ostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <functional>

using std::vector;
using std::ostream;
using std::string;

class AbstractRepo{
public:
    [[nodiscard]] virtual bool exist(const Oferta& oferta) const =0;
    virtual void addRepo(const Oferta& oferta)=0;
    [[nodiscard]] virtual vector<Oferta> getAll() const=0;
    virtual void deleteRepo(const string& denumire)=0;
    virtual void modifyRepo(const Oferta& oferta)=0;
    [[nodiscard]] virtual long long findByDenumire(const string& denumire) const =0;
    [[nodiscard]] virtual Oferta findRepo(const string& denumire) const=0;
};

// class AgentieRepo pentru repository-ul agentiei
class AgentieRepo : public AbstractRepo{
private:
    vector<Oferta> agentie;
public:
    //constructor implicit pentru clasa
    AgentieRepo() = default;
    //nu permitem copierea obiectelor de tip repo
    AgentieRepo(const AgentieRepo& ot) = delete;
    /**
     * repo function care verifica daca un obiect de tipul oferta exista deja
     * @param oferta - Oferta
     * @return true/false
     */
    [[nodiscard]] bool exist(const Oferta& oferta) const override;
    /**
     * repo function pentru a adauga oferte in repo
     * @param oferta - Oferta
     */
    void addRepo(const Oferta& oferta) override;
    /**
     * repo function pentru a returna toate obiecte de tip oferta din repo
     * @return vector<oferta>
     */
    [[nodiscard]] vector<Oferta> getAll() const override;
    /**
     * repo function pentru a sterge obiectele cu o denumire
     * @param denumire - string
     */
    void deleteRepo(const string& denumire) override;
    /**
     * repo function pentru a modifica destinatia, tipul, pretul obiectului cu aceea denumire
     * @param oferta - Oferta
     */
    void modifyRepo(const Oferta& oferta) override;
    /**
     * repo function pentru a gasi un obiect cu o anumita denumire
     * @param denumire - string
     * @return pozitia pe care a gasit elementul/-1 instead
     */
    [[nodiscard]] long long findByDenumire(const string& denumire) const override;
    /**
     * repo function pentru a gasi un obiect cu o anumita denumire
     * @param denumire - string
     * @return obiectul oferta cu aceea denumire/arunca eroare instead
     */
    [[nodiscard]] Oferta findRepo(const string& denumire) const override;
    virtual ~AgentieRepo() = default;
};

/**
 * clasa RepositoryException pentru a trata exceptiile din repo
 */
class RepositoryException : public std::exception {
    std::string msg;
public:
    explicit RepositoryException(std::string  message) : msg(std::move(message)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return msg.c_str();
    }
};
//metoda pentru a afisa mesajele
ostream& operator<<(ostream& out, const RepositoryException& ex);
// functie pentru teste din repo
void testeRepo();

class AgentieRepoFile : public AgentieRepo{
private:
    void loadFromFile();
    void saveToFile();
    string filename;
public:
    explicit AgentieRepoFile(string n): AgentieRepo(), filename{std::move(n)}{
        loadFromFile();
    }
    void addRepo(const Oferta& of) override{
        AgentieRepo::addRepo(of);
        saveToFile();
    }
    void deleteRepo(const string& denumire) override{
        AgentieRepo::deleteRepo(denumire);
        saveToFile();
    }
    void modifyRepo(const Oferta& of) override{
        AgentieRepo::modifyRepo(of);
        saveToFile();
    }
};

#endif //TURISM_QT_AGENTIEREPO_H
