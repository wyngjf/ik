/*
 * Roboterpraktikum Versuch 6: IK
 * Betreuer: Peter Kaiser
 */

#include "ConstrainedIKWindow.h"
#include "MySingleConstraintIK.h"
#include "MyDualConstraintIK.h"
#include "MyCustomConstraint.h"
#include "SolutionSwitch.h"

#include <VirtualRobot/EndEffector/EndEffector.h>
#include <VirtualRobot/Workspace/Reachability.h>
#include <VirtualRobot/RuntimeEnvironment.h>
#include <VirtualRobot/XML/SceneIO.h>
#include <VirtualRobot/IK/ConstrainedHierarchicalIK.h>
#include <VirtualRobot/IK/constraints/TSRConstraint.h>
#include <VirtualRobot/IK/constraints/PoseConstraint.h>
#include <VirtualRobot/IK/constraints/BalanceConstraint.h>
#include <VirtualRobot/Visualization/CoinVisualization/CoinVisualizationFactory.h>

#include <MotionPlanning/Planner/BiRrt.h>

#include <QFileDialog>
#include <Eigen/Geometry>

#include <time.h>
#include <vector>
#include <iostream>
#include <cmath>

#include <Inventor/actions/SoLineHighlightRenderAction.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoUnits.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoMaterial.h>

#include <sstream>
using namespace std;
using namespace VirtualRobot;

// Change for more iterations in IK solving
#define IK_MAX_ITERATIONS 1000

ConstrainedIKWindow::ConstrainedIKWindow(Qt::WindowFlags flags)
:QMainWindow(NULL)
{
    sceneSep = new SoSeparator;
    sceneSep->ref();
    robotSep = new SoSeparator;
    sceneSep->addChild(robotSep);
    obstacleSep = new SoSeparator;
    sceneSep->addChild(obstacleSep);
    debugSep = new SoSeparator;
    sceneSep->addChild(debugSep);
    floorSep = new SoSeparator;
    sceneSep->addChild(floorSep);
    comSep = new SoSeparator;
    sceneSep->addChild(comSep);

    setupUI();

    loadRobot(DEMO_BASE_DIR "/data/robot/ArmarIII.xml");
    loadScene1();

    viewer->viewAll();
}


ConstrainedIKWindow::~ConstrainedIKWindow()
{
    robot.reset();
    sceneSep->unref();
}

void ConstrainedIKWindow::setupUI()
{
    UI.setupUi(this);
    viewer = new SoQtExaminerViewer(UI.frameViewer,"",TRUE,SoQtExaminerViewer::BUILD_POPUP);

    viewer->setBackgroundColor(SbColor(1.0f, 1.0f, 1.0f));
    viewer->setAccumulationBuffer(false);

    viewer->setGLRenderAction(new SoLineHighlightRenderAction);
    viewer->setTransparencyType(SoGLRenderAction::BLEND);
    viewer->setFeedbackVisibility(true);
    viewer->setSceneGraph(sceneSep);
    viewer->setAntialiasing(true, 4);

    viewer->viewAll();

    connect(UI.pushButtonReset, SIGNAL(clicked()), this, SLOT(reset()));
    connect(UI.pushButtonExercise1, SIGNAL(clicked()), this, SLOT(exercise1()));
    connect(UI.pushButtonExercise2, SIGNAL(clicked()), this, SLOT(exercise2()));
    connect(UI.pushButtonExercise3, SIGNAL(clicked()), this, SLOT(exercise3()));
    connect(UI.pushButtonExercise4, SIGNAL(clicked()), this, SLOT(exercise4()));
    connect(UI.pushButtonExercise5, SIGNAL(clicked()), this, SLOT(exercise5()));

    connect(UI.checkBoxTCPCoordSystems, SIGNAL(clicked()), this, SLOT(rebuildVisualization()));
    connect(UI.checkBoxColModel, SIGNAL(clicked()), this, SLOT(rebuildVisualization()));
    connect(UI.checkBoxTCPCoordSystems, SIGNAL(clicked()), this, SLOT(rebuildVisualization()));

    connect(UI.pushButtonScene1, SIGNAL(clicked()), this, SLOT(loadScene1()));
    connect(UI.pushButtonScene2, SIGNAL(clicked()), this, SLOT(loadScene2()));
    connect(UI.pushButtonScene3, SIGNAL(clicked()), this, SLOT(loadScene3()));
    connect(UI.pushButtonScene4, SIGNAL(clicked()), this, SLOT(loadScene4()));

    UI.splitter->setStretchFactor(0, 1);
    UI.splitter->setStretchFactor(1, 0);
}

