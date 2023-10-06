#include "algorithms/line_fitter_linear.h"
#include "utils/line_pt_generator.h"
#include "utils/white_board.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(fit_line, linear_ref)
{
    Eigen::Vector3d model_gt { 0.5, -1.0, 10 };
    abc::LinePtGenerator generator;
    generator.params.setCoeff(model_gt);
    generator.params.noise_std = 5.0;
    generator.params.outlier_rate = 0.0;

    auto pts = generator.gen();
    abc::ref::LineFitterLinear algo;
    auto model_fitted = algo.fitLine(pts);
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
