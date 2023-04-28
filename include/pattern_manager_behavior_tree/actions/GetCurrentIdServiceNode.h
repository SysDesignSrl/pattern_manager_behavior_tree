#ifndef PATTERN_MANAGER_BEHAVIOR_TREE_GET_CURRENT_ID_SERVICE_NODE_H
#define PATTERN_MANAGER_BEHAVIOR_TREE_GET_CURRENT_ID_SERVICE_NODE_H
#include <string>
// ROS
#include <ros/ros.h>
#include <ros/console.h>
#include <pattern_manager/GetCurrentId.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_ros/bt_service_node.h>


namespace sysdesign { namespace bt {


class GetCurrentIdServiceNode : public BT::RosServiceNode<pattern_manager::GetCurrentId> {
private:
  const std::string LOGNAME = "GetCurrentIdServiceNode";

public:

  GetCurrentIdServiceNode(ros::NodeHandle &node, const std::string &name, const BT::NodeConfiguration &config)
  : BT::RosServiceNode<pattern_manager::GetCurrentId>(node, name, config) { }

  static BT::PortsList providedPorts()
  {
    return
    {
      BT::OutputPort<unsigned long>("transform_id"),
      BT::OutputPort<std::string>("transform_name")
    };
  }

  void sendRequest(pattern_manager::GetCurrentId::Request &request) override
  {

  }

  BT::NodeStatus onResponse(const pattern_manager::GetCurrentId::Response &response) override
  {
    setOutput<unsigned long>("transform_id", response.id);
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "response.id: " << response.id);

    setOutput<std::string>("transform_name", response.name);
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "response.name: " << response.name);

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
