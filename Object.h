#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <cmath>

class Object : public sf::Drawable, sf::Transformable
{
public:
	
	Object();
	Object(sf::Vector2f center, float radius);
	~Object();

	void			setPosition(float x, float y);
	void			setAngle(float angle);
	void			setAcceleration(sf::Vector2f acceleration);
	void			setVelocity(sf::Vector2f velocity);
	
	const sf::Vector2f	getPosition() const;
	const sf::Vector2f	getVelocity() const;
	const sf::Vector2f	getAcceleration();
	float			getRadius();
	float			getMass();

	
	void			updateVelocity(float deltaTime);
	bool			checkCollisionPoint(const sf::Vector2f& mouse);
	void			updateCollisionBorder(const sf::RenderWindow& window);

	void			update(const sf::RenderWindow& window, float deltaTime);
	void			render();
private:
	int				MAX_POINTS;
	float			VISCOSITY; //Коэф-т вязкости
	float			GRAVITY;
	sf::VertexArray m_vertices;
	sf::Color		COLOR_SHAPE;
	sf::Color		m_color;
	sf::Vector2f	viscosity; //Вязкость
	sf::Vector2f    m_center;
	sf::Vector2f	m_velocity;
	sf::Vector2f	m_acceleration;// while m_a != 0 : m_a -= VISCOSITY
	float           m_radius;
	float           m_angle;
	float			m_mass;
	void			initVariables();
	void			initShape();
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif
