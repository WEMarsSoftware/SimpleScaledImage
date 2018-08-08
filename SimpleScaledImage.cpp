
// OpenCV includes
#include <opencv2/opencv.hpp>



int main(int argc, char **argv) {

		
	float depth;
	std::cout<<"Distance (depth) between images in meters: ";
	std::cin>>depth;

	float pixelRatio;
	std::string line;
	std::string::size_type sz;
	std::ifstream cf("calibration.txt");
	if (cf.is_open())
	{
		getline(cf, line); // get magic number
		pixelRatio = std::stof(line, &sz);
		cf.close();
	}

	else {
		std::cout << "\nError: missing calibration file.";
		return 0;
	}
		
	cv::Mat im1 = cv::imread(argv[1]);
	cv::Mat im2 = cv::imread(argv[2]);

	cv::Rect2d roi1 = cv::selectROI(im1);
	cv::Rect2d roi2 = cv::selectROI(im2);

		
	float r = 0.5*((roi2.width / roi1.width) + (roi2.height / roi1.height));

	float d = -r*depth / (1 - r);
	float objWidth = roi1.width * pixelRatio / d;
	float objHeight = roi1.height * pixelRatio / d;

	// Crop image
	//cv::Mat imCrop = im1(roi);
			
	char width[50], height[50];
	sprintf(width, "%.2fm", objWidth);
	sprintf(height, "%.2fm", objHeight);

	cv::putText(im1, width, cv::Point2f(roi1.x + roi1.width/4, roi1.y + roi1.height+50),CV_FONT_HERSHEY_SIMPLEX,1,cv::Scalar(255,0,0),2);							
	cv::putText(im1, height, cv::Point2f(roi1.x - 100, roi1.y+ roi1.height/2), CV_FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,0, 0), 2);
		
	std::cout << "\nEnter file name (without extension): ";
	std::string filename;
	std::cin >> filename;
	cv::imshow("Scaled image", im1);
	cv::imwrite(filename + ".png", im1);	
	std::cout << "\nImage saved as" << filename + ".png" << std::endl;

	while (cv::waitKey(0) != 27); //spin until esc is pressed
        
    return 0;
}
