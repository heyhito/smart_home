/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *connectButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *templabel;
    QLabel *label_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *humlabel;
    QLabel *label_5;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *lightlabel;
    QLabel *label_6;
    QWidget *tab_2;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout;
    QPushButton *kitchbutton;
    QPushButton *alermbutton;
    QWidget *tab_3;
    QLabel *label_7;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(450, 500);
        Widget->setMinimumSize(QSize(450, 500));
        Widget->setMaximumSize(QSize(450, 500));
        horizontalLayout = new QHBoxLayout(Widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        connectButton = new QPushButton(tab);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(120, 370, 171, 61));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(41, 40, 321, 91));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        templabel = new QLabel(layoutWidget);
        templabel->setObjectName(QStringLiteral("templabel"));

        horizontalLayout_2->addWidget(templabel);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(41, 151, 321, 91));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        humlabel = new QLabel(layoutWidget1);
        humlabel->setObjectName(QStringLiteral("humlabel"));

        horizontalLayout_3->addWidget(humlabel);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        layoutWidget2 = new QWidget(tab);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(41, 250, 321, 101));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        lightlabel = new QLabel(layoutWidget2);
        lightlabel->setObjectName(QStringLiteral("lightlabel"));

        horizontalLayout_4->addWidget(lightlabel);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        tabWidget->addTab(tab, QString());
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        connectButton->raise();
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        layoutWidget3 = new QWidget(tab_2);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(80, 30, 261, 371));
        verticalLayout = new QVBoxLayout(layoutWidget3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        kitchbutton = new QPushButton(layoutWidget3);
        kitchbutton->setObjectName(QStringLiteral("kitchbutton"));
        QFont font;
        font.setPointSize(16);
        kitchbutton->setFont(font);
        kitchbutton->setIconSize(QSize(12, 16));

        verticalLayout->addWidget(kitchbutton);

        alermbutton = new QPushButton(layoutWidget3);
        alermbutton->setObjectName(QStringLiteral("alermbutton"));
        alermbutton->setFont(font);

        verticalLayout->addWidget(alermbutton);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(160, 40, 91, 41));
        textEdit = new QTextEdit(tab_3);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(110, 90, 200, 200));
        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 340, 100, 50));
        pushButton_2 = new QPushButton(tab_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 340, 100, 50));
        tabWidget->addTab(tab_3, QString());

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        connectButton->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\346\243\200\346\265\213\346\225\260\346\215\256", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">\346\270\251\345\272\246</span></p></body></html>", Q_NULLPTR));
        templabel->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\"><br/></span></p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">\342\204\203</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">\346\271\277\345\272\246</span></p></body></html>", Q_NULLPTR));
        humlabel->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\"><br/></span></p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">hPa</span></p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">\344\272\256\345\272\246</span></p></body></html>", Q_NULLPTR));
        lightlabel->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\"><br/></span></p></body></html>", Q_NULLPTR));
        label_6->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">cd/m\302\262</span></p></body></html>", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "\347\216\257\345\242\203\346\243\200\346\265\213", Q_NULLPTR));
        kitchbutton->setText(QApplication::translate("Widget", "\345\216\250\346\210\277\347\201\257", Q_NULLPTR));
        alermbutton->setText(QApplication::translate("Widget", "\346\212\245\350\255\246\345\231\250", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "\350\277\234\347\250\213\346\216\247\345\210\266", Q_NULLPTR));
        label_7->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">\350\257\255\351\237\263\350\257\206\345\210\253</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Widget", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Widget", "\346\270\205\351\231\244", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Widget", "\350\257\255\351\237\263\346\216\247\345\210\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
