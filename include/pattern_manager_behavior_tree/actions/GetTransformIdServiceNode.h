#ifndef PATTERN_MANAGER_BEHAVIOR_TREE_GET_TRANSFORM_ID_SERVICE_NODE_H
#define PATTERN_MANAGER_BEHAVIOR_TREE_GET_TRANSFORM_ID_SERVICE_NODE_H
#include <string>
// ROS
#include <ros/ros.h>
#include <ros/console.h>
#include <pattern_manager/GetTransformId.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_ros/bt_service_node.h>


namespace sysdesign { namespace bt {


class GetTransformIdServiceNode : public BT::RosServiceNode<pattern_manager::GetTransformId> {
private:
  const std::string LOGNAME = "GetTransformIdServiceNode";

public:

  GetTransformIdServiceNode(ros::NodeHandle &node, const std::string &name, const BT::NodeConfiguration &config)
  : BT::RosServiceNode<pattern_manager::GetTransformId>(node, name, config) { }

  static BT::PortsList providedPorts()
  {
    return
    {
      BT::InputPort<std::string>("transform_name"),
      BT::OutputPort<unsigned long>("transform_id")
    };
  }

  void sendRequest(pattern_manager::GetTransformId::Request &request) override
  {
    if (!getInput("transform_name", request.name))
    {
      throw BT::RuntimeError("missing required port [transform_name]");
    }
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "request.name: " << request.name);
  }

  BT::NodeStatus onResponse(const pattern_manager::GetTransformId::Response &response) override
  {
    if (!setOutput<unsigned long>("transform_id", response.id))
    {
      throw BT::RuntimeError("missing required port [transform_id]");
    }
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "response.id: " << response.id);

    if (response.id != 0)
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
