#include <ros/ros.h>
#include <geometry_msgs/Twist.h> //tutlesimはgeometory_msgs::Twist型のTopicを受け取るため
#include <sensor_msgs/Joy.h> //joystick_msgを扱うため

class turtle_operate{
    public:
        turtle_operate();

    private:
        void callback(const sensor_msgs::Joy::ConstPtr &joy);

        ros::NodeHandle nh;
        ros::Publisher pub;
        ros::Subscriber sub;
};

turtle_operate::turtle_operate(){
//turtleがSubscribeしているTopicにPublishする
    pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
//Joy_nodeがPublishするTopicにSubscribeする
    sub = nh.subscribe<sensor_msgs::Joy>("joy", 10, &turtle_operate::callback,this);

}

//callbackでJoy_nodeからのmessageをTwistに変換してPublishする
void turtle_operate::callback(const sensor_msgs::Joy::ConstPtr &joy) {
    geometry_msgs::Twist twist;
    twist.angular.z = joy->axes[3]; //axes[3]が右スティックの左右方向
    twist.linear.x = joy->axes[1]; //axes[1]が左スティックの前後方向
    pub.publish(twist);

}


int main(int argc, char** argv) {
    ros::init(argc,argv, "turtlesim_joy");
    turtle_operate turtle_operate;

    ros::spin();
}
