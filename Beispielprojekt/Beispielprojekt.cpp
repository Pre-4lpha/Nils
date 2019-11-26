#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <list>

#include "Vektor2d.h"
using namespace std;

int Fenster_x = 1920;
int Fenster_y = 1080;
double rot_geschwindigkeit = 0.2;
int Welle = 0;
double PI = 3.1415962;
string stringgeld = "Geld: ";
string Nachricht = "";		//diesen string kannst du bei bedarf umbenennen, er wird rechts unten ausgegeben f¸r nachrichten an spieler
unsigned geld = 1000;
int rakete_auswahl = 1;
double x_maus;
double y_maus;
bool Klick_maus_links;
bool Klick_maus_links_remember;		//f¸rs toggeln
int Anzahl_Ernter = 0;				//max: 10
bool raumstation_setzen = false;
int Anzahl_Raumstationen = 0;
//*************************************start

//*************************************end

class Objekt {
public:
	Gosu::Image Bild;
	double pos_x;
	double pos_y;
	double rot;
	Objekt* Target_Objekt_Ptr;
	Objekt(double x, double y, Objekt* oz, Gosu::Image B,double v) : pos_x(x), pos_y(y), Target_Objekt_Ptr(oz) , Bild(B), v(v) {};
	double dy;
	double dx;
	double abstand;
	double v; // Geschwindigkeit


	virtual void abstand_berechnen() {
		 dy = ( this->Target_Objekt_Ptr->pos_y- this->pos_y);
		if (dy == 0)
			dy += 0.01;
		 dx = (this->Target_Objekt_Ptr->pos_x - this->pos_x );
		if (dx == 0)
			dx += 0.01;
		abstand = sqrt(dy*dy + dx*dx);
		

	};
	virtual void rot_berechnen() {	
	this->rot=Gosu::angle(this->pos_x, this->pos_y, this->Target_Objekt_Ptr->pos_x, this->Target_Objekt_Ptr->pos_y, 0);
	};
	void bewegung() {
		
		this->pos_x = (this->pos_x + ((dx / abstand) * v));
		this->pos_y = this->pos_y + ((dy / abstand) * v);
	}
	virtual void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0,this->rot, 0.5, 0.5);

	}



};

class Raumschiff : public Objekt {
public:
	Raumschiff(double x, double y, Objekt* oz, Gosu::Image B, double v) : Objekt(x, y, oz, B,v) { }
	int Leben;
	int Ort = 0;
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, this->rot, 0.5, 0.5,0.05,0.05);

	}
};
class Rakete : public Objekt {
public:
	Rakete(double x, double y, Objekt* oz, Gosu::Image B, double v) : Objekt(x, y, oz, B, v) { }

};

class Asteroid : public Objekt {
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
		: Objekt(x, y, oz, B, v), v(v), radius(r), rot(rot), Bild_full(B_full), status(status) { }

	//es werden zwei bilder ¸bergeben, f¸r leer und mit Ernter besetzt

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




void Wellen_Funktion(list<Raumschiff>& liste, int Welle,Raumschiff &T1,Raumschiff &T2, Raumschiff &T3) {
	int durchlauf = 1;
	int Anzahl_Typ1 = Welle;
	cout << Anzahl_Typ1 << endl;
	int Anzahl_Typ2 = 0;
	cout << Anzahl_Typ2 << endl;
	int Anzahl_Typ3 = 0;
	cout << Anzahl_Typ3 << endl;
	if (Welle >= 3) {

		Anzahl_Typ2 = int(Welle/ 3.0);
		//int Anzahl_Typ2 = ((Welle - (Welle % 3)) / 3.0);
	}
	cout << Anzahl_Typ2 << endl;

	if (Welle >= 5) {
		Anzahl_Typ3 = ((Welle - (Welle % 5)) / 5);
	}
	cout << Anzahl_Typ3 << endl;
	durchlauf = 1+ Welle;
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ3); Wellen_Groeﬂe--) {
		liste.push_back(T3);
		cout << "test3" << endl;
		T3.pos_x = Fenster_x/2+(-1400 * (pow(1.05, durchlauf-Welle)) * cos(durchlauf*(2.0*PI/double (Anzahl_Typ3))));
		T3.pos_y = Fenster_y/2 +( 1400 * (pow(1.05, durchlauf-Welle)) * sin(durchlauf*(2.0*PI / double (Anzahl_Typ3))));
		durchlauf += 1;
	}
	durchlauf = 1;
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ3-Anzahl_Typ2); Wellen_Groeﬂe--) {
		liste.push_back(T2);
		cout << "test2" <<endl;
		T2.pos_x = Fenster_x/2 + (1200 * (pow(1.05, durchlauf)) * cos(durchlauf*(2.0*PI / double (Anzahl_Typ2))));
		T2.pos_y = Fenster_y/2 + (-1200 * (pow(1.05, durchlauf)) * sin(durchlauf*(2.0*PI/ double(Anzahl_Typ2))));
		durchlauf += 1;
	}
	durchlauf = 1;
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ1); Wellen_Groeﬂe--) {
		liste.push_back(T1);
		cout << "test1" << endl;
		T1.pos_x = Fenster_x/2 +( -1000*(pow(1.05,durchlauf)) * sin(durchlauf*(2.0*PI/ double(Anzahl_Typ1))));
		cout << sin(durchlauf*(1.0 / double(Anzahl_Typ1))) << endl;
		T1.pos_y = Fenster_y/2 + (1000 * (pow(1.05, durchlauf)) * cos(durchlauf*(2.0*PI/ double(Anzahl_Typ1))));
		durchlauf += 1;
	}


}

