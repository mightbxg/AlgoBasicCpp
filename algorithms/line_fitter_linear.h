#pragma once

#include "line_fitter.h"

namespace abc::ref {

class LineFitterLinear : public LineFitter {
public:
    [[nodiscard]] Eigen::Vector3d fitLine(const std::vector<Eigen::Vector2d>& pts) const override;
};

} // namespace abc::ref
