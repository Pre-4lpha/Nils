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
//*************************************start
double misx = 0.0;
double misy = 0.0;
double misxnew = 0.0;
double misynew = 0.0;
bool misexist = false;
double x_maus = 0;
double y_maus = 0;
double deltax = 0.0;
double deltay = 0.0;
double deltad = 0.0;
double reichweite = 1000;
//*************************************end

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


class Raumschiff : public Objekt {
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
		//*************************************start
		Raumschiff.draw(x_maus, y_maus, 0.0,
			1.0, // Rotationswinkel in Grad
			1.0 // Position der "Mitte" relativ zu x, y (*20=Pixel)
		);
		if (misexist == true)
		{
			if (misx == 0 || misy == 0)
			{
				misx = 100;
				misy = 100;
			}
			deltax = x_maus - misx;
			deltay = y_maus - misy;
			deltad = sqrt((y_maus - misy) * (y_maus - misy) + (x_maus - misx) * (x_maus - misx));
			misxnew = misx + ((deltax / deltad) * 8);
			misynew = misy + ((deltay / deltad) * 8);
			//rot = (double)(((int)(270 + asin(deltay / deltad))) % 360);
			//rot = 45.0;
			reichweite = reichweite - sqrt((misynew - misy) * (misynew - misy) + (misxnew - misx) * (misxnew - misx));
			if (reichweite <= 0 || deltad <= 30)
			{
				misexist = false;
				reichweite = 1000;
			}
			Raumschiff.draw_rot(misxnew, misynew, 0.0, 45.0, 0.0);
			misx = misxnew;
			misy = misynew;
		}
		//*************************************end
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//****************************************start
		x_maus = input().mouse_x();
		y_maus = input().mouse_y();
		if (input().down(Gosu::MS_LEFT)) {
			misexist = true;
		}
		else if (input().down(Gosu::MS_RIGHT))
		{
			misexist = false;
		}
		//****************************************end
	}
};

// C++ Hauptprogramm
int main()
{
	
	GameWindow window;
	window.show();


}