void Update_Raumschiff(list<Raumschiff> &liste) {
	list<Raumschiff>::iterator i = liste.begin();
	while(i != liste.end())
	{
		i->abstand_berechnen();
		i->rot_berechnen();
		i->bewegung();
		if (i->abstand <= 100) {
		i = liste.erase(i);
		}
		else {
			i++;
		}

		
	}
}



void Wellen_Update(int &Welle, double &Zeit, list<Raumschiff> &liste,Raumschiff &T1, Raumschiff &T2, Raumschiff &T3){
	Zeit = 1.0/60.0 + Zeit ;
	if (Zeit >= 15.0) {
		Welle += 1;
		Zeit = 0;
		Wellen_Funktion(liste, Welle, T1, T2, T3);

	}
	else if (liste.size() == 0) {
		Welle += 1;
		Zeit = 0;
		Wellen_Funktion(liste, Welle, T1, T2, T3);
	}
}
void Update_Raumschiff_draw(list<Raumschiff> &liste) {
	list<Raumschiff>::iterator i = liste.begin();
	while (i != liste.end()) {
		i->draw();
		i++;
	}
}

void Update_Rakete_draw(list<Rakete> &liste) {
	list<Rakete>::iterator i = liste.begin();
	while (i != liste.end()) {
		i->draw();
		i++;
	}
}

void Raketen_Funktion(list<Rakete> &liste, Rakete Rakete, list<Raumschiff>::iterator Raumschiff) {

	Rakete.Target_Objekt_Ptr = *Raumschiff;
		liste.push_back(Rakete);
}


