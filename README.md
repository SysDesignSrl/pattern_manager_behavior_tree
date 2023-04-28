# SysDesign / Pattern Manager - BehaviorTree

## Overview 
This package contains the BehaviorTree nodes to call the services advertised by the PatternManager node.

## Continuous Integration
| Branch | Status |
| ------ | ------ |
| main   | [![CI](https://github.com/SysDesignSrl/pattern_manager_behavior_tree/actions/workflows/ci.yaml/badge.svg)](https://github.com/SysDesignSrl/pattern_manager_behavior_tree/actions/workflows/ci.yaml) |

## BT Actions

### Filename
##### Input
- **path**: The path to the fila containing the pattern configuration to load.

### GetCurrentId
##### Output
- **transform_id**: The current transform id.
- **transform_name**: The current transform name.

### GetTransformId
##### Input
- **transform_name**: The name of the requested transform id.
##### Output
- **transform_id**: The requested transform id.

### SetActive
##### Input
- **transform_id**: The id of the transform to enable/disable.
- **active**: Enable/Disable the relative transform id.

### Trigger