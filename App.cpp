#include "App.h"
#include "Line.h"
#include "Object.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>


const bool App::running() const
{
	return window->isOpen();
}

void App::initWindow()
{
	videoMode = sf::VideoMode(800, 600);
	window = new sf::RenderWindow(videoMode, "Simple physics", sf::Style::Default);	
	window->setFramerateLimit(60);
	force = sf::VertexArray(sf::LinesStrip, 2);
	Line* line1 = new Line(100.f,100.f,700.f,100.f, sf::Color::Red);
	Line* line2 = new Line(100.f,500.f,700.f,500.f, sf::Color::Red);
	lines.push_back(line1);
	lines.push_back(line2);
}


void App::dragging(Object *circle)
{
	if (dragged)
	{
		force[0] = circle->getPosition();
		force[1] = m_mouse;
	}
	else
	{
		force[1] = circle->getPosition();
	}
}

App::App()
{
	initWindow();
}

App::~App()
{
	delete window;
}

void App::pollEvents()
{
	while (window->pollEvent(sfmlEvent))
	{
		switch (sfmlEvent.type)
		{
			case sf::Event::Closed:
				window->close(); 
				break;
			case sf::Event::KeyPressed:
				if (sfmlEvent.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (sfmlEvent.mouseButton.button == sf::Mouse::Left)
				{
					Object* newObject = new Object(m_mouse, 50);
					circles.push_back(newObject);
				}
				if (sfmlEvent.mouseButton.button == sf::Mouse::Right)
				{
					for (auto circle : circles)
					{
						if (circle->checkCollisionPoint(m_mouse))
						{
							draggedCircle = circle;
							dragged = true;
						}
					}	
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (sfmlEvent.mouseButton.button == sf::Mouse::Right && dragged)
				{
					draggedCircle->setVelocity(sf::Vector2f((draggedCircle->getPosition().x - m_mouse.x),
															(draggedCircle->getPosition().y - m_mouse.y)));
					dragged = false;
				}
				break;
			case sf::Event::MouseMoved:
				m_mouse.x = sfmlEvent.mouseMove.x;
				m_mouse.y = sfmlEvent.mouseMove.y;
				break;
		}
	}	
}

sf::Vector2f App::getMouseCoords()
{
	return m_mouse;
}

void App::collisionObjects(Object* obj1, Object* obj2)
{
	sf::Vector2f distance = obj1->getPosition() - obj2->getPosition();
	float distanceBetween = (sqrtf((distance.x*distance.x) + (distance.y*distance.y)));
	if (obj1 != obj2)
	{
		if (distanceBetween < (obj1->getRadius()+obj2->getRadius()))
		{

			float overlap = (distanceBetween - obj1->getRadius() - obj2->getRadius()) / 2.f;
			float moveX = (overlap * (obj1->getPosition().x - obj2->getPosition().x) / distanceBetween);
			float moveY = (overlap * (obj1->getPosition().y - obj2->getPosition().y) / distanceBetween);	
			obj1->setPosition(obj1->getPosition().x - moveX, obj1->getPosition().y - moveY);
			obj2->setPosition(obj2->getPosition().x +  moveX, obj2->getPosition().y + moveY);

			sf::Vector2f normal;
			normal.x = distance.x / distanceBetween;
			normal.y = distance.y / distanceBetween;

			sf::Vector2f tangential;
			tangential.x = -normal.y;
			tangential.y =  normal.x;

			float dotProductTangential1 = obj1->getVelocity().x*tangential.x + 
											obj1->getVelocity().y*tangential.y;
			float dotProductTangential2 = obj2->getVelocity().x*tangential.x +
											obj2->getVelocity().y*tangential.y;
			
			float dotProductNormal1 = obj1->getVelocity().x*normal.x + obj1->getVelocity().y*normal.y;
			float dotProductNormal2 = obj2->getVelocity().x*normal.x + obj2->getVelocity().y*normal.y;
	
			float m1 = (2.f*obj2->getMass()*dotProductNormal2 + 
						dotProductNormal1*(obj1->getMass() - obj2->getMass())) / 
							(obj1->getMass()+obj2->getMass());
			/*fixed high acceleration (m2 ~ obj1.mas - obj2.mas)*/
			float m2 = (2.f*obj1->getMass()*dotProductNormal1 + 
						dotProductNormal2*(obj2->getMass() - obj1->getMass())) / 
							(obj1->getMass()+obj2->getMass());
			obj1->setVelocity(dotProductTangential1*tangential + m1*normal);
			obj2->setVelocity(dotProductTangential2*tangential + m2*normal);
			
		}
	}
}

void App::collisionCircleLine(Object* circle, Line* line)
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
			circle->setVelocity(sf::Vector2f(-normal.x*dotProductNormal + tangential.x*dotProductTangential,
												-normal.y*dotProductNormal + tangential.y*dotProductTangential));
		
			float overlap = distanceBetween - circle->getRadius();
			circle->setPosition(p.x - distance.x * overlap / distanceBetween, 
									p.y -distance.y * overlap / distanceBetween);
		}
	}

}

void App::update()
{
	float deltaTime = 0.f;
	deltaTime = clock.restart().asSeconds();
	pollEvents();
	for (auto circle : circles)
	{
		for (auto circle2 : circles)
		{
			collisionObjects(circle, circle2);
		}
		for (auto line : lines)
		{
			collisionCircleLine(circle, line);
		}
		if (dragged)
		{
			dragging(draggedCircle);
		}
		else
		{	
			force[0].position = sf::Vector2f(0.f, 0.f);
			force[1].position = sf::Vector2f(0.f, 0.f);
		}
		circle->update(*window,	deltaTime);
	}
}

void App::render()
{
	window->clear();
	for (auto circle : circles)
	{
		window->draw(*circle);
	}
	for (auto line : lines)
	{
		window->draw(*line);
	}
	window->draw(force);	
	window->display();
}
