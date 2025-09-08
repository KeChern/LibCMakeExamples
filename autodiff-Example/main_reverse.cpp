// C++ includes
#include <iostream>
#include <chrono>
// autodiff include
#include <autodiff/reverse/var.hpp>
#include <autodiff/reverse/var/eigen.hpp>
using namespace autodiff;
using namespace std::chrono;
using namespace std;

struct Params {
    double a;
};

var f(const VectorXvar &X, const Params &params) {
    return params.a * (X[0] * X[0] + params.a * X[1] * X[1]);
    // return params.a * X.squaredNorm();  // f(x) = x^T x
}

int main() {
    int n = 2;
    VectorXvar X(n);
    // for (int i = 0; i < n; i++) {
    //     X[i] = i * 5-3;
    // }
    X[0] = 1.0;
    X[1] = 3.0;
    Params params;   // initialize the parameter variables
    params.a = 4.0;  // the parameter a of type var, not double!
    // params.b = 2.0;  // the parameter b of type var, not double!
    // params.c = 3.0;  // the parameter c of type var, not double!

    var u = f(X, params);
    auto start = high_resolution_clock::now();
    // Eigen::VectorXd g = gradient(y, X);
    auto ux = gradient(u, X); // evaluate the derivatives of u with respect to x and parameters a, b, c

    auto end = high_resolution_clock::now();
    cout << "u = " << u << endl;    // print the evaluated output u
    cout << "ux = " << ux << endl;  // print the evaluated derivative du/dx
    // cout << "ua = " << ua << endl;  // print the evaluated derivative du/da


    std::cout << "Time: " << duration<double>(end - start).count() << " s\n";
    // std::cout<<g<<std::endl;
}
