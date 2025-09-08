#include <cppad/cppad.hpp>
#include <iostream>
#include <Eigen/Core>
using namespace Eigen;

int main() {
    using Real = CppAD::AD<double>;
    using VectorXReal = CppAD::vector<Real>;
    using Vector3Real = Matrix<Real, 3, 1>;

    // 设置变量数量 n
    int n = 3;  // 你可以通过修改 n 来控制变量数量
    size_t m = 1;  // 目标函数的输出维度


    // 创建一个独立的变量向量 (x)，大小为 n
    // 创建目标函数的输出向量
    VectorXReal x(n), y(m);
    for (size_t i = 0; i < n; i++) {
        x[i] = 3*i;
    }
    double a = 2.0;

    // 启动自动微分的追踪
    CppAD::Independent(x);

    // // 定义一个简单的目标函数 f(x) = sum(x_i^2)
    // for (int i = 0; i < n; ++i) {
    //     y[0] += a * x[i] * x[i];  // 目标函数：f(x) = x0^2 + x1^2 + ... + xn^2
    // }
    Vector3Real z;
    z[0] = x[0];
    z[1] = x[1];
    z[2] = x[2];
    y[0] += a * z.dot(z);
    std::cout<<y[0]<<std::endl;

    // 创建函数对象 f
    CppAD::ADFun<double> f(x, y);

    // 计算梯度，传入点 (1.0, 2.0, ..., n+1)
    CppAD::vector<double> x_value(n);
    for (int i = 0; i < n; ++i) {
        x_value[i] = 1.0 + i;  // 设置自变量的值
    }

    // 计算梯度（Jacobian）
    CppAD::vector<double> grad = f.Jacobian(x_value);  // 计算雅可比矩阵（梯度）

    // 打印计算结果
    std::cout << "f(x) = sum(x_i^2) at x = ";
    for (int i = 0; i < n; ++i) {
        std::cout << x_value[i] << " ";
    }
    std::cout << ": " << f.Forward(0, x_value)[0] << std::endl;

    std::cout << "Gradient of f at x: [";
    for (int i = 0; i < n; ++i) {
        std::cout << grad[i] << (i < n - 1 ? ", " : "]\n");
    }

    return 0;
}
