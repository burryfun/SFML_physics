#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>

#include "Shape.h"

class Circle : public Shape
{
public:
	Circle(sf::Vector2f centerPos, float radius, sf::Color color=sf::Color::Yellow, int pointCount = 40);
	~Circle();
			virtual void			setPosition		(sf::Vector2f)	override;
			virtual void			setAcceleration	(sf::Vector2f)	override;
			virtual void			setVelocity		(sf::Vector2f)	override;
			virtual void			setAngle		(float)			override;

	const	virtual sf::Vector2f	getPosition		()	const		override;
/*
	const	virtual sf::Vector2f	getAcceleration ()	const		override;
	const	virtual sf::Vector2f	getVelocity		()	const		override;
	const	virtual float			getSize			()	const		override;
	const	virtual float			getAngle		()	const		override;

			virtual void			initVariables()					= 0;
*/
			virtual void			initShape()						override;
//			sf::VertexArray m_vertices;	
	int MAX_POINTS;
	float m_radius;
};

#endif
