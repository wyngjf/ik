/*
 * Roboterpraktikum Versuch 6: IK
 * Betreuer: Peter Kaiser
 */

#ifndef MY_SINGLE_CONSTRAINT_IK
#define MY_SINGLE_CONSTRAINT_IK

#include <VirtualRobot/IK/Constraint.h>

class MySingleConstraintIK
{
    public:
        MySingleConstraintIK(const VirtualRobot::RobotPtr &robot, const VirtualRobot::RobotNodeSetPtr &nodeSet, const VirtualRobot::ConstraintPtr &constraint);

        bool solveIkStep();

    protected:
        VirtualRobot::RobotPtr robot;
        VirtualRobot::RobotNodeSetPtr nodeSet;
        VirtualRobot::ConstraintPtr constraint;
};

#endif
