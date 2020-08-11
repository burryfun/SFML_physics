#include "Core.h"
#include "Circle.h"
#include "Line.h"
#include "Shape.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

void Core::initShapes()
{
	/*Circle* circle = new Circle(sf::Vector2f(100.f,100.f), 15, sf::Color::Red, 40);
	Circle* circle2 = new Circle(sf::Vector2f(500.f,50.f), 10);
	m_shapes.push_back(circle);
	m_shapes.push_back(circle2);

	Line* line2 = new Line(50, 500, 600, 250);
	lines.push_back(line2);	
	*/

	Line* line1 = new Line(400, 300, 800, 300);
	lines.push_back(line1);	
	for(int i = 0; i != 5; i++)
	{
		Circle* c = new Circle(sf::Vector2f(60*i, 20), 10+2*i);
		m_shapes.push_back(c);
	}

	for(int i = 0; i != 5; i++)
	{
		Circle* c = new Circle(sf::Vector2f(800 - 60*i, 20), 10+2*i);
		m_shapes.push_back(c);
	}
}

Core::Core()
{
	VISCOSITY = 0.8f;
	GRAVITY = 2000.f;

	dragged = false;
	force = sf::VertexArray(sf::LineStrip, 2);
	
	initShapes();
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
	for(auto shape : m_shapes)
	{
		if ((shape->m_position.x + shape->getBounds().width/2) > window.getSize().x)
		{
			shape->setPosition(sf::Vector2f(window.getSize().x - shape->getBounds().width/2, shape->m_position.y));
			shape->m_velocity.x = -shape->m_velocity.x;
		}
		if ((shape->m_position.x - shape->getBounds().width/2) < 0.f)
		{
			shape->setPosition(sf::Vector2f(shape->getBounds().width/2, shape->m_position.y));
			shape->m_velocity.x = -shape->m_velocity.x;
		}
		if ((shape->m_position.y + shape->getBounds().height/2) > window.getSize().y)
		{
			if (GRAVITY == 0.f)
			{
				shape->setPosition(sf::Vector2f(shape->m_position.x, window.getSize().y - shape->getBounds().height/2));
				shape->m_velocity.y = -shape->m_velocity.y;
			}
			else
			{
				shape->setPosition(sf::Vector2f(shape->m_position.x, window.getSize().y - shape->getBounds().height/2));
				// M1 > M2 ==> BOUNCE1 < BOUNCE2
				shape->m_velocity.y = -shape->m_velocity.y * (1 - shape->m_mass) / (1 + shape->m_mass);
			}
		}
		if ((shape->m_position.y - shape->getBounds().height/2) < 0.f)
		{
			if (GRAVITY == 0.f)
			{
				shape->m_velocity.y = -shape->m_velocity.y;
				shape->setPosition(sf::Vector2f(shape->m_position.x, shape->getBounds().height/2));
			}
			else
			{
				shape->setPosition(sf::Vector2f(shape->m_position.x, shape->getBounds().height/2));
				// M1 > M2 ==> BOUNCE1 < BOUNCE2
				shape->m_velocity.y = -shape->m_velocity.y * (1 - shape->m_mass) / (1 + shape->m_mass);
			}
		}
	}
}

void Core::updateCollisionCircles(Circle *c1, Circle *c2)
{
	
	sf::Vector2f distance = c1->getPosition() - c2->getPosition();
	float distanceBetween = (sqrtf((distance.x*distance.x) + (distance.y*distance.y)));
	if (c1 != c2)
	{
		if (distanceBetween < (c1->getRadius()+c2->getRadius()))
		{

			float overlap = (distanceBetween - c1->getRadius() - c2->getRadius()) / 2.f;
			float moveX = (overlap * (c1->getPosition().x - c2->getPosition().x) / distanceBetween);
			float moveY = (overlap * (c1->getPosition().y - c2->getPosition().y) / distanceBetween);	
			c1->setPosition(sf::Vector2f(c1->getPosition().x - moveX, c1->getPosition().y - moveY));
			c2->setPosition(sf::Vector2f(c2->getPosition().x +  moveX, c2->getPosition().y + moveY));

			sf::Vector2f normal;
			normal.x = distance.x / distanceBetween;
			normal.y = distance.y / distanceBetween;

			sf::Vector2f tangential;
			tangential.x = -normal.y;
			tangential.y =  normal.x;

			float dotProductTangential1 = c1->getVelocity().x*tangential.x + 
											c1->getVelocity().y*tangential.y;
			float dotProductTangential2 = c2->getVelocity().x*tangential.x +
											c2->getVelocity().y*tangential.y;
			
			float dotProductNormal1 = c1->getVelocity().x*normal.x + c1->getVelocity().y*normal.y;
			float dotProductNormal2 = c2->getVelocity().x*normal.x + c2->getVelocity().y*normal.y;

			float m1 = (2.f*c2->getMass()*dotProductNormal2 + 
						dotProductNormal1*(c1->getMass() - c2->getMass())) / 
							(c1->getMass()+c2->getMass());
			/*fixed high acceleration (m2 ~ c1.mas - c2.mas)*/
			float m2 = (2.f*c1->getMass()*dotProductNormal1 + 
						dotProductNormal2*(c2->getMass() - c1->getMass())) / 
							(c1->getMass()+c2->getMass());
			c1->setVelocity(dotProductTangential1*tangential + m1*normal);
			c2->setVelocity(dotProductTangential2*tangential + m2*normal);
			
		}
	}
}

