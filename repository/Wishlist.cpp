//
// Created by Blajan David on 4/26/2024.
//
#include <algorithm>
#include <random>
#include <cassert>
#include "Wishlist.h"

void Wishlist::clearCart() {
    cart.clear();
}

void Wishlist::addCart(const string& denumire) {
    vector<Oferta> oferte = repo.getAll();
    auto it = std::find_if(oferte.begin(), oferte.end(), [&](const Oferta& of){
        return of.getDenumire() == denumire;
    });
    if(it!=oferte.end()){
        long long pos = std::distance(oferte.begin(), it);
        Oferta& of = oferte.at(pos);
        cart.push_back(of);
    }else{
        throw RepositoryException("item deosnt exist");
    }
}

void Wishlist::fillCart(const int numberOfOferte) {
    vector<Oferta> oferte = repo.getAll();
    vector<Oferta> randomOferte;
    std::shuffle(oferte.begin(), oferte.end(), std::default_random_engine(std::random_device{}()));
    while(cart.size() < numberOfOferte && !oferte.empty()){
        cart.push_back(oferte.back());
        randomOferte.push_back(oferte.back());
        oferte.pop_back();
        if(oferte.empty() && cart.size() < numberOfOferte){
            oferte = randomOferte;
            randomOferte.clear();
            std::shuffle(oferte.begin(), oferte.end(), std::default_random_engine(std::random_device{}()));
        }
    }
}

void Wishlist::exportToHtml(const std::string &filename) {
    std::ofstream out(filename);
    if(!out.is_open()){
        throw RepositoryException("Corrupted file: " + filename);
    }
    out << "<html><body>" << std::endl;
    out << R"(<table border="1" style="width:100% ">)" << std::endl;
    for(const auto& oferta : cart ){
        out << "<tr>" << std::endl;
        out << "<td>" << oferta.getDenumire() << "</td>" << std::endl;
        out << "<td>" << oferta.getDestinatie() << "</td>" << std::endl;
        out << "<td>" << oferta.getTip() << "</td>" << std::endl;
        out << "<td>" << oferta.getPret() << "</td>" << std::endl;
        out << "</tr>" << std::endl;
    }
    out << "</table>" << std::endl;
    out << "</body></html>" << std::endl;
    out.close();
}

void testAdaugaClear(){
    AgentieRepo repo;
    Wishlist wishlist{repo};
    const int pret1 = 534;
    const int pret2 = 634;
    repo.addRepo(Oferta{"abc", "def", "ghi", pret1});
    repo.addRepo(Oferta{"aaa","bbb","ccc",pret2});
    wishlist.addCart("abc");
    assert(wishlist.size() == 1);
    wishlist.addCart("aaa");
    assert(wishlist.size() == 2);
    try{
        wishlist.addCart("gtr");
    }catch(RepositoryException& e){
        assert(true);
    }
    wishlist.clearCart();
    assert(wishlist.size() == 0);
}

void testFillCart(){
    AgentieRepo repo;
    Wishlist wishlist{repo};
    const int pret1 = 534;
    const int pret2 = 634;
    const int pret3 = 321;
    const int numberOfOferte = 7;
    repo.addRepo(Oferta{"abc", "def", "ghi", pret1});
    repo.addRepo(Oferta{"aaa","bbb","ccc",pret2});
    repo.addRepo(Oferta{"gtr","hyth","htr",pret3});
    wishlist.fillCart(numberOfOferte);
    assert(wishlist.size() == 7);
}

void testExportToHtml(){
    AgentieRepo repo;
    Wishlist wishlist{repo};
    const int pret1 = 534;
    const int pret2 = 634;
    const int pret3 = 321;
    repo.addRepo(Oferta{"abc", "def", "ghi", pret1});
    repo.addRepo(Oferta{"aaa","bbb","ccc",pret2});
    repo.addRepo(Oferta{"gtr","hyth","htr",pret3});
    wishlist.addCart("abc");
    wishlist.addCart("aaa");
    wishlist.addCart("gtr");
    wishlist.exportToHtml("export_test.html");
}

void testWishlist(){
    testAdaugaClear();
    testFillCart();
    testExportToHtml();
}