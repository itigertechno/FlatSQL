#include <QtGui/QApplication>
#include "testdialog/testdialog.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    TestDialog w;
    w.show();
    return a.exec();}