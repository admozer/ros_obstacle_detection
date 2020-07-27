#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
using namespace std;
//160201024 Adem ÖZER
class RobotMove
{
public:
    ros::NodeHandle nh;
    geometry_msgs::Twist value;
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    void Robotcallback(const sensor_msgs::LaserScan::ConstPtr &scan_msg);
};
void RobotMove::Robotcallback(const sensor_msgs::LaserScan::ConstPtr &scan_msg)
{
    ros::Rate rate(1);
    int arraysize = scan_msg->ranges.size();
    int middle = arraysize / 2;
    for (int i = 0; i < 1; ++i)
    {
        if (!std::isinf(scan_msg->ranges[i]) && scan_msg->ranges[i] <= 1.0)
        {
            if ((scan_msg->ranges[90]) > (scan_msg->ranges[3 * middle / 2]))
            {
                //left
                ROS_INFO("first 90 : %f", (scan_msg->ranges[middle / 2]));
                ROS_INFO("first 270 : %f", (scan_msg->ranges[3 * middle / 2]));
                value.angular.z = (middle / 2 * M_PI / middle);
                value.linear.x = 0.0;
                pub.publish(value);
                rate.sleep();
            }
            else
            {
                //right
                ROS_INFO("second 90 distance : %f", (scan_msg->ranges[middle / 2]));
                ROS_INFO("second 270 distance : %f", (scan_msg->ranges[3 * middle / 2]));
                value.angular.z = -((middle / 2) * M_PI / middle);
                value.linear.x = 0.0;
                pub.publish(value);
                rate.sleep();
            }
        }
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_move");

    ros::NodeHandle n;
    RobotMove robot_move;
    ros::Subscriber subscriber = n.subscribe("scan", 1, &RobotMove::Robotcallback, &robot_move);
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    geometry_msgs::Twist twist_value;
    ros::Rate rate(1);
    while (ros::ok())
    {
        ros::spinOnce();
        twist_value.angular.z = 0.0;
        twist_value.linear.x = 0.1;
        pub.publish(twist_value);
        rate.sleep();
    }

    return 0;
}