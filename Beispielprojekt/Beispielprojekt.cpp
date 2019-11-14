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
double rot(Objekt x, Objekt y) {}
//*************************************end

class Objekt {
public:
	Gosu::Image Bild;
	double pos_x;
	double pos_y;
	double rot;
	int Ziel_x;
	int Ziel_y;
	Objekt* Target_Objekt_Ptr;
	Objekt(int x, int y, Objekt* oz, Gosu::Image B) : pos_x(x), pos_y(y), Target_Objekt_Ptr(oz), Bild(B) {};
	double dy;
	double dx;
	double abstand;

	void abstand_berechnen() {
		double dy = (this->pos_y - this->Target_Objekt_Ptr->pos_y);
		if (dy == 0)
			dy += 0,01;
		double dx = (this->pos_x - this->Target_Objekt_Ptr->pos_x);
		if (dx == 0)
			dx += 0, 01;
		abstand = sqrt(dy*dy + dx*dx);

	};
	void rot_berechnen() {	
	this->rot=Gosu::angle(this->pos_x, this->pos_y, this->Target_Objekt_Ptr->pos_x, this->Target_Objekt_Ptr->pos_y, 0);
	};
	void bewegung() {
		this->pos_x = this->dx + ((dx / abstand) * 8);
		this->pos_y = this->dy + ((dy / abstand)) * 8);
	}
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, rot, 0.5, 0.5);

	}


};



class Erde : public Objekt  {

	Gosu::Image Bild;

public:
	
	Erde(int x, int y, Objekt* oz, Gosu::Image B): Objekt(x,y,oz,B)  {

	}
	
	int pos_x = Fenster_x / 2;
	int pos_y = Fenster_y / 2;
	
};




class Raumschiff : public Objekt {
public:
	int Geschwindigkeit;
	
	

};
	

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image Raumschiff;
	

	GameWindow()
		: Window(Fenster_x, Fenster_y),
		Raumschiff("rakete.png")
	{
		set_caption("Earth");
	}
	
	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{

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
