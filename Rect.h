#ifndef RECT_H
#define RECT_H


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <vector>
#include "Shape.h"
#include "Line.h"

class Rect : public Shape
{
public:
					Rect(	sf::Vector2f	position	= sf::Vector2f(0.f, 0.f),
							float			size		= 1.f					,
							sf::Color		color		= sf::Color::Yellow
						);
					Rect(	sf::Vector2f	position	= sf::Vector2f(0.f, 0.f),
							float			width		= 1.f					,
							float			height		= 1.f					,
							sf::Color		color		= sf::Color::Yellow
						);
			
					~Rect();
	
			virtual void			setPosition		(sf::Vector2f)	override;
			virtual void			setAcceleration	(sf::Vector2f)	override;
			virtual void			setVelocity		(sf::Vector2f)	override;
			virtual void			setAngle		(float)			override;

	const	virtual sf::Vector2f	getPosition		()	const		override;
	//const	virtual sf::Vector2f	getAcceleration ()	const		override;
	const	virtual sf::Vector2f	getVelocity		()	const		override;
	const	virtual float			getMass			()	const		override;
	const	virtual sf::FloatRect	getBounds		()	const		override;

			void			render(sf::RenderTarget& target);
	/*
	const	virtual float			getSize			()	const		= 0;
	const	virtual float			getAngle		()	const		= 0;

			virtual void			updateVelocity  (float)			= 0;
			virtual void			update() = 0;

			virtual void			initVariables()					= 0;
*/
			virtual void			initShape()						override;
			std::vector<Line> shape;
	float m_width;
	float m_height;
			//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
