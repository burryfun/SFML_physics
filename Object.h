#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>

#include <SFML/Window/Window.hpp>
#include <cmath>

class Object : public sf::Drawable, sf::Transformable
{
public:

	
	Object();
	~Object();
	

	void setPosition(float x, float y);
	void setAngle(float angle);
	void setAcceleration(sf::Vector2f acceleration);
	void updateAcceleration();
	void setVelocity(sf::Vector2f velocity);
	void updateVelocity(const float& time);

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getAcceleration();
	
	void move(sf::Vector2f velocity);
	void rotate(float angle);

	void updateEdges(const sf::Vector2f& mouse, sf::RenderTarget& target);

	void update(const sf::Vector2f& mouse, sf::RenderTarget& target, const float& time);
	void render();
private:
	int				MAX_POINTS;
	float			VISCOSITY;
	sf::Vector2f	viscosity; //Вязкость
	sf::VertexArray distance = sf::VertexArray(sf::LinesStrip, 2);
	sf::VertexArray m_vertices;
	sf::Vector2f    m_center;
	sf::Vector2f	m_velocity;
	sf::Vector2f	m_acceleration;// while m_a != 0 : m_a -= VISCOSITY
	float           m_radius;
	float           m_angle;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void initVariables();
	void initShape();
};


#endif
