#pragma once
#include "libincludes.h"
#include "shape.h"
#include "functions.h"

namespace CSG2D
{
class Rectangle : public Shape
{
public:
	Rectangle(const sf::Vector2f& position, const double& h, const double& w, const double& angle = 0.0) 
    : Shape(position, angle), width_(w), height_(h) {}
    [[nodiscard]] virtual bool isIn(const sf::Vector2f &test_position) const override;

protected:
    double height_;
    double width_;
	
};
}
