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
int Zeit = 0;
double rot_geschwindigkeit = 0.2;
int Welle = 0;
bool neue_welle;
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
	void update() {
		rot_berechnen;
		abstand_berechnen;
		bewegung;
	}


};

list<Raumschiff> Raumschiff_Liste;


void Wellen_Funktion(list<Raumschiff> liste, int Welle,Raumschiff T1,Raumschiff T2, Raumschiff T3) {
	int Anzahl_Typ1 = Welle;
	int Anzahl_Typ2 = 0;
	int Anzahl_Typ3 = 0;
	if (Welle >= 3) {
		int Anzahl_Typ2 = (Welle - (Welle % 3)) / 3;
	}
	if (Welle >= 5) {
		int Anzahl_Typ3 = (Welle - (Welle % 5)) / 5;
	}
	int Wellen_Groeﬂe = Welle;
	int Durchlauf = 0;
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ3); Wellen_Groeﬂe--) {
		liste.push_back(T3);
		T1.pos_x = -700 * cos((360 / Anzahl_Typ3)*Durchlauf);
		T1.pos_x = 700 * sin((360 / Anzahl_Typ3)*Durchlauf);
		Durchlauf += 1;
	}
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ3-Anzahl_Typ2); Wellen_Groeﬂe--) {
		liste.push_back(T2);
		T1.pos_x = 600 * cos((360 / Anzahl_Typ2)*Durchlauf);
		T1.pos_x = -600 * sin((360 / Anzahl_Typ2)*Durchlauf);
		Durchlauf += 1;
	}
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe >= (Welle - Anzahl_Typ3-Anzahl_Typ2-Anzahl_Typ1); Wellen_Groeﬂe--) {
		liste.push_back(T1);
		T1.pos_x = -500 * sin((360 / Anzahl_Typ3)*Durchlauf);
		T1.pos_x = 500 * cos((360 / Anzahl_Typ3)*Durchlauf);
		Durchlauf += 1;
	}


}

void Update_Raumschiff(list<Raumschiff> liste) {
	for (list<Raumschiff>::iterator i = liste.begin(); i != liste.end(); i++)
	{
		*i->update;
	}
}

void Wellen_Update(int Welle, double Zeit, list<Raumschiff> liste,Raumschiff T1, Raumschiff T2, Raumschiff T3){
	Zeit += 1 / 60;
	if (Zeit == 60) {
		Welle += 1;
		Zeit -= 60;
		neue_welle = true;

	}
}

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
	int Ort = 0;
	void angriff() {
		if (this->abstand <= 100) {
			Raumschiff_Liste.erase.at(Ort);
	}
	}
	void update() {
		this->rot_berechnen;
		this->abstand_berechnen;
		this->bewegung;
		this->angriff;
	}
};
	

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image Bild_Raumschiff;
	Gosu::Image Bild_Erde;
	Erde Erde;
	Raumschiff Typ1;
	Raumschiff Typ2;
	Raumschiff Typ3;
	
	GameWindow() : Window(Fenster_x, Fenster_y), Bild_Raumschiff("rakete.png"), Bild_Erde("Erde.png"), Erde(Fenster_x / 2, Fenster_y / 2, nullptr, Bild_Erde), Typ1(500, 0, &Erde, Bild_Raumschiff), Typ2(600, 0, &Erde, Bild_Raumschiff), Typ3(700, 0, &Erde, Bild_Raumschiff) {
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
		Wellen_Update(Welle, Zeit, Raumschiff_Liste, Typ1, Typ2, Typ3);
		Update_Raumschiff(Raumschiff_Liste);
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
