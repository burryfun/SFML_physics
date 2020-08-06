#include "Core.h"
#include "Circle.h"
#include "Shape.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <vector>

Core::Core(std::vector<Shape*> shapes)
	: m_shapes(shapes)
{
	VISCOSITY = 0.8f;
	GRAVITY = 1000.f;

	dragged = false;
}

Core::~Core()
{

}

bool Core::isMouseInShape(Shape* shape)
{
		float x_mouse = m_mouse.x;
		float y_mouse = m_mouse.y;
		/* 
		 * FOR CIRCLES
		*/
		if (dynamic_cast<Circle*>(shape))
		{
			if(((x_mouse - shape->m_position.x)*(x_mouse - shape->m_position.x) +
				(y_mouse - shape->m_position.y)*(y_mouse - shape->m_position.y)) <= 
					dynamic_cast<Circle*>(shape)->m_radius * dynamic_cast<Circle*>(shape)->m_radius)
			{
				for (int i = 0; i != (dynamic_cast<Circle*>(shape)->MAX_POINTS); i++)
				{
					shape->m_colorShape = sf::Color::Cyan;
				}
				return true;
			}
			shape->m_colorShape = shape->COLOR;
		}
	return false;
}

void Core::updateCollisionBorder(const sf::RenderWindow& window)
{
	//std::cout << m_center.x << " " << m_center.y << std::endl;
	for(auto shape : m_shapes)
	{
		if ((shape->m_position.x + shape->m_bounds.width/2) > window.getSize().x)
		{
			shape->setPosition(sf::Vector2f(window.getSize().x - shape->m_bounds.width/2, shape->m_position.y));
			shape->m_velocity.x = -shape->m_velocity.x;
		}
		if ((shape->m_position.x - shape->m_bounds.width/2) < 0.f)
		{
			shape->setPosition(sf::Vector2f(shape->m_bounds.width/2, shape->m_position.y));
			shape->m_velocity.x = -shape->m_velocity.x;
		}
		if ((shape->m_position.y + shape->m_bounds.height/2) > window.getSize().y)
		{
			shape->setPosition(sf::Vector2f(shape->m_position.x, window.getSize().y - shape->m_bounds.height/2));
			shape->m_velocity.y = -shape->m_velocity.y;
		}
		if ((shape->m_position.y - shape->m_bounds.height/2) < 0.f)
		{
			shape->setPosition(sf::Vector2f(shape->m_position.x, shape->m_bounds.height/2));
			shape->m_velocity.y = -shape->m_velocity.y;
		}
	}
}


void Core::updateVelocityShapes(float deltaTime)
{
	for (auto i : m_shapes)
	{
		i->m_acceleration = -i->m_velocity * VISCOSITY;
		i->m_acceleration.y += GRAVITY;
		i->m_velocity += i->m_acceleration * deltaTime;
		i->setPosition(sf::Vector2f(i->m_position.x + i->m_velocity.x*deltaTime, 
									i->m_position.y + i->m_velocity.y*deltaTime));
		i->setAngle(atan2f(i->m_velocity.y, i->m_velocity.x)*180.f/M_PI);
		if ((std::abs(i->m_velocity.x) < 0.1f || std::abs(i->m_velocity.y) < 0.1f) && GRAVITY == 0.f)
		{
			i->m_velocity = sf::Vector2f(0.f,0.f);
		}
		i->initShape();
	}
}

void Core::pollEvents(const sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		m_mouse.x = event.mouseMove.x;
		m_mouse.y = event.mouseMove.y;
	}
	if (event.type == sf::Event::MouseButtonPressed)
	{
	
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			Circle* newObject = new Circle(m_mouse, 10);
			m_shapes.push_back(newObject);
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			for (auto shape : m_shapes)
			{
				if (isMouseInShape(shape))
				{
					draggedShape = shape;
					dragged = true;
				}
			}	
		}
	}
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Right && dragged)
		{
			draggedShape->setVelocity(sf::Vector2f((draggedShape->getPosition().x - m_mouse.x),
													(draggedShape->getPosition().y - m_mouse.y)));
			dragged = false;
		}
	}
}

void Core::update(const sf::RenderWindow& window, float& deltaTime)
{
	updateCollisionBorder(window);
	updateVelocityShapes(deltaTime);
}

void Core::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto i : m_shapes)
	{
		target.draw(i->m_vertices);
	}
}



