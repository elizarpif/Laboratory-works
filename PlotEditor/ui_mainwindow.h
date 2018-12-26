/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *spravka;
    QWidget *centralWidget;
    QCustomPlot *plot;
    QLineEdit *equiv_edit;
    QSpinBox *spin_min;
    QSpinBox *spin_max;
    QTextEdit *textEdit;
    QLabel *min;
    QLabel *nax;
    QPushButton *pushButton;
    QTreeWidget *treeCurves;
    QTextEdit *text_invar;
    QPushButton *pushButton_2;
    QPushButton *rotate90;
    QMenuBar *menuBar;
    QMenu *menu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(776, 680);
        QFont font;
        font.setFamily(QStringLiteral("Comic Sans MS"));
        font.setPointSize(10);
        MainWindow->setFont(font);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        spravka = new QAction(MainWindow);
        spravka->setObjectName(QStringLiteral("spravka"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        plot = new QCustomPlot(centralWidget);
        plot->setObjectName(QStringLiteral("plot"));
        plot->setGeometry(QRect(290, 60, 451, 311));
        equiv_edit = new QLineEdit(centralWidget);
        equiv_edit->setObjectName(QStringLiteral("equiv_edit"));
        equiv_edit->setGeometry(QRect(290, 20, 361, 20));
        spin_min = new QSpinBox(centralWidget);
        spin_min->setObjectName(QStringLiteral("spin_min"));
        spin_min->setGeometry(QRect(570, 390, 42, 22));
        spin_min->setMinimum(-1000);
        spin_min->setMaximum(-1);
        spin_min->setValue(-10);
        spin_max = new QSpinBox(centralWidget);
        spin_max->setObjectName(QStringLiteral("spin_max"));
        spin_max->setGeometry(QRect(700, 390, 42, 22));
        spin_max->setMinimum(0);
        spin_max->setMaximum(1000);
        spin_max->setValue(10);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 450, 271, 161));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(163, 32, 32, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        textEdit->setPalette(palette);
        textEdit->setAutoFillBackground(false);
        textEdit->setReadOnly(true);
        min = new QLabel(centralWidget);
        min->setObjectName(QStringLiteral("min"));
        min->setGeometry(QRect(510, 390, 61, 16));
        nax = new QLabel(centralWidget);
        nax->setObjectName(QStringLiteral("nax"));
        nax->setGeometry(QRect(630, 390, 61, 16));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(670, 20, 75, 23));
        treeCurves = new QTreeWidget(centralWidget);
        treeCurves->setObjectName(QStringLiteral("treeCurves"));
        treeCurves->setGeometry(QRect(20, 30, 221, 371));
        text_invar = new QTextEdit(centralWidget);
        text_invar->setObjectName(QStringLiteral("text_invar"));
        text_invar->setGeometry(QRect(330, 450, 411, 161));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        text_invar->setPalette(palette1);
        text_invar->setAutoFillBackground(false);
        text_invar->setReadOnly(true);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(420, 390, 75, 23));
        rotate90 = new QPushButton(centralWidget);
        rotate90->setObjectName(QStringLiteral("rotate90"));
        rotate90->setGeometry(QRect(310, 390, 91, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 776, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(spravka);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\272\321\200\320\270\320\262\321\213\321\205", nullptr));
        action->setText(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        action_2->setText(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        spravka->setText(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        equiv_edit->setText(QApplication::translate("MainWindow", "x^2+y^2-9=0", nullptr));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Comic Sans MS'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">x^2+y^2-9=0</p></body></html>", nullptr));
        min->setText(QApplication::translate("MainWindow", "X, Y min", nullptr));
        nax->setText(QApplication::translate("MainWindow", "X, Y max", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\277\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeCurves->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\320\232\321\200\320\270\320\262\321\213\320\265", nullptr));
        text_invar->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Comic Sans MS'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        rotate90->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
