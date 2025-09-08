#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

const int N = 100000000;  // 1 亿个元素

// **单线程版本**
double sum_serial(const vector<double>& data) {
    double sum = 0.0;
    for (int i = 0; i < data.size(); i++) {
        sum += data[i] * data[i];  // 计算平方和
    }
    return sum;
}

// **OpenMP 并行版本**
double sum_parallel(const vector<double>& data) {
    double sum = 0.0;

#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < data.size(); i++) {
        sum += data[i] * data[i];
    }

    return sum;
}

int main() {
    vector<double> data(N, 2.0);  // 生成 N 个 1.0 的元素

    // **测量单线程时间**
    auto start_serial = high_resolution_clock::now();
    double result_serial = sum_serial(data);
    auto end_serial = high_resolution_clock::now();
    auto duration_serial = duration_cast<milliseconds>(end_serial - start_serial);

    // **测量 OpenMP 并行时间**
    auto start_parallel = high_resolution_clock::now();
    double result_parallel = sum_parallel(data);
    auto end_parallel = high_resolution_clock::now();
    auto duration_parallel = duration_cast<milliseconds>(end_parallel - start_parallel);

    // **打印结果**
    cout << "Serial Result: " << result_serial << " Time: " << duration_serial.count() << " ms\n";
    cout << "Parallel Result: " << result_parallel << " Time: " << duration_parallel.count() << " ms\n";

    return 0;
}