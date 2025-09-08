#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <Eigen/Dense>
#include <omp.h>

using namespace std;
using namespace Eigen;
using namespace std::chrono;

double computeSomething(const VectorXd &v) {
    return v.squaredNorm(); // 模拟任务：平方和
}

int main() {
    const int numTasks = 100000;
    const int dim = 1000;
    const int nThreads = 8;  // 设置你想用的线程数

    omp_set_num_threads(nThreads);  // 设置 OpenMP 线程数

    // 生成随机数据
    vector<VectorXd> data(numTasks);
    mt19937 gen(42);
    normal_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < numTasks; ++i) {
        data[i] = VectorXd(dim);
        for (int j = 0; j < dim; ++j)
            data[i][j] = dist(gen);
    }

    vector<double> results(numTasks);

    // ===== 串行版本 =====
    auto startSerial = high_resolution_clock::now();
    for (int i = 0; i < numTasks; ++i) {
        results[i] = computeSomething(data[i]);
    }
    auto endSerial = high_resolution_clock::now();
    auto serialTime = duration_cast<milliseconds>(endSerial - startSerial).count();
    cout << "Serial time: " << serialTime << " ms" << endl;

    // ===== 并行版本 =====
    auto startParallel = high_resolution_clock::now();
#pragma omp parallel for
    for (int i = 0; i < numTasks; ++i) {
        results[i] = computeSomething(data[i]);
    }
    auto endParallel = high_resolution_clock::now();
    auto parallelTime = duration_cast<milliseconds>(endParallel - startParallel).count();
    cout << "Parallel time (" << nThreads << " threads): " << parallelTime << " ms" << endl;

    return 0;
}
