/*
 * Roboterpraktikum Versuch 6: IK
 * Betreuer: Peter Kaiser
 */

#ifndef MY_DUAL_CONSTRAINT_IK
#define MY_DUAL_CONSTRAINT_IK

#include <VirtualRobot/IK/Constraint.h>

class MyDualConstraintIK
{
    public:
        MyDualConstraintIK(const VirtualRobot::RobotPtr &robot, const VirtualRobot::RobotNodeSetPtr &nodeSet, const VirtualRobot::ConstraintPtr &constraint1, const VirtualRobot::ConstraintPtr &constraint2);

        bool solveStackedIkStep();
        bool solveNullspaceIkStep();

    protected:
        VirtualRobot::RobotPtr robot;
        VirtualRobot::RobotNodeSetPtr nodeSet;
        VirtualRobot::ConstraintPtr constraint1;
        VirtualRobot::ConstraintPtr constraint2;
};

#endif
