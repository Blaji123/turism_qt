//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_CONSOLE_H
#define TURISM_QT_CONSOLE_H

#include "../service/AgentieService.h"
#include "../repository/Wishlist.h"

class Console{
private:
    AgentieService& service;
    // ui function pentru a adauga
    void adaugaUI();
    // ui function pentru a sterge
    void deleteUi();
    // ui function pentru a modifica
    void changeUI();
    // ui function pentru a cauta
    void findUI();
    void adaugaWishlistUi();
    void fillWishlistUi();
    void exportWishlistToHtmlUi();
    void getElementsByDestinatieUi();
    // ui function pentru a tipari
    static void tipareste(const vector<Oferta>& oferte);
public:
    // constructor implicit pentru clasa
    explicit Console(AgentieService& serv):service{serv}{}
    Console(const Console& ot) = delete;
    //function pentru a incepe aplicatia
    void start();
};

#endif //TURISM_QT_CONSOLE_H
