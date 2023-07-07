#ifndef PATTERN_MANAGER_BEHAVIOR_TREE_GET_TRANSFORM_PARAMS_SERVICE_NODE_H
#define PATTERN_MANAGER_BEHAVIOR_TREE_GET_TRANSFORM_PARAMS_SERVICE_NODE_H
#include <string>
// ROS
#include <ros/ros.h>
#include <ros/console.h>
#include <pattern_manager/Params.h>
#include <pattern_manager/GetTransformParams.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_ros/bt_service_node.h>


namespace sysdesign { namespace bt {


class GetTransformParams : public BT::RosServiceNode<pattern_manager::GetTransformParams> {
private:
  const std::string LOGNAME = "GetTransformParams";

public:

  GetTransformParams(ros::NodeHandle &node, const std::string &name, const BT::NodeConfiguration &config)
  : BT::RosServiceNode<pattern_manager::GetTransformParams>(node, name, config) { }

  static BT::PortsList providedPorts()
  {
    return
    {
      BT::InputPort<unsigned long>("transform_id"),
      BT::OutputPort<std::string>("transform_name"),
      BT::OutputPort<unsigned long>("parent_id"),
      BT::OutputPort<std::string>("ref_frame"),
      BT::OutputPort<unsigned long>("id"),
      BT::OutputPort<bool>("active")
    };
  }

  void sendRequest(pattern_manager::GetTransformParams::Request &request) override
  {
    if (!getInput("transform_id", request.id))
    {
      throw BT::RuntimeError("missing required port [transform_id]");
    }
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "request.id: " << request.id);
  }

  BT::NodeStatus onResponse(const pattern_manager::GetTransformParams::Response &response) override
  {
    setOutput<std::string>("transform_name", response.params.name);
    setOutput<unsigned long>("parent_id", response.params.parent_id);
    setOutput<std::string>("ref_frame", response.params.ref_frame);
    setOutput<unsigned long>("id", response.params.id);
    setOutput<bool>("active", response.params.active);

    ROS_DEBUG_STREAM_NAMED(LOGNAME, "transform_name: " << response.params.name);
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "parent_id: " << response.params.parent_id);
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "ref_frame: " << response.params.ref_frame);
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "id: " << response.params.id);
    ROS_DEBUG_NAMED(LOGNAME, "active: %s", (response.params.active) ? "True" : "False");

    return BT::NodeStatus::SUCCESS;
  }

};

} }  // namespace
#endif
