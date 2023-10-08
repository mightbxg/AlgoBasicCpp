#include "line_fitter.h"

namespace abc::ref {

/// @brief Gauss-Newton method
class LineFitterGn : public LineFitter {
public:
    explicit LineFitterGn(int _max_iter_cnt = 100, double _min_iter_step = 0.01, bool _show_debug_info = false)
        : max_iter_cnt(_max_iter_cnt)
        , min_iter_step(_min_iter_step)
        , show_debug_info(_show_debug_info)
    {
    }

    [[nodiscard]] Eigen::Vector3d fitLine(const std::vector<Eigen::Vector2d>& pts) const override;

public:
    int max_iter_cnt { 100 };
    double min_iter_step { 0.01 };
    bool show_debug_info { false };
};

} // namespace abc::ref
