#include "line_fitter_gn.h"
#include <Eigen/Dense>
#include <iostream>

namespace abc::ref {

Eigen::Vector3d LineFitterGn::fitLine(const std::vector<Eigen::Vector2d>& pts) const
{
    if (pts.size() < 2)
        return Eigen::Vector3d::Zero();
    // ax+y+b=0
    Eigen::Vector2d p = Eigen::Vector2d::Zero();

    for (int iter_cnt = 0; iter_cnt < max_iter_cnt; ++iter_cnt) {
        Eigen::Matrix<double, Eigen::Dynamic, 2> J(pts.size(), 2);
        Eigen::Matrix<double, Eigen::Dynamic, 1> res(pts.size());
        double res_sum = 0.0;
        for (int i = 0; i < static_cast<int>(pts.size()); ++i) {
            const auto& pt = pts[i];
            J(i, 0) = pt.x();
            J(i, 1) = 1.0;
            res(i) = p(0) * pt.x() + pt.y() + p(1);
            res_sum += res(i);
        }
        auto ldl = (J.transpose() * J).ldlt();
        if (ldl.info() == Eigen::NumericalIssue || !(ldl.vectorD().array() > 0).all()) {
            if (show_debug_info) {
                std::cout << "fit line error: " << ldl.vectorD().transpose() << "\n";
                return Eigen::Vector3d::Zero();
            }
        }
        Eigen::Vector2d h = (J.transpose() * J).ldlt().solve(-J.transpose() * res);
        p += h;
        if (show_debug_info) {
            std::cout << "iter " << iter_cnt << ": step[" << h.transpose() << "] res[" << res_sum / static_cast<double>(pts.size()) << "]\n";
        }
        if (std::abs(h(0)) < min_iter_step && std::abs(h(1)) < min_iter_step) {
            break;
        }
    }
    return { p(0), 1, p(1) };
}

} // namespace abc::ref
