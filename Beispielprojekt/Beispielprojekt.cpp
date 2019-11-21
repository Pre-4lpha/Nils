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
int Welle = 50;
int durchlauf = 0;
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
	Raumschiff(double x, double y, Objekt* oz, Gosu::Image B, double G, double v) : Objekt(x, y, oz, B,v) { }
	int Leben;
	int Ort = 0;
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, this->rot, 0.5, 0.5,0.05,0.05);

	}
};




void Wellen_Funktion(list<Raumschiff>& liste, int Welle,Raumschiff &T1,Raumschiff &T2, Raumschiff &T3) {
	int durchlauf = 0;
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
	
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ3); Wellen_Groeﬂe--) {
		liste.push_back(T3);
		cout << "test3" << endl;
		T3.pos_x = Fenster_x/2+(-1400 * cos((360.0 / Anzahl_Typ3)*durchlauf));
		T3.pos_y = Fenster_y/2 +( 1400 * sin((360.0 / Anzahl_Typ3)*durchlauf));
		durchlauf += 1;
	}
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ3-Anzahl_Typ2); Wellen_Groeﬂe--) {
		liste.push_back(T2);
		cout << "test2" <<endl;
		T2.pos_x = Fenster_x/2 + (1200 * cos((360.0 / Anzahl_Typ2)*durchlauf));
		T2.pos_y = Fenster_y/2 + (-1200 * sin((360.0 / Anzahl_Typ2)*durchlauf));
		durchlauf += 1;
	}
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ1); Wellen_Groeﬂe--) {
		liste.push_back(T1);
		cout << "test1" << endl;
		T1.pos_x = Fenster_x/2 +( -1200 * sin((360.0 / double(Anzahl_Typ1))*durchlauf));
		T1.pos_y = Fenster_y/2 + (1200 * cos((360.0 / double(Anzahl_Typ1))*durchlauf));
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
	if (Zeit >= 1.0) {
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

class Erde : public Objekt  {
public:
	Erde(double x, double y, Objekt* oz, Gosu::Image B,double v) : Objekt(x, y, oz, B), v(v) { }
	void rot_berechnen(){
		this->rot += v;
		

	}
	double v = 0.1;
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, this->rot, 0.5, 0.5, 0.5, 0.5);

	}
};





	

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image Bild_Raumschiff1;
	Gosu::Image Bild_Raumschiff2;
	Gosu::Image Bild_Raumschiff3;

	Gosu::Image Bild_Erde;
	Erde Erde;
	Raumschiff Typ1;
	Raumschiff Typ2;
	Raumschiff Typ3;
	list<Raumschiff> Raumschiff_Liste;
	double Zeit = 57;
	
	GameWindow()
		: Window(Fenster_x, Fenster_y),
		Bild_Raumschiff1("R1.png"),
		Bild_Raumschiff2("R2.png"),
		Bild_Raumschiff3("R3.png"),
		Bild_Erde("Erde.png"),
		Erde(Fenster_x / 2, Fenster_y / 2, nullptr, Bild_Erde, 0.2),
		Typ1(500, 0, &Erde, Bild_Raumschiff1,50),
		Typ2(600, 0, &Erde, Bild_Raumschiff2,100),
		Typ3(700, 0, &Erde, Bild_Raumschiff3,5) {
		set_caption("Earth");
	}

	
	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		Erde.draw();
		Update_Raumschiff_draw(Raumschiff_Liste);
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
