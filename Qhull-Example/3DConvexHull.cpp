#include <libqhullcpp/Qhull.h>
#include <libqhullcpp/QhullFacetList.h>
#include <libqhullcpp/QhullFacet.h>
#include <libqhullcpp/QhullHyperplane.h>
#include <libqhullcpp/QhullVertexSet.h>
#include <iostream>
#include <vector>

using namespace orgQhull;

int main() {
    // 构造一个三维点集
    std::vector<double> coords = {
        0, 0, 0,
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
        1, 1, 0,
        0, 1, 1,
        1, 0, 1,
        1, 1, 1,
        0.5, 0.5, 0.5
    };

    int dim = 3;
    int num_points = coords.size() / dim;

    try {
        // 构建 Qhull 凸包对象
        Qhull qh("qhull", dim, num_points, coords.data(), "Qt");  // Qt = triangulate

        std::cout << "✅ 3D Convex Hull Computed\n";
        std::cout << "Number of input points: " << num_points << "\n";
        std::cout << "Number of convex hull facets (triangles): "
            << qh.facetCount() << "\n\n";

        int facet_id = 0;
        for (auto facet = qh.facetList().begin(); facet != qh.facetList().end(); ++facet) {
            if (facet->isGood()) {
                std::cout << "🔹 Facet " << facet_id++ << ":\n";

                // 顶点编号
                QhullVertexSet vs = facet->vertices();
                std::cout << "  Vertices: ";
                for (const auto &vertex: vs) {
                    std::cout << vertex.point().id() << " ";
                }
                std::cout << "\n";

                // 法向量和偏移
                QhullHyperplane hp = facet->hyperplane();
                std::vector<double> normal(hp.begin(), hp.end());

                std::cout << "  Normal: (";
                for (size_t i = 0; i < normal.size(); ++i) {
                    std::cout << normal[i];
                    if (i < normal.size() - 1)
                        std::cout << ", ";
                }
                std::cout << ")\n";
                std::cout << "  Offset: " << hp.offset() << "\n\n";
            }
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Qhull error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