void ConstrainedIKWindow::reset()
{
    if(!robot)
    {
        return;
    }

    Eigen::VectorXf c(nodeSet->getSize());
    c.setZero();
    nodeSet->setJointValues(c);

    rightHandEndEffector->openActors();
    leftHandEndEffector->openActors();

    updateRobotCom();
}

void ConstrainedIKWindow::rebuildVisualization()
{
    SceneObject::VisualizationType colModel = (UI.checkBoxColModel->isChecked())?SceneObject::Collision:SceneObject::Full;

    robotSep->removeAllChildren();

    if (robot)
    {
        std::shared_ptr<CoinVisualization> visualization = robot->getVisualization(colModel);
        SoNode* visualisationNode = NULL;
        if (visualization)
            visualisationNode = visualization->getCoinVisualization();

        if (visualisationNode)
            robotSep->addChild(visualisationNode);
    }

    obstacleSep->removeAllChildren();
    if (obstacles)
    {
        for (size_t i=0;i<obstacles->getSceneObjects().size();i++)
        {
            std::shared_ptr<CoinVisualization> visualization = obstacles->getSceneObjects().at(i)->getVisualization<CoinVisualization>(colModel);
            SoNode* visualisationNode = NULL;
            if (visualization)
                visualisationNode = visualization->getCoinVisualization();

            if (visualisationNode)
                obstacleSep->addChild(visualisationNode);
        }
    }

    rightHandNode->showCoordinateSystem(UI.checkBoxTCPCoordSystems->isChecked());
    leftHandNode->showCoordinateSystem(UI.checkBoxTCPCoordSystems->isChecked());

    updateRobotCom();
}

void ConstrainedIKWindow::exercise1()
{
    leftHandEndEffector->openActors();
    rightHandEndEffector->openActors();

    Eigen::Matrix4f transformation = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f eefOffset = Eigen::Matrix4f::Identity();
    eefOffset(0,3) = -60;

    Eigen::MatrixXf bounds = exercise1GetTSRBounds();
    TSRConstraintPtr constraint(new TSRConstraint(robot, nodeSet, rightHandNode, transformation, eefOffset, bounds));

    MySingleConstraintIK ik(robot, nodeSet, constraint);

    // Loop for interactive solving
    for(unsigned int attempt = 0; attempt < IK_MAX_ITERATIONS; attempt++)
    {
        if(ik.solveIkStep())
        {
            std::cout << "Info: IK succeeded" << std::endl;
            rightHandEndEffector->closeActors(objectToGrasp1);
            break;
        }
        else if(UI.checkBoxVisualizeIK->isChecked())
        {
            QApplication::processEvents();
            updateRobotCom();
        }
    }
}

void ConstrainedIKWindow::visualizeTSR(const Eigen::Matrix4f &pose, const Eigen::MatrixXf &bounds, int numSamples)
{
    debugSep->removeAllChildren();

    SoUnits *u = new SoUnits;
    u->units = SoUnits::MILLIMETERS;
    debugSep->addChild(u);

    Eigen::VectorXf sample(6);
    for(int i = 0; i < numSamples; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            float a = rand() % 100 / 100.0;
            sample(j) = bounds(j,0) + a * (bounds(j,1) - bounds(j,0));
        }

        Eigen::Matrix4f S;
        VirtualRobot::MathTools::posrpy2eigen4f(sample.block<3,1>(0,0), sample.block<3,1>(3,0), S);

        SoSeparator *sep = new SoSeparator;
        debugSep->addChild(sep);

        SoMatrixTransform *m = new SoMatrixTransform;
        SbMatrix M = CoinVisualizationFactory::getSbMatrix(pose * S);
        m->matrix.setValue(M);
        sep->addChild(m);

        sep->addChild(CoinVisualizationFactory::CreateCoordSystemVisualization(1.5));
    }
}

Eigen::MatrixXf ConstrainedIKWindow::exercise1GetTSRBounds()
{
    Eigen::Matrix4f M = objectToGrasp1->getGlobalPose();

    Eigen::MatrixXf bounds(6,2);
    bounds <<  M(0,3),   M(0,3),       // [X_min, X_max]
               M(1,3),   M(1,3),       // [Y_min, Y_max]
               M(2,3),   M(2,3),       // [Z_min, Z_max]
                -1.57,    -1.57,       // [Roll_min, Roll_max]
                    0,        0,       // [Pitch_min, Pitch_max]
                0,     6.28;       // [Yaw_min, Yaw_max]
    return bounds;
}

