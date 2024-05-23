#include "circle.h"

bool CSG2D::Circle::isIn(const sf::Vector2f &test_position) const
{
    return (test_position.x - position_.x) * (test_position.x - position_.x)
            + (test_position.y - position_.y) * (test_position.y - position_.y) <= radius_ * radius_;
}