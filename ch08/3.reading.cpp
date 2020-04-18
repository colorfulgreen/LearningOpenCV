#include <opencv2/opencv.hpp>
#include <time.h>

using namespace std;

int main(int, char** argv) {
    cv::FileStorage fs("data/test.yml", cv::FileStorage::READ);

    // (type) operator on FileNode
    int frameCount = (int)fs["frameCount"];

    // cv::FileNode::operator >>
    std::string date;
    fs["calibrationDate"] >> date;

    cv::Mat cameraMatrix, distCoeffs;
    fs["cameraMatrix"] >> cameraMatrix;
    fs["distCoeffs"] >> distCoeffs;

    cout << "frame count: " << frameCount << endl
         << "calibration date: " << date << endl
         << "camera matrix: " << cameraMatrix << endl
         << "distortion coeffs: " << distCoeffs << endl;

    cv::FileNode features = fs["features"];
    cv::FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    std::vector<uchar> lbpval;
    for(; it != it_end; ++it, idx++) {
        cout << "feature #" << idx << ": ";
        cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";

        // easily read numerical arrays using FileNode >> std::vector
        (*it)["lbp"] >> lbpval;
        for(int i = 0; i < (int)lbpval.size(); i++) 
            cout << " " << (int)lbpval[i];
        cout << ")" << endl;
    }

    fs.release();

    return 0;
}
