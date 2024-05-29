//
// Created by Blajan David on 5/20/2024.
//

#ifndef TURISM_QT_TABLEMODEL_H
#define TURISM_QT_TABLEMODEL_H

#include <QAbstractTableModel>
#include "../domain/Oferta.h"

class TableModel : public QAbstractTableModel{
    AgentieService& agentieService;
    std::vector<Oferta> oferte;
public:
    explicit TableModel(const std::vector<Oferta>& oferte, AgentieService& agentieService1):oferte{oferte}, agentieService{agentieService1}{
    }
    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override{
        return oferte.size();
    }
    [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override{
        return 4;
    }
    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const auto& p = oferte[index.row()];
            switch (index.column()) {
                case 0: return QString::fromStdString(p.getDenumire());
                case 1: return QString::fromStdString(p.getDestinatie());
                case 2: return QString::fromStdString(p.getTip());
                case 3: return QString::number(p.getPret());
                default: return QVariant{};
            }
        }
        return QVariant{};

    }

    void setOferte(const std::vector<Oferta>& oferte1) {
        this->oferte = oferte1;
        updateModel();
    }

    void updateModel(){
        beginResetModel(); // Begin model reset
        endResetModel(); // End model reset
    }

    void refreshModel(){
        this->oferte = agentieService.getAll();
        updateModel();
    }
};

#endif //TURISM_QT_TABLEMODEL_H
