//
// Created by Blajan David on 4/26/2024.
//
#include "GUI.h"
#include "wishlistGUI.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

void GUI::initGuiCmps() {
    auto* mainLayout = new QHBoxLayout(this);
    this->setLayout(mainLayout);

    auto* leftWindow = new QWidget;
    auto* verticalLeftLayout = new QVBoxLayout(leftWindow);
    leftWindow->setLayout(verticalLeftLayout);
    listWidget = new QListWidget;
    verticalLeftLayout->addWidget(listWidget);

    auto* leftWindowButtons = new QWidget;
    auto* hbox1 = new QHBoxLayout(leftWindowButtons);
    leftWindowButtons->setLayout(hbox1);
    lbtn1 = new QPushButton("Sort By Denumire");
    lbtn2 = new QPushButton("Sort By Destinatie");
    lbtn3 = new QPushButton("Sort By Tip+Pret");
    hbox1->addWidget(lbtn1);
    hbox1->addWidget(lbtn2);
    hbox1->addWidget(lbtn3);
    verticalLeftLayout->addWidget(leftWindowButtons);

    auto* leftWindowButtons2 = new QWidget;
    auto* hbox12 = new QHBoxLayout(leftWindowButtons2);
    leftWindowButtons2->setLayout(hbox12);
    lbtn4 = new QPushButton("Filter By Destinatie");
    lbtn5 = new QPushButton("Filter By Denumire");
    hbox12->addWidget(lbtn4);
    hbox12->addWidget(lbtn5);
    verticalLeftLayout->addWidget(leftWindowButtons2);

    auto* windowExportToHTML = new QWidget;
    auto* boxExportToHTML = new QHBoxLayout(windowExportToHTML);
    windowExportToHTML->setLayout(boxExportToHTML);
    auto* enterFileHTML = new QLabel("Enter File Name: ");
    txtsavehtml = new QLineEdit;
    lbtn6 = new QPushButton("Export To .html");
    boxExportToHTML->addWidget(enterFileHTML);
    boxExportToHTML->addWidget(txtsavehtml);
    boxExportToHTML->addWidget(lbtn6);
    verticalLeftLayout->addWidget(windowExportToHTML);

    verticalLeftLayout->addStretch();
    mainLayout->addWidget(leftWindow);

    auto* rightWindow = new QWidget;
    auto* verticalRightLayout = new QVBoxLayout(rightWindow);
    rightWindow->setLayout(verticalRightLayout);

    auto* windowDetails = new QWidget;
    auto* denumire = new QLabel("Denumire: ");
    auto* details = new QFormLayout(windowDetails);
    txtdenumire = new QLineEdit;
    details->addRow(denumire, txtdenumire);
    auto* destinatie = new QLabel("Destinatie: ");
    txtdestinatie = new QLineEdit;
    details->addRow(destinatie, txtdestinatie);
    auto* tip = new QLabel("Tip: ");
    txttip = new QLineEdit;
    details->addRow(tip, txttip);
    auto* pret = new QLabel("Pret: ");
    txtpret = new QLineEdit;
    details->addRow(pret, txtpret);
    verticalRightLayout->addWidget(windowDetails);

    auto* windowRightUnderDetails = new QWidget;
    auto* hbox2 = new QHBoxLayout(windowRightUnderDetails);
    windowRightUnderDetails->setLayout(hbox2);

    btn0 = new QPushButton("REFRESH");

    auto* windowRightRefreshLeft = new QWidget;
    auto* vbox1 = new QVBoxLayout(windowRightRefreshLeft);
    windowRightRefreshLeft->setLayout(vbox1);

    auto* windowRightRefreshRight = new QWidget;
    auto* vbox2 = new QVBoxLayout(windowRightRefreshLeft);
    windowRightRefreshRight->setLayout(vbox2);

    hbox2->addWidget(windowRightRefreshLeft);
    hbox2->addWidget(btn0);
    hbox2->addWidget(windowRightRefreshRight);

    verticalRightLayout->addWidget(windowRightUnderDetails);

    add = new QPushButton("&ADD");
    remove = new QPushButton("&REMOVE");
    update = new QPushButton("&UPDATE");

    auto* windowButtons = new QWidget;
    auto* hbox3 = new QHBoxLayout(windowButtons);
    windowButtons->setLayout(hbox3);
    hbox3->addWidget(add);
    hbox3->addWidget(remove);
    hbox3->addWidget(update);
    verticalRightLayout->addWidget(windowButtons);

    btn1 = new QPushButton("UNDO");
    btn2 = new QPushButton("WishlistCRUDGUI");
    btn4 = new QPushButton("WishReadOnlyGUI");
    btn3 = new QPushButton("Find By Denumire");

    txtDenumireCos = new QLineEdit;
    btnAdaugaCos = new QPushButton("Add Cos");
    btnClearCos = new QPushButton("Clear Cos");
    nr_cos = new QLineEdit;
    btnGenerareCos = new QPushButton("Generate Cos");

    auto* windowCosButtons = new QWidget;
    auto* hboxCos = new QHBoxLayout(windowCosButtons);
    windowCosButtons->setLayout(hboxCos);
    hboxCos->addWidget(txtDenumireCos);
    hboxCos->addWidget(btnAdaugaCos);
    hboxCos->addWidget(btnClearCos);
    hboxCos->addWidget(nr_cos);
    hboxCos->addWidget(btnGenerareCos);
    verticalRightLayout->addWidget(windowCosButtons);

    auto* windowButtons2 = new QWidget;
    auto* hbox4 = new QHBoxLayout(windowButtons2);
    windowButtons2->setLayout(hbox4);
    hbox4->addWidget(btn1);
    hbox4->addWidget(btn2);
    hbox4->addWidget(btn4);
    hbox4->addWidget(btn3);
    verticalRightLayout->addWidget(windowButtons2);

    dynamicButtonsLayout = new QHBoxLayout();
    verticalRightLayout->addLayout(dynamicButtonsLayout);

    verticalRightLayout->addStretch();

    mainLayout->addWidget(rightWindow);

    this->show();
}

