#include "rectangle.h"

bool CSG2D::Rectangle::isIn(const sf::Vector2f &test_position) const
{
    //rotacja wokol srodka figury zamiast srodka ukladu wspolrzednych, duzo ulatwia
    const sf::Vector2f rotated_position = rotate(test_position - position_, -angle_rad_) + position_;

    return rotated_position.x >= position_.x - width_/2 && rotated_position.x <= position_.x + width_/2
            && rotated_position.y >= position_.y - height_/2 && rotated_position.y <= position_.y + height_/2;
}