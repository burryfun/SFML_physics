#include "Circle.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>


void Circle::initShape()
{

	m_vertices.resize(MAX_POINTS);
	m_vertices.setPrimitiveType(sf::LinesStrip);

	float x = 0.f;
	float y = 0.f;
	for (int i = 0; i != MAX_POINTS-2; i++)
	{
		x = m_position.x + m_radius * cos(((360.f)/(static_cast<float>(MAX_POINTS-3)) * i + m_angle) * M_PI/180.f);
		y = m_position.y + m_radius * sin(((360.f)/(static_cast<float>(MAX_POINTS-3)) * i + m_angle) * M_PI/180.f);
		m_vertices[i] = sf::Vertex(sf::Vector2f(x, y), m_colorShape);
			
	}	
		m_vertices[MAX_POINTS-1].position = m_vertices[0].position;	
		m_vertices[MAX_POINTS - 2] = sf::Vertex(sf::Vector2f(m_position.x, m_position.y), sf::Color::White);
		m_bounds = sf::FloatRect(0.f, 0.f, 2*m_radius, 2*m_radius);
}

Circle::Circle(sf::Vector2f centerPos, float radius, sf::Color color, int pointCount)
	: Shape(pointCount, centerPos, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), color, 0.f, 0.f), 
		m_radius(radius)
{
	initShape();
	m_mass = 0.01f * m_radius;
}

Circle::~Circle()
{
}

void Circle::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void Circle::setAcceleration(sf::Vector2f acceleration)
{
	m_acceleration = acceleration;
}
void Circle::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}
void Circle::setAngle(float angle)
{
	m_angle = angle;
}


const sf::Vector2f Circle::getPosition() const
{
	return m_position;
}

const sf::Vector2f Circle::getVelocity() const
{
	return m_velocity;
}

const float Circle::getMass() const
{
	return m_mass;
}

const sf::FloatRect Circle::getBounds() const
{
	return m_bounds;
}
const float Circle::getRadius() const
{
	return m_radius;
}

