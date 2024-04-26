//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_WISHLISTGUI_H
#define TURISM_QT_WISHLISTGUI_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "Observer.h"
#include "../service/AgentieService.h"

class wishlistGUI : public QWidget, public Observer{
private:
    AgentieService& service;
    Wishlist& wishlist;
    QListWidget* listWidget;
    QPushButton* btn;
    QPushButton* btnRandom;
    QPushButton* btnAdd;
    QLineEdit* name;
    QLineEdit* nr_products;
    void loadList(const std::vector<Oferta>& oferte);
    void initGUI();
    void connectSignals();
public:
    wishlistGUI(AgentieService& agentieService, Wishlist& wishlist): service{agentieService}, wishlist{wishlist}{
        initGUI();
        connectSignals();
        wishlist.addObserver(this);
        loadList(wishlist.getAll());
    }
    void update() override{
        loadList(wishlist.getAll());
    }
    ~wishlistGUI() override{
        wishlist.removeObserver(this);
    }
};

#endif //TURISM_QT_WISHLISTGUI_H
