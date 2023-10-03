#pragma once

#include <Eigen/Core>
#include <opencv2/opencv.hpp>
#include <utility>

namespace abc {

class WhiteBoard {
public:
    struct Config {
        Config() { }
        int rows { 300 };
        int cols { 400 };
        cv::Scalar background { cv::Scalar::all(255) };
        bool flip_y { true };
    };

    template <typename Scalar = float>
    struct Pt {
        template <typename S>
        Pt(const cv::Point_<S>& v)
            : v_ { v.x, v.y }
        {
        }

        template <typename S>
        Pt(const Eigen::Matrix<S, 2, 1>& v)
            : v_ { float(v.x()), float(v.y()) }
        {
        }

        Scalar& x() { return v_[0]; }
        Scalar& y() { return v_[1]; }
        Scalar& operator[](int i) { return v_[i]; }
        const Scalar& x() const { return v_[0]; }
        const Scalar& y() const { return v_[1]; }
        const Scalar& operator[](int i) const { return v_[i]; }

        operator cv::Point_<Scalar>() const
        {
            return { x(), y() };
        }

    private:
        Scalar v_[2] = { 0 };
    };

    explicit WhiteBoard(Config config = Config())
        : cfg_(std::move(config))
    {
        reset();
    }

    void reset()
    {
        board_ = cv::Mat(cfg_.rows, cfg_.cols, CV_8UC3, cfg_.background);
    }

    void setRows(int rows)
    {
        cfg_.rows = rows;
        reset();
    }

    void setCols(int cols)
    {
        cfg_.cols = cols;
        reset();
    }

    void setBackground(const cv::Scalar& color)
    {
        cfg_.background = color;
        reset();
    }

    /// @note point type can be cv::Point_ or Eigen::Vector2
    template <typename T>
    void drawPts(const std::vector<T>& pts,
        const cv::Scalar& color = cv::Scalar::all(0),
        int size = 0)
    {
        for (const auto& pt : pts) {
            Pt tmp(pt);
            flipY(tmp);
            cv::circle(board_, cv::Point2f(tmp), size, color, cv::FILLED);
        }
    }

    /// line: ax+by+c=0
    template <typename Scalar>
    void drawLine(const Eigen::Matrix<Scalar, 3, 1>& line,
        const cv::Scalar& color = cv::Scalar::all(0),
        int thickness = 1)
    {
        auto is_zero = [](double v) { return std::abs(v) < 1e-6; };
        CV_Assert(!is_zero(line.x()) || !is_zero(line.y()));
        cv::Point2f pt1, pt2;
        if (is_zero(line.x())) {
            pt1.y = pt2.y = -line.z() / line.y();
            pt1.x = 0.f;
            pt2.x = static_cast<float>(cfg_.cols);
        } else if (is_zero(line.y())) {
            pt1.x = pt2.x = -line.z() / line.x();
            pt1.y = 0.f;
            pt2.y = static_cast<float>(cfg_.rows);
        } else {
            pt1 = { 0.f, float(-line.z() / line.y()) };
            pt2 = { float(cfg_.cols), float(-(line.x() * cfg_.cols + line.z()) / line.y()) };
        }
        flipY(pt1);
        flipY(pt2);
        cv::line(board_, pt1, pt2, color, thickness);
    }

    [[nodiscard]] const cv::Mat& image() const { return board_; }

private:
    template <typename Scalar>
    void flipY(Pt<Scalar>& pt)
    {
        if (cfg_.flip_y)
            pt.y() = cfg_.rows - 1 - pt.y();
    }
    template <typename Scalar>
    void flipY(cv::Point_<Scalar>& pt)
    {
        if (cfg_.flip_y)
            pt.y = cfg_.rows - 1 - pt.y;
    }

    Config cfg_;
    cv::Mat board_;
};

} // namespace abc
