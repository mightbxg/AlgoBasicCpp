#pragma once

#include <Eigen/Core>
#include <vector>

namespace abc {

class LineFitter {
public:
    [[nodiscard]] virtual Eigen::Vector3d fitLine(const std::vector<Eigen::Vector2d>& pts) const = 0;
};

} // namespace abc::ref
