#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    cv::Mat src = cv::imread(argv[1], 1);
    if(src.empty()) {cout << "Cannot load " << argv[1] << endl; return -1;}

    cv::Mat dst(src.size(), src.type()), src2(src.size(), src.type());

    for(int i=1; i<=10; i++) {
        double M = i * 10;
        cv::logPolar(src, dst, 
                     cv::Point2f(src.cols*0.5f, src.rows*0.5f), // Center of transform 
                     M,                                      // Scale factor
                     cv::INTER_LINEAR | cv::WARP_FILL_OUTLIERS);
        cv::imshow("log-polar scale=" + to_string(i*10), dst);

        cv::logPolar(dst, src2, cv::Point2f(src.cols*0.5f, src.rows*0.5f), M,
                     cv::INTER_LINEAR | cv::WARP_INVERSE_MAP);

        cv::imshow("inverse log-polar scale=" + to_string(i*10), src2);

    }

    cv::waitKey();

    return 0;
}
