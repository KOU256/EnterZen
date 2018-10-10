/* ヘッダファイルのインクルード */
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Float32MultiArray.h>
#include "EnterZen_joy/EnterZen_joy.hpp"

/* joyトピックからメッセージを受け取ったときに呼び出される関数 */
void joyCallback(const sensor_msgs::Joy::ConstPtr joy) {
    std_msgs::Float32MultiArray axes;
    ros::NodeHandle nh;
    ros::Publisher joy_pub = nh.advertise<std_msgs::Float32MultiArray>("motor_instructer", 100);

    axes.data.resize(2);
    ros::Rate loop_rate(10);

    while(ros::ok()) {
        for(EAxes index : {LEFT_STICK_HOR, LEFT_STICK_VER}){
            if(joy->axes[index] > 0.3 || joy->axes[index] < -0.3){
                axes.data[index] = joy->axes[index];
            }
        }
        
        joy_pub.publish(axes);
        ros::spinOnce();
        loop_rate.sleep();
    }
}

/* メイン関数 */
int main(int argc, char** argv) {
    ros::init(argc, argv, "EnterZen_joy");
    ros::NodeHandle nh;
    ros::Subscriber joy_sub = nh.subscribe<sensor_msgs::Joy>("joy", 10, &joyCallback);
    ros::spin();

    return 0;
}