void GUI::connectSignalSlots() {
    QObject::connect(btn2, &QPushButton::clicked, this, [&](){
        wishlistGUI1();
    });
    QObject::connect(btn1, &QPushButton::clicked, this, [&](){
        undoGUI();
    });
    QObject::connect(lbtn4, &QPushButton::clicked, this, [&](){
        filterDestinatieGUI();
    });
    QObject::connect(lbtn5, &QPushButton::clicked, this, [&](){
        filterDenumireGUI();
    });
    QObject::connect(lbtn6, &QPushButton::clicked, this, [&](){
        exportHTMLGUI();
    });
    QObject::connect(lbtn1, &QPushButton::clicked, this, [&](){
        sortDenumireGUI();
    });
    QObject::connect(lbtn2, &QPushButton::clicked, this, [&](){
        sortDestinatieGUI();
    });
    QObject::connect(lbtn3, &QPushButton::clicked, this, [&](){
        sortTipPretGUI();
    });
    QObject::connect(add, &QPushButton::clicked, this, [&](){
        addGUI();
    });
    QObject::connect(remove, &QPushButton::clicked, this, [&](){
        removeGUI();
    });
    QObject::connect(update, &QPushButton::clicked, this, [&](){
        updateGUI();
    });
    QObject::connect(listWidget, &QListWidget::itemSelectionChanged, [&](){
        if(this->listWidget->selectedItems().isEmpty()){
            txtdenumire->setText("");
            txtdestinatie->setText("");
            txttip->setText("");
            txtpret->setText("");
            return;
        }
        auto* selItem = listWidget->selectedItems().at(0);
        QString denumire = selItem->text();
        txtdenumire->setText(denumire);
        QString tip = selItem->data(Qt::UserRole).toString();
        txttip->setText(tip);
        try{
            Oferta of = agentieService.findService(denumire.toStdString());
            txtpret->setText(QString::number(of.getPret()));
            txtdestinatie->setText(QString::fromStdString(of.getDestinatie()));
        }catch (RepositoryException& ex){
            QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.what()));
        }
    });
    QObject::connect(btn3, &QPushButton::clicked, this, [&](){
        findGUI();
    });
    QObject::connect(btn4, &QPushButton::clicked, this, [&](){
       auto* figuresWindow = new HistogramGUI(this->wishlist);
       figuresWindow->show();
    });
    QObject::connect(btn0, &QPushButton::clicked, this, [&](){
        refreshGUI();
    });
    QObject::connect(btnAdaugaCos, &QPushButton::clicked, this, [&]() {
        try {
            wishlist.addCart(agentieService.findService(txtDenumireCos->text().toStdString()).getDenumire());
        } catch (RepositoryException &ex) {
            QMessageBox::warning(this, "warning!", QString::fromStdString(ex.what()));
        }
    });
    QObject::connect(btnClearCos, &QPushButton::clicked, this, [&]() {
        wishlist.clearCart();
    });
    QObject::connect(btnGenerareCos, &QPushButton::clicked, this, [&]() {
        wishlist.fillCart(nr_cos->text().toInt());
    });
}

