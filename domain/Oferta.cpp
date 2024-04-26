//
// Created by Blajan David on 4/26/2024.
//
#include "Oferta.h"
/**
 * functie pentru a compara denumirea
 * @param of1 - Oferta
 * @param of2 - Oferta
 * @return T/F
 */
bool cmpDenumire(const Oferta& of1, const Oferta& of2){
    return of1.getDenumire() < of2.getDenumire();
}

/**
 * functie pentru a compara destinatie
 * @param of1 - Oferta
 * @param of2 - Oferta
 * @return T/F
 */
bool cmpDestinatie(const Oferta& of1, const Oferta& of2){
    return of1.getDestinatie() < of2.getDestinatie();
}

/**
 * functie pentru a compara denumirea descrescator
 * @param of1 - Oferta
 * @param of2 - Oferta
 * @return T/F
 */
bool cmpDenumireDescrescator(const Oferta& of1, const Oferta& of2){
    return of1.getDenumire() > of2.getDenumire();
}

/**
 * functie pentru a compara destinatia descrescator
 * @param of1 - Oferta
 * @param of2 - Oferta
 * @return T/F
 */
bool cmpDestinatieDescrescator(const Oferta& of1, const Oferta& of2){
    return of1.getDestinatie() > of2.getDestinatie();
}