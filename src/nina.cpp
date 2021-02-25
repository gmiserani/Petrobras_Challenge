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
using namespace std;

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

  Controle *ctrl = new Controle();

  // vai até a posição da primeira caixa 

  ctrl->mudarPosicao(4.0, -2.0, 2.0);
  ctrl->mudarPosicao(4.0, -2.0, 0.4);

  ctrl->attach("equipmentA", "link_A");

  ctrl->mudarPosicao(4.0, -2.0, 2.0);

  // compara a string lida pelo qrcode e solta a caixa na base correspondente

  ctrl->detach(base, "equipmentA", "link_A");

  // vai até a posição da segunda caixa 

  ctrl->mudarPosicao(5.0, -1.0, 2.0);
  ctrl->mudarPosicao(5.0, -1.0, 0.4);

  ctrl->attach("equipmentB", "link_B");

  ctrl->mudarPosicao(5.0, -1.0, 2.0);

  // compara a string lida pelo qrcode e solta a caixa na base correspondente

  ctrl->detach(base, "equipmentB", "link_B");

  // vai até a posição da terceira caixa

  ctrl->mudarPosicao(6.0, -0.2, 2.0);
  ctrl->mudarPosicao(6.0, -0.2, 0.4);

  ctrl->attach("equipmentC", "link_C");

  ctrl->mudarPosicao(6.0, -0.2, 2.0);

  // compara a string lida pelo qrcode e solta a caixa na base correspondente

  ctrl->detach(base, "equipmentC", "link_C");

  // retorna para a base inicial e pousa

  ctrl->mudarPosicao(0.0, 0.0, 2.0);

  return 0;

}