list<Raumschiff>::iterator Check_Maus(int x, int y, list<Raumschiff> & liste) {
	//gibt Zeiger auf markiertes Raumschiff aus
	int min_abstand = 20;
	list<Raumschiff>::iterator Ziel;
	list<Raumschiff>::iterator i = liste.begin();
	while (i != liste.end()) {
		{
			int dx = i->pos_x - x;
			int dy = i->pos_y - y;
			int abstand = sqrt((dx*dx) + (dy*dy));
			if (abstand < min_abstand)
			{
				min_abstand = abstand;
				Ziel = i;
			}
			i++;
		}
	}
	return Ziel;
}






		class GameWindow : public Gosu::Window
		{
		public:
	
			Gosu::Image Bild_Raumschiff1;
			Gosu::Image Bild_Raumschiff2;
			Gosu::Image Bild_Raumschiff3;
			Gosu::Image Bild_Rakete;
			Gosu::Image Bild_Erde;
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

			Erde Erde;
			Raumschiff Typ1;
			Raumschiff Typ2;
			Raumschiff Typ3;
			list<Raumschiff> Raumschiff_Liste;
			double Zeit = 0;
			list<Rakete> Raketen_Liste;
			Rakete Rakete;


			Objekt Raumstation_1;
			Objekt Raumstation_2;
			Objekt Raumstation_3;
			vector<Objekt> Raumstationen_vector{ Raumstation_1, Raumstation_2, Raumstation_3 };

			Asteroid ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8, ast9, ast10;
			vector<Asteroid> Asteroiden_vector{ ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8, ast9, ast10 };



			GameWindow() : Window(Fenster_x, Fenster_y),
				Bild_Raumschiff1("R1.png"),
				Bild_Raumschiff2("R2.png"),
				Bild_Raumschiff3("R3.png"),
				Bild_Erde("Erde.png"),
				Bild_Rakete("rakete.png"),
				Erde(Fenster_x / 2, Fenster_y / 2, nullptr, Bild_Erde, 0.2),
				Typ1(500, 0, &Erde, Bild_Raumschiff1, 1),
				Typ2(600, 0, &Erde, Bild_Raumschiff2, 2.5),
				Typ3(700, 0, &Erde, Bild_Raumschiff3, 0.5), Rakete((Fenster_x / 2 + 50), (Fenster_y / 2 - 67), nullptr, (Bild_Rakete), (20)), Ernter("Ernter.png"),
				Raumstation("Raumstation.png"),
				Raumstation_rahmen("Raumstation_rahmen.png"),
				Asteroid_1("Asteroid_2.png"),
				Asteroid_2("Asteroid_1.png"),
				Asteroid_1_full("Asteroid_2_full.png"),
				Asteroid_2_full("Asteroid_1_full.png"),
				Platzhalter("Platzhalter.png"),
				pfeil("pfeil.png"),
				Ring_lila("Ring_lila.png"),
				Ring_gelb("Ring_gelb.png"),
				rahmen("rahmen.png"),

				Raumstation_1(0.0, 0.0, nullptr, Raumstation, 0),
				Raumstation_2(0.0, 0.0, nullptr, Raumstation, 0),
				Raumstation_3(0.0, 0.0, nullptr, Raumstation, 0),
				ast1(900, 900, nullptr, Asteroid_1, -0.03, 6, 210.0, Asteroid_1_full, 0),
				ast2(900, 900, nullptr, Asteroid_2, -0.04, 8.7, 120.0, Asteroid_2_full, 0),
				ast3(900, 900, nullptr, Asteroid_1, -0.005, 8, 30.0, Asteroid_1_full, 0),
				ast4(900, 900, nullptr, Asteroid_2, -0.01, 7.9, 40.0, Asteroid_2_full, 0),
				ast5(900, 900, nullptr, Asteroid_1, -0.03, 8.5, 250.0, Asteroid_1_full, 0),
				ast6(900, 900, nullptr, Asteroid_2, 0.09, 6.2, 60.0, Asteroid_2_full, 0),
				ast7(900, 900, nullptr, Asteroid_1, 0.05, 8.5, 270.0, Asteroid_1_full, 0),
				ast8(900, 900, nullptr, Asteroid_2, 0.08, 7, 80.0, Asteroid_2_full, 0),
				ast9(900, 900, nullptr, Asteroid_1, 0.009, 7.9, 90.0, Asteroid_1_full, 0),
				ast10(900, 900, nullptr, Asteroid_2, 0.1, 7.3, 100.0, Asteroid_2_full, 0),

				testfont(20) {}

			void Vordergrund() {
				//
				stringgeld += to_string(geld);
				stringgeld += "$";
				testfont.draw(stringgeld, 1660, 70, 1.0, 2.0, 2.0, Gosu::Color::RED);
				stringgeld = "Geld: ";
				Platzhalter.draw(1660.0, 130.0, 0.0, 0.1, 0.1);
				testfont.draw("SM-3       400$", 1730.0, 130.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
				Platzhalter.draw(1660.0, 190.0, 0.0, 0.1, 0.1);
				testfont.draw("Trident    400$", 1730.0, 190.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
				Platzhalter.draw(1660.0, 250.0, 0.0, 0.1, 0.1);
				testfont.draw("Satan      700$", 1730.0, 250.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
				Ernter.draw(1660.0, 310.0, 0.0, 0.165, 0.165);
				if (Anzahl_Ernter <= 10)
				{
					testfont.draw("Miner	  300$", 1730.0, 310.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
				}
				else
				{
					testfont.draw("all Miners used", 1730.0, 310.0, 0.0, 1.0, 1.0, Gosu::Color::RED);
				}
				Raumstation_rahmen.draw(1660.0, 370.0, 0.0, 0.1, 0.1);
				testfont.draw("Satellit  1000$", 1730.0, 370.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);

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
				testfont.draw(Nachricht, 1730.0, 1000.0, 0.0, 1.0, 1.0, Gosu::Color::RED);

			}

			void Asteroiden_update(std::vector<Asteroid>& Asteroiden_vector) {
				if (Klick_maus_links && (rakete_auswahl == 4) && (geld >= 300))
				{
					Anzahl_Ernter = Anzahl_Ernter + 1;
					geld = geld - 300;
				}
				else if (Klick_maus_links && (rakete_auswahl == 4) && (geld < 300))
				{
					Nachricht = "nicht genug Geld";
				}

				for (int i = 0; i < 10; i++)
				{
					if ((i + 1) <= (Anzahl_Ernter))
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
			bool Toggle_Maus_Links() {
				if ((input().down(Gosu::MS_LEFT)) && (Klick_maus_links_remember == false)) {
					Klick_maus_links = true;
					Klick_maus_links_remember = true;
				}
				else if ((input().down(Gosu::MS_LEFT)) && (Klick_maus_links_remember == true))
				{
					Klick_maus_links = false;
				}
				else
				{
					Klick_maus_links = false;
					Klick_maus_links_remember = false;
				}
				return Klick_maus_links;
			
			}


			// wird bis zu 60x pro Sekunde aufgerufen.
			// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
			// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
			void draw() override
			{
				Erde.draw();
				Update_Raumschiff_draw(Raumschiff_Liste);
				Update_Rakete_draw(Raketen_Liste);
				pfeil.draw(x_maus,y_maus,1);
			}



			// Wird 60x pro Sekunde aufgerufen
			void update() override
			{
				Wellen_Update(Welle, Zeit, Raumschiff_Liste, Typ1, Typ2, Typ3);
				Update_Raumschiff(Raumschiff_Liste);
				Erde.rot_berechnen();
				x_maus = input().mouse_x();
				y_maus = input().mouse_y();
				if (Toggle_Maus_Links() == true) {
				Raketen_Funktion (Check_Maus(x_maus,y_maus,Raumschiff_Liste)
				
				}
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