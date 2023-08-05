# 模块介绍
该模块是驱动层程序

## 适用项目

1. sjtu-移动机器人
2. sgmw-agv

## 开发与部署方法

本项目使用catkin_make进行编译。

建议您使用VS Code和devcontainer插件，以便在Docker容器中进行开发工作。这可以让您更轻松地配置和管理开发环境，并保持环境的一致性。

### 编译
1. catkin_make --source . 

说明：

catkin_make 的标准使用流程为，将package放置于src目录下，再workspace中使用catkin_make进行编译。但这种方法存在无法支持clangd 和 vscode cmaketool插件，导致开发效率低的问题。为了解决此问题，我们将在src下直接进行编译，因此需要指定当前路径为src路径，即使用 catkin_make --source .  进行编译。此时您可使用vscode 打开本项目，会自动支持clangd 和 vscode cmaketool插件。


### 部署

如果您需要将该程序部署到现场，请按照以下步骤操作：
1. 在成功编译的基础上，运行 catkin_make install --source . （请确保此时没有install文件夹，若有请删除）
2. 打包install文件，根据项目需求进行部署即可

## 模块

