#include "Object.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>
void Object::initVariables()
{
	MAX_POINTS = 40;
	VISCOSITY = 0.8f;
	COLOR_SHAPE = sf::Color::Red;
	GRAVITY = 0.f; // Optimal__1000.f

	m_radius = 10.f;
	m_angle = 0.f;
	m_center = sf::Vector2f(100.f, 100.f);
	m_velocity = sf::Vector2f(0.f, 0.f);
	m_acceleration = sf::Vector2f(0.f, 0.f);
	m_vertices.setPrimitiveType(sf::LinesStrip);
	m_vertices.resize(MAX_POINTS);
	m_color = COLOR_SHAPE;
	m_mass = m_radius;
}

void Object::initShape()
{
	float x = 0.f;
	float y = 0.f;
	for (int i = 0; i != MAX_POINTS-2; i++)
	{
		x = m_center.x + m_radius * cos(((360.f)/(static_cast<float>(MAX_POINTS-3)) * i + m_angle) * M_PI/180.f);
		y = m_center.y + m_radius * sin(((360.f)/(static_cast<float>(MAX_POINTS-3)) * i + m_angle) * M_PI/180.f);
		m_vertices[i] = sf::Vertex(sf::Vector2f(x, y), m_color);
			
	}	
		m_vertices[MAX_POINTS-1].position = m_vertices[0].position;	
		m_vertices[MAX_POINTS - 2] = sf::Vertex(sf::Vector2f(m_center.x, m_center.y), sf::Color::White);
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
	m_radius = rand()%20 + 2.f;
	COLOR_SHAPE = sf::Color::Yellow;
	m_color = COLOR_SHAPE;
	m_velocity = sf::Vector2f(0.f, 0.f);
	m_acceleration = sf::Vector2f(0.f, 0.f);
	m_mass = 10.f*m_radius;
}

Object::~Object()
{
	m_vertices.clear();
}

void Object::setPosition(float x, float y)
{
	m_center.x = x;
	m_center.y = y;
	//initShape();	
}

void Object::setAcceleration(sf::Vector2f acceleration)
{
	m_acceleration.x = acceleration.x;
	m_acceleration.y = acceleration.y;
}


void Object::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

const sf::Vector2f Object::getVelocity() const
{
	return m_velocity;
}

void Object::updateVelocity(float deltaTime)
{
	//std::cout << deltaTime << std::endl;
	//std::cout << getVelocity().x << " " << getVelocity().y << std::endl; 
	
	m_acceleration = -m_velocity * VISCOSITY;
	m_acceleration.y += GRAVITY;
	m_velocity += m_acceleration * deltaTime;
	setPosition(m_center.x + m_velocity.x*deltaTime, m_center.y + m_velocity.y*deltaTime);
	setAngle(atan2f(m_velocity.y, m_velocity.x)*180.f/M_PI);
	if ((std::abs(m_velocity.x) < 0.1f || std::abs(m_velocity.y) < 0.1f) && GRAVITY == 0.f)
	{
		m_velocity = sf::Vector2f(0.f,0.f);
	}
}

const sf::Vector2f Object::getPosition() const
{
	return m_center;
}

float Object::getRadius()
{
	return m_radius;
}

float Object::getMass()
{
	return m_mass;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vertices);
}

void Object::setAngle(float angle)
{
	m_angle = angle;
	initShape();
}

void Object::updateCollisionBorder(const sf::RenderWindow& window)
{
	//std::cout << m_center.x << " " << m_center.y << std::endl;
	if ((m_center.x + m_radius) > window.getSize().x)
	{
		setPosition(window.getSize().x - m_radius, m_center.y);
		m_velocity.x = -m_velocity.x;
	}
	if ((m_center.x - m_radius) < 0.f)
	{
		setPosition(m_radius, m_center.y);
		m_velocity.x = -m_velocity.x;
	}
	if ((m_center.y + m_radius) > window.getSize().y)
	{
		setPosition(m_center.x, window.getSize().y - m_radius);
		m_velocity.y = -m_velocity.y;
	}
	if ((m_center.y - m_radius) < 0.f)
	{
		setPosition(m_center.x, m_radius);
		m_velocity.y = -m_velocity.y;
	}
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
		return true;
	}
	m_color = COLOR_SHAPE;
	return false;
}



void Object::update(const sf::RenderWindow& window, float deltaTime)
{
	initShape();
	updateCollisionBorder(window);
	updateVelocity(deltaTime);
}

