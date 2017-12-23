#include <iostream>
#include <SFML\Graphics.hpp>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\info_parser.hpp>

#include "camera.h"

typedef boost::property_tree::ptree Settings;

Settings settings;

int main()
{
	boost::property_tree::info_parser::read_info("settings.info", settings);
	Camera camera = Camera(512, 320, "Map Generation");

	while (camera.cameraFrame())
	{

		//camera.clearWindow();
	}
}