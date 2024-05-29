//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_GUI_H
#define TURISM_QT_GUI_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include "../service/AgentieService.h"

class GUI : public QWidget{
    Q_OBJECT
private:
    Wishlist& wishlist;
    AgentieService& agentieService;
    QListWidget* listWidget{};
    QPushButton* add{};
    QPushButton* remove{};
    QPushButton* update{};
    QPushButton* btn0{};
    QPushButton* btn1{};
    QPushButton* btn2{};
    QPushButton* btn3{};
    QPushButton* btn4{};
    QPushButton* lbtn1{};
    QPushButton* lbtn2{};
    QPushButton* lbtn3{};
    QPushButton* lbtn4{};
    QPushButton* lbtn5{};
    QPushButton* lbtn6{};
    QPushButton* btnAdaugaCos{};
    QPushButton* btnClearCos{};
    QPushButton* btnGenerareCos{};
    QLineEdit* txtDenumireCos{};
    QLineEdit* nr_cos{};
    QLineEdit* txtdenumire{};
    QLineEdit* txtdestinatie{};
    QLineEdit* txttip{};
    QLineEdit* txtpret{};
    QLineEdit* txtsavehtml{};
    void initGuiCmps();
    void connectSignalSlots();
    void reloadList(const std::vector<Oferta>& all);
    void addGUI();
    void removeGUI();
    void updateGUI();
    void refreshGUI();
    void findGUI();
    void sortDenumireGUI();
    void sortDestinatieGUI();
    void sortTipPretGUI();
    void filterDestinatieGUI();
    void filterDenumireGUI();
    void undoGUI();
    void exportHTMLGUI();
    void wishlistGUI1();
    QHBoxLayout* dynamicButtonsLayout{};
    std::unordered_map<string, QPushButton*> destinatieButtons;
    void updateDestinatieButtons();

public:
    GUI(AgentieService& agentieService, Wishlist& wishlist): agentieService{agentieService}, wishlist{wishlist}{
        initGuiCmps();
        connectSignalSlots();
        reloadList(agentieService.getAll());
        updateDestinatieButtons();
    }
};

#endif //TURISM_QT_GUI_H
