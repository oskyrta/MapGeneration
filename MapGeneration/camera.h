#pragma once
/////////////////////////////////////////////////
// Include
#include <SFML\Graphics.hpp>
#include <boost\property_tree\ptree.hpp>
#include "vec2.h"

/////////////////////////////////////////////////
// Class Camera
class Camera
{
public:
	Camera();
	Camera(int x, int y, std::string name);
	~Camera();

	void setPosition(Vec2 position);
	Vec2 getPosition() { return m_position; };

	void setBackgroundColor(sf::Color color) { m_backgoundColor = color; };
	sf::Color getBackgoundColor() { return m_backgoundColor; }

	Vec2 getSize() { return m_size; };

	sf::RenderWindow* getRenderWindow() { return m_renderWindow; };

	bool cameraFrame();
	void clearWindow();

private:
	Vec2 m_position;
	Vec2 m_size;

	sf::Color m_backgoundColor;
	sf::View m_view;
	sf::RenderWindow* m_renderWindow;
};