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

//*************************************end

class Objekt {
public:
	Gosu::Image Bild;
	double pos_x;
	double pos_y;
	double rot;
	Objekt* Target_Objekt_Ptr;
	Objekt(double x, double y, Objekt* oz, Gosu::Image B) : pos_x(x), pos_y(y), Target_Objekt_Ptr(oz) , Bild(B) {};
	double dy;
	double dx;
	double abstand;

	void abstand_berechnen() {
		 dy = ( this->Target_Objekt_Ptr->pos_y- this->pos_y);
		if (dy == 0)
			dy += 0.01;
		 dx = (this->Target_Objekt_Ptr->pos_x - this->pos_x );
		if (dx == 0)
			dx += 0.01;
		abstand = sqrt(dy*dy + dx*dx);
		

	};
	void rot_berechnen() {	
	this->rot=Gosu::angle(this->pos_x, this->pos_y, this->Target_Objekt_Ptr->pos_x, this->Target_Objekt_Ptr->pos_y, 0);
	};
	void bewegung() {
		
		this->pos_x = (this->pos_x + ((dx / abstand) * 8.0));
		cout << this->pos_x << endl;
		this->pos_y = this->pos_y + ((dy / abstand) * 8.0);
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
	Raumschiff(double x, double y, Objekt* oz, Gosu::Image B) : Objekt(x, y, oz, B) { }
};
	

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image Bild_Raumschiff;
	
	Raumschiff test1;
	Raumschiff test2;
	GameWindow() : Window(Fenster_x, Fenster_y), Bild_Raumschiff("rakete.png"), test1(800, 40, &test2, Bild_Raumschiff), test2(30, 120, &test1, Bild_Raumschiff)
	{
		set_caption("Earth");
	}

	
	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		test1.draw();
		test2.draw();
	}



	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		test1.rot_berechnen();
		test1.abstand_berechnen();
		test1.bewegung();
		test2.rot_berechnen();
		test2.abstand_berechnen();
		test2.bewegung();
		//****************************************start
	
		//****************************************end
	}
};

// C++ Hauptprogramm
int main()
{
	
	GameWindow window;
	window.show();


}
