#pragma once

#include <Eigen/Core>
#include <opencv2/opencv.hpp>

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
            : v_ { v.x(), v.y() }
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

    WhiteBoard(const Config& config = Config())
        : cfg_(config)
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

    void setBackground(const cv::Scalar color)
    {
        cfg_.background = color;
        reset();
    }

    template <typename T>
    void drawPts(const std::vector<T>& pts, int size = 0,
        const cv::Scalar& color = cv::Scalar::all(0))
    {
        for (const auto& pt : pts) {
            Pt tmp(pt);
            if (cfg_.flip_y)
                tmp.y() = cfg_.rows - tmp.y() - 1.0;
            cv::circle(board_, cv::Point2f(tmp), size, color, cv::FILLED);
        }
    }

    const cv::Mat& image() const { return board_; }

private:
    Config cfg_;
    cv::Mat board_;
};

} //namespace abc
