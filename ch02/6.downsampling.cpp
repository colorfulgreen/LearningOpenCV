#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    cv::Mat img1, img2;

    cv::namedWindow("in", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("out", cv::WINDOW_AUTOSIZE);

    img1 = cv::imread(argv[1]);
    cv::imshow("in", img1);

    /* NOTE: use Gaussian blurring to downsample an image

    Downsampling is equivalent to convolving with a series of delta functions, which introduces 
    high frequencies into the result signal. When an image contains high-frequency content (fast 
    variations), downsampling can produce visually weird or annoying aliasing or moiré artifacts.

    To avoid this, we want to first run a high-pass(?) filter over the signal to band-limit its 
    frequencies so that they are all below the sampling frequency. TODO

    Sampling theorem: Band-limited function can be recovered completely from a set of its samples 
    if the samples are acquired at a rate exceeding twice the highest frequency content of the 
    function. Sampling must exceed the Nyquist rate.

    */
    cv::pyrDown(img1, img2);
    cv::imshow("out", img2);

    cv::waitKey(0);

    return 0;
}
