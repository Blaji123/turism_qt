////
//// Created by Blajan David on 4/26/2024.
////
//#include <QHBoxLayout>
//#include <QLabel>
//#include <QMessageBox>
//#include "wishlistGUI.h"
//
//void wishlistGUI::initGUI() {
//    auto *ly = new QHBoxLayout;
//    listWidget = new QListWidget;
//    ly->addWidget(listWidget);
//
//    auto *firstCol = new QWidget;
//    auto *boxFirstCol = new QVBoxLayout(firstCol);
//    firstCol->setLayout(boxFirstCol);
//
//    btn = new QPushButton("Clear cos");
//    boxFirstCol->addWidget(btn);
//
//    auto *secondRow = new QWidget;
//    auto *boxSecondRow = new QHBoxLayout(secondRow);
//    secondRow->setLayout(boxSecondRow);
//    auto *enterDenumire = new QLabel("Denumire: ");
//    name = new QLineEdit;
//    btnAdd = new QPushButton("Add oferta");
//    boxSecondRow->addWidget(enterDenumire);
//    boxSecondRow->addWidget(name);
//    boxSecondRow->addWidget(btnAdd);
//
//    boxFirstCol->addWidget(secondRow);
//    boxFirstCol->addStretch();
//    ly->addWidget(firstCol);
//
//    auto *thirdRow = new QWidget;
//    auto *boxThirdRow = new QHBoxLayout(thirdRow);
//    thirdRow->setLayout(boxThirdRow);
//
//    auto *nrProd = new QLabel("Number of products: ");
//    nr_products = new QLineEdit;
//    btnRandom = new QPushButton("Add random");
//    boxThirdRow->addWidget(nrProd);
//    boxThirdRow->addWidget(nr_products);
//    boxThirdRow->addWidget(btnRandom);
//    ly->addWidget(thirdRow);
//
//    setLayout(ly);
//}
//
//void wishlistGUI::connectSignals() {
//    wishlist.addObserver(this);
//
//    QObject::connect(btnAdd, &QPushButton::clicked, this, [&]() {
//        try {
//            wishlist.addCart(service.findService(name->text().toStdString()).getDenumire());
//            loadList(wishlist.getAll());
//            wishlist.notify();
//        } catch (RepositoryException &ex) {
//            QMessageBox::warning(this, "warning!", QString::fromStdString(ex.what()));
//        }
//    });
//    QObject::connect(btn, &QPushButton::clicked, this, [&]() {
//        wishlist.clearCart();
//        loadList(wishlist.getAll());
//        wishlist.notify();
//    });
//    QObject::connect(btnRandom, &QPushButton::clicked, this, [&]() {
//        wishlist.fillCart(nr_products->text().toInt());
//        loadList(wishlist.getAll());
//        wishlist.notify();
//    });
//}
//
//void wishlistGUI::loadList(const std::vector<Oferta> &oferte) {
//    listWidget->clear();
//    for(auto& of : oferte){
//        listWidget->addItem(QString::fromStdString(of.getDenumire()));
//    }
//}
