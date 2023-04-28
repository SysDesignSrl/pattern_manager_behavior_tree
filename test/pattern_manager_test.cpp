#include <string>
// ROS
#include <ros/ros.h>
#include <ros/console.h>
#include <gtest/gtest.h>
// BehaviorTree.ROS
#include <behaviortree_cpp_v3/bt_factory.h>
#include <behaviortree_cpp_v3/loggers/bt_cout_logger.h>
#include <behaviortree_cpp_v3/loggers/bt_file_logger.h>
#include <behaviortree_ros/bt_service_node.h>
//
#include "pattern_manager_behavior_tree/conversions.h"
#include "pattern_manager_behavior_tree/actions/FilenameServiceNode.h"
#include "pattern_manager_behavior_tree/actions/GetCurrentIdServiceNode.h"
#include "pattern_manager_behavior_tree/actions/GetTransformIdServiceNode.h"
#include "pattern_manager_behavior_tree/actions/SetActiveServiceNode.h"
#include "pattern_manager_behavior_tree/actions/TriggerServiceNode.h"


class PatternManagerFixture : public ::testing::Test {
protected:
  ros::NodeHandle node;

  BT::BehaviorTreeFactory bt_factory;
  BT::Tree bt_tree;

  PatternManagerFixture() : node("~")
  {

  }

  void SetUp() override
  { 
    BT::RegisterRosService<sysdesign::bt::FilenameServiceNode>(bt_factory, "Filename", node);
    BT::RegisterRosService<sysdesign::bt::GetCurrentIdServiceNode>(bt_factory, "GetCurrentId", node);
    BT::RegisterRosService<sysdesign::bt::GetTransformIdServiceNode>(bt_factory, "GetTransformId", node);
    BT::RegisterRosService<sysdesign::bt::SetActiveServiceNode>(bt_factory, "SetActive", node);
    BT::RegisterRosService<sysdesign::bt::TriggerServiceNode>(bt_factory, "Trigger", node);
  }
};


TEST_F(PatternManagerFixture, tickRoot)
{
  std::string bt_file;
  ASSERT_TRUE(node.getParam("bt_file", bt_file));
  ASSERT_NO_THROW({
    bt_tree = bt_factory.createTreeFromFile(bt_file);
  });

  BT::NodeStatus bt_status;

  double freq = node.param("frequency", 1.0);
  ros::Rate rate(freq);
  do
  {
    rate.sleep();
    bt_status = bt_tree.tickRoot();
    ros::spinOnce();
  }
  while ((bt_status == BT::NodeStatus::RUNNING) && node.ok());
  ASSERT_EQ(bt_status, BT::NodeStatus::SUCCESS);
}


int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);

  ros::init(argc, argv, "palletizer_test");

  return RUN_ALL_TESTS();
}
