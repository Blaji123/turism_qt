//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_OFERTA_H
#define TURISM_QT_OFERTA_H

#include <string>
#include <utility>
#include <iostream>

using std::string;

//class Oferta cu atributele denumire, destinatie, tip, pret
class Oferta{
private:
    string denumire;
    string destinatie;
    string tip;
    int pret;
public:
    /**
     * constructor pentru Oferta
     * @param den - string
     * @param des -string
     * @param t -string
     * @param p -int
     */
    Oferta()=default;
    Oferta(string  den, string  des, string  t, const int p):
            denumire{std::move(den)}, destinatie{std::move(des)}, tip{std::move(t)}, pret{p}{}

    Oferta(const Oferta& ot) = default;

    bool operator==(const Oferta& ot){ return ot.denumire == denumire && ot.destinatie == destinatie && ot.tip == tip && ot.pret == pret;}

    // getter pentru denumire
    [[nodiscard]] string getDenumire() const{
        return denumire;
    }

    //getter pentru destinatie
    [[nodiscard]] string getDestinatie() const{
        return destinatie;
    }

    //getter pentru tip
    [[nodiscard]] string getTip() const{
        return tip;
    }

    //getter pentru pret
    [[nodiscard]] int getPret() const{
        return pret;
    }
};

/**
 * functie pentru a compara denumirea
 * @param of1 - Oferta
 * @param of2 - Oferta
 * @return T/F
 */
bool cmpDenumire(const Oferta& of1, const Oferta& of2 );

/**
 * functie pentru a compara destinatie
 * @param of1 - Oferta
 * @param of2 - Oferta
 * @return T/F
 */
bool cmpDestinatie(const Oferta& of, const Oferta& of2);

/**
 * functie pentru a compara denumirea descrescator
 * @param of1 - Oferta
 * @param of2 - Oferta
 * @return T/F
 */
bool cmpDenumireDescrescator(const Oferta& of1, const Oferta& of2);

/**
 * functie pentru a compara destinatia descrescator
 * @param of1 - Oferta
 * @param of2 - Oferta
 * @return T/F
 */
bool cmpDestinatieDescrescator(const Oferta& of1, const Oferta& of2);

#endif //TURISM_QT_OFERTA_H
