/********************************************************************************
** Form generated from reading UI file 'opengltest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENGLTEST_H
#define UI_OPENGLTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_opengltestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    GLWidget *openGLWidget;
    QGroupBox *groupBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *opengltestClass)
    {
        if (opengltestClass->objectName().isEmpty())
            opengltestClass->setObjectName(QStringLiteral("opengltestClass"));
        opengltestClass->resize(1228, 768);
        centralWidget = new QWidget(opengltestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        openGLWidget = new GLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMinimumSize(QSize(1000, 0));

        gridLayout->addWidget(openGLWidget, 0, 2, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(groupBox, 0, 1, 1, 1);

        opengltestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(opengltestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1228, 21));
        opengltestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(opengltestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        opengltestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(opengltestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        opengltestClass->setStatusBar(statusBar);

        retranslateUi(opengltestClass);

        QMetaObject::connectSlotsByName(opengltestClass);
    } // setupUi

    void retranslateUi(QMainWindow *opengltestClass)
    {
        opengltestClass->setWindowTitle(QApplication::translate("opengltestClass", "opengltest", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("opengltestClass", "GroupBox", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class opengltestClass: public Ui_opengltestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENGLTEST_H
