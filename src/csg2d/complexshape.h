#pragma once
#include "libincludes.h"
#include "shape.h"
#include "functions.h"
#include "operation.h"

namespace CSG2D
{
class ComplexShape : public Shape
{
public:
	ComplexShape(const std::shared_ptr<Shape>& s1, const std::shared_ptr<Shape>& s2, OPERATION op, 
                    const sf::Vector2f& position, const double& angle = 0.0) : Shape(position, angle), shape1_(s1), shape2_(s2), op_(op) {}
    [[nodiscard]] virtual bool isIn(const sf::Vector2f &test_position) const override;

protected:
    std::shared_ptr<Shape> shape1_;
	std::shared_ptr<Shape> shape2_;
    OPERATION op_;
};
}
