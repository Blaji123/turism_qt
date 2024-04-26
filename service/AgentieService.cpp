//
// Created by Blajan David on 4/26/2024.
//
#include <cassert>
#include "AgentieService.h"

/**
     * Service function care adauga obiectele de tip Oferta in repo
     * @param denumire - string
     * @param destinatie -string
     * @param tip -string
     * @param pret - int
     */
void AgentieService::addService(const std::string &denumire, const std::string &destinatie, const std::string &tip,
                                int pret) {
    Oferta of{denumire, destinatie, tip, pret};
    OfertaValidator::validate(of);
    repo.addRepo(of);
    undo.push_back(std::make_unique<UndoAdauga>(this->repo, of));
}

/**
     * Service function care sterge obiectele cu aceea denumire
     * @param denumire -string
     */
void AgentieService::deleteService(const std::string &denumire) {
    Oferta of = repo.findRepo(denumire);
    repo.deleteRepo(denumire);
    undo.push_back(std::make_unique<UndoSterge>(this->repo, of));
}

/**
     * Service function care modifica destinatia, tipul, pretul obiectelor care au aceea denumire
     * @param denumire - string
     * @param destinatie - string
     * @param tip - string
     * @param pret - int
     */
void AgentieService::changeService(const std::string &denumire, const std::string &destinatie, const std::string &tip,
                                   int pret) {
    Oferta old_oferta = repo.findRepo(denumire);
    Oferta of{denumire, destinatie, tip, pret};
    OfertaValidator::validate(of);
    repo.modifyRepo(of);
    undo.push_back(std::make_unique<UndoModifica>(this->repo, old_oferta));
}

/**
     * Service function pentru a gasi obiectul cu aceea denumire
     * @param denumire - string
     * @return Oferta
     */
Oferta AgentieService::findService(const std::string &denumire) {
    return repo.findRepo(denumire);
}

/**
     * generic filter function
     * @param fct - functie pentru a vedea in functie de ce comparam
     * @return vector<Oferta>
     */
vector<Oferta> AgentieService::genericFilter(const function<bool(const Oferta &)> &fct) {
    vector<Oferta> rez;
    vector<Oferta> oferte = repo.getAll();
    std::copy_if(oferte.begin(), oferte.end(), std::back_inserter(rez), fct);
    return rez;
}

/**
     * Service function pentru a filtra obiectele care au aceeasi destinatie
     * @param destinatie - string
     * @return vector<Oferta>
     */
vector<Oferta> AgentieService::filterByDestinatie(const std::string &destinatie) {
    return genericFilter([destinatie](const Oferta &of) {
        return of.getDestinatie() == destinatie;
    });
}
vector<Oferta> AgentieService::filterByDenumire(const std::string &denumire) {
    return genericFilter([denumire](const Oferta& of){
        return of.getDenumire() == denumire;
    });
}

/**
     * Service function pentru a filtra obiectele care au pretul intre pretMinim si pretMaxim
     * @param pretMinim - int
     * @param pretMaxim - int
     * @return vector<Oferta>
     */
vector<Oferta> AgentieService::filterByPret(const int pretMinim, const int pretMaxim) {
    return genericFilter([=](const Oferta &of) {
        return of.getPret() >= pretMinim && of.getPret() <= pretMaxim;
    });
}

/**
     * generic sort function
     * @param maiMicF - functie pentru a vedea in functie de ce comparam
     * @return vector<Oferta>
     */
vector<Oferta> AgentieService::genericSort(bool (*maiMicF)(const Oferta &, const Oferta &)) {
    vector<Oferta> sortedArray{repo.getAll()};
    std::sort(sortedArray.begin(), sortedArray.end(), maiMicF);
    return sortedArray;
}

/**
 * Service function to sort by denumire ascending
 * @return vector<Oferta>
 */
vector<Oferta> AgentieService::sortByDenumire() {
    return genericSort(cmpDenumire);
}

/**
 * Service function to sort by denumire non-ascending
 * @return vector<Oferta>
 */
vector<Oferta> AgentieService::sortByDenumireDescrescator() {
    return genericSort(cmpDenumireDescrescator);
}

/**
 * Service function to sort by destinatie ascending
 * @return vector<Oferta>
 */
vector<Oferta> AgentieService::sortByDestinatie() {
    return genericSort(cmpDestinatie);
}

/**
 * Service function to sort by destinatie non-ascending
 * @return vector<Oferta>
 */
vector<Oferta> AgentieService::sortByDestinatieDescrescator() {
    return genericSort(cmpDestinatieDescrescator);
}

/**
 * Service function to sort by tip+pret ascending
 * @return vector<Oferta>
 */
