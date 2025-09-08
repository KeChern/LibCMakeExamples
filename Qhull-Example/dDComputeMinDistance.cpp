#include <libqhullcpp/Qhull.h>
#include <libqhullcpp/QhullFacetList.h>
#include <libqhullcpp/QhullFacet.h>
#include <libqhullcpp/QhullVertexSet.h>
#include <libqhullcpp/QhullVertex.h>
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <limits>

// 递归求点到任意维 simplex 的最近点
void point_to_simplex_distance(const Eigen::VectorXd& query_point,
                               const std::vector<Eigen::VectorXd>& facet_points,
                               Eigen::VectorXd& closest_point,
                               double& dist2) {
    const int dim = static_cast<int>(query_point.size());
    const int k = static_cast<int>(facet_points.size());

    if (k == 1) {
        closest_point = facet_points[0];
        dist2 = (query_point - closest_point).squaredNorm();
        return;
    }

    Eigen::MatrixXd A(dim, k - 1);
    for (int i = 1; i < k; ++i)
        A.col(i - 1) = facet_points[i] - facet_points[0];

    Eigen::VectorXd rhs = query_point - facet_points[0];
    Eigen::VectorXd coeffs = A.colPivHouseholderQr().solve(rhs);

    Eigen::VectorXd candidate = facet_points[0];
    double sum = 0.0;
    bool inside = true;
    for (int i = 0; i < k - 1; ++i) {
        if (coeffs[i] < 0.0) inside = false;
        sum += coeffs[i];
        candidate += coeffs[i] * (facet_points[i + 1] - facet_points[0]);
    }
    if (sum > 1.0) inside = false;

    if (inside) {
        closest_point = candidate;
        dist2 = (query_point - closest_point).squaredNorm();
        return;
    }

    dist2 = std::numeric_limits<double>::infinity();
    for (int i = 0; i < k; ++i) {
        std::vector<Eigen::VectorXd> sub_simplex;
        for (int j = 0; j < k; ++j) {
            if (j != i) sub_simplex.push_back(facet_points[j]);
        }
        Eigen::VectorXd sub_closest(dim);
        double sub_dist2;
        point_to_simplex_distance(query_point, sub_simplex, sub_closest, sub_dist2);
        if (sub_dist2 < dist2) {
            dist2 = sub_dist2;
            closest_point = sub_closest;
        }
    }
}

int main() {
    const int d = 4; // 改成你想要的维度
    std::vector<Eigen::VectorXd> points;
    for (int i = 0; i < (1 << d); ++i) {
        Eigen::VectorXd pt(d);
        for (int j = 0; j < d; ++j)
            pt[j] = (i >> j) & 1;
        points.push_back(pt);
    }

    std::vector<double> coords;
    for (const auto& pt : points)
        for (int i = 0; i < d; ++i)
            coords.push_back(pt[i]);

    orgQhull::Qhull qhull;
    qhull.runQhull("", d, static_cast<int>(points.size()), coords.data(), "Qt");

    Eigen::VectorXd query_point(d);
    query_point.setConstant(0.5);  // 或你想要的值
    // query_point << 2, 2, 2, 2;  // 示例：在凸包外

    double min_dist2 = std::numeric_limits<double>::infinity();
    Eigen::VectorXd closest_point(d);

    for (const orgQhull::QhullFacet& facet : qhull.facetList()) {
        if (!facet.isGood()) continue;

        orgQhull::QhullVertexSet vertices = facet.vertices();
        std::vector<Eigen::VectorXd> facet_points;
        for (const orgQhull::QhullVertex& v : vertices)
            facet_points.emplace_back(Eigen::VectorXd::Map(v.point().coordinates(), d));

        Eigen::VectorXd candidate(d);
        double dist2;
        point_to_simplex_distance(query_point, facet_points, candidate, dist2);
        if (dist2 < min_dist2) {
            min_dist2 = dist2;
            closest_point = candidate;
        }
    }

    // 判断是否在凸包内部
    bool inside = true;
    for (const orgQhull::QhullFacet& facet : qhull.facetList()) {
        if (!facet.isGood()) continue;

        const orgQhull::QhullHyperplane& hyperplane = facet.hyperplane();
        const double* normal_ptr = hyperplane.coordinates();
        double offset = hyperplane.offset();

        double dot = 0.0;
        for (int i = 0; i < d; ++i)
            dot += query_point[i] * normal_ptr[i];

        if (dot + offset > 1e-12) {
            inside = false;
            break;
        }
    }

    double signed_distance = std::sqrt(min_dist2);
    if (inside)
        signed_distance *= -1.0;

    std::cout << "Query point: " << query_point.transpose() << std::endl;
    std::cout << "Closest point on convex hull boundary: " << closest_point.transpose() << std::endl;
    std::cout << "Signed distance: " << signed_distance << std::endl;

    return 0;
}
