//
// Created by Blajan David on 4/26/2024.
//
#include "console.h"
#include <iostream>

using std::cout;
using std::cin;

// ui function pentru a tipari
void Console::tipareste(const vector<Oferta>& oferte){
    cout<<"Oferte:\n";
    for(const auto & it : oferte){
        cout<<" "<<it.getDenumire()<<" "<<it.getDestinatie()<<" "<<it.getTip()<<" "<<it.getPret()<<"\n";
    }
}
// ui function pentru a adauga
void Console::adaugaUI() {
    try {
        string denumire, destinatie, tip;
        int pret = 0;
        cout << "Dati denumirea:";
        cin >> denumire;
        cout << "Dati destinatia:";
        cin >> destinatie;
        cout << "Dati tipul:";
        cin >> tip;
        cout << "Dati pretul:";
        cin >> pret;
        service.addService(denumire, destinatie, tip, pret);
        cout << "Adaugat cu succes\n";
    }catch (RepositoryException& e){
        cout<<e.what()<<" ";
    }catch (ValidatorException& e){
        cout<<e.what()<<" ";
    }
}

// ui function pentru a sterge
void Console::deleteUi() {
    try {
        string denumire;
        cout << "Dati denumirea:";
        cin >> denumire;
        service.deleteService(denumire);
        cout << "Sters cu succes\n";
    }catch(RepositoryException& e){
        cout<<e.what()<<" ";
    }
}

// ui function pentru a modifica
void Console::changeUI() {
    try {
        string denumire, destinatie, tip;
        int pret = 0;
        cout << "Dati denumirea ofertei care trebuie schimbate:";
        cin >> denumire;
        cout << "Dati destinatia:";
        cin >> destinatie;
        cout << "Dati tipul:";
        cin >> tip;
        cout << "Dati pretul:";
        cin >> pret;
        service.changeService(denumire, destinatie, tip, pret);
        cout << "Modificat cu succes\n";
    }catch (RepositoryException& e){
        cout<<e.what()<<" ";
    }catch (ValidatorException& e){
        cout<<e.what()<<" ";
    }
}

// ui function pentru a cauta
void Console::findUI() {
    try {
        string denumire;
        cout << "Dati denumirea: ";
        cin >> denumire;
        Oferta of = service.findService(denumire);
        cout << "Oferta este: \n";
        cout << of.getDenumire() << " " << of.getDestinatie() << " " << of.getTip() << " " << of.getPret() << "\n";
    }catch (RepositoryException& e){
        cout<<e.what()<<" ";
    }
}

void Console::adaugaWishlistUi() {
    try{
        string denumire;
        cout<<"Dati denumirea: ";
        cin>>denumire;
        service.addToWishlist(denumire);
        cout<<service.wishlistSize()<<"\n";
    }catch(RepositoryException& e){
        cout<<e.what()<<" ";
    }
}

void Console::fillWishlistUi() {
    int numberOfOferte = 0;
    cout<<"Dati numarul de oferte:";
    cin>>numberOfOferte;
    service.fillWishlist(numberOfOferte);
    cout<<service.wishlistSize()<<"\n";

}

void Console::exportWishlistToHtmlUi() {
    try{
        string filename;
        cout<<"Dati numele fisierului: ";
        cin>>filename;
        service.exportWishlistToHtml(filename);
        cout<<service.wishlistSize()<<"\n";
    }catch (RepositoryException& e){
        cout<<e.what()<<" ";
    }
}

void Console::getElementsByDestinatieUi() {
    std::unordered_map<string, vector<string>> rez = service.getElementsForDestinatie();
    for (auto &it: rez) {
        cout << it.first << ":";
        for (auto &oferte: it.second)
            cout << oferte << " ";
        cout<<std::endl;
    }
}
//function pentru a incepe aplicatia
void Console::start() {
    while(true){
        cout<<"Meniu\n";
        cout<<"0. Exit\n"
              "1. Tipareste ofertele\n"
              "2. Adauga oferta\n"
              "3. Sterge oferta\n"
              "4. Modifica oferta\n"
              "5. Cautare oferta\n"
              "6. Filtrare oferta cu destinatie\n"
              "7. Filtrare oferta cu pret\n"
              "8. Sortare dupa denumire\n"
              "9. Sortare dupa destinatie\n"
              "10. Sortare dupa tip+pret\n"
              "11. Clear cart\n"
              "12. Add to cart\n"
              "13. Fill cart with random oferte\n"
              "14. Export to html file from cart\n"
              "15. Undo\n"
              "16. get map with destinatie : vector<denumire>\n";
        int cmd = 0;
        string destinatie;
        string crescator;
        int pretMinim = 0, pretMaxim = 0;
        cin>>cmd;
        try{
            switch(cmd) {
                case 0:
                    return;
                case 1:
                    tipareste(service.getAll());
                    break;
                case 2:
                    adaugaUI();
                    break;
                case 3:
                    deleteUi();
                    break;
                case 4:
                    changeUI();
                    break;
                case 5:
                    findUI();
                    break;
                case 6:
                    cout<<"Dati destinatia:";
                    cin>>destinatie;
                    tipareste(service.filterByDestinatie(destinatie));
                    break;
                case 7:
                    cout<<"Dati pretul minim: ";
                    cin>>pretMinim;
                    cout<<"Dati pretul maxim: ";
                    cin>>pretMaxim;
                    tipareste(service.filterByPret(pretMinim, pretMaxim));
                    break;
                case 8:
                    cout<<"Y for non-ascending/N for ascending";
                    cin>>crescator;
                    if(crescator=="Y")
                        tipareste(service.sortByDenumireDescrescator());
                    else
                        tipareste(service.sortByDenumire());
                    break;
                case 9:
                    cout<<"Y for non-ascending/N for ascending";
                    cin>>crescator;
                    if(crescator=="Y")
                        tipareste(service.sortByDestinatieDescrescator());
                    else
                        tipareste(service.sortByDestinatie());
                    break;
                case 10:
                    cout<<"Y for non-ascending/N for ascending: ";
                    cin>>crescator;
                    if(crescator=="Y")
                        tipareste(service.sortByTipPretDescrescator());
                    else
                        tipareste(service.sortByTipPret());
                    break;
                case 11:
                    service.clearWishlist();
                    cout<<service.wishlistSize()<<"\n";
                    break;
                case 12:
                    adaugaWishlistUi();
                    break;
                case 13:
                    fillWishlistUi();
                    break;
                case 14:
                    exportWishlistToHtmlUi();
                    break;
                case 15:
                    try{
                        service.serviceUndo();
                    }catch (RepositoryException& e){
                        cout<<e.what()<<" ";
                    }
                    break;
                case 16:
                    getElementsByDestinatieUi();
                    break;
                default:
                    cout<<"Comanda invalida\n";
            }
        }catch(const RepositoryException& ex){
            cout<<ex<<"\n";
        }
    }
}