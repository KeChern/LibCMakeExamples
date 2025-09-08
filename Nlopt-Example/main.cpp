#include <nlopt.hpp>
#include <iostream>
#include <vector>
#include <cmath>

// 目标函数
double objective_function(const std::vector<double>& x, std::vector<double>& grad, void* f_data) {
    double sum = 0.0;

    // 计算目标函数值：f(x) = sum_{i=1}^{640} (x_i^2 + sin(x_i)) + sum_{i=1}^{639} (x_i * x_{i+1}) + sum_{i=1}^{640} (exp(-x_i^2))
    for (int i = 0; i < x.size(); ++i) {
        sum += x[i] * x[i] + std::sin(x[i]); // 二次项 + 正弦项
        sum += std::exp(-x[i] * x[i]);      // 高斯项
    }

    for (int i = 0; i < x.size() - 1; ++i) {
        sum += x[i] * x[i + 1]; // 交叉项
    }

    // 计算梯度（如果 grad 非空）
    if (!grad.empty()) {
        for (int i = 0; i < x.size(); ++i) {
            grad[i] = 2.0 * x[i] + std::cos(x[i]) - 2.0 * x[i] * std::exp(-x[i] * x[i]); // 梯度：df/dx_i = 2x_i + cos(x_i) - 2x_i * exp(-x_i^2)
            if (i > 0) {
                grad[i] += x[i - 1]; // 交叉项的梯度贡献
            }
            if (i < x.size() - 1) {
                grad[i] += x[i + 1]; // 交叉项的梯度贡献
            }
        }
    }

    return sum;
}

int main() {
    const int n = 640; // 变量数

    // 创建 NLopt 优化器，使用 LD_LBFGS 算法（基于梯度的优化算法）
    nlopt::opt opt(nlopt::LD_LBFGS, n);

    // 设置目标函数
    opt.set_min_objective(objective_function, nullptr);

    // 设置变量的下界和上界
    std::vector<double> lb(n, -10.0); // 下界
    std::vector<double> ub(n, 10.0);  // 上界
    opt.set_lower_bounds(lb);
    opt.set_upper_bounds(ub);

    // 设置优化容忍度
    opt.set_xtol_rel(1e-6);

    // 初始猜测值
    std::vector<double> x(n, 1.0); // 初始值全设为 1.0

    // 优化结果
    double minf;
    try {
        nlopt::result result = opt.optimize(x, minf);
        std::cout << "Optimization result: " << result << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Optimization failed: " << e.what() << std::endl;
        return 1;
    }

    // 输出结果
    std::cout << "Found minimum value = " << minf << std::endl;

    return 0;
}