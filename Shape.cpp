#include "Shape.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

Shape::Shape(int points, sf::Vector2f pos, sf::Vector2f acc, sf::Vector2f vel, sf::Color col, float ang, float mass)
	: MAX_POINTS(points), m_position(pos), m_acceleration(acc), m_velocity(vel), COLOR(col), m_angle(ang), m_mass(mass)
{
	m_vertices = sf::VertexArray();
	m_colorShape = COLOR;
	m_bounds = sf::FloatRect(0.f, 0.f, 0.f, 0.f);
}
Shape::~Shape()
{

}

void Shape::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_vertices);
}



