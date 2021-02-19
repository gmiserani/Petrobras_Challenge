#include <iostream>
#include <ros/ros.h>
#include <ros/time.h>
#include <ros/duration.h>
#include <mrs_msgs/ReferenceStamped.h>
#include <mrs_msgs/PositionCommand.h>
#include <gazebo_ros_link_attacher/Attach.h>
#include "gazebo_ros_link_attacher/AttachRequest.h"
#include "gazebo_ros_link_attacher/AttachResponse.h"
#include "controle.cpp"
#include "qrcode.cpp"
#include <sstream>
#include <string.h>

string base = "";

void callback(const sensor_msgs::ImageConstPtr& msg) {
  QR *qr = new QR();
  Mat im = qr->imageCb(msg);
  base = qr->decode(im);
  delete qr;
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "Nina");

  ros::NodeHandle n;
  
  ros::Subscriber sub = n.subscribe("/uav1/bluefox_optflow/image_raw", 10, callback);

  ros::ServiceClient a_client = n.serviceClient<gazebo_ros_link_attacher::Attach>("link_attacher_node/attach");

  ros::ServiceClient d_client = n.serviceClient<gazebo_ros_link_attacher::Attach>("link_attacher_node/detach");

	gazebo_ros_link_attacher::Attach attach_srv;
	gazebo_ros_link_attacher::Attach detach_srv;

	attach_srv.request.model_name_1 = "uav1";
	attach_srv.request.link_name_1 = "base_link";

  detach_srv.request.model_name_1 = "uav1";
	detach_srv.request.link_name_1 = "base_link";

	Controle *ctrl = new Controle();

	ctrl->mudarPosicao(4.0, -2.0, 2.0);
	ctrl->mudarPosicao(4.0, -2.0, 0.4);

	attach_srv.request.model_name_2 = "equipmentA";
	attach_srv.request.link_name_2 = "link_A";
  detach_srv.request.model_name_2 = "equipmentA";
	detach_srv.request.link_name_2 = "link_A";

	a_client.call(attach_srv);

  ctrl->mudarPosicao(4.0, -2.0, 2.0);

  if(base == "A") {

	  ctrl->mudarPosicao(3.2, 0.0, 2.4);
    ctrl->mudarPosicao(3.2, 0.0, 1.0);
	  d_client.call(detach_srv);

  } else if(base == "B") {
  
    ctrl->mudarPosicao(4.0, -2.0, 2.0);
  	ctrl->mudarPosicao(4.0, -2.0, 0.5);
    d_client.call(detach_srv);
    ctrl->mudarPosicao(4.0, -2.0, 2.0);
    
  } else {

    ctrl->mudarPosicao(5.0, -1.0, 2.0);
    ctrl->mudarPosicao(5.0, -1.0, 0.5);
    d_client.call(detach_srv);
    ctrl->mudarPosicao(5.0, -1.0, 2.0);
    
  }

  ctrl->mudarPosicao(5.0, -1.0, 2.0);
  ctrl->mudarPosicao(5.0, -1.0, 0.4);

  attach_srv.request.model_name_2 = "equipmentB";
	attach_srv.request.link_name_2 = "link_B";
  detach_srv.request.model_name_2 = "equipmentB";
	detach_srv.request.link_name_2 = "link_B";

	a_client.call(attach_srv);

  ctrl->mudarPosicao(5.0, -1.0, 2.0);

  if(base == "A") {

	  ctrl->mudarPosicao(3.2, 0.0, 2.4);
	  ctrl->mudarPosicao(3.2, 0.0, 1.0);
	  d_client.call(detach_srv);

  } else if(base == "B") {
  
    ctrl->mudarPosicao(4.0, -2.0, 2.0);
  	ctrl->mudarPosicao(4.0, -2.0, 0.5);
    d_client.call(detach_srv);
    ctrl->mudarPosicao(4.0, -2.0, 2.0);
    
  } else {

    ctrl->mudarPosicao(5.0, -1.0, 2.0);
    ctrl->mudarPosicao(5.0, -1.0, 0.5);
    d_client.call(detach_srv);
    ctrl->mudarPosicao(5.0, -1.0, 2.0);
    
  }

  ctrl->mudarPosicao(6.0, -0.2, 2.0);
  ctrl->mudarPosicao(6.0, -0.2, 0.4);

  attach_srv.request.model_name_2 = "equipmentC";
	attach_srv.request.link_name_2 = "link_C";
  detach_srv.request.model_name_2 = "equipmentC";
	detach_srv.request.link_name_2 = "link_C";

	a_client.call(attach_srv);

  ctrl->mudarPosicao(6.0, -0.2, 2.0);

  if(base == "A") {

	  ctrl->mudarPosicao(3.2, 0.0, 2.4);
	  ctrl->mudarPosicao(3.2, 0.0, 1.0);
	  d_client.call(detach_srv);

  } else if(base == "B") {
  
    ctrl->mudarPosicao(4.0, -2.0, 2.0);
  	ctrl->mudarPosicao(4.0, -2.0, 0.5);
    d_client.call(detach_srv);
    ctrl->mudarPosicao(4.0, -2.0, 2.0);
    
  } else {

    ctrl->mudarPosicao(5.0, -1.0, 2.0);
    ctrl->mudarPosicao(5.0, -1.0, 0.5);
    d_client.call(detach_srv);
    ctrl->mudarPosicao(5.0, -1.0, 2.0);
    
  }

  ctrl->mudarPosicao(0.0, 0.0, 2.0);

	return 0;
}
