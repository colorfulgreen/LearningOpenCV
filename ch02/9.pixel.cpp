#include <opencv2/opencv.hpp>

using namespace std;

void pixel(cv::Mat & img_rgb, cv::Mat & img_gry, cv::Mat & img_cny) {
    int x = 16, y = 32;
    cv::Mat img_pyr;
    cv::Vec3b intensity = img_rgb.at<cv::Vec3b>(y,x);

    uchar blue = intensity[0];
    uchar green = intensity[1];
    uchar red = intensity[2];

    std::cout << "At(x,y) = (" << x << ", " << y << "): (blue, green, red) = (" <<
        (unsigned int)blue << ", " << (unsigned int)green << ", " << (unsigned int)red << ")" 
        << endl;
    std::cout << "Gray pixel there is: " << (unsigned int)img_gry.at<uchar>(y,x) << std::endl;

    x /= 4; y /= 4;
    cv::pyrDown(img_gry, img_pyr);
    cv::pyrDown(img_pyr, img_pyr);
    std::cout << "Pyramid2 pixel there is: " << (unsigned int)img_pyr.at<uchar>(y,x) << std::endl;

    img_cny.at<uchar>(x,y) = 128;

}

int main(int argc, char** argv) {
    cv::Mat img_rgb, img_gry, img_cny;

    cv::namedWindow("Gray", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Canny", cv::WINDOW_AUTOSIZE);

    img_rgb = cv::imread(argv[1]);

    cv::cvtColor(img_rgb, img_gry, cv::COLOR_BGR2GRAY);
    cv::imshow("Gray", img_gry);

    cv::Canny(img_gry, img_cny, 60, 100, 3, true);

    pixel(img_rgb, img_gry, img_cny);

    cv::waitKey(0);
}
