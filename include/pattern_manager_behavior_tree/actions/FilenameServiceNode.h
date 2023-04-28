#ifndef PATTERN_MANAGER_BEHAVIOR_TREE_FILENAME_SERVICE_NODE_H
#define PATTERN_MANAGER_BEHAVIOR_TREE_FILENAME_SERVICE_NODE_H
#include <string>
// ROS
#include <ros/ros.h>
#include <ros/console.h>
#include <pattern_manager/Filename.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_ros/bt_service_node.h>


namespace sysdesign { namespace bt {


class FilenameServiceNode : public BT::RosServiceNode<pattern_manager::Filename> {
private:
  const std::string LOGNAME = "FilenameServiceNode";

public:

  FilenameServiceNode(ros::NodeHandle &node, const std::string &name, const BT::NodeConfiguration &config)
  : BT::RosServiceNode<pattern_manager::Filename>(node, name, config) { }

  static BT::PortsList providedPorts()
  {
    return
    {
      BT::InputPort<std::string>("path"),
    };
  }

  void sendRequest(pattern_manager::Filename::Request &request) override
  {
    if (!getInput("path", request.path))
    {
      throw BT::RuntimeError("missing required port [path]");
    }
    ROS_DEBUG_STREAM_NAMED(LOGNAME, "request.path: " << request.path);
  }

  BT::NodeStatus onResponse(const pattern_manager::Filename::Response &response) override
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
