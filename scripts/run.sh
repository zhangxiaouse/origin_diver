#!/bin/bash

# 获取当前脚本的上级目录路径
scripts_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ws_path="$(dirname "$scripts_path")"

print_usage() {
    echo "使用方法:"
    echo "-h, --help            显示帮助信息"
    echo "--run_sjtuagv         启动松灵机器人底盘"
    echo "--run_sgmwagv         启动SGMW-AGV机器人底盘"
    echo "  mapping_driver      所选模式下启动 建图程序驱动"
    echo "  localization_driver 所选模式下启动 定位程序驱动"
}

run_sjtuagv() {
    source $ws_path/devel/setup.bash
    mode=$1
    case $mode in
        "mapping_driver")
            echo "在线模式：启动 getGNSS ..."
            gnome-terminal \
            --tab --title "get_gnss" -e 'bash -c "sleep 2;roslaunch livox_ros_driver2 msg_MID360.launch; exec bash;"' \
            --tab --title "get_gnss" -e 'bash -c "sleep 2;roslaunch chassis tracer.launch; exec bash;"' 
            ;;
        "localization_driver")
            echo "在线模式：启动 pointcloudMap ..."
            gnome-terminal \
            --tab --title "get_gnss" -e 'bash -c "sleep 2;roslaunch livox_ros_driver2 rviz_MID360.launch; exec bash;"' \
            --tab --title "get_gnss" -e 'bash -c "sleep 2;roslaunch chassis tracer.launch; exec bash;"' 
            ;;
        *)
            echo "无效的参数。使用 -h 或 --help 查看帮助信息。"
            read -p "按任意键继续..."
            exit 1
            ;;
    esac
}

run_sgmwagv() {
    source $ws_path/devel/setup.bash
    mode=$1
    case $mode in
        "mapping_driver")
            echo "在线模式：启动 getGNSS ..."
            gnome-terminal \
            --tab --title "get_gnss" -e 'bash -c "sleep 2;roslaunch livox_ros_driver2 msg_MID360.launch; exec bash;"' \
            --tab --title "get_gnss" -e 'bash -c "sleep 2;roslaunch serial_rs232 serial_pub_sub.launch; exec bash;"' 
            ;;
        "localization_driver")
            echo "在线模式：启动 pointcloudMap ..."
            gnome-terminal \
            --tab --title "get_gnss" -e 'bash -c "sleep 2;roslaunch livox_ros_driver2 rviz_MID360.launch; exec bash;"' \
            --tab --title "get_gnss" -e 'bash -c "sleep 2;roslaunch serial_rs232 serial_pub_sub.launch; exec bash;"' 
            ;;
        *)
            echo "无效的参数。使用 -h 或 --help 查看帮助信息。"
            read -p "按任意键继续..."
            exit 1
            ;;
    esac
}

if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    print_usage
    read -p "按任意键继续..."
    exit 0
fi

# 检查输入参数并执行相应的脚本
case "$1" in
    "--run_sjtuagv")
        if [[ -z "$2" ]]; then
            echo "缺少参数。使用 -h 或 --help 查看帮助信息。"
            read -p "按任意键继续..."
            exit 1
        fi
        run_online "$2"
        ;;
    "--run_sgmwagv")
        if [[ -z "$2" ]]; then
            echo "缺少参数。使用 -h 或 --help 查看帮助信息。"
            read -p "按任意键继续..."
            exit 1
        fi
        run_offline "$2"
        ;;
    *)
        echo "无效的参数。使用 -h 或 --help 查看帮助信息。"
        read -p "按任意键继续..."
        exit 1
        ;;
esac