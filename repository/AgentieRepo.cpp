//
// Created by Blajan David on 4/26/2024.
//
#include "AgentieRepo.h"
#include <string>
#include <cassert>
#include <sstream>
#include <algorithm>

using std::string;

/**
     * repo function care verifica daca un obiect de tipul oferta exista deja
     * @param oferta - Oferta
     * @return true/false
     */
bool AgentieRepo::exist(const Oferta &oferta) const {
    return std::any_of(agentie.begin(), agentie.end(), [&](const Oferta& of){
        return of.getDenumire() == oferta.getDenumire();
    });
}

/**
    * repo function pentru a gasi un obiect cu o anumita denumire
    * @param denumire - string
    * @return pozitia pe care a gasit elementul/-1 instead
    */
long long AgentieRepo::findByDenumire(const string &denumire) const {
    auto it = std::find_if(agentie.begin(), agentie.end(),[&](const Oferta& of){
        return of.getDenumire() == denumire;
    });
    if (it != agentie.end()){
        return std::distance(agentie.begin(), it);
    }
    return -1;
}

/**
     * repo function pentru a gasi un obiect cu o anumita denumire
     * @param denumire - string
     * @return obiectul oferta cu aceea denumire/arunca eroare instead
     */
Oferta AgentieRepo::findRepo(const string &denumire) const {
    auto it = std::find_if(agentie.begin(), agentie.end(), [&](const Oferta& of){
        return of.getDenumire() == denumire;
    });
    if(it!=agentie.end()){
        return *it;
    }
    throw RepositoryException("Nu exista oferta cu denumire: " + denumire);
}

/**
     * repo function pentru a adauga oferte in repo
     * @param oferta - Oferta
     */
void AgentieRepo::addRepo(const Oferta &oferta) {
    if(exist(oferta)){
        throw RepositoryException("item already exists with denumire : " + oferta.getDenumire());
    }
    agentie.push_back(oferta);
}

/**
     * repo function pentru a returna toate obiecte de tip oferta din repo
     * @return vector<oferta>
     */
vector<Oferta> AgentieRepo::getAll() const{
    return agentie;
}

/**
     * repo function pentru a sterge obiectele cu o denumire
     * @param denumire - string
     */
void AgentieRepo::deleteRepo(const string& denumire) {
    const Oferta& of = findRepo(denumire);
    auto res= std::remove(agentie.begin(), agentie.end(), of);
    agentie.erase(res);
}

/**
     * repo function pentru a modifica destinatia, tipul, pretul obiectului cu aceea denumire
     * @param oferta - Oferta
     */
void AgentieRepo::modifyRepo(const Oferta &oferta) {
    if(findByDenumire(oferta.getDenumire())==-1){
        throw RepositoryException("item doesnt exist");
    }
    const long long pos = findByDenumire(oferta.getDenumire());
    agentie.at(pos) = oferta;
}

//metoda pentru a afisa mesajele
ostream& operator<<(ostream& out,const RepositoryException& ex){
    out << ex.what();
    return out;
}

void AgentieRepoFile::loadFromFile() {
    std::ifstream in(filename);
    if(!in.is_open()){
        throw RepositoryException("Unable to open file: " + filename);
    }
    while(!in.eof()){
        string denumire;
        in >> denumire;
        string destinatie;
        in >> destinatie;
        string tip;
        in >> tip;
        int pret = 0;
        in >> pret;
        if (denumire.empty()) {
            break;
        }
        Oferta of{denumire, destinatie, tip, pret};
        AgentieRepo::addRepo(of);
    }
    in.close();
}

void AgentieRepoFile::saveToFile() {
    std::ofstream out(filename);
    if(!out.is_open()){
        throw RepositoryException("Unable to open file:" + filename);
    }
    for(const auto& of : AgentieRepo::getAll()){
        out<<of.getDenumire()<<" ";
        out<<of.getDestinatie()<<" ";
        out<<of.getTip()<<" ";
        out<<of.getPret()<<" ";
        out<<std::endl;
    }
    out.close();
}

//functii de teste
void testAdaugaRepo(){
    AgentieRepo repo;
    const int pret1 = 534;
    const int pret2 = 634;
    const int pret3 = 252;
    repo.addRepo(Oferta{"abc", "def", "ghi", pret1});
    assert(repo.getAll().size() == 1);
    assert(repo.findRepo("abc").getDestinatie() == "def");
    assert(repo.findRepo("abc").getPret() == 534);
    repo.addRepo(Oferta{"aaa","bbb","ccc",pret2});
    assert(repo.getAll().size() == 2);
    assert(repo.findRepo("aaa").getDestinatie() == "bbb");
    assert(repo.findRepo("aaa").getPret() == 634);
    try{
        repo.addRepo(Oferta{"abc","s","s",pret3});
    }catch(const RepositoryException&){
        assert(true);
    }

    try{
        assert(repo.findRepo("htr").getDenumire().empty());
    }catch(const RepositoryException& e){
        std::stringstream os;
        os << e;
        assert(os.str().find("exista")>=0);
    }
}

void testDeleteRepo(){
    AgentieRepo repo;
    const int pret1 = 534;
    const int pret2 = 634;
    repo.addRepo(Oferta{"abc", "def", "ghi", pret1});
    repo.addRepo(Oferta{"aaa","bbb","ccc",pret2});
    assert(repo.getAll().size() == 2);
    repo.deleteRepo("abc");
    assert(repo.findRepo("aaa").getDestinatie() == "bbb");
    assert(repo.getAll().size()==1);
    try {
        repo.deleteRepo("gtr");
    }catch(RepositoryException&){
        assert(true);
    }
}

void testModifyRepo(){
    AgentieRepo repo;
    const int pret1 = 534;
    const int pret2 = 634;
    const int pret3 = 13;
    const int pret4 = 431;
    repo.addRepo(Oferta{"abc", "def", "ghi", pret1});
    repo.addRepo(Oferta{"aaa","bbb","ccc",pret2});
    repo.modifyRepo(Oferta{"abc", "gtr","ht",pret3});
    assert(repo.findRepo("abc").getDestinatie() == "gtr");
    assert(repo.findRepo("abc").getTip() == "ht");
    assert(repo.findRepo("abc").getPret()==13);
    try{
        repo.modifyRepo(Oferta{"gre","gre","gtr",pret4});
    }catch (RepositoryException&){
        assert(true);
    }
}

void testeRepo(){
    testAdaugaRepo();
    testDeleteRepo();
    testModifyRepo();
}