vector<Oferta> AgentieService::sortByTipPret() {
    return genericSort([](const Oferta &of1, const Oferta &of2) {
        if (of1.getTip() == of2.getTip()) {
            return of1.getPret() < of2.getPret();
        }
        return of1.getTip() < of2.getTip();
    });
}

/**
 * Service function to sort by tip+pret non-ascending
 * @return vector<Oferta>
 */
vector<Oferta> AgentieService::sortByTipPretDescrescator() {
    return genericSort([](const Oferta &of1, const Oferta &of2) {
        if (of1.getTip() == of2.getTip()) {
            return of1.getPret() > of2.getPret();
        }
        return of1.getTip() > of2.getTip();
    });
}

void AgentieService::clearWishlist() {
    wishlist.clearCart();
}

void AgentieService::addToWishlist(const std::string &denumire) {
    wishlist.addCart(denumire);
}

void AgentieService::fillWishlist(const int numberOfOferte) {
    wishlist.fillCart(numberOfOferte);
}

void AgentieService::exportWishlistToHtml(const std::string &filename) {
    wishlist.exportToHtml(filename);
}

unsigned long long AgentieService::wishlistSize() {
    return wishlist.size();
}

void AgentieService::serviceUndo() {
    if (undo.empty()) {
        throw RepositoryException("no more undo's to be done");
    }
    undo.back()->doUndo();
    undo.pop_back();
}

std::unordered_map<string, vector<string>> AgentieService::getElementsForDestinatie() {
    vector<Oferta> oferte = repo.getAll();
    std::unordered_map<string, vector<string>> map;
    for (const auto &oferta: oferte) {
        map[oferta.getDestinatie()].push_back(oferta.getDenumire());
    }
    return map;
}

void testAddService() {
    AgentieRepo agentieRepo;
    Wishlist wishlist{agentieRepo};
    AgentieService agentieService{agentieRepo, wishlist};
    const int pret1 = 144;
    const int pret2 = 435;
    agentieService.addService("asd", "gre", "tr", pret1);
    agentieService.addService("gthr", "ght", "hty", pret2);
    assert(agentieService.getAll().size() == 2);
    assert(agentieService.findService("asd").getPret() == 144);
    assert(agentieService.findService("gthr").getPret() == 435);
}

void testDeleteService() {
    AgentieRepo agentieRepo;
    Wishlist wishlist{agentieRepo};
    AgentieService agentieService{agentieRepo, wishlist};
    const int pret1 = 144;
    const int pret2 = 435;
    agentieService.addService("asd", "gre", "tr", pret1);
    agentieService.addService("gthr", "ght", "hty", pret2);
    assert(agentieService.getAll().size() == 2);
    agentieService.deleteService("asd");
    assert(agentieService.getAll().size() == 1);
    agentieService.deleteService("gthr");
    assert(agentieService.getAll().empty());
}

void testChangeService() {
    AgentieRepo agentieRepo;
    Wishlist wishlist{agentieRepo};
    AgentieService agentieService{agentieRepo, wishlist};
    const int pret1 = 144;
    const int pret2 = 435;
    const int pret3 = 123;
    agentieService.addService("asd", "gre", "tr", pret1);
    agentieService.addService("gthr", "ght", "hty", pret2);
    agentieService.changeService("asd", "hyt", "Hy", pret3);
    assert(agentieService.findService("asd").getDestinatie() == "hyt");
    assert(agentieService.findService("asd").getTip() == "Hy");
    assert(agentieService.findService("asd").getPret() == 123);
    assert(agentieService.getAll().size() == 2);

}

void testFiltrare() {
    AgentieRepo agentieRepo;
    Wishlist wishlist{agentieRepo};
    AgentieService agentieService{agentieRepo, wishlist};
    const int pret1 = 144;
    const int pret2 = 435;
    const int pret3 = 123;
    const int pret4 = 342;
    agentieService.addService("asd", "gre", "tr", pret1);
    agentieService.addService("gthr", "gre", "hty", pret2);
    agentieService.addService("hty", "ht", "hyt", pret3);
    agentieService.addService("tyh", "jyu", "hjyu", pret4);
    vector<Oferta> oferte = agentieService.filterByDestinatie("gre");
    assert(oferte.size() == 2);
    assert(oferte[0].getDenumire() == "asd");
    assert(oferte[1].getDenumire() == "gthr");
    const int pretMinim = 400;
    const int pretMaxim = 500;
    vector<Oferta> oferte2 = agentieService.filterByPret(pretMinim, pretMaxim);
    assert(oferte2.size() == 1);
    assert(oferte2[0].getDenumire() == "gthr");
    const int pretMinim1 = 100;
    const int pretMaxim1 = 110;
    vector<Oferta> oferte4 = agentieService.filterByPret(pretMinim1, pretMaxim1); // Range with no offers
    assert(oferte4.empty());

    const int pretMinim2 = 300;
    const int pretMaxim2 = 400;
    vector<Oferta> oferte5 = agentieService.filterByPret(pretMinim2, pretMaxim2); // Range with offers
    assert(!oferte5.empty()); // Ensure some offers are returned within this price range
    assert(oferte5.size() == 1); // Ensure the correct number of offers are returned
    assert(oferte5[0].getDenumire() == "tyh"); // Ensure
}