void GUI::reloadList(const std::vector<Oferta> &all) {
    this->listWidget->clear();
    for(const auto& of : all){
        auto* listWidgetItem = new QListWidgetItem(QString::fromStdString(of.getDenumire()), listWidget);
        listWidgetItem->setData(Qt::UserRole, QString::fromStdString(of.getTip()));
        if(of.getPret() < 10){
            listWidgetItem->setBackground(Qt::red);
        }
    }
    txtdenumire->setText("");
    txtdestinatie->setText("");
    txttip->setText("");
    txtpret->setText("");
}

void GUI::addGUI() {
    try{
        this->agentieService.addService(txtdenumire->text().toStdString(), txtdestinatie->text().toStdString(), txttip->text().toStdString(), txtpret->text().toInt());
        reloadList(agentieService.getAll());
        updateDestinatieButtons();
    }catch (RepositoryException& ex){
        QMessageBox::warning(this, "warning!", QString::fromStdString(ex.what()));
    }catch (ValidatorException& ex){
        QMessageBox::warning(this, "warning!", QString::fromStdString(ex.what()));
    }
}

void GUI::removeGUI(){
    try{
        this->agentieService.deleteService(txtdenumire->text().toStdString());
        reloadList(agentieService.getAll());
        updateDestinatieButtons();
    }catch (RepositoryException& ex){
        QMessageBox::warning(this, "warning!", QString::fromStdString(ex.what()));
    }
}

void GUI::updateGUI(){
    try{
        this->agentieService.changeService(txtdenumire->text().toStdString(), txtdestinatie->text().toStdString(), txttip->text().toStdString(), txtpret->text().toInt());
        reloadList(agentieService.getAll());
    }catch (RepositoryException& ex){
        QMessageBox::warning(this, "warning!", QString::fromStdString(ex.what()));
    }catch (ValidatorException& ex){
        QMessageBox::warning(this, "warning!", QString::fromStdString(ex.what()));
    }
}

void GUI::refreshGUI() {
    reloadList(agentieService.getAll());
}

void GUI::findGUI() {
    try {
        string denumire = txtdenumire->text().toStdString();
        Oferta of = this->agentieService.findService(denumire);
        txtdestinatie->setText(QString::fromStdString(of.getDestinatie()));
        txttip->setText(QString::fromStdString(of.getTip()));
        txtpret->setText(QString::number(of.getPret()));
    }catch (RepositoryException& ex){
        QMessageBox::warning(this, "warning!", QString::fromStdString(ex.what()));
    }
}

void GUI::sortDenumireGUI() {
    this->reloadList(agentieService.sortByDenumire());
}

void GUI::sortDestinatieGUI() {
    this->reloadList(agentieService.sortByDestinatie());
}

void GUI::sortTipPretGUI() {
    this->reloadList(agentieService.sortByTipPret());
}

void GUI::filterDestinatieGUI() {
    this->reloadList(agentieService.filterByDestinatie(txtdestinatie->text().toStdString()));
}

void GUI::filterDenumireGUI() {
    this->reloadList(agentieService.filterByDenumire(txtdenumire->text().toStdString()));
}

void GUI::undoGUI() {
    try{
        agentieService.serviceUndo();
    }catch(RepositoryException& ex){
        QMessageBox::warning(this, "warning!", QString::fromStdString(ex.what()));
    }
    this->reloadList(agentieService.getAll());
}

void GUI::exportHTMLGUI() {
    try{
        agentieService.exportWishlistToHtml(txtsavehtml->text().toStdString());
    }catch (RepositoryException& ex){
        QMessageBox::warning(this, "warning!", QString::fromStdString(ex.what()));
    }
}

void GUI::wishlistGUI1() {
    auto* wsh = new WishlistGuiTabel{this->agentieService, this->wishlist};
    wsh->show();
}

void GUI::updateDestinatieButtons() {
    // Clear existing buttons
    for (auto& pair : destinatieButtons) {
        dynamicButtonsLayout->removeWidget(pair.second);
        delete pair.second;
    }
    destinatieButtons.clear();

    // Get the current "Destinatie" counts
    auto destinatieCounts = agentieService.getElementsForDestinatie();

    // Create buttons for each "Destinatie"
    for (const auto& pair : destinatieCounts) {
        const string& destinatie = pair.first;
        int count = pair.second;

        auto* btn = new QPushButton(QString::fromStdString(destinatie + ": " + std::to_string(count)));
        dynamicButtonsLayout->addWidget(btn);
        destinatieButtons[destinatie] = btn;

        QObject::connect(btn, &QPushButton::clicked, this, [destinatie, count]() {
            QMessageBox::information(nullptr, "Destinatie Count", QString::fromStdString("There are " + std::to_string(count) + " offers for " + destinatie));
        });
    }
}
