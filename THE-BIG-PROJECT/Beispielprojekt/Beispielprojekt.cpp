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
string stringgeld = "Geld: ";
string Nachricht = "";		//diesen string kannst du bei bedarf umbenennen, er wird rechts unten ausgegeben für nachrichten an spieler
unsigned geld = 1000;
int rakete_auswahl = 1;
int x_maus;
int y_maus;
bool Klick_maus_links;				
bool Klick_maus_links_remember;		//fürs toggeln
int Anzahl_Ernter = 0;				//max: 10
bool raumstation_setzen = false;
int Anzahl_Raumstationen = 0;

class Objekt {
public:
	Gosu::Image Bild;
	double pos_x;
	double pos_y;
	double rot;
	Objekt* Target_Objekt_Ptr;
	Objekt(double x, double y, Objekt* oz, Gosu::Image B, double v) : pos_x(x), pos_y(y), Target_Objekt_Ptr(oz), Bild(B), v(v) {};
	double dy;
	double dx;
	double abstand;
	double v;			// Geschwindigkeit


	virtual void abstand_berechnen() {
		dy = (this->Target_Objekt_Ptr->pos_y - this->pos_y);
		if (dy == 0)
			dy += 0.01;
		dx = (this->Target_Objekt_Ptr->pos_x - this->pos_x);
		if (dx == 0)
			dx += 0.01;
		abstand = sqrt(dy * dy + dx * dx);


	};
	virtual void rot_berechnen() {
		this->rot = Gosu::angle(this->pos_x, this->pos_y, this->Target_Objekt_Ptr->pos_x, this->Target_Objekt_Ptr->pos_y, 0);
	};
	void bewegung() {

		this->pos_x = (this->pos_x + ((dx / abstand) * v));
		this->pos_y = this->pos_y + ((dy / abstand) * v);
	}
	virtual void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, this->rot, 0.5, 0.5);

	}



};
class Erde : public Objekt {
public:
	Erde(double x, double y, Objekt* oz, Gosu::Image B, double v) : Objekt(x, y, oz, B, v) { }
	void rot_berechnen() {
		this->rot += v;
	}
	double v = 0.1;
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, this->rot, 0.5, 0.5, 0.3, 0.3);
	}
};

class Raumschiff : public Objekt {
public:
	Raumschiff(double x, double y, Objekt* oz, Gosu::Image B, double v) : Objekt(x, y, oz, B, v) { }
	int Leben;
	int Ort = 0;
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, this->rot, 0.5, 0.5, 0.5, 0.5);

	}
};

class Asteroid: public Objekt {
public:
	int radius;
	double rot;
	double r;
	double v;
	Gosu::Image Bild_full;
	int x = Fenster_x / 2;
	int y = Fenster_y / 2;
	int status;
	Asteroid(double x, double y, Objekt* oz, Gosu::Image B, double v, int r, double rot, Gosu::Image B_full, int status) 
		: Objekt(x, y, oz, B,v), v(v), radius(r), rot(rot),Bild_full(B_full), status(status){ }							
	
	//es werden zwei bilder übergeben, für leer und mit Ernter besetzt

	void rot_berechnen() 
	{
		this->rot += v;
	}
	void draw()
	{
		if (this->status == 0)
		{
			this->Bild.draw_rot(this->x, this->y, 0.0, rot, radius, 0.5, 0.15, 0.15);
		}
		else
		{
			this->Bild_full.draw_rot(this->x, this->y, 0.0, rot, radius, 0.5, 0.15, 0.15);
		}
	}
};



class GameWindow : public Gosu::Window
{
public:
	Gosu::Image Bild_Raumschiff;
	Raumschiff Puffer;
	Raumschiff test1;
	Raumschiff test2;
	Raumschiff test3;