void ConstrainedIKWindow::exercise2()
{
    leftHandEndEffector->openActors();
    rightHandEndEffector->openActors();

    Eigen::Matrix4f transformation = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f eefOffset = Eigen::Matrix4f::Identity();
    eefOffset(0,3) = -60;

    Eigen::MatrixXf bounds = exercise2GetTSRBounds();
    if(bounds.rows() == 0)
    {
        std::cout << "Exercise not solved yet" << std::endl;
        return;
    }

    TSRConstraintPtr constraint(new TSRConstraint(robot, nodeSet, leftHandNode, transformation, eefOffset, bounds));
    MySingleConstraintIK ik(robot, nodeSet, constraint);

    for(unsigned int attempt = 0; attempt < IK_MAX_ITERATIONS; attempt++)
    {
        if(ik.solveIkStep())
        {
            std::cout << "Info: IK succeeded" << std::endl;
            leftHandEndEffector->closeActors(objectToGrasp2);
            break;
        }
        else if(UI.checkBoxVisualizeIK->isChecked())
        {
            QApplication::processEvents();
            updateRobotCom();
        }
    }
}

Eigen::MatrixXf ConstrainedIKWindow::exercise2GetTSRBounds()
{
    Eigen::Matrix4f M = objectToGrasp2->getGlobalPose();

    Eigen::MatrixXf bounds(6,2);

    // PUT CODE HERE FOR EXERCISE 2

    return bounds;
}

void ConstrainedIKWindow::exercise3()
{
    leftHandEndEffector->openActors();
    rightHandEndEffector->openActors();

    Eigen::Matrix4f transformation = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f eefOffset = Eigen::Matrix4f::Identity();
    eefOffset(0,3) = -60;

    Eigen::MatrixXf bounds_right = exercise1GetTSRBounds();
    TSRConstraintPtr constraint_right(new TSRConstraint(robot, nodeSet, rightHandNode, transformation, eefOffset, bounds_right));

    Eigen::MatrixXf bounds_left = exercise2GetTSRBounds();
    TSRConstraintPtr constraint_left(new TSRConstraint(robot, nodeSet, leftHandNode, transformation, eefOffset, bounds_left));

    MyDualConstraintIK ik(robot, nodeSet, constraint_right, constraint_left);

    for(unsigned int attempt = 0; attempt < IK_MAX_ITERATIONS; attempt++)
    {
        if(ik.solveStackedIkStep())
        {
            std::cout << "Info: IK succeeded" << std::endl;
            rightHandEndEffector->closeActors(objectToGrasp1);
            leftHandEndEffector->closeActors(objectToGrasp2);
            break;
        }
        else if(UI.checkBoxVisualizeIK->isChecked())
        {
            QApplication::processEvents();
            updateRobotCom();
        }
    }
}

void ConstrainedIKWindow::exercise4()
{
    leftHandEndEffector->openActors();
    rightHandEndEffector->openActors();

    Eigen::Matrix4f transformation = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f eefOffset = Eigen::Matrix4f::Identity();
    eefOffset(0,3) = -60;

    Eigen::MatrixXf bounds_right = exercise1GetTSRBounds();
    TSRConstraintPtr constraint_right(new TSRConstraint(robot, nodeSet, rightHandNode, transformation, eefOffset, bounds_right));

    Eigen::MatrixXf bounds_left = exercise2GetTSRBounds();
    TSRConstraintPtr constraint_left(new TSRConstraint(robot, nodeSet, leftHandNode, transformation, eefOffset, bounds_left));

    MyDualConstraintIK ik(robot, nodeSet, constraint_right, constraint_left);

    for(unsigned int attempt = 0; attempt < IK_MAX_ITERATIONS; attempt++)
    {
        if(ik.solveNullspaceIkStep())
        {
            std::cout << "Info: IK succeeded" << std::endl;
            rightHandEndEffector->closeActors(objectToGrasp1);
            leftHandEndEffector->closeActors(objectToGrasp2);
            std::cout << nodeSet->getTCP()->getName() << ": " << VirtualRobot::MathTools::eigen4f2posrpy(leftHandNode->getPoseInRootFrame());

            break;
        }
        else if(UI.checkBoxVisualizeIK->isChecked())
        {
            QApplication::processEvents();
            updateRobotCom();
        }
    }
}

