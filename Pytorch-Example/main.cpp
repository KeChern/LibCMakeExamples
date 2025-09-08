#include <torch/torch.h>
#include <iostream>
torch::Tensor Nor(torch::Tensor &pt) {
    auto t=pt/torch::sqrt(pt[0] * pt[0] + pt[1] * pt[1] + pt[2] * pt[2]);
    return t;
}

int main() {
    // 初始化一个 double 数组
    double x_data[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

    // 转换为 torch::Tensor，并设置 requires_grad = true
    torch::Tensor x = torch::from_blob(x_data, {10}, torch::TensorOptions().dtype(torch::kDouble)).clone().detach().
        requires_grad_(true);
    torch::Tensor r = Nor(x);

    torch::Tensor x_var=torch::tensor({1.0,2.0,3.0});
    std::cout << "Gradients: " << x_var.grad() << std::endl;

    // 定义一个函数 f(x) = sum(x^2 + 3x + 5)
    double a=2.0;
    torch::Tensor q = torch::tensor(2.0) * x * x/x[0];
    std::cout << q << std::endl;

    torch::Tensor y = q.dot(q);

    // 计算梯度
    y.backward();

    // 输出梯度 df/dx
    std::cout << "Gradients: " << x.grad() << std::endl;

    return 0;
}
