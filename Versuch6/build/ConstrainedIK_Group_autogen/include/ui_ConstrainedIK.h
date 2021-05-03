/********************************************************************************
** Form generated from reading UI file 'ConstrainedIK.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSTRAINEDIK_H
#define UI_CONSTRAINEDIK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PathPlanning
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QFrame *frameViewer;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButtonScene1;
    QPushButton *pushButtonScene2;
    QPushButton *pushButtonScene3;
    QPushButton *pushButtonScene4;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButtonReset;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButtonExercise1;
    QPushButton *pushButtonExercise2;
    QPushButton *pushButtonExercise3;
    QPushButton *pushButtonExercise4;
    QPushButton *pushButtonExercise5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBoxColModel;
    QCheckBox *checkBoxVisualizeIK;
    QCheckBox *checkBoxTCPCoordSystems;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PathPlanning)
    {
        if (PathPlanning->objectName().isEmpty())
            PathPlanning->setObjectName(QStringLiteral("PathPlanning"));
        PathPlanning->resize(1103, 559);
        centralwidget = new QWidget(PathPlanning);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        frameViewer = new QFrame(splitter);
        frameViewer->setObjectName(QStringLiteral("frameViewer"));
        frameViewer->setFrameShape(QFrame::StyledPanel);
        frameViewer->setFrameShadow(QFrame::Raised);
        splitter->addWidget(frameViewer);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButtonScene1 = new QPushButton(groupBox_2);
        pushButtonScene1->setObjectName(QStringLiteral("pushButtonScene1"));

        verticalLayout_4->addWidget(pushButtonScene1);

        pushButtonScene2 = new QPushButton(groupBox_2);
        pushButtonScene2->setObjectName(QStringLiteral("pushButtonScene2"));

        verticalLayout_4->addWidget(pushButtonScene2);

        pushButtonScene3 = new QPushButton(groupBox_2);
        pushButtonScene3->setObjectName(QStringLiteral("pushButtonScene3"));

        verticalLayout_4->addWidget(pushButtonScene3);

        pushButtonScene4 = new QPushButton(groupBox_2);
        pushButtonScene4->setObjectName(QStringLiteral("pushButtonScene4"));

        verticalLayout_4->addWidget(pushButtonScene4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        pushButtonReset = new QPushButton(groupBox_2);
        pushButtonReset->setObjectName(QStringLiteral("pushButtonReset"));

        verticalLayout_4->addWidget(pushButtonReset);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(layoutWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        pushButtonExercise1 = new QPushButton(groupBox_3);
        pushButtonExercise1->setObjectName(QStringLiteral("pushButtonExercise1"));

        verticalLayout_5->addWidget(pushButtonExercise1);

        pushButtonExercise2 = new QPushButton(groupBox_3);
        pushButtonExercise2->setObjectName(QStringLiteral("pushButtonExercise2"));

        verticalLayout_5->addWidget(pushButtonExercise2);

        pushButtonExercise3 = new QPushButton(groupBox_3);
        pushButtonExercise3->setObjectName(QStringLiteral("pushButtonExercise3"));

        verticalLayout_5->addWidget(pushButtonExercise3);

        pushButtonExercise4 = new QPushButton(groupBox_3);
        pushButtonExercise4->setObjectName(QStringLiteral("pushButtonExercise4"));

        verticalLayout_5->addWidget(pushButtonExercise4);

        pushButtonExercise5 = new QPushButton(groupBox_3);
        pushButtonExercise5->setObjectName(QStringLiteral("pushButtonExercise5"));

        verticalLayout_5->addWidget(pushButtonExercise5);


        verticalLayout->addWidget(groupBox_3);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        checkBoxColModel = new QCheckBox(groupBox);
        checkBoxColModel->setObjectName(QStringLiteral("checkBoxColModel"));

        verticalLayout_3->addWidget(checkBoxColModel);

        checkBoxVisualizeIK = new QCheckBox(groupBox);
        checkBoxVisualizeIK->setObjectName(QStringLiteral("checkBoxVisualizeIK"));
        checkBoxVisualizeIK->setChecked(true);

        verticalLayout_3->addWidget(checkBoxVisualizeIK);

        checkBoxTCPCoordSystems = new QCheckBox(groupBox);
        checkBoxTCPCoordSystems->setObjectName(QStringLiteral("checkBoxTCPCoordSystems"));

        verticalLayout_3->addWidget(checkBoxTCPCoordSystems);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        splitter->addWidget(layoutWidget);

        verticalLayout_2->addWidget(splitter);

        PathPlanning->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PathPlanning);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1103, 20));
        PathPlanning->setMenuBar(menubar);
        statusbar = new QStatusBar(PathPlanning);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        PathPlanning->setStatusBar(statusbar);

        retranslateUi(PathPlanning);

        QMetaObject::connectSlotsByName(PathPlanning);
    } // setupUi

    void retranslateUi(QMainWindow *PathPlanning)
    {
        PathPlanning->setWindowTitle(QApplication::translate("PathPlanning", "PathPlanning", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("PathPlanning", "Scenes", Q_NULLPTR));
        pushButtonScene1->setText(QApplication::translate("PathPlanning", "Load Scene 1", Q_NULLPTR));
        pushButtonScene2->setText(QApplication::translate("PathPlanning", "Load Scene 2", Q_NULLPTR));
        pushButtonScene3->setText(QApplication::translate("PathPlanning", "Load Scene 3", Q_NULLPTR));
        pushButtonScene4->setText(QApplication::translate("PathPlanning", "Load Scene 4", Q_NULLPTR));
        pushButtonReset->setText(QApplication::translate("PathPlanning", "Reset Scene", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("PathPlanning", "Exercises", Q_NULLPTR));
        pushButtonExercise1->setText(QApplication::translate("PathPlanning", "Exercise 1", Q_NULLPTR));
        pushButtonExercise2->setText(QApplication::translate("PathPlanning", "Exercise 2", Q_NULLPTR));
        pushButtonExercise3->setText(QApplication::translate("PathPlanning", "Exercise 3", Q_NULLPTR));
        pushButtonExercise4->setText(QApplication::translate("PathPlanning", "Exercise 4", Q_NULLPTR));
        pushButtonExercise5->setText(QApplication::translate("PathPlanning", "Exercise 5", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("PathPlanning", "Visualization", Q_NULLPTR));
        checkBoxColModel->setText(QApplication::translate("PathPlanning", "Robot Collision Model", Q_NULLPTR));
        checkBoxVisualizeIK->setText(QApplication::translate("PathPlanning", "Visualize IK", Q_NULLPTR));
        checkBoxTCPCoordSystems->setText(QApplication::translate("PathPlanning", "TCP Coordinate Systems", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PathPlanning: public Ui_PathPlanning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSTRAINEDIK_H
