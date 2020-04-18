#include <opencv2/opencv.hpp>

using namespace std;

void meanStdDevTest(void) {
    cout << "\n/*** meanStdDev ***/" << endl;

    cv::Mat mat(10, 1, CV_32F);
    cv::Scalar mean, stddev;

    cv::randu(mat, 1, 100);
    cout << "mat: \n" << mat << endl;

    cv::meanStdDev(mat, mean, stddev);
    cout << "mean: \n" << mean << endl;
    cout << "stddev: \n" << stddev << endl;
}


void calcCovarMatrixTest(void) {
    cout << "\n/*** calcCovarMatrix ***/" << endl;

    float data[] = {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1};
    cv::Mat mat(3, 4, CV_32F, data);
    cout << "mat: \n" << mat << endl;

    cv::Mat covar, mean;
    calcCovarMatrix(mat, covar, mean, cv::COVAR_NORMAL + cv::COVAR_COLS + cv::COVAR_SCALE);
    cout << "mean: \n" << mean << endl;
    cout << "covariance: \n" << covar << endl;

    /* NOTE: scrambled covariance matrix - 用于 fast PCA(Principal Components Analysis)
       PCA 将协方差矩阵相似对角化(即转换成线性无关的特征)，特征值(对应方差)越大的特征包含越多信息.
     */
    calcCovarMatrix(mat, covar, mean, cv::COVAR_SCRAMBLED + cv::COVAR_COLS + cv::COVAR_SCALE);
    cout << "scrambled covariance: \n" << covar << endl;

}


void determinantTest(void) {
    cout << "\n/*** determinant ***/" << endl;

    float data[] = {1,0,0,0,2,0,0,0,3};
    cv::Mat mat(3, 3, CV_32F, data);
    cout << "mat:\n" << mat << endl;

    /* NOTE: 对于小矩阵直接使用特征值公式计算, 对于大矩阵使用高斯消元.

    https://en.wikipedia.org/wiki/Gaussian_elimination#Computing_determinants
    To explain how Gaussian elimination allows the computation of the determinant of a square matrix, we have to recall how the elementary row operations change the determinant:
    - Swapping two rows multiplies the determinant by −1
    - Multiplying a row by a nonzero scalar multiplies the determinant by the same scalar
    - Adding to one row a scalar multiple of another does not change the determinant.

    If Gaussian elimination applied to a square matrix A produces a row echelon matrix B, let d be the product of the scalars by which the determinant has been multiplied, using the above rules. Then the determinant of A is the quotient by d of the product of the elements of the diagonal of B.

    Computationally, for an n × n matrix, this method needs only O(n^3) arithmetic operations, while solving by elementary methods requires O(2^n) or O(n!) operations.
     */
    float r = cv::determinant(mat);
    cout << "determimant:\n" << r << endl;
}


void eigenTest(void) {
    cout << "\n/*** eigen ***/" << endl;

    float data[] = {3,1,0,1,5,3,0,3,2};
    cv::Mat mat(3, 3, CV_32F, data);
    cout << "mat:\n" << mat << endl;

    cv::Mat eigenvalues;
    cv::Mat eigenvectors;
    cv::eigen(mat, eigenvalues, eigenvectors);
    cout << "eigenvalues:\n" << eigenvalues << endl;
    cout << "eigenvectors:\n" << eigenvectors << endl;
}


int main(void) {
    meanStdDevTest();
    calcCovarMatrixTest();
    determinantTest();
    eigenTest();

    return 0;
}
