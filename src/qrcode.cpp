#include <iostream>

#include <ros/ros.h>
#include <algorithm>
#include <vector>
#include <sensor_msgs/Image.h>
#include <zbar.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <sstream>
#include <string.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;
using namespace zbar;

class QR {

public:

	QR(){};

	~QR(){};
	
	Mat imageCb(const sensor_msgs::ImageConstPtr& msg);
	
	string decode(Mat &im);

};

Mat QR::imageCb(const sensor_msgs::ImageConstPtr& msg) {
	cv_bridge::CvImagePtr cv_ptr;
	cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

	return cv_ptr->image;
}

string QR::decode(Mat &im)
{

  ImageScanner scanner;

  scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 0);
  scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

  Mat imGray;
  cvtColor(im, imGray,CV_BGR2GRAY);

  Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

  int n = scanner.scan(image);
  string objData, resultado = "nenhum";

  int x[4], y[4];
  for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
  {
    objData = symbol->get_data();
    resultado = objData;

    // pegar os pontos dos cantos da bounding box
    // podemos assumir 4 pontos, pois estamos interessados apenas em qr code
    for(int i = 0; i < 4; i++) {
      x[i] = symbol->get_location_x(i);
      y[i] = symbol->get_location_y(i);
    }
 
  }

  // desenha a bounding box no qr code com dois pontos opostos
  cv::rectangle(im, cv::Point(x[0], y[0]), cv::Point(x[2], y[2]), Scalar(0, 255, 0), 3, cv::LINE_8);

  // escrever o resultado da leitura na imagem
  std::stringstream img_info;
  img_info << "Resultado: " << resultado;

  cv::putText(im, img_info.str(), cv::Point(25, 25), cv::FONT_HERSHEY_DUPLEX, 
                    1.0, CV_RGB(0, 255, 0), 2.0);

  // exibir a imagem
  cv::imshow("Camera do Drone", im);
  cv::waitKey(50);

  return objData;
}
