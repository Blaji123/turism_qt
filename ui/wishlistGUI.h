//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_WISHLISTGUI_H
#define TURISM_QT_WISHLISTGUI_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>
#include <QPainter>
#include "Observer.h"
#include "TableModel.h"
#include "../service/AgentieService.h"

//class wishlistGUI : public QWidget, public Observer{
//private:
//    AgentieService& service;
//    Wishlist& wishlist;
//    QListWidget* listWidget;
//    QPushButton* btn;
//    QPushButton* btnRandom;
//    QPushButton* btnAdd;
//    QLineEdit* name;
//    QLineEdit* nr_products;
//    void loadList(const std::vector<Oferta>& oferte);
//    void initGUI();
//    void connectSignals();
//public:
//    wishlistGUI(AgentieService& agentieService, Wishlist& wishlist): service{agentieService}, wishlist{wishlist}{
//        initGUI();
//        connectSignals();
//        wishlist.addObserver(this);
//        loadList(wishlist.getAll());
//    }
//    void update() override{
//        loadList(wishlist.getAll());
//    }
//    ~wishlistGUI() override{
//        wishlist.removeObserver(this);
//    }
//};

class HistogramGUI: public QWidget, public Observer{
private:
    Wishlist& wishlist;
public:
    explicit HistogramGUI(Wishlist& wishlist1): wishlist{wishlist1}{
        wishlist.addObserver(this);
    }
    void update() override{
        repaint();
    }
    void paintEvent(QPaintEvent* ev) override{
        QPainter p{this};
        srand(time(nullptr));
        for(const auto& of : wishlist.getAll()){
            int x = rand() % 300;
            int y = rand() % 300;
            p.drawRect(x,y, 20, of.getPret()/10);
            p.drawImage(x,y,QImage("sky.jpeg"));
        }
    }
};

class WishlistGUILabel : public QLabel, public Observer{
private:
    Wishlist& wishlist;
public:
    WishlistGUILabel(Wishlist& wishlist1): wishlist{wishlist1}{
        setFont(QFont{"arial", 24});
        setAttribute(Qt::WA_DeleteOnClose);
        wishlist.addObserver(this);
        update();
    }
    void update() override{
        setText("Wishlistul contine: " + QString::number(wishlist.getAll().size()));
    }
    ~WishlistGUILabel(){
        wishlist.removeObserver(this);
    }
};

class WishlistGuiTabel : public QWidget, public Observer {
private:
    [[maybe_unused]] AgentieService& agentieService;
    Wishlist& wishlist;
    QPushButton* btn{};
    QPushButton* btnRandom{};
    TableModel* tableModel;
    QTableView* tblV{};

    void initGUI() {
        auto* ly = new QHBoxLayout;
        tblV = new QTableView;
        ly->addWidget(tblV);
        btn = new QPushButton("Clear Cos");
        ly->addWidget(btn);
        btnRandom = new QPushButton("Add random 4");
        ly->addWidget(btnRandom);
        setLayout(ly);
    }

    void connectSignals() {
        wishlist.addObserver(this);
        QObject::connect(btn, &QPushButton::clicked, [&]() {
            wishlist.clearCart();
        });
        QObject::connect(btnRandom, &QPushButton::clicked, [&]() {
            wishlist.fillCart(4);
        });
    }

    void update() override {
        tableModel->setOferte(wishlist.getAll());
    }

public:
    WishlistGuiTabel(AgentieService& agentieService1, Wishlist& wishlist1)
            : agentieService{agentieService1}, wishlist{wishlist1} {
        initGUI();
        tableModel = new TableModel{wishlist.getAll(), agentieService1};
        tblV->setModel(tableModel);
        connectSignals();
        wishlist.addObserver(this);
        tableModel->refreshModel();
    }

    ~WishlistGuiTabel() override {
        wishlist.removeObserver(this);
    }
};


#endif //TURISM_QT_WISHLISTGUI_H
