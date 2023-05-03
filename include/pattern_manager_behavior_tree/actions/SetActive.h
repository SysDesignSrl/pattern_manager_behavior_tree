#ifndef PATTERN_MANAGER_BEHAVIOR_TREE_SET_ACTIVE_SERVICE_NODE_H
#define PATTERN_MANAGER_BEHAVIOR_TREE_SET_ACTIVE_SERVICE_NODE_H
#include <string>
// ROS
#include <ros/ros.h>
#include <ros/console.h>
#include <pattern_manager/SetActive.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_ros/bt_service_node.h>


namespace sysdesign { namespace bt {


class SetActive : public BT::RosServiceNode<pattern_manager::SetActive> {
private:
  const std::string LOGNAME = "SetActive";

public:

  SetActive(ros::NodeHandle &node, const std::string &name, const BT::NodeConfiguration &config)
  : BT::RosServiceNode<pattern_manager::SetActive>(node, name, config) { }

  static BT::PortsList providedPorts()
  {
    return
    {
      BT::InputPort<unsigned long>("transform_id"),
      BT::InputPort<bool>("active", true, "Enable/Disable the relative transform id")
    };
  }

  void sendRequest(pattern_manager::SetActive::Request &request) override
  {
    if (!getInput("transform_id", request.id))
    {
      throw BT::RuntimeError("missing required port [transform_id]");
    }
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "request.id: " << request.id);
    
    request.active = getInput<bool>("active").value();
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "request.active: " << request.active);
  }

  BT::NodeStatus onResponse(const pattern_manager::SetActive::Response &response) override
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
