#include<ros/ros.h>
#include<sensor_msgs/Joy.h>
#include<std_msgs/Float32MultiArray.h>

void joyCallback(const sensor_msgs::Joy::ConstPtr joy) {
    std_msgs::Float32MultiArray axes;
    axes.data.resize(2);
    ros::NodeHandle nh;
    ros::Publisher joy_pub = nh.advertise<std_msgs::Float32MultiArray>("motor_instructer", 100);

    ros::Rate loop_rate(10);
    while(ros::ok()) {
        for(int i = 0; i <= 1; i++){
            if(joy->axes[i] > 0.3 || joy->axes[i] < -0.3){
                axes.data[i] = joy->axes[i];
            }
        }
        joy_pub.publish(axes);
        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "EnterZen_joy");
    ros::NodeHandle nh;
    ros::Subscriber joy_sub = nh.subscribe<sensor_msgs::Joy>("joy", 10, &joyCallback);
    ros::spin();

    return 0;
}