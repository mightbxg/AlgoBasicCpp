#pragma once

#include "line_fitter.h"

namespace abc::ref {

class LineFitterOptimizeAuto : public LineFitter {
public:
    explicit LineFitterOptimizeAuto(bool _show_debug_info = false)
        : show_debug_info(_show_debug_info)
    {
    }

    [[nodiscard]] Eigen::Vector3d fitLine(const std::vector<Eigen::Vector2d>& pts) const override;

public:
    bool show_debug_info { false };
};

class LineFitterOptimizeAnalytical : public LineFitter {
public:
    explicit LineFitterOptimizeAnalytical(bool _show_debug_info = false)
        : show_debug_info(_show_debug_info)
    {
    }

    [[nodiscard]] Eigen::Vector3d fitLine(const std::vector<Eigen::Vector2d>& pts) const override;

public:
    bool show_debug_info { false };
};

} // namespace abc::ref
