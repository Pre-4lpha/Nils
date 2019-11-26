#pragma once

#include <string>
#include <Gosu\Image.hpp>
#include "Vektor2d.h"

struct Planet {
	Vektor2d pos;
	double mass;
	Gosu::Image img;
	Planet(Vektor2d pos, double mass, std::string img);
	void draw();
};
