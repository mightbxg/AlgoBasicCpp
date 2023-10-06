#include "utils/line_pt_generator.h"
#include "utils/white_board.h"

int main(int, char**)
{
    int rand_seed = -1;
    Eigen::Vector3d line_coeff { 0.5, -1.0, 10.0 };
    abc::LinePtGenerator generator;
    generator.params.setCoeff(line_coeff);
    auto pts = generator.gen(rand_seed);

    abc::WhiteBoard::Config bd_conf;
    bd_conf.rows = 300;
    bd_conf.cols = 500;
    abc::WhiteBoard bd(bd_conf);
    bd.drawLine(line_coeff, { 0, 255, 0 });
    bd.drawPts(pts, { 0, 0, 255 }, 1);
    cv::imshow("line pts", bd.image());
    cv::waitKey(0);
}
