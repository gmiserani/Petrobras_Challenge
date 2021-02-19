#include <iostream>
#include <ros/ros.h>
#include <mrs_msgs/ReferenceStamped.h>
#include <mrs_msgs/PositionCommand.h>
#include <std_msgs/String.h>

class Controle {

public:

	Controle();

	~Controle();

	void mudarPosicao(double x, double y, double z);
};

	Controle::Controle() {
		ROS_INFO("objeto criado");	
	}

	Controle::~Controle() {
		ROS_INFO("objeto destruido");
	}

	void Controle::mudarPosicao(double x, double y, double z) {

		ros::NodeHandle n;
		ros::Publisher pub = n.advertise<mrs_msgs::ReferenceStamped>("/uav1/control_manager/reference", 1000);

		mrs_msgs::ReferenceStamped pos;
		pos.reference.position.x = x;
		pos.reference.position.y = y;
		pos.reference.position.z = z;

		ros::Rate loop_rate(5);
		int count = 0;

		while(ros::ok()) {
	
			pub.publish(pos);
    
			ros::spinOnce();
			loop_rate.sleep();
    			count++;

    			if(count == 60) {

    				break; }}}
