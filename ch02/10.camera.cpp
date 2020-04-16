#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    cv::namedWindow("camera", cv::WINDOW_AUTOSIZE);

    cv::VideoCapture cap;
    if(argc == 1) {
        cap.open(0); // open the first camera
    } else {
        cap.open(argv[1]);
    }
    if( !cap.isOpened() ) {
        cerr << "Couldn't open capture." << endl;
        return -1;
    }

    cv::Mat frame;
    for(;;) {
        cap >> frame;
        if( frame.empty() ) break;     // Ran out of film
        cv::imshow( "camera", frame );
        if(cv::waitKey(33) >= 0) break;
    }

    return 0;

}
