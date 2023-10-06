#include "line_fitter_optimize.h"
#include <ceres/ceres.h>
#include <iostream>

namespace abc::ref {

struct LineCostFunctor {
    explicit LineCostFunctor(const Eigen::Vector2d& _pt)
        : pt(_pt)
    {
    }

    template <typename T>
    bool operator()(const T* const p, T* residual) const
    {
        residual[0] = p[0] * pt.x() - pt.y() + p[1];
        return true;
    }

    const Eigen::Vector2d pt;
};

Eigen::Vector3d LineFitterOptimizeAuto::fitLine(const std::vector<Eigen::Vector2d>& pts) const
{
    if (pts.size() < 2)
        return Eigen::Vector3d::Zero();
    ceres::Problem problem;
    Eigen::Vector2d p { 0.0, 0.0 };
    ceres::LossFunction* loss_function = use_loss_function ? new ceres::CauchyLoss(2.0) : nullptr;
    for (const auto& pt : pts) {
        problem.AddResidualBlock(new ceres::AutoDiffCostFunction<LineCostFunctor, 1, 2>(new LineCostFunctor(pt)), loss_function, p.data());
    }
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = show_debug_info;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    if (show_debug_info) {
        std::cout << summary.BriefReport() << "\n";
    }
    return { p.x(), -1.0, p.y() };
}

class LineCostFunction : public ceres::SizedCostFunction<1, 2> {
public:
    explicit LineCostFunction(const Eigen::Vector2d& _pt)
        : pt(_pt)
    {
    }
    bool Evaluate(double const* const* params, double* res, double** jac) const override
    {
        const double* p = params[0];
        res[0] = p[0] * pt.x() - pt.y() + p[1];
        if (jac && jac[0]) {
            jac[0][0] = pt.x();
            jac[0][1] = 1.0;
        }
        return true;
    }

public:
    const Eigen::Vector2d pt;
};

Eigen::Vector3d LineFitterOptimizeAnalytical::fitLine(const std::vector<Eigen::Vector2d>& pts) const
{
    if (pts.size() < 2)
        return Eigen::Vector3d::Zero();
    ceres::Problem problem;
    Eigen::Vector2d p { 0.0, 0.0 };
    ceres::LossFunction* loss_function = use_loss_function ? new ceres::CauchyLoss(2.0) : nullptr;
    for (const auto& pt : pts) {
        problem.AddResidualBlock(new LineCostFunction(pt), loss_function, p.data());
    }
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = show_debug_info;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    if (show_debug_info) {
        std::cout << summary.BriefReport() << "\n";
    }
    return { p.x(), -1.0, p.y() };
}

} // namespace abc::ref
