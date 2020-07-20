#include "Object.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <iostream>
void Object::initVariables()
{
	MAX_POINTS = 40;
	VISCOSITY = 0.02f;
	COLOR_SHAPE = sf::Color::Red;

	m_radius = 100;
	m_angle = 0;
	m_center = sf::Vector2f(100.f, 100.f);
	m_velocity = sf::Vector2f(0.f, 0.f);
	m_acceleration = sf::Vector2f(0.f, 0.f);
	m_vertices.setPrimitiveType(sf::LinesStrip);
	m_vertices.resize(MAX_POINTS);
	m_color = COLOR_SHAPE;
}

void Object::initShape()
{
	float x = m_center.x + m_radius * cos((m_angle)/(static_cast<float>(MAX_POINTS-2)) * M_PI/180.f);
	float y = m_center.x + m_radius * sin((m_angle)/(static_cast<float>(MAX_POINTS-2)) * M_PI/180.f);

	for (int i = 0; i != MAX_POINTS-1; i++)
	{
		x = m_center.x + m_radius * cos(((360.f)/(static_cast<float>(MAX_POINTS-2)) * i + m_angle) * M_PI/180.f);
		y = m_center.y + m_radius * sin(((360.f)/(static_cast<float>(MAX_POINTS-2)) * i + m_angle) * M_PI/180.f);
		//x *= cos(45.f * M_PI/180.f);
		//y *= sin(45.f * M_PI/180.f);	
		//vertices[i] = sf::Vertex(sf::Vector2f(x, y), sf::Color::Red);	
		//vertices[MAX_POINTS - 1] = sf::Vertex(sf::Vector2f(400, 300), sf::Color::White);
		m_vertices[i] = sf::Vertex(sf::Vector2f(x, y), m_color);
		m_vertices[MAX_POINTS].position = m_vertices[0].position;	
		m_vertices[MAX_POINTS - 1] = sf::Vertex(sf::Vector2f(m_center.x, m_center.y), sf::Color::White);
			
	}	
	/*
	for (int i = 0; i != MAX_POINTS - 1; i++)
	{
		x = m_center.x + m_radius * cos((360.f + m_angle)/(static_cast<float>(MAX_POINTS-2)) * i * M_PI/180.f);
		y = m_center.y + m_radius * sin((360.f + m_angle)/(static_cast<float>(MAX_POINTS-2)) * i * M_PI/180.f);
		//vertices[i] = sf::Vertex(sf::Vector2f(x, y), sf::Color::Red);	
		//vertices[MAX_POINTS - 1] = sf::Vertex(sf::Vector2f(400, 300), sf::Color::White);
		m_vertices[i] = sf::Vertex(sf::Vector2f(x, y), sf::Color::Red);	
		m_vertices[MAX_POINTS - 1] = sf::Vertex(sf::Vector2f(m_center.x, m_center.y), sf::Color::White);	
	}	
	*/
	
}

Object::Object()
{
	initVariables();
	initShape();
}

Object::Object(sf::Vector2f center, float radius)
{
	initVariables();
	m_center = center;
	m_radius = rand()%50 + 10;
	COLOR_SHAPE = sf::Color::Yellow;
	m_color = COLOR_SHAPE;
	m_velocity = sf::Vector2f(0.f, 0.f);
	m_acceleration = sf::Vector2f(0.f, 0.f);
}

Object::~Object()
{

}


void Object::setPosition(float x, float y)
{
	m_center.x = x;
	m_center.y = y;
	initShape();	
}

void Object::setAcceleration(sf::Vector2f acceleration)
{
	m_acceleration.x = acceleration.x;
	m_acceleration.y = acceleration.y;
}

void Object::updateAcceleration()
{
	if (m_acceleration.x > 0.f)
		m_acceleration.x = m_acceleration.x + viscosity.x;
	if (m_acceleration.y > 0.f)
		m_acceleration.y = m_acceleration.y + viscosity.y;
}

void Object::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

sf::Vector2f Object::getVelocity()
{
	return m_velocity;
}

void Object::updateVelocity(const float& time)
{
	std::cout << getVelocity().x << " " << getVelocity().y << std::endl; 
	updateAcceleration();
	viscosity.x = -m_velocity.x * VISCOSITY;
	viscosity.y = -m_velocity.y * VISCOSITY;
	m_velocity.x += (m_acceleration.x + viscosity.x)/2;
	m_velocity.y += (m_acceleration.y + viscosity.y)/2;
	//rotate(m_velocity.x);
	if (std::abs(m_velocity.x) > 0.01f || std::abs(m_velocity.y) > 0.01f)
	{
		setPosition(m_center.x + m_velocity.x, m_center.y + m_velocity.y);
	}
	else
	{
		m_velocity = sf::Vector2f(0.f,0.f);
	}
}

sf::Vector2f Object::getPosition()
{
	return m_center;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vertices);
}

void Object::move(sf::Vector2f velocity)
{
	setPosition(m_center.x + velocity.x, m_center.y + velocity.y);	
}

void Object::setAngle(float angle)
{
	m_angle = angle;
	initShape();
}

void Object::rotate(float angle)
{
	setAngle(m_angle + angle);
}
bool Object::checkCollisionPoint(const sf::Vector2f& mouse)
{
	float x_mouse = mouse.x;
	float y_mouse = mouse.y;
	if ( ((x_mouse - m_center.x)*(x_mouse - m_center.x) +
		  (y_mouse - m_center.y)*(y_mouse - m_center.y)) <= m_radius*m_radius )
	{
		for (int i = 0; i != MAX_POINTS; i++)
		{
			m_color = sf::Color::Cyan;
		}
		//std::cout << "mouse in circle area" << std::endl;
		return true;
	}
	m_color = COLOR_SHAPE;
	return false;
}


void Object::dragging(const sf::Vector2f& mouse)
{
	sf::Vector2f force = sf::Vector2f(mouse - m_center);
	setAcceleration(force);
	
}

void Object::update(const sf::Vector2f& mouse, sf::RenderTarget& target, const float& time)
{
	initShape();
	updateVelocity(time);
}

