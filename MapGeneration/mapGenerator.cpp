#include "mapGenerator.h"
#include "camera.h"
#include "utils.h"

#include <iostream>


sf::Image img;
sf::Sprite spr;

const float persent = 0.4f;

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

void MapGenerator::Generate(GenerateType type)
{
	switch (type)
	{
	case Interpolating:
		Random_InterpolateGenerate(0.5, 8);
		break;

	case DiamodAndSquare:
		DiamodAndSquareGenerate(0.5);
		break;

	case PerlinNoise:
		break;
	}
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

void MapGenerator::Random_InterpolateGenerate(float tf, int lvl)
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

	m_mapUpdated = true;
}

void displace(float& a, int lvl)
{
	a += GetRandomFloat(-persent, persent) / (kSize / lvl);
	if (a > 1) a = 1;
	if (a < 0) a = 0;
}

void Square(float** a, int x, int y, int lvl)
{
	a[x][y] = (	  
		  a[(kSize + (x - lvl/2)) % kSize][(kSize + (y - lvl/2)) % kSize]
		+ a[(kSize + (x - lvl/2)) % kSize][(y + lvl/2) % kSize]
		+ a[(x + lvl/2) % kSize][(kSize + (y - lvl/2)) % kSize]
		+ a[(x + lvl/2) % kSize][(y + lvl/2) % kSize] ) / 4;
	displace(a[x][y], lvl);
}

void Diamond(float** a, int x, int y, int lvl)
{
	a[x][y] = (	
		  a[x][(kSize + (y - lvl/2)) % kSize] 
		+ a[(kSize + (x - lvl/2)) % kSize][y] 
		+ a[x][(y + lvl/2) % kSize] 
		+ a[(x + lvl/2) % kSize][y] ) / 4;
	displace(a[x][y], lvl);
}

void MapGenerator::DiamodAndSquareGenerate(float tf)
{
	m_fmap[0][0]			 = GetRandomFloat(0, 1);
	m_fmap[0][kSize-1]		 = GetRandomFloat(0, 1);
	m_fmap[kSize-1][0]		 = GetRandomFloat(0, 1);
	m_fmap[kSize-1][kSize-1] = GetRandomFloat(0, 1);

	for (int lvl = kSize; lvl > 2; lvl = lvl/2 + 1)
	{
		for (int i = lvl / 2; i < kSize; i += lvl-1)
		{
			for (int j = lvl / 2; j < kSize; j += lvl-1)
			{
				Square(m_fmap, i, j, lvl);
			}
		}

		
		for (int i = lvl / 2; i < kSize; i += lvl-1)
		{
			for (int j = lvl / 2; j < kSize; j += lvl-1)
			{
				Diamond(m_fmap, i, j + lvl / 2, lvl);
				Diamond(m_fmap, i, j - lvl / 2, lvl);
				Diamond(m_fmap, i + lvl / 2, j, lvl);
				Diamond(m_fmap, i - lvl / 2, j, lvl);
			}
		}
	}


	for (int y = 0; y < kSize; y++)
	{
		for (int x = 0; x < kSize; x++)
		{
			if (m_fmap[x][y] > tf) m_map[x][y] = 1;
			else m_map[x][y] = 0;
		}
	}

	m_mapUpdated = true;
}

sf::Color GetColorGradientValue(sf::Color left, sf::Color right, double a)
{
	sf::Color color;
	color.r = (int)(left.r * (1 - a) + right.r * a);
	color.g = (int)(left.g * (1 - a) + right.g * a);
	color.b = (int)(left.b * (1 - a) + right.b * a);

	return color;
}

const sf::Color leftDeapSea = sf::Color(42, 51, 121);
const sf::Color rightDeapSea = sf::Color(41, 88, 141);

const sf::Color leftSea = sf::Color(51, 101, 154);
const sf::Color rightSea = sf::Color(160, 221, 229);

const sf::Color leftSand = sf::Color(246, 238, 108);
const sf::Color rightSand = sf::Color(239, 234, 87);

const sf::Color leftLand = sf::Color(175, 210, 83);
const sf::Color rightLand = sf::Color(92, 186, 75);

const sf::Color leftMoutain = sf::Color(159, 160, 157);
const sf::Color rightMoutain = sf::Color(200, 200, 200);

const sf::Color leftSnow = sf::Color(225, 225, 225);
const sf::Color rightSnow = sf::Color(255, 255, 255);


const double deapSeaLevel = 0.2;
const double seaLevel = 0.31;
const double sandLevel = 0.37; 
const double landLevel = 0.7;
const double mountainLevel = 0.92;
const double snowLevel = 1.0;

sf::Color getColor(float a)
{
	sf::Color color;

	if (a < deapSeaLevel)
	{
		double value = a / deapSeaLevel;
		color = GetColorGradientValue(leftDeapSea, rightDeapSea, value);
		return color;
	}

	if (a < seaLevel)
	{
		double value = (a - deapSeaLevel) / (seaLevel - deapSeaLevel);
		color = GetColorGradientValue(leftSea, rightSea, value);
		return color;
	}

	if (a < sandLevel)
	{
		double value = (a - seaLevel) / (sandLevel - seaLevel);
		color = GetColorGradientValue(leftSand, rightSand, value);
		return color;
	}

	if (a < landLevel)
	{
		double value = (a - sandLevel) / (landLevel - sandLevel);
		color = GetColorGradientValue(leftLand, rightLand, value);
		return color;
	}

	if (a < mountainLevel)
	{
		double value = (a-landLevel) / (mountainLevel - landLevel);
		color = GetColorGradientValue(leftMoutain, rightMoutain, value);
		return color;
	}
	
	if (a < snowLevel)
	{
		double value = (a - mountainLevel) / (snowLevel - mountainLevel);
		color = GetColorGradientValue(leftSnow, rightSnow, value);
		return color;
	}

	return rightSnow;
}

bool MapGenerator::Draw(DrawType type, int pixelSize)
{
	if (!m_camera->cameraFrame()) return false;
	m_camera->clearWindow();

	if (!m_mapUpdated) return true;

	img.create(kSize, kSize, sf::Color());

	switch (type)
	{
	case Noise:
		for (int y = 0; y < kSize; y++)
		{
			for (int x = 0; x < kSize; x++)
			{
				int col = 255 - (m_fmap[x][y] * 255);

				img.setPixel(x, y, sf::Color(col, col, col));
			}
		}
		break;

	case Cave:
		for (int y = 0; y < kSize; y++)
		{
			for (int x = 0; x < kSize; x++)
			{
				int col = 255 - (m_map[x][y] * 255);

				img.setPixel(x, y, sf::Color(col, col, col));
			}
		}
		break;

	case Landscape:
		for (int y = 0; y < kSize; y++)
		{
			for (int x = 0; x < kSize; x++)
			{
				sf::Color col;

				col = getColor(m_fmap[x][y]);
				img.setPixel(x, y, col);
			}
		}
		break;

	default:
		break;
	}

	sf::Texture tex;
	tex.loadFromImage(img);
	spr.setTexture(tex);

	spr.setScale(sf::Vector2f(pixelSize, pixelSize));

	m_camera->getRenderWindow()->draw(spr);
	m_camera->getRenderWindow()->display();

	m_mapUpdated = false;

	return true;
}
