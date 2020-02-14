#include <ros/ros.h>
#include <geometory_msgs/Twist.h> //tutlesimはgeometory_msgs::Twist型のTopicを受け取る
#include <sensor_msgs/Joy.h> //joystick_msgを受け取るため

class TeleopTurtle{
    public:
        TeleopTurtle();

    private:
        void  joyCallback(const sensor_msgs::Joy::ConstPtr& joy_): //sensor...Ptrが型で&をつけることで参照渡しにしている

        ros::NodeHandle nh_; //privateに_をお尻につける

        int linear_, angular_;
        double l_scale_, a_scale_;
        ros::Publisher vel_pub_;
        ros::Subscriber joy_sub_;

};

TeleopTurtle::TeleopTurtle(): linear_(1), angular_(2) { //コンストラクタの記法　lenear_を1，angular_を2尼初期化している
    nh_.param("axis_linear", linear_, linear_);
    nh_.param("axis_angular", angular_, angular_);
    nh_.paran("scale_angular", a_scale_, a_scale_);
    nh_.param("scale_linear", l_scale_, l_scale_);


    vel_pub_ = nh_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);

    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopTurtle::joyCallback, this);
}


void TeleopTurtle::joyCallback(const sensor_msgs::Joy::ConstPtr &joy) {
    geometry_msgs::Twist twist;
    twist.angular.z = a_scale_*joy->axes[angular_];
    twist.linear.x = l_scale_*joy->axes[linear_];
    vel_pub_.publish(twist);
}


int main() {
    ros::init(argc,argv, "teleop_turtle");
    TeleopTurtle teleop_turtle;


    ros::spin();
}
