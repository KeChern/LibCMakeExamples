#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/AutoDiff>

int main() {
    using namespace Eigen;

    int n = 640;

    // 定义自动微分类型
    using Real = AutoDiffScalar<VectorXd>;
    using VectorXReal = Matrix<Real, Dynamic, 1>;

    // 定义变量 x（n 维）
    VectorXReal x;
    x.resize(n);
    for (int i = 0; i < n; ++i) {
        x[i].value() = i + 3.0;  // 初始值 x_i = i + 1
        x[i].derivatives() = VectorXd::Unit(n, i);  // 为每个变量设置偏导
    }

    // 定义目标函数 f(x_1, ..., x_n)
    Real f = 0.0;
    for (int i = 0; i < n; ++i) {
        f += (x[i] - (i + 1)) * (x[i] - (i + 1));  // f = sum((x_i - (i+1))^2)
    }

    // 输出函数值
    std::cout << "Function value: " << f.value() << std::endl;

    // 输出梯度
    std::cout << "Gradient: ";
    for (int i = 0; i < n; ++i) {
        std::cout << f.derivatives()[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