void ConstrainedIKWindow::exercise5()
{
    leftHandEndEffector->openActors();
    rightHandEndEffector->openActors();

    Eigen::Matrix4f transformation = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f eefOffset = Eigen::Matrix4f::Identity();
    eefOffset(0,3) = -60;

    Eigen::MatrixXf bounds_right = exercise1GetTSRBounds();
    TSRConstraintPtr constraint_right(new TSRConstraint(robot, nodeSet, rightHandNode, transformation, eefOffset, bounds_right));

    MyCustomConstraintPtr constraint_custom(new MyCustomConstraint(robot, nodeSet, nodeSetFull, platformNode));

    MyDualConstraintIK ik(robot, nodeSet, constraint_right, constraint_custom);

    for(unsigned int attempt = 0; attempt < IK_MAX_ITERATIONS; attempt++)
    {
        if(ik.solveNullspaceIkStep())
        {
            std::cout << "Info: IK succeeded" << std::endl;
            rightHandEndEffector->closeActors(objectToGrasp1);
            leftHandEndEffector->closeActors(objectToGrasp2);
            break;
        }
        else if(UI.checkBoxVisualizeIK->isChecked())
        {
            QApplication::processEvents();
            updateRobotCom();
        }
    }
}

void ConstrainedIKWindow::loadScene1()
{
    loadScene(DEMO_BASE_DIR "/data/ConstrainedIKScene1.xml");
}

void ConstrainedIKWindow::loadScene2()
{
    loadScene(DEMO_BASE_DIR "/data/ConstrainedIKScene2.xml");
}

void ConstrainedIKWindow::loadScene3()
{
    loadScene(DEMO_BASE_DIR "/data/ConstrainedIKScene3.xml");
}

void ConstrainedIKWindow::loadScene4()
{
    loadScene(DEMO_BASE_DIR "/data/ConstrainedIKScene4.xml");
}

void ConstrainedIKWindow::updateRobotCom()
{
    Eigen::Vector3f com = robot->getCoMGlobal();

    comSep->removeAllChildren();

    SoMaterial *m = new SoMaterial;
    m->ambientColor.setValue(1, 0, 0);
    m->diffuseColor.setValue(1, 0, 0);
    comSep->addChild(m);

    SoTransform *t = new SoTransform;
    t->translation.setValue(com.x() / 1000, com.y() / 1000, 0);
    comSep->addChild(t);

    SoSphere *s = new SoSphere;
    s->radius = 0.05;
    comSep->addChild(s);
}

void ConstrainedIKWindow::closeEvent(QCloseEvent *event)
{
    quit();
    QMainWindow::closeEvent(event);
}

int ConstrainedIKWindow::main()
{
    SoQt::show(this);
    SoQt::mainLoop();
    return 0;
}

void ConstrainedIKWindow::quit()
{
    close();
    SoQt::exitMainLoop();
}

void ConstrainedIKWindow::loadScene(const string &sceneFilename)
{
    robotSep->removeAllChildren();
    std::cout << "Loading Scene from " << sceneFilename << std::endl;
    scene.reset();

    try
    {
        scene = SceneIO::loadScene(sceneFilename);
    }
    catch (VirtualRobotException &e)
    {
        std::cout << " ERROR while creating scene" << std::endl;
        std::cout << e.what();
        return;
    }

    if (!scene)
    {
        std::cout << " ERROR while creating scene" << std::endl;
        return;
    }
    scene->registerRobot(robot);

    obstacles = scene->getSceneObjectSet("Obstacles");

    if (!obstacles)
    {
        std::cout << "No SceneObjectSet with name 'Obstacles' found in scene definition!!!" << std::endl;
    }

    floor = scene->getObstacle("Floor");
    objectToGrasp1 = scene->getObstacle("Glas1");
    objectToGrasp2 = scene->getObstacle("Glas2");

    // build visualization
    rebuildVisualization();
    viewer->viewAll();
}

bool ConstrainedIKWindow::loadRobot(const std::string &robotFilename)
{
    cout << "Loading Robot from " << robotFilename << endl;
    robot.reset();

    try
    {
        robot = RobotIO::loadRobot(robotFilename,RobotIO::eFull);
    }
    catch (VirtualRobotException &e)
    {
        cout << "ERROR while creating robot" << endl;
        cout << e.what();
        return false;
    }

    if (!robot)
    {
        cout << "ERROR while creating robot" << endl;
        return false;
    }

    nodeSet = robot->getRobotNodeSet("TorsoBothArms");
    nodeSetFull = robot->getRobotNodeSet("Robot");
    if(!nodeSet || !nodeSetFull)
    {
        cout << "ERROR: Could not obtain robot node sets" << endl;
        return false;
    }

    platformNode = robot->getRobotNode("Platform");
    rightHandNode = robot->getRobotNode("TCP R");
    leftHandNode = robot->getRobotNode("TCP L");
    rightHandEndEffector = robot->getEndEffector("Hand R");
    leftHandEndEffector = robot->getEndEffector("Hand L");

    return true;
}

