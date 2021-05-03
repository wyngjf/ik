/*
 * Roboterpraktikum Versuch 6: IK
 * Betreuer: Peter Kaiser
 */

#include "MySingleConstraintIK.h"
#include "SolutionSwitch.h"
#include <VirtualRobot/MathTools.h>

MySingleConstraintIK::MySingleConstraintIK(const VirtualRobot::RobotPtr &robot, const VirtualRobot::RobotNodeSetPtr &nodeSet, const VirtualRobot::ConstraintPtr &constraint) :
    robot(robot),
    nodeSet(nodeSet),
    constraint(constraint)
{

}

/*
 * Exercise 1
 */
bool MySingleConstraintIK::solveIkStep()
{
    // The current Jacobian matrix for the chosen constraint
    // Eigen::MatrixXf J = constraint->getJacobianMatrix();

    // The Jacobian's pseudoinverse
    // Eigen::MatrixXf J_inv = VirtualRobot::MathTools::getPseudoInverse(J);

    // The constraint's current error vector
    // Eigen::VectorXf e = constraint->getError();

    // Getting and setting the robot's current configuration
    // Eigen::VectorXf config;
    // nodeSet->getJointValues(config);
    // nodeSet->setJointValues(config + delta);

    float error_delta = 0.1;
    float error_epsilon = 0.1;

    // PUT CODE HERE FOR EXERCISE 1

    return false;
}
