#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"

int main(int argc, char **argv) {
	
	cv::VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    // Loop until 'q' is pressed
    char key = ' ';
    while (key != 'q') {
		
		cv::Mat im;
		cap >> im;
		cv::imshow("Video stream", im);
		
		
		if (key == 'x') {
			std::cout << "Object distance (m): ";
			float dist;
			std::cin>>dist;
			
			cv::Rect2d roi = cv::selectROI(im);

			std::cout << "\nWidth: " << roi.width << ", height: " << roi.height << "\n";
		}

		
		// Handle key event
		key = cv::waitKey(10);        
    }
    return 0;
}

