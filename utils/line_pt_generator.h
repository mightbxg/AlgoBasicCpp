#pragma once

#include <Eigen/Core>
#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

namespace abc {

class LinePtGenerator {
public:
    struct Params {
        Eigen::Vector2d coeff { 1.0, 0.0 }; // y=ax+b
        double x_min { 10.0 };
        double x_max { 490.0 };
        size_t pt_num { 50 };
        double noise_std { 2.0 };
        double outlier_rate { 0.2 };

        /// @brief Set coefficients from ax+by+c=0
        void setCoeff(const Eigen::Vector3d& p)
        {
            assert(std::abs(p.y()) > 1e-6);
            coeff.x() = -p.x() / p.y();
            coeff.y() = -p.z() / p.y();
        }
    };

    [[nodiscard]] std::vector<Eigen::Vector2d> gen(int rand_seed = -1) const
    {
        assert(params.x_min < params.x_max);
        assert(params.noise_std >= 0.0);
        assert(params.outlier_rate >= 0.0);
        assert(params.outlier_rate <= 1.0);

        // random
        std::random_device rd;
        unsigned seed = rand_seed < 0 ? rd() : rand_seed;
        std::mt19937 gen(seed);
        std::normal_distribution distr(0.0, params.noise_std);
        distr(gen);

        // generate pts with noise
        auto getY = [&](double x) {
            return params.coeff(0) * x + params.coeff(1);
        };
        double step = (params.x_max - params.x_min) / static_cast<double>(params.pt_num);
        std::vector<Eigen::Vector2d> pts;
        pts.reserve(params.pt_num);
        double x = params.x_min;
        for (size_t i = 0; i < params.pt_num; ++i) {
            double y = getY(x);
            pts.emplace_back(x + distr(gen), y + distr(gen));
            x += step;
        }

        // add outliers
        auto outlier_num = static_cast<size_t>(std::round(static_cast<double>(params.pt_num) * params.outlier_rate));
        if (outlier_num > 0) {
            std::vector<size_t> indices(params.pt_num);
            std::iota(indices.begin(), indices.end(), 0);
            std::shuffle(indices.begin(), indices.end(), gen);
            double y_min = getY(params.x_min);
            double y_max = getY(params.x_max);
            if (y_min > y_max)
                std::swap(y_min, y_max);
            std::uniform_real_distribution outlier_distr(y_min - params.noise_std * 3.0, y_max + params.noise_std * 3.0);
            for (size_t i = 0; i < outlier_num; ++i) {
                pts[indices[i]].y() = outlier_distr(gen);
            }
        }
        return pts;
    }

public:
    Params params;
};

} // namespace abc
