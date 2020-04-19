#include <opencv2/opencv.hpp>

using namespace std;

// 100 1 9 30 10 data/whiterose.jpg
int main(int argc, char** argv) {
    double fixed_threshold = (double)atof(argv[1]);
    int threshold_type = atoi(argv[2]) ? cv::THRESH_BINARY : cv::THRESH_BINARY_INV;
    int adaptive_method = atoi(argv[3]) ? cv::ADAPTIVE_THRESH_MEAN_C
                                        : cv::ADAPTIVE_THRESH_GAUSSIAN_C;
    int block_size = atoi(argv[4]);
    double offset = (double)atof(argv[5]);

    cv::Mat Igray = cv::imread(argv[6], cv::IMREAD_GRAYSCALE);
    if(Igray.empty()) {
        cout << "can not load " << argv[6] << endl;
        return -1;
    }

    cv::Mat It, Iat;
    cv::threshold(Igray, It, fixed_threshold, 255, threshold_type);
    cv::adaptiveThreshold(Igray, Iat, 255, adaptive_method, threshold_type, block_size, offset);

    cv::imshow("Raw", Igray);
    cv::imshow("Threshold", It);
    cv::imshow("Adaptive Threshold", Iat);
    cv::waitKey(0);
}
