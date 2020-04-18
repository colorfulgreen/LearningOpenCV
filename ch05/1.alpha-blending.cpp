#include <opencv2/opencv.hpp>

using namespace std;

// data/faceTemplate.jpg data/faces.png 230 155 0.8 0.2
int main(int argc, char** argv) {
    cv::Mat temp = cv::imread(argv[1], 1);
    cv::Mat target = cv::imread(argv[2], 1);

    cout << argc << endl;
    cout << temp.empty() << endl;
    if( argc == 7 && !temp.empty() && !target.empty() ) {
        int x = atoi(argv[3]);
        int y = atoi(argv[4]);
        int w = temp.size().width - 1;
        int h = temp.size().height - 1; 
        double alpha = (double)atof(argv[5]);
        double beta = (double)atof(argv[6]);

        printf("(x,y)=(%d,%d), (w,h)=(%d,%d)\n", x,y,w,h);
        cv::Mat roiTemp(temp, cv::Rect(0,0,w,h));
        cv::Mat roiTarget(target, cv::Rect(x,y,w,h));

        cv::addWeighted(roiTemp, alpha, roiTarget, beta, 0.0, roiTarget);

        cv::namedWindow("Alpha Blend", 1);
        cv::imshow("Alpha Blend", target);
        cv::waitKey(0);
    } 

    return 0;
}
