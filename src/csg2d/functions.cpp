#include "functions.h"
#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "complexshape.h"

sf::Vector2f rotate(const sf::Vector2f &v, float angle_rad)
{
	const float cs = std::cos(angle_rad);
	const float sn = std::sin(angle_rad);

	return { v.x*cs - v.y*sn, v.x*sn + v.y*cs };
}

void updateTexture(sf::Texture &t, const CSG2D::Shape &s, const sf::Color &foreground_color, const sf::Color &background_color)
{
	const auto tex_size = t.getSize();
	std::vector<sf::Uint8> tex_data(tex_size.x*tex_size.y*4u, 0u);
	const sf::Vector2f center = sf::Vector2f(tex_size)/2.f - sf::Vector2f(0.5f, 0.5f);
    for(std::size_t py = 0u; py < tex_size.y; ++py)
    {
	    for(std::size_t px = 0u; px < tex_size.x; ++px)
	    {
	        auto pos = sf::Vector2f(px, py) - center;
	        pos.y = -pos.y;
	        
	        const auto color = s.isIn(pos) ? foreground_color : background_color;

	        const std::size_t pi = py*tex_size.x + px;
	        const auto i = pi*4u;
	        tex_data[i] = color.r;
	        tex_data[i + 1u] = color.g;
	        tex_data[i + 2u] = color.b;
	        tex_data[i + 3u] = color.a;
	    }
    }
    t.update(tex_data.data());
}

std::shared_ptr<CSG2D::Shape> createCSG2DScene()
{
	// const auto op = CSG2D::OPERATION::UNION;
    // auto circle_shp = std::make_shared<CSG2D::Circle>(sf::Vector2f(-50.f, 0.f), 100.f);
    // auto rect_shp = std::make_shared<CSG2D::Rectangle>( sf::Vector2f(50.f, 0.f), 200.f, 200.f);
    // auto shp = std::make_shared<CSG2D::ComplexShape>(circle_shp, rect_shp, op, sf::Vector2f(200.f, 0.f), std::numbers::pi / 4.f);

	auto base = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(0.f, 0.f), 500.f, 500.f);

	auto corner1 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(250.f, 250.f), 200.f, 200.f, std::numbers::pi / 4.f);
	auto shp1 = std::make_shared<CSG2D::ComplexShape>(base, corner1, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f));

	auto corner2 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(250.f, -250.f), 200.f, 200.f, std::numbers::pi / 4.f);
	auto shp2 = std::make_shared<CSG2D::ComplexShape>(shp1, corner2, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f));

	auto corner3 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(-250.f, -250.f), 200.f, 200.f, std::numbers::pi / 4.f);
	auto shp3 = std::make_shared<CSG2D::ComplexShape>(shp2, corner3, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f));

	auto corner4 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(-250.f, 250.f), 200.f, 200.f, std::numbers::pi / 4.f);
	auto shp4 = std::make_shared<CSG2D::ComplexShape>(shp3, corner4, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f), std::numbers::pi / 8.f);

	auto circle1 = std::make_shared<CSG2D::Circle>(sf::Vector2f(0.f, 0.f), 150.f);
	auto circle2 = std::make_shared<CSG2D::Circle>(sf::Vector2f(0.f, 0.f), 80.f);
	auto circle3 = std::make_shared<CSG2D::ComplexShape>(circle1, circle2, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f));

	auto shp5 = std::make_shared<CSG2D::ComplexShape>(shp4, circle3, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 0.f));

	auto rect1 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(50.f, 0.f), 75.f, 200.f);

	auto shp6 = std::make_shared<CSG2D::ComplexShape>(shp5, rect1, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f));

	auto rect2 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(100.f, 40.f), 35.f, 100.f, std::numbers::pi / 12.f);
	auto shp7 = std::make_shared<CSG2D::ComplexShape>(shp6, rect2, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f));

	auto rect3 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(100.f, -40.f), 35.f, 100.f, -std::numbers::pi / 12.f);
	auto shp8 = std::make_shared<CSG2D::ComplexShape>(shp7, rect3, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f));

	auto plus_h = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(0.f, 0.f), 15.f, 40.f);
	auto plus_v = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(0.f, 0.f), 15.f, 40.f, std::numbers::pi / 2.f);
	auto plus1 = std::make_shared<CSG2D::ComplexShape>(plus_v, plus_h, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f));
	auto plus2 = std::make_shared<CSG2D::ComplexShape>(plus_v, plus_h, CSG2D::OPERATION::UNION, sf::Vector2f(50.f, 0.f));
	auto pluses = std::make_shared<CSG2D::ComplexShape>(plus1, plus2, CSG2D::OPERATION::UNION, sf::Vector2f(165.f, 0.f));

	auto shp9 = std::make_shared<CSG2D::ComplexShape>(shp8, pluses, CSG2D::OPERATION::DIFFERENCE, sf::Vector2f(0.f, 200.f));

	auto rect4 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(-250.f, 0.f), 200.f, 50.f);
	auto rect5 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(-210.f, 40.f), 120.f, 50.f, -std::numbers::pi / 4.f);
	auto rect6 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(-210.f, -40.f), 120.f, 50.f, std::numbers::pi / 4.f);
	auto k_part = std::make_shared<CSG2D::ComplexShape>(rect5, rect6, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f));

	auto k = std::make_shared<CSG2D::ComplexShape>(rect4, k_part, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, -200.f));
	auto shp10 = std::make_shared<CSG2D::ComplexShape>(shp9, k, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f));
	
	auto rect7 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(0.f, 0.f), 200.f, 50.f);
	auto rect8 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(50.f, 30.f), 120.f, 50.f, std::numbers::pi / 4.f);
	auto d_part = std::make_shared<CSG2D::ComplexShape>(rect7, rect8, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, -200.f));
	auto rect9 = std::make_shared<CSG2D::Rectangle>(sf::Vector2f(50.f, -230.f), 120.f, 50.f, -std::numbers::pi / 4.f);
	auto d = std::make_shared<CSG2D::ComplexShape>(d_part, rect9, CSG2D::OPERATION::UNION, sf::Vector2f(-60.f, 0.f));

	auto shp11 = std::make_shared<CSG2D::ComplexShape>(shp10, d, CSG2D::OPERATION::UNION, sf::Vector2f(0.f, 0.f));
	

    return shp11;
}
