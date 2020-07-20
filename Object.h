#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
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
	Object(sf::Vector2f center, float radius);
	~Object();
	

	void setPosition(float x, float y);
	void setAngle(float angle);
	void setAcceleration(sf::Vector2f acceleration);
	void setVelocity(sf::Vector2f velocity);
	
	void updateAcceleration();
	void updateVelocity(const float& time);
	
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getAcceleration();
	
	void move(sf::Vector2f velocity);
	void rotate(float angle);
	
	bool checkCollisionPoint(const sf::Vector2f& mouse);
	void dragging(const sf::Vector2f& mouse);
	void updateEdges(const sf::Vector2f& mouse, bool& dragged);

	void update(const sf::Vector2f& mouse, sf::RenderTarget& target, const float& time);
	void render();
private:
	int				MAX_POINTS;
	float			VISCOSITY; //Коэф-т вязкости
	sf::Color		COLOR_SHAPE;
	sf::Vector2f	viscosity; //Вязкость
	sf::VertexArray m_vertices;
	sf::Vector2f    m_center;
	sf::Vector2f	m_velocity;
	sf::Vector2f	m_acceleration;// while m_a != 0 : m_a -= VISCOSITY
	sf::Color		m_color;
	float           m_radius;
	float           m_angle;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void initVariables();
	void initShape();
};


#endif