	Objekt Raumstation_1;
	Objekt Raumstation_2;
	Objekt Raumstation_3;
	vector<Objekt> Raumstationen_vector{ Raumstation_1, Raumstation_2, Raumstation_3 };
	Gosu::Image Bild_Erde;
	Erde Erde;
	Gosu::Image Raumstation;
	Gosu::Image Raumstation_rahmen;
	Gosu::Image Ernter;
	Gosu::Image Asteroid_1;
	Gosu::Image Asteroid_2;
	Gosu::Image Asteroid_1_full;
	Gosu::Image Asteroid_2_full;
	Gosu::Image Platzhalter;
	Gosu::Image rahmen;
	Gosu::Image pfeil;
	Gosu::Image Ring_lila;
	Gosu::Image Ring_gelb;
	Gosu::Font testfont;
	Raumschiff* markiert_ptr = nullptr;
	Asteroid ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8, ast9, ast10;
	vector<Asteroid> Asteroiden_vector{ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8, ast9, ast10};
	



	GameWindow() : Window(Fenster_x, Fenster_y),
					Ernter("Ernter.png"),
					Raumstation("Raumstation.png"),
					Raumstation_rahmen("Raumstation_rahmen.png"),
					Asteroid_1("Asteroid_2.png"),
					Asteroid_2("Asteroid_1.png"),
					Asteroid_1_full("Asteroid_2_full.png"),
					Asteroid_2_full("Asteroid_1_full.png"),
					Bild_Raumschiff("rakete.png"),
					Bild_Erde("Erde.png"),
					Platzhalter("Platzhalter.png"),
					pfeil("pfeil.png"),
					Ring_lila("Ring_lila.png"),
					Ring_gelb("Ring_gelb.png"),
					rahmen("rahmen.png"),

					testfont(20),
		
					Erde(Fenster_x / 2, Fenster_y / 2, nullptr, Bild_Erde, 0.2),
					Puffer(x_maus, y_maus, nullptr, Bild_Raumschiff, 1.0),
								
					Raumstation_1(0.0,	0.0, nullptr, Raumstation, 0),
					Raumstation_2(0.0,	0.0, nullptr, Raumstation, 0),
					Raumstation_3(0.0,	0.0, nullptr, Raumstation, 0),
					ast1( 900, 900,	nullptr, Asteroid_1, -0.03,		6,			210.0, Asteroid_1_full, 0),
					ast2( 900, 900, nullptr, Asteroid_2, -0.04,		8.7,		120.0, Asteroid_2_full, 0),
					ast3( 900, 900, nullptr, Asteroid_1, -0.005,	8,			30.0,  Asteroid_1_full,	0),
					ast4( 900, 900, nullptr, Asteroid_2, -0.01,		7.9,		40.0,  Asteroid_2_full, 0),
					ast5( 900, 900, nullptr, Asteroid_1, -0.03,		8.5,		250.0, Asteroid_1_full, 0),
					ast6( 900, 900, nullptr, Asteroid_2, 0.09,		6.2,		60.0,  Asteroid_2_full, 0),
					ast7( 900, 900, nullptr, Asteroid_1, 0.05,		8.5,		270.0, Asteroid_1_full, 0),
					ast8( 900, 900, nullptr, Asteroid_2, 0.08,		7,			80.0,  Asteroid_2_full, 0),
					ast9( 900, 900, nullptr, Asteroid_1, 0.009,		7.9,		90.0,  Asteroid_1_full, 0),
					ast10(900, 900, nullptr, Asteroid_2, 0.1,		7.3,		100.0, Asteroid_2_full, 0),
					test1(800, 40, nullptr, Bild_Raumschiff, 1.0),
					test2(30, 120, nullptr, Bild_Raumschiff, 1.0),
					test3(1000, 600, nullptr, Bild_Raumschiff, 1.0)
					
					
					
