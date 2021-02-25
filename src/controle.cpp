#include <iostream>
#include <sstream>
#include <ros/ros.h>
#include <mrs_msgs/ReferenceStamped.h>
#include <mrs_msgs/PositionCommand.h>
#include <std_msgs/String.h>
#include <gazebo_ros_link_attacher/Attach.h>
#include "gazebo_ros_link_attacher/AttachRequest.h"
#include "gazebo_ros_link_attacher/AttachResponse.h"
using namespace std;

class Controle {

public:

  Controle();

  ~Controle();

  void mudarPosicao(double x, double y, double z);
  void attach(string model2, string link2);
  void detach(string base, string model2, string link2);
  void Landing(double z);

};

Controle::Controle() {}

Controle::~Controle(){}

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

    if(count == 70) break; }}

void Controle::attach(string model2, string link2) {

  ros::NodeHandle n;

  ros::ServiceClient a_client = n.serviceClient<gazebo_ros_link_attacher::Attach>("link_attacher_node/attach");

  gazebo_ros_link_attacher::Attach attach_srv;

  attach_srv.request.model_name_1 = "uav1";
  attach_srv.request.link_name_1 = "base_link";

  attach_srv.request.model_name_2 = model2;
  attach_srv.request.link_name_2 = link2;

  ROS_INFO("Pegando a Caixa");

  a_client.call(attach_srv);

}

void Controle::detach(string base, string model2, string link2) {

  ros::NodeHandle n;

  ros::ServiceClient d_client = n.serviceClient<gazebo_ros_link_attacher::Attach>("link_attacher_node/detach");

  gazebo_ros_link_attacher::Attach detach_srv;

  detach_srv.request.model_name_1 = "uav1";
  detach_srv.request.link_name_1 = "base_link";

  detach_srv.request.model_name_2 = model2;
  detach_srv.request.link_name_2 = link2;

  if(base == "A") {

    mudarPosicao(3.2, 0.0, 2.4);
    mudarPosicao(3.2, 0.0, 1.0);

	ROS_INFO("Soltando a Caixa");

    d_client.call(detach_srv);

  } else if(base == "B") {
  
    mudarPosicao(4.0, -2.0, 2.0);
    mudarPosicao(4.0, -2.0, 0.5);

	ROS_INFO("Soltando a Caixa");

    d_client.call(detach_srv);
    mudarPosicao(4.0, -2.0, 2.0);

  } else {

    mudarPosicao(5.0, -1.0, 2.0);
    mudarPosicao(5.0, -1.0, 0.5);

	ROS_INFO("Soltando a Caixa");

    d_client.call(detach_srv);
    mudarPosicao(5.0, -1.0, 2.0);
  }
}

void Controle::Landing(double z){

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<mrs_msgs::ReferenceStamped>("/uav1/control_manager/reference", 1000);

  mrs_msgs::ReferenceStamped pos;

  pos.reference.position.z = z;

  ros::Rate loop_rate(5);

  int count = 0;

  while(ros::ok()) {
	
    pub.publish(pos);
    
    ros::spinOnce();
    loop_rate.sleep();

    ++count;

    if(count == 70) break; }}