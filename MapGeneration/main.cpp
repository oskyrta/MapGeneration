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

	do
	{
		float t = 0.6, n = 5;
		std::cin >> t >> n;
		gen.RandomPlusInterpolateGenerate(t, n);
		gen.DrawCave();
	} 
	while (true);
}