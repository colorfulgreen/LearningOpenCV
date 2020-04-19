#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/opengl.hpp>

using namespace std;

int rotx = 55, roty = 40;

void on_opengl(void* param) {
    cv::ogl::Texture2D* backgroundTex = (cv::ogl::Texture2D*)param;
    glEnable(GL_TEXTURE_2D);
    backgroundTex->bind();
    cv::ogl::render(*backgroundTex);
    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -0.5);
    glRotatef(rotx, 1, 0, 0);
    glRotatef(roty, 0, 1, 0);
    glRotatef(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    static const int coords[6][4][3] = {
        { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
        { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
        { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
        { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
        { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
        { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
    };
    for(int i = 0; i < 6; ++i) {
        glColor3ub(i*20, 100 + i*10, i*42);
        glBegin(GL_QUADS);
        for(int j = 0; j < 4; ++j) {
            glVertex3d(
                    0.2 * coords[i][j][0],
                    0.2 * coords[i][j][1],
                    0.2 * coords[i][j][2]);
            glEnd();
        }
    }
}


void on_trackbar(int, void*) {
    cv::updateWindow("OpenGL");
}


int main(int argc, char** argv) {
    cv::Mat img = cv::imread(argv[1]);
    if(img.empty()) {
        cout << "Cannot load " << argv[1] << endl;
        return -1;
    }

    cv::namedWindow("OpenGL", cv::WINDOW_OPENGL);
    cv::resizeWindow("OpenGL", img.cols, img.rows);
    cv::createTrackbar("X-rotation", "OpenGL", &rotx, 360, on_trackbar);
    cv::createTrackbar("Y-rotation", "OpenGL", &roty, 360, on_trackbar);

    cv::ogl::Texture2D backgroundText(img);
    cv::setOpenGlDrawCallback("OpenGL", on_opengl, &backgroundText);
    cv::updateWindow("OpenGL");

    cv::waitKey(0);
    cv::setOpenGlDrawCallback("OpenGL", 0, 0);
    cv::destroyAllWindows();

    return 0;
}
