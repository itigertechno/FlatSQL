//
// Created by Paul156551 on 21.03.2023.
//

#ifndef FLATSQL_TESTDIALOG_H
#define FLATSQL_TESTDIALOG_H

#include "ui_testdialog.h"
#include <QDialog>
class QSqlTableModel;
class QSqlRecord;

class TestDialog : public QDialog, private Ui::TestDialog {
    Q_OBJECT
public:
    TestDialog(QWidget *parent = 0);
private slots:
            void on_buttonBox_clicked(QAbstractButton* button);
    void on_addColButton_clicked();
    void on_insertButton_clicked();
    void on_removeButton_clicked();
#ifndef AUTOINCREMENT
    void table1PrimeInsert(int row, QSqlRecord& record);
#endif

};

#endif //FLATSQL_TESTDIALOG_H
