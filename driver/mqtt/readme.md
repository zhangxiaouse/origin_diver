sudo apt install libmosquittopp-dev

------
### ros-发布:
1. mqtt节点发布：设置 上料点位置topic，数据范围为 1-14；
    pub_work_positions_ = nh_.advertise<std_msgs::Int8MultiArray>("/mqtt/fork/positions", 1);  
2. mqtt节点发布：设置下料点位置topic，数据范围为1-14；
    pub_work_unfork_positions_ = nh_.advertise<std_msgs::Int8MultiArray>("/mqtt/fork/unfork_positions", 1);  
3. mqtt节点发布：通过web控制叉车功能
    pub_cmd_from_mqtt        = nh_.advertise<std_msgs::Int32>("/mqtt/cmd", 1); 
    1：云端留用作为连接车辆使用；2：启动；3：停止；4：暂停；5:重置；6：重规划；
4. mqtt节点发布：通过mqtt响应上货指令
    pub_upload_task_= nh_.advertise<std_msgs::Bool>("/mqtt/fork/upload_task", 1);  
    true：上货；false:默认。
    


------
### ros-订阅:
1. mqtt节点订阅：叉车完成上料任务；
    sub_upload_task_done = nh_.subscribe("/mqtt/fork/upload_task/done",5, &ForkMqtt::uploadTaskCompleteCallback, this);
    std_msgs:Bool : true:完成任务；其他：默认无效。
------
### mqtt-订阅:
1. mqtt节点订阅：云端留用作为连接车辆使用；2：启动；3：停止；4：暂停；5:重置；6：重规划；
    iot_client->subscribe(NULL, "/request_fork_control");
2. mqtt节点订阅：无人物流车发送的申请上料请求
    iot_client->subscribe(NULL, "/001/request_upload_goods/0001/0001/0001/01/0001");
    /版本号/request_upload_goods/路线编号/物流车编号/站点编号/货物种类/任务号
------
### mqtt-发布:
1.    心跳
         json_object["count"]       = count;
        json_object["vehicle"]       = "5003";
        json_object["online"]       = "0";
        iot_client->publish_data("/heart/5003",json_object );
2. 任务完成
        Json::Value json_object;
        json_object["vehicle"]       = "5003";
        json_object["upload_task_done"]       = "1";
        iot_client->publish_data("/001/upload_goods_complete/0001/0001/0001/01/0001",json_object );

