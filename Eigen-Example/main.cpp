#include <iostream>
#include <Eigen/Dense>

int main() {
    // 定义两个 3D 向量
    Eigen::Vector3d v1(-1,0,1);
    Eigen::Vector3d v2(0,0,-1);

    // 计算叉乘
    Eigen::Vector3d cross_product = v1.cross(v2);

    // 输出结果
    std::cout << "v1: " << v1.transpose() << std::endl;
    std::cout << "v2: " << v2.transpose() << std::endl;
    std::cout << "Cross product: " << cross_product.transpose() << std::endl;

    return 0;
}