void testSort() {
    AgentieRepo agentieRepo;
    Wishlist wishlist{agentieRepo};
    AgentieService agentieService{agentieRepo, wishlist};
    const int pret1 = 144;
    const int pret2 = 435;
    const int pret3 = 123;
    const int pret4 = 342;
    agentieService.addService("asd", "gre", "tr", pret1);
    agentieService.addService("gthr", "gre", "hyt", pret2);
    agentieService.addService("hty", "ht", "hyt", pret3);
    agentieService.addService("tyh", "jyu", "hjyu", pret4);
    vector<Oferta> vectorSortat = agentieService.sortByDenumire();
    assert(vectorSortat[0].getDenumire() == "asd");
    assert(vectorSortat[1].getDenumire() == "gthr");
    assert(vectorSortat[2].getDenumire() == "hty");
    assert(vectorSortat[3].getDenumire() == "tyh");
    vectorSortat = agentieService.sortByDenumireDescrescator();
    assert(vectorSortat[0].getDenumire() == "tyh");
    assert(vectorSortat[1].getDenumire() == "hty");
    assert(vectorSortat[2].getDenumire() == "gthr");
    assert(vectorSortat[3].getDenumire() == "asd");
    vectorSortat = agentieService.sortByDestinatie();
    assert(vectorSortat[0].getDenumire() == "asd");
    assert(vectorSortat[1].getDenumire() == "gthr");
    assert(vectorSortat[2].getDenumire() == "hty");
    assert(vectorSortat[3].getDenumire() == "tyh");
    vectorSortat = agentieService.sortByDestinatieDescrescator();
    assert(vectorSortat[0].getDenumire() == "tyh");
    assert(vectorSortat[1].getDenumire() == "hty");
    assert(vectorSortat[2].getDenumire() == "asd");
    assert(vectorSortat[3].getDenumire() == "gthr");
    vectorSortat = agentieService.sortByTipPret();
    assert(vectorSortat[0].getDenumire() == "tyh");
    assert(vectorSortat[1].getDenumire() == "hty");
    assert(vectorSortat[2].getDenumire() == "gthr");
    assert(vectorSortat[3].getDenumire() == "asd");
    vectorSortat = agentieService.sortByTipPretDescrescator();
    assert(vectorSortat[0].getDenumire() == "asd");
    assert(vectorSortat[1].getDenumire() == "gthr");
    assert(vectorSortat[2].getDenumire() == "hty");
    assert(vectorSortat[3].getDenumire() == "tyh");
}

void testUndoAndWishlist() {
    AgentieRepo agentieRepo;
    Wishlist wishlist{agentieRepo};
    AgentieService agentieService{agentieRepo, wishlist};
    const int pret1 = 144;
    const int pret2 = 435;
    const int pret3 = 123;
    const int pret4 = 342;
    const int numberOfOferte = 5;
    agentieService.addService("asd", "gre", "tr", pret1);
    agentieService.addService("gthr", "gre", "hyt", pret2);
    agentieService.addService("hty", "ht", "hyt", pret3);
    agentieService.addService("tyh", "jyu", "hjyu", pret4);
    agentieService.addToWishlist("asd");
    agentieService.addToWishlist("gthr");
    agentieService.addToWishlist("hty");
    assert(agentieService.wishlistSize() == 3);
    agentieService.fillWishlist(numberOfOferte);
    assert(agentieService.wishlistSize() == 5);
    agentieService.exportWishlistToHtml("export_text2.html");
    agentieService.clearWishlist();
    assert(agentieService.wishlistSize() == 0);
    agentieService.serviceUndo();
    assert(agentieRepo.getAll().size() == 3);
    agentieService.deleteService("gthr");
    assert(agentieRepo.getAll().size() == 2);
    agentieService.serviceUndo();
    assert(agentieRepo.getAll().size() == 3);
    agentieService.changeService("asd", "yth", "hyt", pret2);
    vector<Oferta> oferte = agentieRepo.getAll();
    assert(oferte[0].getDestinatie() == "yth");
    agentieService.serviceUndo();
}

void testeService() {
    testAddService();
    testDeleteService();
    testChangeService();
    testFiltrare();
    testUndoAndWishlist();
    testSort();
}