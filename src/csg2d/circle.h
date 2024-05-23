#pragma once
#include "libincludes.h"
#include "shape.h"

namespace CSG2D
{
class Circle : public Shape
{
public:
	Circle(const sf::Vector2f& position, const double& radius) : Shape(position, 0.0), radius_(radius) {}
    [[nodiscard]] virtual bool isIn(const sf::Vector2f &test_position) const override;

protected:
    double radius_;
	
};
}
