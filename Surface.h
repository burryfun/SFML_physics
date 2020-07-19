#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Surface
{
public:
	Surface();
	virtual ~Surface();

	void update();
	void render(sf::RenderTarget* target);
private:
	sf::RectangleShape shape;

	void initShape();
};
