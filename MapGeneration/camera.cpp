////////////////////////////////////////////////
// Include
#include "camera.h"
#include "vec2.h"

////////////////////////////////////////////////
// Class Camera
Camera::Camera()
{
	m_position = Vec2();
	m_size = Vec2();

	m_renderWindow = 0;

	m_view = sf::View();
}

Camera::Camera(int x, int y, std::string name)
{
	m_renderWindow = new sf::RenderWindow(
		sf::VideoMode(x, y, 32),
		name,
		sf::Style::Titlebar | sf::Style::Close
	);

	m_size = Vec2(x, y);
	m_view = sf::View(sf::FloatRect(0, 0, x, y));
	m_position = Vec2();

	m_backgoundColor = sf::Color(25, 26, 29);
}

Camera::~Camera()
{
	if (m_renderWindow)
		delete m_renderWindow;
}

bool Camera::cameraFrame()
{
	if (!m_renderWindow->isOpen())
		return false;

	sf::Event event;
	while (m_renderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_renderWindow->close();
	}

	return true;
}

void Camera::clearWindow()
{
	m_renderWindow->clear(m_backgoundColor);
}

void Camera::setPosition(Vec2 position)
{
	m_view.move(position.x - m_position.x, position.y - m_position.y);
	m_renderWindow->setView(m_view);
	m_position = position;
}