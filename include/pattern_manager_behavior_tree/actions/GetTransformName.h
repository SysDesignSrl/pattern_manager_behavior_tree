#ifndef PATTERN_MANAGER_BEHAVIOR_TREE_GET_TRANSFORM_NAME_SERVICE_NODE_H
#define PATTERN_MANAGER_BEHAVIOR_TREE_GET_TRANSFORM_NAME_SERVICE_NODE_H
#include <string>
// ROS
#include <ros/ros.h>
#include <ros/console.h>
#include <pattern_manager/GetTransformName.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_ros/bt_service_node.h>


namespace sysdesign { namespace bt {


class GetTransformName : public BT::RosServiceNode<pattern_manager::GetTransformName> {
private:
  const std::string LOGNAME = "GetTransformName";

public:

  GetTransformName(ros::NodeHandle &node, const std::string &name, const BT::NodeConfiguration &config)
  : BT::RosServiceNode<pattern_manager::GetTransformName>(node, name, config) { }

  static BT::PortsList providedPorts()
  {
    return
    {
      BT::InputPort<unsigned long>("transform_id"),
      BT::OutputPort<std::string>("transform_name")
    };
  }

  void sendRequest(pattern_manager::GetTransformName::Request &request) override
  {
    if (!getInput("transform_id", request.id))
    {
      throw BT::RuntimeError("missing required port [transform_id]");
    }
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "request.id: " << request.id);
  }

  BT::NodeStatus onResponse(const pattern_manager::GetTransformName::Response &response) override
  {
    if (!setOutput<std::string>("transform_name", response.name))
    {
      throw BT::RuntimeError("missing required port [transform_name]");
    }
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "response.name: " << response.name);

    if (!response.name.empty())
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
