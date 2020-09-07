#include "Rect.h"
#include "Shape.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>


void Rect::initShape()
{
	
	m_vertices.resize(MAX_POINTS);
	m_vertices.setPrimitiveType(sf::LineStrip);
	m_vertices[0] = sf::Vertex(m_position, m_colorShape);
	m_vertices[1] = sf::Vertex(sf::Vector2f(m_position.x + m_width, m_position.y), m_colorShape);
	m_vertices[2] = sf::Vertex(sf::Vector2f(m_position.x + m_width, m_position.y + m_height), m_colorShape);
	m_vertices[3] = sf::Vertex(sf::Vector2f(m_position.x, m_position.y + m_height), m_colorShape);
	m_vertices[4] = sf::Vertex(m_position, m_colorShape);
	
	/*
	Line l1 = Line(m_position.x, m_position.y, m_position.x + m_width, m_position.y);
	Line l2 = Line(m_position.x + m_width, m_position.y, m_position.x + m_width, m_position.y + m_height);
	Line l3 = Line(m_position.x + m_width, m_position.y + m_height, m_position.x, m_position.y + m_height);
	Line l4 = Line(m_position.x, m_position.y + m_height, m_position.x, m_position.y);
	shape.push_back(l1);
	shape.push_back(l2);
	shape.push_back(l3);
	shape.push_back(l4);
*/
	m_bounds = sf::FloatRect(0.f, 0.f, m_width, m_height);
}

Rect::Rect(sf::Vector2f pos, float s, sf::Color col)
	:	Shape(5, pos, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), col, 0.f, 0.f),
		m_width(s), m_height(s)
{
	initShape();
}





Rect::~Rect()
{

}


void Rect::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void Rect::setAcceleration(sf::Vector2f acceleration)
{
	m_acceleration = acceleration;
}
void Rect::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}
void Rect::setAngle(float angle)
{
	m_angle = angle;
}


void Rect::render(sf::RenderTarget &target)
{
	for (auto i : shape)
	{
		target.draw(i);
	}
}

const sf::Vector2f Rect::getPosition() const
{
	return m_position;
}

const sf::Vector2f Rect::getVelocity() const
{
	return m_velocity;
}

const float Rect::getMass() const
{
	return m_mass;
}

const sf::FloatRect Rect::getBounds() const
{
	return m_bounds;
}

