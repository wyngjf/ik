/*
 * Roboterpraktikum Versuch 6: IK
 * Betreuer: Peter Kaiser
 */

#include "MyCustomConstraint.h"
#include "SolutionSwitch.h"

#include <VirtualRobot/Nodes/RobotNodeRevolute.h>
#include <VirtualRobot/Nodes/RobotNodePrismatic.h>
#include <VirtualRobot/IK/SupportPolygon.h>
#include "VirtualRobot/SceneObject.h"
#include <VirtualRobot/RobotNodeSet.h>

MyCustomConstraint::MyCustomConstraint(const VirtualRobot::RobotPtr &robot, const VirtualRobot::RobotNodeSetPtr &nodeSet, const VirtualRobot::RobotNodeSetPtr &nodeSetFull, const VirtualRobot::RobotNodePtr &platformNode) :
    Constraint(nodeSet),
    robot(robot),
    nodeSet(nodeSet),
    nodeSetFull(nodeSetFull)
{
    VirtualRobot::SceneObjectSetPtr s(new VirtualRobot::SceneObjectSet());
    s->addSceneObject(platformNode);

    supportPolygon.reset(new VirtualRobot::SupportPolygon(s));
    supportPolygon->updateSupportPolygon();
}

Eigen::MatrixXf MyCustomConstraint::getJacobianMatrix()
{
    // The i'th robot node
    // VirtualRobot::RobotNodePtr node = nodeSet->getNode(i);

    // The CoM of a robot node
    // Eigen::Vector3f com = node->getCoMGlobal();

    // The node's mass
    // float mass = node->getMass();

    // (Positional) Jacobian for a node's CoM
    // Eigen::MatrixXf J_com = getJacobianOfCoM(node);

    Eigen::MatrixXf J(2, nodeSet->getSize());
    J.setZero();

    // PUT CODE HERE FOR EXERCISE 5

    return J;
}

Eigen::VectorXf MyCustomConstraint::getError(float stepSize)
{
    // The CoM of the robot
    // Eigen::Vector3f com = nodeSet->getCoM();

    // The support polygon as convex hull
    // VirtualRobot::MathTools::ConvexHull2DPtr ch = supportPolygon->getSupportPolygon2D();

    // The center of a convex hull
    // VirtualRobot::MathTools::getConvexHullCenter(ch);

    Eigen::VectorXf e(2);
    e.setZero();

    // PUT CODE HERE FOR EXERCISE 5

    return e;
}



// Everything below does not need to be changed

Eigen::MatrixXf MyCustomConstraint::getJacobianMatrix(VirtualRobot::SceneObjectPtr tcp)
{
    // Not used
    return getJacobianMatrix();
}

bool MyCustomConstraint::checkTolerances()
{
    // Not used
    return false;
}

Eigen::MatrixXf MyCustomConstraint::getJacobianOfCoM(const VirtualRobot::RobotNodePtr& node)
{
    // Get number of degrees of freedom
    size_t nDoF = rns->getAllRobotNodes().size();

    // Create matrices for the position and the orientation part of the jacobian.
    Eigen::MatrixXf position = Eigen::MatrixXf::Zero(3, nDoF);

    std::vector<VirtualRobot::RobotNodePtr> bodyNodes = nodeSet->getAllRobotNodes();
    std::map< VirtualRobot::RobotNodePtr, std::vector<VirtualRobot::RobotNodePtr> > bodyNodeParents;
    for (size_t i = 0; i < bodyNodes.size(); i++)
    {
        // get all joints that influence the body
        std::vector<VirtualRobot::RobotNodePtr> parentsN = bodyNodes[i]->getAllParents(rns);
        // maybe this node is joint and body
        if (nodeSet->hasRobotNode(bodyNodes[i]))
        {
            parentsN.push_back(bodyNodes[i]);
        }
        bodyNodeParents[bodyNodes[i]] = parentsN;
    }
    std::vector<VirtualRobot::RobotNodePtr> parentsN = bodyNodeParents[node];

    // Iterate over all degrees of freedom
    for (size_t i = 0; i < nDoF; i++)
    {
        VirtualRobot::RobotNodePtr dof = rns->getNode((int)i);// bodyNodes[i];

        // Check if the tcp is affected by this DOF
        if (find(parentsN.begin(), parentsN.end(), dof) != parentsN.end())
        {
            // Calculus for rotational joints is different as for prismatic joints.
            if (dof->isRotationalJoint())
            {
                // get axis
                std::shared_ptr<VirtualRobot::RobotNodeRevolute> revolute
                    = std::dynamic_pointer_cast<VirtualRobot::RobotNodeRevolute>(dof);
//                THROW_VR_EXCEPTION_IF(!revolute, "Internal error: expecting revolute joint");
                Eigen::Vector3f axis = revolute->getJointRotationAxis();

                // For CoM-Jacobians only the positional part is necessary
                Eigen::Vector3f toTCP = node->getCoMGlobal()
                                        - dof->getGlobalPose().block(0, 3, 3, 1);

                position.block(0, i, 3, 1) = axis.cross(toTCP);
            }
            else if (dof->isTranslationalJoint())
            {
                std::shared_ptr<VirtualRobot::RobotNodePrismatic> prismatic
                    = std::dynamic_pointer_cast<VirtualRobot::RobotNodePrismatic>(dof);
//                THROW_VR_EXCEPTION_IF(!prismatic, "Internal error: expecting prismatic joint");
                Eigen::Vector3f axis = prismatic->getJointTranslationDirection();

                position.block(0, i, 3, 1) = axis;
            }
        }
    }

    return position;
}

