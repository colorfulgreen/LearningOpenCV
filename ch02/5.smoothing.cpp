#include <opencv2/opencv.hpp>

void smoothing(const cv::Mat & image) {
    cv::namedWindow("in", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("out", cv::WINDOW_AUTOSIZE);

    cv::imshow("in", image);

    cv::Mat out;

    // NOTE: Spatial Domain Filtering 
    cv::GaussianBlur(image, out, cv::Size(5,5), 3, 3);
    cv::GaussianBlur(out, out, cv::Size(5,5), 3, 3);

    // NOTE: Frequency Domain Filtering
    // High frequencies are caused by sharp transitions in intensity. Therefore, a filter that
    // attenuates high frequencies while passing low frequencies would blur an image.

    cv::imshow("out", out);

    cv::waitKey(0);
}

int main(int argc, char** argv) {
    cv::Mat img = cv::imread(argv[1], -1);
    smoothing(img);
    return 0;
}
