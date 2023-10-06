#include "line_fitter_linear.h"
#include <Eigen/Dense>

namespace abc::ref {

Eigen::Vector3d LineFitterLinear::fitLine(const std::vector<Eigen::Vector2d>& pts) const
{
    // ax + b = y
    if (pts.size() < 2)
        return Eigen::Vector3d::Zero();
    Eigen::Matrix<double, Eigen::Dynamic, 2> A(pts.size(), 2);
    Eigen::Matrix<double, Eigen::Dynamic, 1> b(pts.size());
    for (int i = 0; i < static_cast<int>(pts.size()); ++i) {
        const auto& pt = pts[i];
        A(i, 0) = pt.x();
        A(i, 1) = 1;
        b(i) = pt.y();
    }
    Eigen::Vector2d p = (A.transpose() * A).ldlt().solve(A.transpose() * b);
    return { p.x(), -1, p.y() };
}

} // namespace abc::ref
