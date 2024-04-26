//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_WISHLIST_H
#define TURISM_QT_WISHLIST_H

#include "../domain/Oferta.h"
#include "AgentieRepo.h"
#include "../ui/Observer.h"
#include <fstream>
#include <iostream>
#include <vector>

using std::vector;

class Wishlist : public Observable{
private:
    vector<Oferta> cart;
    AbstractRepo& repo;
public:
    explicit Wishlist(AgentieRepo& repository): repo{repository} {}
    Wishlist(const Wishlist& ws) = delete;
    ~Wishlist() = default;
    void clearCart();
    void addCart(const string& denumire);
    void fillCart(int numberOfOferte);
    void exportToHtml(const string& filename);
    vector<Oferta>& getAll(){
        return cart;
    }
    unsigned long long size(){
        return cart.size();
    }

};

void testWishlist();

#endif //TURISM_QT_WISHLIST_H
