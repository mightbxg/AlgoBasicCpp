#include "algorithms/line_fitter_linear.h"
#include "algorithms/line_fitter_optimize.h"
#include "utils/line_pt_generator.h"
#include "utils/white_board.h"
#include <ceres/ceres.h>
#include <gtest/gtest.h>
#include <iostream>

static void testFitLine(const abc::LineFitter* algo, double outlier_rate = 0.0)
{
    assert(algo);
    Eigen::Vector3d model_gt { 0.5, -1.0, 10 };
    abc::LinePtGenerator generator;
    generator.params.setCoeff(model_gt);
    generator.params.noise_std = 5.0;
    generator.params.outlier_rate = outlier_rate;

    auto pts = generator.gen();
    auto model_fitted = algo->fitLine(pts);
    std::cout << "    gt: " << model_gt.transpose() << "\n"
              << "fitted: " << model_fitted.transpose() << "\n";

    // visualize
    abc::WhiteBoard bd;
    bd.drawLine(model_gt, { 0, 255, 0 });
    bd.drawLine(model_fitted, { 255, 0, 0 });
    bd.drawPts(pts, { 0, 0, 255 }, 1);
    cv::imshow("fit_line_linear", bd.image());
    cv::waitKey(0);
}

TEST(fit_line, linear_ref)
{
    testFitLine(new abc::ref::LineFitterLinear());
}

TEST(fit_line, optimize_auto)
{
    testFitLine(new abc::ref::LineFitterOptimizeAuto(false, true));
}

TEST(fit_line, optimize_analytical)
{
    testFitLine(new abc::ref::LineFitterOptimizeAnalytical(false, true));
}

TEST(fit_line_with_outlier, optimize_auto)
{
    testFitLine(new abc::ref::LineFitterOptimizeAuto(true, true), 0.2);
}

TEST(fit_line_with_outlier, optimize_analytical)
{
    testFitLine(new abc::ref::LineFitterOptimizeAnalytical(true, true), 0.2);
}
