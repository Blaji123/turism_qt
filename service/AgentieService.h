//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_AGENTIESERVICE_H
#define TURISM_QT_AGENTIESERVICE_H

#include "../repository/AgentieRepo.h"
#include "../domain/validator.h"
#include "../repository/Wishlist.h"
#include "../undo/Undo.h"
#include <functional>
#include <vector>
#include <iterator>
#include <memory>

using std::function;
using std::unique_ptr;

// class AgentieService pentru serviceul agentiei
class AgentieService{
private:
    AbstractRepo& repo;
    Wishlist& wishlist;
    vector<unique_ptr<ActiuneUndo>> undo;
    /**
     * generic filter function
     * @param fct - functie pentru a vedea in functie de ce comparam
     * @return vector<Oferta>
     */
    vector<Oferta> genericFilter(const function<bool(const Oferta&)>& fct);
    /**
     * generic sort function
     * @param maiMicF - functie pentru a vedea in functie de ce comparam
     * @return vector<Oferta>
     */
    vector<Oferta> genericSort(bool (*maiMicF)(const Oferta&, const Oferta&));
public:
    //constructor implicit pentru clasa
    AgentieService(AbstractRepo &repository, Wishlist &wishlist)
            : repo{repository}, wishlist(wishlist) {}
    //nu permitem copierea obiectelor de tip service
    AgentieService(const AgentieService& ot) = delete;
    ~AgentieService() = default;

    /**
     * repo function pentru a returna toate obiecte de tip oferta din repo
     * @return vector<oferta>
     */
    vector<Oferta> getAll(){
        return repo.getAll();
    }
    /**
     * Service function care adauga obiectele de tip Oferta in repo
     * @param denumire - string
     * @param destinatie -string
     * @param tip -string
     * @param pret - int
     */
    void addService(const string& denumire, const string& destinatie, const string& tip, int pret);
    /**
     * Service function care sterge obiectele cu aceea denumire
     * @param denumire -string
     */
    void deleteService(const string& denumire);
    /**
     * Service function care modifica destinatia, tipul, pretul obiectelor care au aceea denumire
     * @param denumire - string
     * @param destinatie - string
     * @param tip - string
     * @param pret - int
     */
    void changeService(const string& denumire, const string& destinatie, const string& tip,int pret);
    /**
     * Service function pentru a gasi obiectul cu aceea denumire
     * @param denumire - string
     * @return Oferta
     */
    Oferta findService(const string& denumire);
    /**
     * Service function pentru a filtra obiectele care au aceeasi destinatie
     * @param destinatie - string
     * @return vector<Oferta>
     */
    vector<Oferta> filterByDestinatie(const string& destinatie);
    /**
     * Service function pentru a filtra obiectele care au pretul intre pretMinim si pretMaxim
     * @param pretMinim - int
     * @param pretMaxim - int
     * @return vector<Oferta>
     */
    vector<Oferta> filterByPret(int pretMinim, int pretMaxim);
    vector<Oferta> filterByDenumire(const string& denumire);
    /**
     * Service function to sort by denumire ascending
     * @return vector<Oferta>
     */
    vector<Oferta> sortByDenumire();
    /**
     * Service function to sort by destinatie ascending
     * @return vector<Oferta>
     */
    vector<Oferta> sortByDestinatie();
    /**
     * Service function to sort by tip+pret ascending
     * @return vector<Oferta>
     */
    vector<Oferta> sortByTipPret();
    /**
     * Service function to sort by denumire non-ascending
     * @return vector<Oferta>
     */
    vector<Oferta> sortByDenumireDescrescator();
    /**
     * Service function to sort by destinatie non-ascending
     * @return vector<Oferta>
     */
    vector<Oferta> sortByDestinatieDescrescator();
    /**
     * Service function to sort by tip+pret non-ascending
     * @return vector<Oferta>
     */
    vector<Oferta> sortByTipPretDescrescator();
    void clearWishlist();
    void addToWishlist(const string& denumire);
    void fillWishlist(int numberOfOferte);
    void exportWishlistToHtml(const string& filename);
    unsigned long long wishlistSize();
    void serviceUndo();
    std::unordered_map<string, vector<string>> getElementsForDestinatie();
};
//functie pentru teste din service
void testeService();


#endif //TURISM_QT_AGENTIESERVICE_H
