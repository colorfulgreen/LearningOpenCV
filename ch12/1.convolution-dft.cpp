#include <opencv2/opencv.hpp>

using namespace std;


int main(int argc, char** argv) {
    cv::Mat A = cv::imread("data/convolution.jpeg", 0);

    cv::Size patchSize(250, 400);
    cv::Point topleft(770, 370);
    cv::Rect roi(topleft.x, topleft.y, patchSize.width, patchSize.height);
    cv::Mat B = A(roi);

    int dft_M = cv::getOptimalDFTSize(A.rows + B.rows - 1);
    int dft_N = cv::getOptimalDFTSize(A.cols + B.cols - 1);
    cout << "ImageSize: " << A.size() << endl;
    cout << "DFT Size: " << dft_N << " x " << dft_M << endl;

    cv::Mat dft_A = cv::Mat::zeros(dft_M, dft_N, CV_32F);
    cv::Mat dft_B = cv::Mat::zeros(dft_M, dft_N, CV_32F);

    // dft_A_part 和 dft_A 共用同一份内存？ 
    cv::Mat dft_A_part = dft_A(cv::Rect(0, 0, A.cols, A.rows));
    cv::Mat dft_B_part = dft_B(cv::Rect(0, 0, B.cols, B.rows)); 
    cout << "DFT Part Size: " << dft_A_part.size() << ", " << dft_B_part.size() << " Type: " << dft_A_part.type() << endl;

    // 得到 A, B 减去均值的二值图像
    A.convertTo(dft_A_part, dft_A_part.type(), 1, -mean(A)[0]);
    B.convertTo(dft_B_part, dft_B_part.type(), 1, -mean(B)[0]);

    cv::dft(dft_A, dft_A, 0, A.rows);
    cv::dft(dft_B, dft_B, 0, B.rows);
    cv::imshow("dft_A", dft_A);
    cv::imshow("dft_B", dft_B);
    cv::waitKey();

    // set the last parameter to false to compute convolution instead of correlation
    cv::mulSpectrums(dft_A, dft_B, dft_A, 0, false);
    cv::idft(dft_A, dft_A, cv::DFT_SCALE, A.rows + B.rows - 1);

    cv::Mat corr = dft_A(cv::Rect(0, 0, A.cols + B.cols - 1, A.rows + B.rows - 1));
    cv::normalize(corr, corr, 0, 1, cv::NORM_MINMAX, corr.type());

    B ^= cv::Scalar::all(255);

    cv::imshow("Image", A);
    cv::imshow("Mask", B);
    cv::imshow("Correlation", corr);
    cv::waitKey();

    return 0;
}
