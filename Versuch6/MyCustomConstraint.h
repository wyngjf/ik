/*
 * Roboterpraktikum Versuch 6: IK
 * Betreuer: Peter Kaiser
 */

#include <VirtualRobot/IK/Constraint.h>

#include <boost/shared_ptr.hpp>

class MyCustomConstraint : public VirtualRobot::Constraint, public boost::enable_shared_from_this<MyCustomConstraint>
{
public:
    MyCustomConstraint(const VirtualRobot::RobotPtr& robot, const VirtualRobot::RobotNodeSetPtr& nodeSet, const VirtualRobot::RobotNodeSetPtr& nodeSetFull, const VirtualRobot::RobotNodePtr &platformNode);

    virtual Eigen::MatrixXf getJacobianMatrix();
    virtual Eigen::MatrixXf getJacobianMatrix(VirtualRobot::SceneObjectPtr tcp);
    virtual Eigen::VectorXf getError(float stepSize = 1.0f);
    virtual bool checkTolerances();

protected:
    Eigen::MatrixXf getJacobianOfCoM(const VirtualRobot::RobotNodePtr& node);

protected:
    VirtualRobot::RobotPtr robot;
    VirtualRobot::RobotNodeSetPtr nodeSet;
    VirtualRobot::RobotNodeSetPtr nodeSetFull;
    VirtualRobot::SupportPolygonPtr supportPolygon;
};

typedef boost::shared_ptr<MyCustomConstraint> MyCustomConstraintPtr;
