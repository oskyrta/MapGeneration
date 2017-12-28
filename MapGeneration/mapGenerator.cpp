#include "mapGenerator.h"
#include "camera.h"
#include "utils.h"

#include <iostream>

void CreateDynamicArray(float **a, int size)
{
	a = new float*[size];

	for (int i = 0; i < size; i++)
		a[i] = new float[size];
}

void DeleteDynamicArray(float **a, int size)
{
	for (int i = 0; i < size; i++)
		delete[] a[i];

	delete[] a;
}

MapGenerator::MapGenerator()
{
	m_camera = new Camera(512, 320, "Map Generation");

	m_fmap = new float*[kSize];

	for (int i = 0; i < kSize; i++)
		m_fmap[i] = new float[kSize];

	for (int y = 0; y < kSize; y++)
	{
		for (int x = 0; x < kSize; x++)
		{
			m_map[x][y] = 0;
			m_fmap[x][y] = 0;
		}
	}

	srand(time(0));
}

MapGenerator::~MapGenerator()
{
	if (m_camera)
		delete m_camera;

	DeleteDynamicArray(m_fmap, kSize);
}

float GetAverage(float **f, int tx, int ty)
{
	float tmp = 0;

	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			if (x == 0 && y == 0)
				continue;
			tmp += f[x + tx][y + ty];
		}
	}

	return tmp / 8;
}

void BilinearInterpolate(float **a, int lvl)
{ 
	for (int n = 0; n < lvl; n++)
	{
		for (int y = 1; y < kSize-1; y++)
		{
			for (int x = 1; x < kSize-1; x++)
			{
				a[x][y] = GetAverage(a, x, y);
			}
		}
	}
}

void MapGenerator::RandomPlusInterpolateGenerate(float tf, int lvl)
{
	int buff[kSize][kSize];

	// Fill the map by ramdom values
	for (int y = 0; y < kSize; y++)
	{
		for (int x = 0; x < kSize; x++)
		{
			if (x == 0 || y == 0 || x == kSize - 1 || y == kSize - 1)
				m_fmap[x][y] = 1;
			else 
				m_fmap[x][y] = GetRandomFloat(0, 1);
		}
	}

	BilinearInterpolate(m_fmap, lvl);

	for (int y = 0; y < kSize; y++)
	{
		for (int x = 0; x < kSize; x++)
		{
			if (m_fmap[x][y] > tf) m_map[x][y] = 1;
			else m_map[x][y] = 0;
		}
	}
}

bool MapGenerator::DrawCave()
{
	if(!m_camera->cameraFrame()) return false;
	m_camera->clearWindow();

	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(3, 3));

	for (int y = 0; y < kSize; y++)
	{
		for (int x = 0; x < kSize; x++)
		{
			rect.setPosition(sf::Vector2f(x*3, y*3));
			int col = 255 - (m_map[x][y] * 255);
			rect.setFillColor(sf::Color(col, col, col));

			m_camera->getRenderWindow()->draw(rect);
		}
	}

	m_camera->getRenderWindow()->display();

	return true;
}

bool MapGenerator::DrawLandscape()
{
	if (!m_camera->cameraFrame()) return false;
	m_camera->clearWindow();

	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(1, 1));

	for (int y = 0; y < kSize; y++)
	{
		for (int x = 0; x < kSize; x++)
		{
			rect.setPosition(sf::Vector2f(x, y));
			sf::Color col;
			if (m_fmap[x][y] < 0.43) col = sf::Color::Blue;
			else if (m_fmap[x][y] < 0.5) col = sf::Color::Yellow;
			else if (m_fmap[x][y] < 0.6) col = sf::Color::Black;
			else col = sf::Color::White;
			rect.setFillColor(col);

			m_camera->getRenderWindow()->draw(rect);
		}
	}

	m_camera->getRenderWindow()->display();

	return false;
}