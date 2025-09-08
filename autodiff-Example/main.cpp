// C++ includes
#include <iostream>
#include <chrono>
// autodiff include
#include <autodiff/forward/dual.hpp>
#include <autodiff/forward/dual/eigen.hpp>
using namespace autodiff;
using namespace std::chrono;

dual f(const VectorXdual &X) {
    return X.squaredNorm();  // f(x) = x^T x
}

int main() {
    int n = 1000;
    VectorXdual X(n);
    for (int i = 0; i < n; i++) {
        X[i] = i * 5 - 3;
    }

    auto start = high_resolution_clock::now();
    Eigen::VectorXd g = gradient(f, wrt(X), at(X));
    auto end = high_resolution_clock::now();

    std::cout << "Forward Mode Time: " << duration<double>(end - start).count() << " s\n";
    // std::cout<<g<<std::endl;
}
