#include "utils/io.hpp"
#include "utils/white_board.hpp"
#include <Eigen/Core>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<Eigen::Vector2d> loadPts(const string& filename)
{
    FileStorage fs(filename, FileStorage::READ);
    vector<float> x, y;
    fs["x"] >> x;
    fs["y"] >> y;
    CV_Assert(x.size() == y.size());
    vector<Eigen::Vector2d> pts;
    pts.reserve(x.size());
    for (size_t i = 0; i < x.size(); ++i)
        pts.emplace_back(x[i], y[i]);
    return pts;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "no input\n";
        return 0;
    }
    auto pts = loadPts(argv[1]);
    cout << pts.size() << " pts loaded.\n";
    Eigen::Vector3d ground_truth = { 0.5, -1.0, 10.0 };

    abc::WhiteBoard::Config bd_config;
    bd_config.rows = 300;
    bd_config.cols = 500;
    abc::WhiteBoard bd(bd_config);
    bd.drawLine(ground_truth, { 0, 255, 0 });
    bd.drawPts(pts, { 0, 0, 255 }, 1);
    imshow("image", bd.image());
    waitKey(0);

    return 0;
}
