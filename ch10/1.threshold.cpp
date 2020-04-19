#include <opencv2/opencv.hpp>

using namespace std;

void sumRGB(const cv::Mat& src, cv::Mat& dst) {
    vector<cv::Mat> planes;
    cv::split(src, planes);

    cv::Mat b = planes[0], g = planes[1], r = planes[2], s;

    cv::addWeighted(r, 1./3, g, 1./3, 0.0, s);
    cv::addWeighted(s, 1, r, 1./3, 0.0, s);

    cv::threshold(s, dst, 150, 100, cv::THRESH_TRUNC);
}

int main(int argc, char** argv) {
    cv::Mat src = cv::imread(argv[1]), dst;
    if(src.empty()) {
        cout << "can not load " << argv[1] << endl;
        return -1;
    }

    sumRGB(src, dst);

    cv::imshow("Raw", src);
    cv::imshow("Thresh", dst);
    cv::waitKey(0);

    return 0;
}
