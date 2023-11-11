/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *button_start;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *THDx_label;
    QFrame *line;
    QLabel *one_label;
    QFrame *line_2;
    QLabel *two_label;
    QFrame *line_3;
    QLabel *three_label;
    QFrame *line_4;
    QLabel *four_label;
    QFrame *line_5;
    QLabel *five_label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 450);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1000, 450));
        MainWindow->setMaximumSize(QSize(1000, 450));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        button_start = new QPushButton(centralwidget);
        button_start->setObjectName(QString::fromUtf8("button_start"));
        button_start->setGeometry(QRect(800, 360, 161, 81));
        QFont font;
        font.setPointSize(25);
        button_start->setFont(font);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 370, 741, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        THDx_label = new QLabel(horizontalLayoutWidget);
        THDx_label->setObjectName(QString::fromUtf8("THDx_label"));
        THDx_label->setMinimumSize(QSize(100, 0));
        QFont font1;
        font1.setPointSize(20);
        THDx_label->setFont(font1);

        horizontalLayout->addWidget(THDx_label);

        line = new QFrame(horizontalLayoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        one_label = new QLabel(horizontalLayoutWidget);
        one_label->setObjectName(QString::fromUtf8("one_label"));
        one_label->setMinimumSize(QSize(100, 0));
        one_label->setFont(font1);

        horizontalLayout->addWidget(one_label);

        line_2 = new QFrame(horizontalLayoutWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        two_label = new QLabel(horizontalLayoutWidget);
        two_label->setObjectName(QString::fromUtf8("two_label"));
        two_label->setMinimumSize(QSize(100, 0));
        two_label->setFont(font1);

        horizontalLayout->addWidget(two_label);

        line_3 = new QFrame(horizontalLayoutWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        three_label = new QLabel(horizontalLayoutWidget);
        three_label->setObjectName(QString::fromUtf8("three_label"));
        three_label->setMinimumSize(QSize(100, 0));
        three_label->setFont(font1);

        horizontalLayout->addWidget(three_label);

        line_4 = new QFrame(horizontalLayoutWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_4);

        four_label = new QLabel(horizontalLayoutWidget);
        four_label->setObjectName(QString::fromUtf8("four_label"));
        four_label->setMinimumSize(QSize(100, 0));
        four_label->setFont(font1);

        horizontalLayout->addWidget(four_label);

        line_5 = new QFrame(horizontalLayoutWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_5);

        five_label = new QLabel(horizontalLayoutWidget);
        five_label->setObjectName(QString::fromUtf8("five_label"));
        five_label->setMinimumSize(QSize(100, 0));
        five_label->setFont(font1);

        horizontalLayout->addWidget(five_label);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        button_start->setText(QApplication::translate("MainWindow", "Start", nullptr));
        THDx_label->setText(QApplication::translate("MainWindow", "THDx:", nullptr));
        one_label->setText(QApplication::translate("MainWindow", "\345\237\272\346\263\242:", nullptr));
        two_label->setText(QApplication::translate("MainWindow", "\344\272\214\346\254\241:", nullptr));
        three_label->setText(QApplication::translate("MainWindow", "\344\270\211\346\254\241:", nullptr));
        four_label->setText(QApplication::translate("MainWindow", "\345\233\233\346\254\241:", nullptr));
        five_label->setText(QApplication::translate("MainWindow", "\344\272\224\346\254\241:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
