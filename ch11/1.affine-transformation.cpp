#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    cv::Mat src = cv::imread(argv[1], 1);
    if(src.empty()) { cout << "Cannot load " << argv[1] << endl; return -1; }

    cv::Point2f srcTri[] = {
        cv::Point2f(0, 0), // top left
        cv::Point2f(src.cols-1, 0), // top right
        cv::Point2f(0, src.rows-1) // bottom left
    };
    cv::Point2f dstTri[] = {
        cv::Point2f(src.cols*0.f, src.rows*0.33f),
        cv::Point2f(src.cols*0.85f, src.rows*0.25f),
        cv::Point2f(src.cols*0.15f, src.rows*0.7f)
    };

    cv::Mat warpMat = cv::getAffineTransform(srcTri, dstTri);
    cv::Mat dst;
    cv::warpAffine(src, dst, warpMat, src.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
    for(int i = 0; i < 3; ++i)
        cv::circle(dst, dstTri[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);

    cout << 2 << endl;
    cv::imshow("Affine Transform Test", dst);
    cv::waitKey();

    for(int frame = 0; ; ++frame) {
        // compute rotation matrix
        cv::Point2f center(src.cols*0.5f, src.rows*0.5f);
        double angle = frame * 3 % 360, 
               scale = (cos((angle - 0) * CV_PI / 180)) * 0.8;
        cv::Mat rotMat = cv::getRotationMatrix2D(center, angle, scale);
        cv::warpAffine(src, dst, rotMat, src.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
        cv::imshow("Rotate Image", dst);
        if(cv::waitKey(30) >= 0)
            break;
    }

    return 0;
}
