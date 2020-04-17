#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

template <class T> void print_matrix(const cv::SparseMat_<T>* sm) {
    cv::SparseMatConstIterator_<T> it = sm->begin();
    cv::SparseMatConstIterator_<T> it_end = sm->end();

    for(; it != it_end; ++it) {
        const typename cv::SparseMat_<T>::Node* node = it.node();
        cout << "( " << node->idx[0] << ", " << node->idx[1]
            << " ) = " << *it << endl;
    }
}

int main(void) {
    int ndim = 2;
    int size[] = {10, 10};

    cv::SparseMat_<float> sm(ndim, size);
    for(int i=0; i<10; i++) {
        int idx[2];
        idx[0] = size[0] * rand();
        idx[1] = size[1] * rand();
        sm.ref(idx) += 1.0f;
    }
    print_matrix<float>( &sm );

    cv::SparseMat sm2(ndim, size, CV_32F);
    for(int i=0; i<10; i++) {
        int idx[2];
        idx[0] = size[0] * rand();
        idx[1] = size[1] * rand();
        sm2.ref<float>(idx) += 1.0f;
    }
    print_matrix<float>( (cv::SparseMat_<float>*) &sm2 );

    return 0;
}
