#include <libqhullcpp/Qhull.h>
#include <libqhullcpp/QhullFacetList.h>
#include <libqhullcpp/QhullFacet.h>
#include <libqhullcpp/QhullHyperplane.h>
#include <libqhullcpp/QhullVertexSet.h>
#include <iostream>
#include <vector>

using namespace orgQhull;

int main() {
    // 构造一个简单的 4D 点集（确保是一般位置的点）
    std::vector<double> coords = {
        0, 0, 0, 0,
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
        1, 1, 1, 1,
        1, 1, 0, 0,
        1, 0, 1, 0,
        1, 0, 0, 1,
        0, 1, 1, 0,
        0, 1, 0, 1,
        0, 0, 1, 1,
        0, 1, 1, 1,
        1, 0, 1, 1,
        1, 1, 0, 1,
        1, 1, 1, 0,
        0.5, 0.5, 0.5, 0.5,
        0.1, 0.2, 0.3, 0.4
    };

    int dim = 4;
    int num_points = coords.size() / dim;

    try {
        Qhull qh("qhull", dim, num_points, coords.data(), "Qt");  // Qt: triangulate facets

        std::cout << "✅ 4D Convex Hull Computed\n";
        std::cout << "Number of input points: " << num_points << "\n";
        std::cout << "Number of convex hull facets (3-simplices): "
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

                // 法向量和 offset
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
