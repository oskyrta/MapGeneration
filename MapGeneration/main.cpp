#include <iostream>
#include <SFML\Graphics.hpp>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\info_parser.hpp>
#include <conio.h>
#include <Windows.h>

#include "mapGenerator.h"
#include "utils.h"

typedef boost::property_tree::ptree Settings;

Settings settings;

int main()
{
	boost::property_tree::info_parser::read_info("settings.info", settings);

	MapGenerator gen;
	bool regenerate = false;
	float t = 0.5, n = 8;

	do
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			gen.Generate(DiamodAndSquare);
		Sleep(1000 / 60);
	} 
	while (gen.Draw(Landscape, 1));
}