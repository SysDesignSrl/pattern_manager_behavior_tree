#ifndef PATTERN_MANAGER_BEHAVIOR_TREE_TRIGGER_SERVICE_NODE_H
#define PATTERN_MANAGER_BEHAVIOR_TREE_TRIGGER_SERVICE_NODE_H
#include <string>
// ROS
#include <ros/ros.h>
#include <ros/console.h>
#include <std_srvs/Trigger.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_ros/bt_service_node.h>


namespace sysdesign { namespace bt {


class TriggerServiceNode : public BT::RosServiceNode<std_srvs::Trigger> {
private:
  const std::string LOGNAME = "TriggerServiceNode";

public:

  TriggerServiceNode(ros::NodeHandle &node, const std::string &name, const BT::NodeConfiguration &config)
  : BT::RosServiceNode<std_srvs::Trigger>(node, name, config) { }

  void sendRequest(std_srvs::Trigger::Request &request) override
  {

  }

  BT::NodeStatus onResponse(const std_srvs::Trigger::Response &response) override
  {
    if (response.success)
    {
      return BT::NodeStatus::SUCCESS;
    }
    else
    {
      return BT::NodeStatus::FAILURE;
    }
  }

};

} }  // namespace
#endif
