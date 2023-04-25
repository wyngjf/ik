/*
 * Roboterpraktikum Versuch 6: IK
 * Betreuer: Peter Kaiser
 */

#ifndef __PathPlanning_WINDOW_H_
#define __PathPlanning_WINDOW_H_

#include <VirtualRobot/VirtualRobot.h>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/VirtualRobotException.h>
#include <VirtualRobot/Nodes/RobotNode.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/Visualization/VisualizationFactory.h>
#include <VirtualRobot/Obstacle.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <VirtualRobot/Visualization/CoinVisualization/CoinVisualizationNode.h>
#include <VirtualRobot/Visualization/CoinVisualization/CoinVisualization.h>
#include <VirtualRobot/IK/ConstrainedHierarchicalIK.h>

#include <string.h>
#include <QtCore/QtGlobal>
#include <QtGui/QtGui>
#include <QtCore/QtCore>

#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoSeparator.h>

#include <vector>

#include "ui_ConstrainedIK.h"

class ConstrainedIKWindow : public QMainWindow
{
    Q_OBJECT
public:
    ConstrainedIKWindow(Qt::WindowFlags flags = 0);
    ~ConstrainedIKWindow();

    /*!< Executes the SoQt mainLoop. You need to call this in order to execute the application. */
    int main();


public slots:
    /*! Closes the window and exits SoQt runloop. */
    void quit();

    /*!< Overriding the close event, so we know when the window was closed by the user. */
    void closeEvent(QCloseEvent *event);

    void reset();

    void loadScene(const std::string &sceneFilename);
    bool loadRobot(const std::string &robotFilename);

    void rebuildVisualization();

    void exercise1();
    Eigen::MatrixXf exercise1GetTSRBounds();

    void exercise2();
    Eigen::MatrixXf exercise2GetTSRBounds();

    void exercise3();
    void exercise4();
    void exercise5();

    void loadScene1();
    void loadScene2();
    void loadScene3();
    void loadScene4();

    void updateRobotCom();

    void visualizeTSR(const Eigen::Matrix4f &pose, const Eigen::MatrixXf &bounds, int numSamples);

protected:
    void setupUI();

    Ui::PathPlanning UI;
    SoQtExaminerViewer *viewer; /*!< Viewer to display the 3D model of the robot and the environment. */

    SoSeparator *sceneSep;
    SoSeparator *robotSep;
    SoSeparator *obstacleSep;
    SoSeparator *debugSep;
    SoSeparator *floorSep;
    SoSeparator *comSep;

    VirtualRobot::SceneObjectSetPtr obstacles;
    VirtualRobot::SceneObjectPtr floor;
    VirtualRobot::SceneObjectPtr objectToGrasp1;
    VirtualRobot::SceneObjectPtr objectToGrasp2;

    VirtualRobot::RobotPtr robot;
    VirtualRobot::RobotNodeSetPtr nodeSet;
    VirtualRobot::RobotNodeSetPtr nodeSetFull;
    VirtualRobot::RobotNodePtr platformNode;
    VirtualRobot::RobotNodePtr rightHandNode;
    VirtualRobot::RobotNodePtr leftHandNode;
    VirtualRobot::EndEffectorPtr rightHandEndEffector;
    VirtualRobot::EndEffectorPtr leftHandEndEffector;
    VirtualRobot::ScenePtr scene;

    std::shared_ptr<VirtualRobot::CoinVisualization> visualization;
};

#endif // __PathPlanning_WINDOW_H_
