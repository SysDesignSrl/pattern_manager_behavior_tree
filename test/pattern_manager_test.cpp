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
#include "pattern_manager_behavior_tree/actions/Filename.h"
#include "pattern_manager_behavior_tree/actions/GetCurrentId.h"
#include "pattern_manager_behavior_tree/actions/GetTransformId.h"
#include "pattern_manager_behavior_tree/actions/SetActive.h"
#include "pattern_manager_behavior_tree/actions/Trigger.h"


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
    BT::RegisterRosService<sysdesign::bt::Filename>(bt_factory, "Filename", node);
    BT::RegisterRosService<sysdesign::bt::GetCurrentId>(bt_factory, "GetCurrentId", node);
    BT::RegisterRosService<sysdesign::bt::GetTransformId>(bt_factory, "GetTransformId", node);
    BT::RegisterRosService<sysdesign::bt::SetActive>(bt_factory, "SetActive", node);
    BT::RegisterRosService<sysdesign::bt::Trigger>(bt_factory, "Trigger", node);
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