	{
		set_caption("Earth");
	}
	
	
	void Vordergrund() {
		//
		stringgeld += to_string(geld);
		stringgeld += "$";
		testfont.draw(stringgeld, 1660, 70, 1.0, 2.0, 2.0, Gosu::Color::RED);
		stringgeld = "Geld: ";
		Platzhalter.draw(						1660.0, 130.0,	0.0, 0.1, 0.1);
			testfont.draw("SM-3       400$",	1730.0, 130.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
		Platzhalter.draw(						1660.0, 190.0,	0.0, 0.1, 0.1);
			testfont.draw("Trident    400$",	1730.0,	190.0,	0.0, 1.0, 1.0, Gosu::Color::WHITE);
		Platzhalter.draw(						1660.0, 250.0,	0.0, 0.1, 0.1);
			testfont.draw("Satan      700$",	1730.0,	250.0,	0.0, 1.0, 1.0, Gosu::Color::WHITE);
		Ernter.draw(							1660.0, 310.0, 0.0, 0.165, 0.165);
			if (Anzahl_Ernter <= 10) 
			{
				testfont.draw("Miner	  300$", 1730.0, 310.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
			}
			else
			{
				testfont.draw("all Miners used", 1730.0, 310.0, 0.0, 1.0, 1.0, Gosu::Color::RED);
			}
		Raumstation_rahmen.draw(				1660.0, 370.0, 0.0, 0.1, 0.1);
			testfont.draw("Satellit  1000$",	1730.0, 370.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);

			switch (rakete_auswahl) 
			{
				case 1:	rahmen.draw(1660.0, 130.0, 0.0, 0.1, 0.1);
					break;
				case 2:	rahmen.draw(1660.0, 190.0, 0.0, 0.1, 0.1);
					break;
				case 3:	rahmen.draw(1660.0, 250.0, 0.0, 0.1, 0.1);
					break;
				case 4:	rahmen.draw(1660.0, 310.0, 0.0, 0.1, 0.1);
					break;
				case 5:	rahmen.draw(1660.0, 370.0, 0.0, 0.1, 0.1);
					break;
			}

		pfeil.draw(x_maus, y_maus, 0.0, 0.1, 0.1);
			testfont.draw(Nachricht,  1730.0, 1000.0, 0.0, 1.0, 1.0, Gosu::Color::RED);		
		
	}
	Raumschiff* Check_Maus(Objekt a, Objekt b, Objekt c, Raumschiff* markiert_ptr) {
		//gibt Zeiger auf markiertes Raumschiff aus
		Raumschiff v[3]{ test3, test2, test1 };
		Raumschiff* hoover_over_ptr = nullptr;
		
		Puffer.pos_x = x_maus;
		Puffer.pos_y = y_maus;
		Puffer.abstand = 1000;
		
		for (int i = 0; i < 3; i++)
		{
			Puffer.Target_Objekt_Ptr = v[i].Target_Objekt_Ptr;
			v[i].Target_Objekt_Ptr = &Puffer;
			v[i].abstand_berechnen();
			if ((v[i].abstand < Puffer.abstand)&(v[i].abstand <25))
			{
				hoover_over_ptr = &v[i];
				Puffer.abstand = v[i].abstand;
			}
			v[i].Target_Objekt_Ptr = Puffer.Target_Objekt_Ptr;
		}
		
		if (Klick_maus_links)
		{
			markiert_ptr = hoover_over_ptr;
		}
		if (hoover_over_ptr != nullptr)
		{
			Ring_lila.draw((hoover_over_ptr->pos_x) - 40, (hoover_over_ptr->pos_y) - 40, 0.0, 0.5, 0.5);
		}
		if (markiert_ptr != nullptr)
		{
			Ring_gelb.draw((markiert_ptr->pos_x)-40, (markiert_ptr->pos_y)-40, 0.0, 0.5, 0.5);
		}
		if (Klick_maus_links)
		{
			testfont.draw("Klick links", 1500.0, 1000.0, 0.0, 1.0, 1.0, Gosu::Color::RED);
		}
		return markiert_ptr;
	}
	void Asteroiden_update(std::vector<Asteroid>& Asteroiden_vector) {
		if (Klick_maus_links && (rakete_auswahl==4) && (geld >=300))
		{
			Anzahl_Ernter = Anzahl_Ernter +1;
			geld = geld - 300;
		}
		else if(Klick_maus_links && (rakete_auswahl == 4) && (geld < 300))
		{
			Nachricht = "nicht genug Geld";
		}

		for (int i = 0; i < 10; i++)
		{
			if ((i+1)<=(Anzahl_Ernter))
			{
				Asteroiden_vector[i].status = 1;
			}
			Asteroiden_vector[i].rot_berechnen();
		}
	}
	void Asteroiden_draw() {
		for (int i = 0; i < 10; i++)
		{
			Asteroiden_vector[i].draw();
		}
	}
	void Toggle_Maus_Links(){
		if ((input().down(Gosu::MS_LEFT)) && (Klick_maus_links_remember==false)) {
			Klick_maus_links = true;
			Klick_maus_links_remember = true;
		}
		else if((input().down(Gosu::MS_LEFT)) && (Klick_maus_links_remember == true))
		{
			Klick_maus_links = false;
		}
		else
		{
			Klick_maus_links = false;
			Klick_maus_links_remember = false;
		}
	}
	void get_Geld_Ernter() {
		for (int i = 0; i < 10; i++)
		{
			if (Asteroiden_vector[i].status == 1)
			{
				geld = geld + 50;
			}
		}
	}
	/*
	void Raumstation_update()
	{
		if ((rakete_auswahl == 5) && (geld >= 1000) && (Klick_maus_links))
		{
			raumstation_setzen = false;
			if (Anzahl_Raumstationen < 3)
			{
				for (int i = 0; i <= (Anzahl_Raumstationen); i++)
				{

					
						if (Raumstationen_vector[i].v == 0)
						{
							Raumstationen_vector[i].pos_x = (x_maus - 25.0);
							Raumstationen_vector[i].pos_y = (y_maus - 25.0);
						}
						Raumstationen_vector[i].v = 1.0;
					
				}
				Anzahl_Raumstationen = Anzahl_Raumstationen + 1;
			}
			
			

		}
		if ((rakete_auswahl == 5) && (geld >= 1000))
		{
			raumstation_setzen = true;
		}
	}
	void draw_Raumstationen()
	{
		if (raumstation_setzen == true)
		{
			Raumstation.draw((x_maus - 25.0), (y_maus - 25.0), 0.0, 0.1, 0.1);
		}
		for (int i = 0; i < 3; i++)
		{
			if (Raumstationen_vector[i].v == 1)
			{
				Raumstationen_vector[i].Bild.draw(Raumstationen_vector[i].pos_x, Raumstationen_vector[i].pos_y,0.0,0.1,0.1);
			}
		}
	}
	*/

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		Erde.draw();
		test1.draw();
		test2.draw();
		test3.draw();
		markiert_ptr = Check_Maus(test3, test2, test1, markiert_ptr);
		Asteroiden_draw();
		//draw_Raumstationen();
		Vordergrund();
		
	}



	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		Toggle_Maus_Links();
		
		Asteroiden_update(Asteroiden_vector);

		Erde.rot_berechnen();
		//Raumstation_update();
		
		x_maus = input().mouse_x();
		y_maus = input().mouse_y();

		if (Gosu::Input::down(Gosu::KB_1))
		{
			rakete_auswahl = 1;
		}
		else if (Gosu::Input::down(Gosu::KB_2))
		{
			rakete_auswahl = 2;
		}
		else if (Gosu::Input::down(Gosu::KB_3))
		{
			rakete_auswahl = 3;
		}
		else if (Gosu::Input::down(Gosu::KB_4))
		{
			rakete_auswahl = 4;
		}
		else if (Gosu::Input::down(Gosu::KB_5))
		{
			rakete_auswahl = 5;
		}



		
	}
};

// C++ Hauptprogramm
int main()
{
	
	GameWindow window;
	window.show();


}
