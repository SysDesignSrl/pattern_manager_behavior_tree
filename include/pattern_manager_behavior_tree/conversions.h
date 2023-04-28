#ifndef PATTERN_MANAGER_BEHAVIOR_TREE_CONVERSIONS_H
#define PATTERN_MANAGER_BEHAVIOR_TREE_CONVERSIONS_H
#include <string>
#include <vector>
// ROS
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>


namespace BT {


template <>
inline std::vector<float> convertFromString(StringView str)
{
  auto parts = splitString(str, ';');

  std::vector<float> output;
  for (int i = 0; i < parts.size(); i++)
  {
    output.push_back(convertFromString<float>(parts[i]));
  }
  return output;
}


template <>
inline std::vector<double> convertFromString(StringView str)
{
  auto parts = splitString(str, ';');

  std::vector<double> output;
  for (int i = 0; i < parts.size(); i++)
  {
    output.push_back(convertFromString<double>(parts[i]));
  }
  return output;
}


template <>
inline geometry_msgs::Vector3 convertFromString(StringView str)
{
  auto parts = splitString(str, ';');

  if (parts.size() != 3)
  {
      throw RuntimeError("invalid input)");
  }
  else
  {
    geometry_msgs::Vector3 vector;
    vector.x = convertFromString<double>(parts[0]);
    vector.y = convertFromString<double>(parts[1]);
    vector.z = convertFromString<double>(parts[2]);
    return vector;
  }
}

template <>
inline geometry_msgs::Pose convertFromString(StringView str)
{
  auto parts = splitString(str, ';');

  if (parts.size() != 7)
  {
      throw RuntimeError("invalid input)");
  }
  else
  {
    geometry_msgs::Pose pose;
    pose.position.x = convertFromString<double>(parts[0]);
    pose.position.y = convertFromString<double>(parts[1]);
    pose.position.z = convertFromString<double>(parts[2]);
    pose.orientation.x = convertFromString<double>(parts[3]);
    pose.orientation.y = convertFromString<double>(parts[4]);
    pose.orientation.z = convertFromString<double>(parts[5]);
    pose.orientation.w = convertFromString<double>(parts[6]);
    return pose;
  }
}


}  // namespace
#endif
