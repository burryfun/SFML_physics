#ifndef CORE_H
#define CORE_H

#include "Circle.h"
#include "Line.h"
#include "Shape.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
class Core : public sf::Drawable
{
public:
	Core();
	~Core();

	std::vector<Shape*> m_shapes;
	std::vector<Line*> lines;
	sf::VertexArray force;
	sf::Vector2f m_mouse;
	float VISCOSITY;
	float GRAVITY;

	bool				dragged;
	Shape*				draggedShape;
	
	bool isMouseInShape(Shape* shape);
	void pollEvents(const sf::RenderWindow& window, sf::Event& event);
	void initShapes();	
	
	void updateCollisionBorder(const sf::RenderWindow& window);
	void updateCollisionCircles(Circle* c1, Circle* c2);
	void updateCollisionCicleLine(Circle* c, Line* l);
	//void updateCollisionCicleLine(Circle* c, Line* l);
	void updateVelocityShapes(float deltaTime);
	void update(const sf::RenderWindow& window, float& deltaTime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
