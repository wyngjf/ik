/*
 * Roboterpraktikum Versuch 6: IK
 * Betreuer: Peter Kaiser
 */

#include "MyDualConstraintIK.h"
#include "SolutionSwitch.h"

MyDualConstraintIK::MyDualConstraintIK(const VirtualRobot::RobotPtr &robot, const VirtualRobot::RobotNodeSetPtr &nodeSet, const VirtualRobot::ConstraintPtr &constraint1, const VirtualRobot::ConstraintPtr &constraint2) :
    robot(robot),
    nodeSet(nodeSet),
    constraint1(constraint1),
    constraint2(constraint2)
{
}

bool MyDualConstraintIK::solveStackedIkStep()
{
    // The current Jacobian matrix for the chosen constraint
    // Eigen::MatrixXf J = constraint->getJacobianMatrix();

    // The Jacobian's pseudoinverse
    // Eigen::MatrixXf J_inv = VirtualRobot::MathTools::getPseudoInverse(J);

    // The constraint's current error vector
    // Eigen::VectorXf e = constraint->getError();

    // Identity matrix
    // Eigen::MatrixXf I = Eigen::MatrixXf::Identity(num_rows, num_columns);

    // Getting and setting the robot's current configuration
    // Eigen::VectorXf config;
    // nodeSet->getJointValues(config);
    // nodeSet->setJointValues(config + delta);

    // Stacking two matrices
    // Eigen::MatrixXf X(Y.rows() + Z.rows(), Y.cols());
    // X << Y, Z;

    float error_epsilon = 1;
    float error_delta = 0.1;

    // PUT CODE HERE FOR EXERCISE 3

    return false;
}

bool MyDualConstraintIK::solveNullspaceIkStep()
{
    // The current Jacobian matrix for the chosen constraint
    // Eigen::MatrixXf J = constraint->getJacobianMatrix();

    // The Jacobian's pseudoinverse
    // Eigen::MatrixXf J_inv = VirtualRobot::MathTools::getPseudoInverse(J);

    // The constraint's current error vector
    // Eigen::VectorXf e = constraint->getError();

    // Identity matrix
    // Eigen::MatrixXf I = Eigen::MatrixXf::Identity(num_rows, num_columns);

    // Getting and setting the robot's current configuration
    // Eigen::VectorXf config;
    // nodeSet->getJointValues(config);
    // nodeSet->setJointValues(config + delta);

    float error_epsilon = 1;
    float error_delta = 0.5;

    // PUT CODE HERE FOR EXERCISE 4

    return false;
}
