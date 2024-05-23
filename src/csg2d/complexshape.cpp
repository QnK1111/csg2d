#include "complexshape.h"

bool CSG2D::ComplexShape::isIn(const sf::Vector2f &test_position) const
{
    //rotacja wokol srodka figury zamiast srodka ukladu wspolrzednych, duzo ulatwia
    const sf::Vector2f rotated_position = rotate(test_position - position_, -angle_rad_) + position_;
    const sf::Vector2f final_position = rotated_position - position_;
    
    
    switch(op_)
    {
        case CSG2D::OPERATION::UNION:
            return shape1_->isIn(final_position) || shape2_->isIn(final_position);
        break;

        case CSG2D::OPERATION::INTERSECTION:
            return shape1_->isIn(final_position) && shape2_->isIn(final_position);
        break;

        case CSG2D::OPERATION::DIFFERENCE:
            return shape1_->isIn(final_position) && !shape2_->isIn(final_position);
        break;

        default:
            return false;
        break;
    }
}