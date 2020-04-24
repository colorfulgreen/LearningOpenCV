#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;

int main(void) {
    cv::Mat src, image;

    src = cv::imread("data/circle.jpeg", 1);

    cv::cvtColor(src, image, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(image, image, cv::Size(5,5), 0, 0);

    vector<cv::Vec3f> circles;
    cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT, 2, image.cols/20);
    cout << circles[0] << endl;

    for(size_t i = 0; i < circles.size(); ++i) {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        cv::circle(src, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
        cv::circle(src, center, radius, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }

    cv::imshow("Hough Circles", src);
    cv::waitKey(0);

    return 0;
}
