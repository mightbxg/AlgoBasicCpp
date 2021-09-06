#include "utils/io.hpp"
#include "utils/white_board.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
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

class LineFitter {
public:
    using Point = Eigen::Vector2d;
    using Line = Eigen::Vector3d;

    static double distanceToLine(const Point& pt, const Line& line)
    {
        return std::abs(pt.x() * line.x() + pt.y() * line.y() + line.z())
            / std::sqrt(line.x() * line.x() + line.y() * line.y());
    }

    static Line fitLine(const std::vector<Point>& pts)
    { // ax+b=y
        using namespace Eigen;
        if (pts.size() < 2)
            return Line();
        Matrix<double, 2, Dynamic> A(2, pts.size());
        Matrix<double, Dynamic, 1> b(pts.size());
        for (size_t i = 0; i < pts.size(); ++i) {
            A(0, i) = pts[i].x();
            A(1, i) = 1;
            b(i) = pts[i].y();
        }
        Vector2d param = (A * A.transpose()).ldlt().solve(A * b);
        return { param.x(), -1, param.y() };
    }
};

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "no input\n";
        return 0;
    }
    auto pts = loadPts(argv[1]);
    cout << pts.size() << " pts loaded.\n";
    Eigen::Vector3d ground_truth = { 0.5, -1.0, 10.0 };

    // draw pts and ground_truth
    abc::WhiteBoard::Config bd_config;
    bd_config.rows = 300;
    bd_config.cols = 500;
    abc::WhiteBoard bd(bd_config);
    bd.drawLine(ground_truth, { 0, 255, 0 });
    bd.drawPts(pts, { 0, 0, 255 }, 1);

    auto fitted_line = LineFitter::fitLine(pts);
    bd.drawLine(fitted_line, { 255, 0, 0 });
    imshow("image", bd.image());
    waitKey(0);

    return 0;
}
