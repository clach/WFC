/********************************************************************************
** Form generated from reading UI file 'cameracontrolshelp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERACONTROLSHELP_H
#define UI_CAMERACONTROLSHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraControlsHelp
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_13;
    QLabel *label_14;
    QFrame *line;
    QLabel *label_11;

    void setupUi(QWidget *CameraControlsHelp)
    {
        if (CameraControlsHelp->objectName().isEmpty())
            CameraControlsHelp->setObjectName(QStringLiteral("CameraControlsHelp"));
        CameraControlsHelp->resize(414, 184);
        label = new QLabel(CameraControlsHelp);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 111, 21));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(CameraControlsHelp);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 111, 21));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(CameraControlsHelp);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 50, 111, 21));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(CameraControlsHelp);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 70, 111, 21));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(CameraControlsHelp);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(150, 30, 141, 21));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(CameraControlsHelp);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(150, 10, 151, 21));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(CameraControlsHelp);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(150, 70, 151, 21));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(CameraControlsHelp);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(150, 50, 131, 21));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_9 = new QLabel(CameraControlsHelp);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 90, 111, 21));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_10 = new QLabel(CameraControlsHelp);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 110, 111, 21));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_13 = new QLabel(CameraControlsHelp);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 130, 141, 21));
        label_13->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_14 = new QLabel(CameraControlsHelp);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 150, 141, 21));
        label_14->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        line = new QFrame(CameraControlsHelp);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(113, 10, 31, 161));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(CameraControlsHelp);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(150, 100, 251, 31));
        label_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11->setWordWrap(true);

        retranslateUi(CameraControlsHelp);

        QMetaObject::connectSlotsByName(CameraControlsHelp);
    } // setupUi

    void retranslateUi(QWidget *CameraControlsHelp)
    {
        CameraControlsHelp->setWindowTitle(QApplication::translate("CameraControlsHelp", "Camera Controls", Q_NULLPTR));
        label->setText(QApplication::translate("CameraControlsHelp", "W: Move forward", Q_NULLPTR));
        label_2->setText(QApplication::translate("CameraControlsHelp", "S: Move backward", Q_NULLPTR));
        label_3->setText(QApplication::translate("CameraControlsHelp", "A: Move left", Q_NULLPTR));
        label_4->setText(QApplication::translate("CameraControlsHelp", "D: Move right", Q_NULLPTR));
        label_5->setText(QApplication::translate("CameraControlsHelp", "Down arrow: Rotate up", Q_NULLPTR));
        label_6->setText(QApplication::translate("CameraControlsHelp", "Up arrow: Rotate down", Q_NULLPTR));
        label_7->setText(QApplication::translate("CameraControlsHelp", "Right arrow: Rotate right", Q_NULLPTR));
        label_8->setText(QApplication::translate("CameraControlsHelp", "Left arrow: Rotate left", Q_NULLPTR));
        label_9->setText(QApplication::translate("CameraControlsHelp", "Q: Move down", Q_NULLPTR));
        label_10->setText(QApplication::translate("CameraControlsHelp", "E: Move up", Q_NULLPTR));
        label_13->setText(QApplication::translate("CameraControlsHelp", "1: Increase FOV", Q_NULLPTR));
        label_14->setText(QApplication::translate("CameraControlsHelp", "2: Decrease FOV", Q_NULLPTR));
        label_11->setText(QApplication::translate("CameraControlsHelp", "R: Reset camera to default position and orientation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CameraControlsHelp: public Ui_CameraControlsHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERACONTROLSHELP_H
