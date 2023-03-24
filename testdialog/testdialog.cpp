//
// Created by Paul156551 on 24.03.2023.
//
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationTableModel>
#include <QStandardModel>
#include <QSqlRelationDelegate>
#include <QItemSelectionModel>
#include <QDebug>
#include <QSqlError>
#include <QSortFilterProxyModel>

#include "mysql/mysqlrelationdelegate.h"
#include "testdialog/testdialog.h"
#include "qxtreemodel/qxtreeproxymodel.h"

#include <QSqlRecord>
#include <QSqlDriver>
#ifdef MODEL_TEST
#include <modeltest.h>
#endif

// to test the various options: define options  in .pro file
#ifndef AUTOINCREMENT
void TestDialog::table1PrimeInsert(int row, QSqlRecord& record) {
    // qDebug() << "table1PrimeInsert" << record;
    // for(int i(0); i < record.count(); ++i) qDebug() << "   before" << record.value(i);
    Q_UNUSED(row);
    static int lastId(1000);
    // record.setValue(QLatin1String("Identifier"), ++lastId);
    // for(int i(0); i < record.count(); ++i) qDebug() << "   after" << record.value(i);
    }
#endif

TestDialog::TestDialog(QWidget *parent) : QDialog(parent) {
    setupUI(this);
    bool ok;
#if (TABLEMODEL==QSQLTABLEMODEL) || (TABLEMODEL==QSQLRELATIONTABLEMODEL)
    QSqlDatabase db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
    db.setDatabaseName(QLatin1String(":memory:"));
    // db.setDatabaseName(QLatin1String("testdb.db"));
    Q_ASSERT(db.open());
    QSqlQuery sqlQuery(db);
    // create Table1 (main table)
#ifdef AUTOINCREMENT
    ok = sqlQuery.exec(QLatin1String("CREATE TABLE Table1(Content, Identifier INTEGER PRIMARY KEY AUTOINCREMENT, Parent INTEGER NOT NULL, Details);"));
#else
    ok = sqlQuery.exec(QLatin1String("CREATE TABLE Table1(Content, Identifier INTEGER PRIMARY KEY, Parent INTEGER NOT NULL, Details);"));
#endif
    Q_ASSERT_X(ok, "CREATE TABLE sql statement", "Table1 likely already exists");



}