#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <cmath>

class Shape //: public sf::Drawable
{
public:
					Shape(	sf::Vector2f position = sf::Vector2f(0.f, 0.f),
							sf::Vector2f acceleration = sf::Vector2f(0.f, 0.f),
							sf::Vector2f velocity = sf::Vector2f(0.f, 0.f),
							sf::Color color = sf::Color::Yellow,
							float angle = 0.f,
							float mass = 0.f
						 );
			virtual ~Shape();
	
			virtual void			setPosition		(sf::Vector2f)	= 0;
			virtual void			setAcceleration	(sf::Vector2f)	= 0;
			virtual void			setVelocity		(sf::Vector2f)	= 0;
			virtual void			setAngle		(float)			= 0;

	const	virtual sf::Vector2f	getPosition		()	const		= 0;
	//const	virtual sf::Vector2f	getAcceleration ()	const		= 0;
	const	virtual sf::Vector2f	getVelocity		()	const		= 0;
	const	virtual float			getMass			()	const		= 0;
	const	virtual sf::FloatRect	getBounds		()	const		= 0;

	/*
	const	virtual float			getSize			()	const		= 0;
	const	virtual float			getAngle		()	const		= 0;

			virtual void			updateVelocity  (float)			= 0;
			virtual void			update() = 0;
			virtual void			render() = 0;

			virtual void			initVariables()					= 0;
*/
			virtual void			initShape()						= 0;
	sf::VertexArray m_vertices;	
	sf::Vector2f m_position;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_velocity;
	sf::Color m_colorShape;
	sf::Color COLOR;
	sf::FloatRect m_bounds;
	float m_mass;
	float m_angle;
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
