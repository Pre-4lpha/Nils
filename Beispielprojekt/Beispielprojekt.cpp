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
	int v; // Geschwindigkeit

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
		
		this->pos_x = (this->pos_x + ((dx / abstand) * v));
		cout << this->pos_x << endl;
		this->pos_y = this->pos_y + ((dy / abstand) * v);
	}
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, rot, 0.5, 0.5);

	}


};



class Erde : public Objekt  {
public:
	Erde(double x, double y, Objekt* oz, Gosu::Image B) : Objekt(x, y, oz, B) { }
	void rot_berechnen(){
		this->rot += v;
		

	}
	double v = 0.1;
};




class Raumschiff : public Objekt {
public:
	Raumschiff(double x, double y, Objekt* oz, Gosu::Image B) : Objekt(x, y, oz, B) { }
	int Leben;
	int v = 2;
};
	

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image Bild_Raumschiff;
	Gosu::Image Bild_Erde;
	Erde Erde;
	
	GameWindow() : Window(Fenster_x, Fenster_y), Bild_Raumschiff("rakete.png"), Bild_Erde("Erde.png"), Erde(Fenster_x / 2, Fenster_y / 2, nullptr, Bild_Erde) {
		set_caption("Earth");
	}

	
	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		Erde.draw();
	}



	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		Erde.rot_berechnen();
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
