#pragma once

#include "line_fitter.h"

namespace abc::ref {

class LineFitterLinear : public LineFitter {
public:
    Eigen::Vector3d fitLine(const std::vector<Eigen::Vector2d>& pts) override;
};

} // namespace abc::ref
