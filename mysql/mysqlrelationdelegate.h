//
// Created by Paul156551 on 21.03.2023.
//
#ifndef FLATSQL_MYSQLRELATIONDELEGATE_H
#define FLATSQL_MYSQLRELATIONDELEGATE_H

#include <QSqlRelationDelegate>

class mySqlRelationDelegate: public QSqlRelationDelegate {
    Q_OBJECT

public:
    explicit mySqlRelationDelegate(QObject *parent = 0);

    QWidjet *createEditor(QWidget *aParent, const QSttyleOptionVieItem &option, const QModelIndex &index) const;
    void setModelData(QWidjet *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    signals:

public slots:

};

#endif //FLATSQL_MYSQLRELATIONDELEGATE_H
