#pragma once

#include <Eigen/Core>
#include <vector>

namespace abc::ref {

class LineFitter {
public:
    virtual Eigen::Vector3d fitLine(const std::vector<Eigen::Vector2d>& pts) = 0;
};

} // namespace abc::ref