void Core::updateCollisionCicleLine(Circle *circle, Line *line)
{
	sf::Vector2f p = sf::Vector2f(circle->getPosition());	//center of circle
	sf::Vector2f s = line->getPoints()[0].position;			//point at start of line
	sf::Vector2f e = line->getPoints()[1].position;			//point at ent of line
	sf::Vector2f ps = p - s;
	sf::Vector2f se = e - s;
	float lengthLine = (e.x - s.x) * (e.x - s.x) + (e.y - s.y) * (e.y - s.y);
	float t = ((ps.x * se.x) + (ps.y * se.y)) /	lengthLine; //point of normal on line
	sf::Vector2f st;
	st.x = s.x + t*se.x;
	st.y = s.y + t*se.y;

	sf::Vector2f distance = p - st;
	float distanceBetween = sqrtf((distance.x*distance.x) + (distance.y*distance.y));
	
	sf::Vector2f normal = distance / distanceBetween;
	float dotProductNormal = circle->getVelocity().x*normal.x + 
								circle->getVelocity().y*normal.y;
	
	sf::Vector2f tangential = sf::Vector2f(-normal.y, normal.x);
	float dotProductTangential = circle->getVelocity().x*tangential.x + 
									circle->getVelocity().y * tangential.y;

	if (distanceBetween <= circle->getRadius())
	{
		if (t > -0.f && t < 1.f)
		{
			if (GRAVITY == 0.f)
			{
				
				circle->setVelocity(sf::Vector2f(
											-normal.x*dotProductNormal + 
											tangential.x*dotProductTangential,
											-normal.y*dotProductNormal +
											tangential.y*dotProductTangential));
			}
			else
			{
			circle->setVelocity(sf::Vector2f(
											-normal.x*dotProductNormal + 
											tangential.x*dotProductTangential,
											// M1 > M2 ==> BOUNCE1 < BOUNCE2
											-normal.y*dotProductNormal * (1 - circle->getMass())/(1 + circle->m_mass) +
											tangential.y*dotProductTangential));
			}
		
			float overlap = distanceBetween - circle->getRadius();
			circle->setPosition(sf::Vector2f(p.x - distance.x * overlap / distanceBetween, 
												p.y -distance.y * overlap / distanceBetween));
		}
	}
}

void Core::updateVelocityShapes(float deltaTime)
{
	for (auto i : m_shapes)
	{
		std::cout << i->getVelocity().y << std::endl;
		i->m_acceleration.x = -i->m_velocity.x * VISCOSITY;
		i->m_acceleration.y = -i->m_velocity.y * VISCOSITY;
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
			Circle* newObject = new Circle(m_mouse, rand()%20 + 10);
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
	if (dragged)
	{
		force[0] = sf::Vertex(sf::Vector2f(draggedShape->getPosition()), sf::Color::White);
		force[1] = sf::Vertex(sf::Vector2f(m_mouse), sf::Color::White);
	}
	else
	{
		force[0].position = sf::Vector2f(0.f,0.f);
		force[1].position = sf::Vector2f(0.f,0.f);
	}
	/*
	 * COLLISION FOR CIRCLES
	*/
	for (auto shape1 : m_shapes)
	{
		for (auto shape2 : m_shapes)
		{	if (dynamic_cast<Circle*>(shape1) != dynamic_cast<Circle*>(shape2))
			{
				updateCollisionCircles(dynamic_cast<Circle*>(shape1), dynamic_cast<Circle*>(shape2));
			}
		}
		for (auto line : lines)
		{
			updateCollisionCicleLine(dynamic_cast<Circle*>(shape1), line);
		}
	}
	updateCollisionBorder(window);
	updateVelocityShapes(deltaTime);
}

void Core::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(force);
	for (auto i : lines)
	{
		target.draw(*i);
	}
	for (auto i : m_shapes)
	{
		target.draw(i->m_vertices);
	}
}



