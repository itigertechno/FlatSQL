//
// Created by Paul156551 on 22.03.2023.
//
#include "mysql/mysqlrelationdelegate.h"
#include <QSqlRelationTableModel>
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QSqlRecord>


mySqlRelationDelegate:mySqlRelationDelegate(QObject *parent) :
     QSqlRelationDelegate (parent) {
}

QWidget *mySqlRelationDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    const QSqlRelationTableModel *sqlModel = qobject_cast<const QSqlRelationTableModel *>(index.model());
    QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;

    if (!childModel) {
        const QAbstractProxyModel* proxyModel = qobject_cast<const QAbstractProxyModel *>(index.model());
        if (proxyModel) {
            sqlModel = qobject_cast<const QSqlRelationTableModel *>(proxyModel->sourceModel());
            childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
        }
    }

    if (!childModel) {
        return QItemDelegate::createEditor(aParent, option, index);
    }

    QComboBox *combo = new QComboBox(aParent);
    combo->setModel(childModel);
    combo->setModelColumn(childModel->fieldIndex(sqlModel->relation(index.column()).displayColumn()));
    combo->installEventFilter(const_cast<mySqlRelationDelegate *>(this));

    return combo;
}

    void mySqlRelationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
        QString strVal = "";
        const QSqlRelationTableModel *sqlModel = qobject_cast<const QSqlRelationTableModel *>(index.model());
        if (!sqlModel) {
            const QAbstractProxymodel *proxyModel = qobject_cast<const QAbstractProxyModel *>(index.model());
            if (proxyModel) {
                strVal = proxyModel->data(index).toString();
            }
        } else {
            strVal = sqlModel->data(index).toString();
        }

        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        if (strVal.isEmpty() || !combo) {
            QItemDelegate::setEditorData(editor, index);
            return;
        }

        combo->setCurrentIndex(combo->findText(strVal));
    }

    void mySqlRelationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
        if (!index.isValid())
            return;

        QSqlRelationTableModel *sqlModel = qobject_cast<QSqlRelationTableModel *>(model);
        QAbstractProxyModel* proxyModel = NULL;
        if (!sqlModel) {
            proxyModel = qobject_cast<QAbstractProxyModel *>(model);
            if (proxyModel)
                sqlModel = qobject_cast<QSqlRelationTableModel *>(proxyModel->sourceModel());
        }

        QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        if (!sqlModel || !childModel || !combo) {
            QItemDelegate::setModelData(editor, model, index);
            return;
        }

        int currentItem = combo->currentIndex();
        int childColIndex = childModel->fieldIndex(sqlModel->relation(index.column()).displayColumn());
        int childEditIndex = childModel->fieldIndex(sqlModel->relation(index.column()).indexColumn());

        if (proxyModel) {
            proxyModel->setData(index, childModel->data(childModel->index(currentItem, childColIndex), Qt::DisplayRole), Qt::DisplayRole);
            proxyModel->setData(index, childModel->data(childModel->index(currentItem, childEditIndex), Qt::EditRole), Qt::EditRole);
        } else {
            sqlModel->setData(index, childModel->data(childModel->index(currentItem, childColIndex), Qt::DisplayRole), Qt::DisplayRole);
            sqlModel->setData(index, childModel->data(childModel->index(curentItem, childEditIndex), Qt::EditRole), Qt::EditRole);
        }
}