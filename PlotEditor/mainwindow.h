#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "vectors.h"
#include <qcustomplot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void Plot();

    void prepareMenu( const QPoint & pos );

    Poly getInput();

    Poly getInput(QString s);

    void GraphInit(int i);

    void FileOpen();

    void FileSave();


private slots:

    void on_spin_min_valueChanged(int arg1);

    void on_spin_max_valueChanged(int arg1);

    void on_pushButton_clicked();

    void slotCustomMenuRequested(QPoint pos);

    void slotAddRecord();

    void slotRemoveRecord();

    void on_treeCurves_itemClicked(QTreeWidgetItem *item, int column);

    void showHelp();

    void on_pushButton_2_clicked();


private:

    Ui::MainWindow *ui;
    int max, min;
    QDialog *f2;
    QString filename = "figures.dat";
    QVector<QString> equals, eq_name;
    int flagOneClick;
};

#endif // MAINWINDOW_H
