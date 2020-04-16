#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    cv::Mat img_rgb, img_gry, img_cny;

    cv::namedWindow("Gray", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Canny", cv::WINDOW_AUTOSIZE);

    img_rgb = cv::imread(argv[1]);

    cv::cvtColor(img_rgb, img_gry, cv::COLOR_BGR2GRAY);
    cv::imshow("Gray", img_gry);


    /* NOTE: Canny edge detection algorithm
       1. Smooth the input image with a Gaussian filter.
       2. Compute the gradient magnitude and angle images.
       3. Apply nonmaxima suppression to the gradient magnitude image.
       4. Use double thresholding and connectivity analysis to detect and link edges.
     */
    cv::Canny(img_gry, img_cny, 60, 100, 3, true);
    cv::imshow("Canny", img_cny);

    cv::waitKey(0);
}
