#include "utils/io.h"
#include "utils/white_board.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <random>

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
    static constexpr double MAX_ERROR = std::numeric_limits<double>::max();

    static double distanceToLine(const Point& pt, const Line& line)
    {
        return std::abs(pt.x() * line.x() + pt.y() * line.y() + line.z())
            / std::sqrt(line.x() * line.x() + line.y() * line.y());
    }

    static Line fitLine(const std::vector<Point>& pts)
    { // ax+b=y
        using namespace Eigen;
        if (pts.size() < 2)
            return {};
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

    static std::vector<Point> randomSample(const std::vector<Point>& pts, size_t num)
    {
        std::vector<Point> out;
        std::sample(pts.begin(), pts.end(), std::back_inserter(out),
            num, std::mt19937(std::random_device {}()));
        return out;
    }

    static std::vector<Point> findConsensusSet(const std::vector<Point>& pts,
        const Line& line, double min_distance)
    {
        std::vector<Point> ret;
        for (const auto& pt : pts)
            if (distanceToLine(pt, line) < min_distance)
                ret.push_back(pt);
        return ret;
    }

    static double avgError(const Line& line, const std::vector<Point>& pts)
    {
        if (pts.empty() || (line.x() == 0 && line.y() == 0))
            return MAX_ERROR;
        double err = 0;
        for (const auto& pt : pts)
            err += distanceToLine(pt, line);
        return err / pts.size();
    }

    static Line fitLineRansac(const std::vector<Point>& pts, int max_iteration = 1000,
        double inlier_rate = 0.7, double min_distance = 5.0)
    {
        if (pts.size() < 4)
            return Line();
        const size_t min_inlier_num = std::round(inlier_rate * pts.size());

        Line best_model;
        double best_model_error = MAX_ERROR;
        for (int i = 0; i < max_iteration; ++i) {
            auto samples = randomSample(pts, 2);
            Line maybe_model = fitLine(samples);
            auto inliers = findConsensusSet(pts, maybe_model, min_distance);
            if (inliers.size() >= min_inlier_num) {
                Line better_model = fitLine(inliers);
                double err = avgError(better_model, inliers);
                if (err < best_model_error) {
                    best_model = better_model;
                    best_model_error = err;
                }
            }
        }
        return best_model;
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

    auto fitted_line = LineFitter::fitLineRansac(pts);
    bd.drawLine(fitted_line, { 255, 0, 0 });
    imshow("image", bd.image());
    waitKey(0);

    return 0;
}
