#include "Surface.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

void Surface::initShape()
{
	shape.setSize(sf::Vector2f(800, 40));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(0, 560);
}

Surface::Surface()
{
	initShape();
}

Surface::~Surface()
{

}

void Surface::render(sf::RenderTarget* target)
{
	target->draw(shape);
}
