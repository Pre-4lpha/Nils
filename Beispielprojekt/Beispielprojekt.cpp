#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "Vektor2d.h"
using namespace std;

int Fenster_x = 1920;
int Fenster_y = 1080;
int Zeit = 0;
double rot_geschwindigkeit = 0.2;

class Objekt {
public:
	int pos_x;
	int pos_y;
	signed int rel_pos_x;
	signed int rel_pos_y;
	signed int rel_pos()
	{
		this->rel_pos_x = (this->pos_x - Fenster_x / 2);
		this->rel_pos_y = (this->pos_y - Fenster_y / 2);

	}

};

class Earth  {

	Gosu::Image Erde;

public:
	
	Earth() :Erde("Erde.png") {

	}
	
	int pos_x = Fenster_x / 2;
	int pos_y = Fenster_y / 2;
	void draw_erde()
	{	
		Erde.draw_rot(this->pos_x, this->pos_y, 0.0, Zeit * rot_geschwindigkeit, 0.5, 0.5);

	}
};


class Rakete : public Objekt {
public:
	int Geschwindigkeit;
	double rotation;
	double rotation_berechnen() {
		return(this->rotation = atan(unsigned (this->rel_pos_x) / unsigned (this->rel_pos_y)));
		if (this->rel_pos_y < 0 && this->rel_pos_x >0)
		{
			this->rotation += 90;
		}
		else if (this->rel_pos_x < 0 && this->rel_pos_y < 0)
		{
			this->rotation += 180;
		}
		else if (this->rel_pos_x < 0 && this->rel_pos_y > 0)
		{
			this->rotation += 190;
		}

	}
	double Bewegung() {
		
	}

};

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image Raumschiff;

	Earth erde;
	GameWindow()
		: Window(Fenster_x, Fenster_y),
		Raumschiff("rakete.png")
	{
		set_caption("Earth");
	}
	int x = 0;
	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		erde.draw_erde();
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		x += 1;
		if (input().down(Gosu::MS_LEFT)) {
		
		}
	}
};

// C++ Hauptprogramm
int main()
{
	
	GameWindow window;
	window.show();


}
