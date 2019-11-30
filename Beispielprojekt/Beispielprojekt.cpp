#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <list>

#include "Vektor2d.h"
using namespace std;

int Fenster_x = 1920;
int Fenster_y = 1080;
double rot_geschwindigkeit = 0.2;
int Welle = 3;
double PI = 3.1415962;
string stringgeld = "Geld: ";
string Nachricht = "";		//diesen string kannst du bei bedarf umbenennen, er wird rechts unten ausgegeben f¸r nachrichten an spieler
unsigned geld = 5000;
int rakete_auswahl = 1;
double x_maus;
double y_maus;
bool Klick_maus_links;
bool Klick_maus_links_remember;		//f¸rs toggeln
int Anzahl_Ernter = 0;				//max: 10
bool raumstation_setzen = false;
int Anzahl_Raumstationen = 0;
bool bool_ziel;
unsigned Score = 0;
string stringScore = "Score: ";


class Objekt {
public:
	Gosu::Image Bild;
	double pos_x = Fenster_x;
	double pos_y = Fenster_y;
	double rot;
	Objekt* Target_Objekt_Ptr;
	Objekt(double x, double y, Objekt* oz, Gosu::Image B, double v, int L) : pos_x(x), pos_y(y), Target_Objekt_Ptr(oz), Bild(B), v(v), Leben(L) {};
	double dy;
	double dx;
	double abstand;
	int Leben;
	double v; // Geschwindigkeit


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
class Raumschiff : public Objekt {
public:
	Raumschiff(double x, double y, Objekt* oz, Gosu::Image* B, double v, int L) : Objekt(x, y, oz, *B, v, L) { }
	int Ort = 0;
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, this->rot, 0.5, 0.5, 0.05, 0.05);

	}
	void draw_markiert()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.1, this->rot, 0.5, 0.5, 0.07, 0.07, Gosu::Color::BLUE);

	}

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
	Asteroid(double x, double y, Objekt* oz, Gosu::Image B, double v, int L, int r, double rot, Gosu::Image B_full, int status)
		: Objekt(x, y, oz, B, v, L), v(v), radius(r), rot(rot), Bild_full(B_full), status(status) { }

	//es werden zwei bilder ¸bergeben, f¸r leer und mit Ernter besetzt

	void rot_berechnen()
	{
		this->rot += v;
		if (this->rot >= 360)
		{
			this->rot = 0;
		}
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
void Get_Geld_Ernter() {
	geld = geld + (Anzahl_Ernter * 50 * Welle);
	Score += (Anzahl_Ernter * 50 * Welle);
}
class Erde : public Objekt {
public:
	Erde(double x, double y, Objekt* oz, Gosu::Image B, double v, int L) : Objekt(x, y, oz, B, v, L) { }
	void rot_berechnen() {
		this->rot += v;
		if (rot > 360) {
			rot -= 360;
		}
	}
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, this->rot, 0.5, 0.5, 0.3, 0.3);
	}
};
class Laser : public Erde {
public:
	Laser(double x, double y, Objekt* oz, Gosu::Image B, double v, int L, int S) : Erde(x, y, oz, B, v, L), Schaden(S) { };
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, -0.1, this->rot, 0.5, 0, 0.5, 1);
	}
	int Schaden;
	void rot_berechnen() {
		this->rot += v;
		if (rot > 360) {
			rot -= 360;
		}
	}
};
class Rakete : public Objekt {
public:
	Rakete(double x, double y, Objekt* oz, Gosu::Image B, double v, int L, int S, double r) : Objekt(x, y, oz, B, v, L), Schaden(S), rot(r) { }
	int Schaden;
	double rot;
	void draw()
	{
		Bild.draw_rot(this->pos_x, this->pos_y, 0.0, this->rot, 0, 0, 0.5, 0.5);

	}
	void rot_berechnen() {
		double temp_rot = Gosu::angle(this->pos_x, this->pos_y, this->Target_Objekt_Ptr->pos_x, this->Target_Objekt_Ptr->pos_y, 0);
		if (360 <= temp_rot + (180 - rot)) {
			temp_rot -= 360;
		}
		if (this->rot <= temp_rot) {
			if ((temp_rot - this->rot) > 5) {
				this->rot += 5;
			}
			else {
				this->rot = temp_rot;
			}
		}
		else {
			if ((this->rot - temp_rot) > 5) {
				this->rot -= 5;
			}
			else {
				this->rot = temp_rot;
			}
		}

	};
	void bewegung() {
		this->pos_x += Gosu::offset_x(rot, 1) * v;
		this->pos_y += Gosu::offset_y(rot, 1) * v;
	}

};

Raumschiff& Check_Maus(int x, int y, list<shared_ptr<Raumschiff>>& liste, int min_abstand) {
	//gibt Zeiger auf markiertes Raumschiff aus
	shared_ptr<Raumschiff> Ziel;
	auto i = liste.begin();
	bool_ziel = false;

	while (i != liste.end()) {
		{
			double dx = (*i)->pos_x - x;
			double dy = (*i)->pos_y - y;
			double abstand = sqrt((dx * dx) + (dy * dy));
			if ((abstand < min_abstand)&&(abstand > 1))
			{
				min_abstand = abstand;
				bool_ziel = true;
				Ziel = *i;
			}
			i++;
		}
	}
	return *Ziel;
}
void Zeiger_Update(list<Rakete>& liste, list<shared_ptr<Raumschiff>>& liste_Raumschiff, Raumschiff& i_raumschiff, Raumschiff& E) {
	list<Rakete>::iterator i = liste.begin();
	while (i != liste.end())
	{

		if (liste_Raumschiff.size() == 0)
		{
			i->Target_Objekt_Ptr = &E;
		}
		else if (i->Target_Objekt_Ptr == &E)
		{
			i->Target_Objekt_Ptr = &Check_Maus(i_raumschiff.pos_y, i_raumschiff.pos_x, liste_Raumschiff, 10000);
		}
		else if (i->Target_Objekt_Ptr == &i_raumschiff)
		{
			if (i->Target_Objekt_Ptr == &Check_Maus(i_raumschiff.pos_y, i_raumschiff.pos_x, liste_Raumschiff, 10000))
			{
				i->Target_Objekt_Ptr = &*liste_Raumschiff.front();
			}
			else i->Target_Objekt_Ptr = &Check_Maus(i_raumschiff.pos_y, i_raumschiff.pos_x, liste_Raumschiff, 10000);
		}
		i++;


	}
}
void Wellen_Funktion(list<shared_ptr<Raumschiff>>& liste, int Welle, Raumschiff& T1, Raumschiff& T2, Raumschiff& T3) {
	int durchlauf = 1;
	int Anzahl_Typ1 = Welle;
	int Anzahl_Typ2 = 0;
	int Anzahl_Typ3 = 0;
	if (Welle >= 3) {

		Anzahl_Typ2 = int(Welle / 3.0);
		//int Anzahl_Typ2 = ((Welle - (Welle % 3)) / 3.0);
	}

	if (Welle >= 5) {
		Anzahl_Typ3 = ((Welle - (Welle % 5)) / 5);
	}
	durchlauf = 1 + Welle;
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ3); Wellen_Groeﬂe--) {
		T3.pos_x = Fenster_x / 2 + (-1400 * (pow(1.05, durchlauf - Welle)) * cos(durchlauf * (2.0 * PI / double(Anzahl_Typ3))));
		T3.pos_y = Fenster_y / 2 + (1400 * (pow(1.05, durchlauf - Welle)) * sin(durchlauf * (2.0 * PI / double(Anzahl_Typ3))));
		liste.push_back(make_shared<Raumschiff>(T3));
		durchlauf += 1;
	}
	durchlauf = 1;
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ3 - Anzahl_Typ2); Wellen_Groeﬂe--) {
		T2.pos_x = Fenster_x / 2 + (1200 * (pow(1.05, durchlauf)) * cos(durchlauf * (2.0 * PI / double(Anzahl_Typ2))));
		T2.pos_y = Fenster_y / 2 + (-1200 * (pow(1.05, durchlauf)) * sin(durchlauf * (2.0 * PI / double(Anzahl_Typ2))));
		liste.push_back(make_shared<Raumschiff>(T2));
		durchlauf += 1;
	}
	durchlauf = 1;
	for (int Wellen_Groeﬂe = Welle; Wellen_Groeﬂe > (Welle - Anzahl_Typ1); Wellen_Groeﬂe--) {
		T1.pos_x = Fenster_x / 2 + (-1000 * (pow(1.05, durchlauf)) * sin(durchlauf * (2.0 * PI / double(Anzahl_Typ1))));
		//cout << sin(durchlauf * (1.0 / double(Anzahl_Typ1))) << endl;
		T1.pos_y = Fenster_y / 2 + (1000 * (pow(1.05, durchlauf)) * cos(durchlauf * (2.0 * PI / double(Anzahl_Typ1))));
		liste.push_back(make_shared<Raumschiff>(T1));
		durchlauf += 1;
	}


}
void Update_Raumschiff(list<shared_ptr<Raumschiff>>& liste, list<Rakete>& liste_Rakete, Raumschiff E, Erde& Erde) {
	auto i = liste.begin();
	while (i != liste.end())
	{
		(*i)->abstand_berechnen();
		(*i)->rot_berechnen();
		(*i)->bewegung();
		if ((*i)->Leben <= 0) {
			
			Zeiger_Update(liste_Rakete, liste, **i, E);
			i = liste.erase(i);
		}
		else if ((*i)->abstand <= 100) {
			Erde.Leben -= ((*i)->Leben)*5;
			Zeiger_Update(liste_Rakete, liste, **i, E);
			i = liste.erase(i);
		}
		else {
			i++;
		}


	}
}
void Update_Rakete(list<Rakete>& liste) {
	auto i = liste.begin();
	while (i != liste.end())
	{
		i->rot_berechnen();
		i->abstand_berechnen();
		i->bewegung();
		if (i->abstand <= 40) {
			i->Target_Objekt_Ptr->Leben -= i->Schaden;
			i = liste.erase(i);
		}
		else {
			i++;
		}


	}
}
void Wellen_Update(int& Welle, double& Zeit, list<shared_ptr<Raumschiff>>& liste, Raumschiff& T1, Raumschiff& T2, Raumschiff& T3) {
	Zeit = 1.0 / 60.0 + Zeit;
	if (Zeit >= 20.0) {
		Welle += 1;
		Zeit = 0;
		Wellen_Funktion(liste, Welle, T1, T2, T3);
		Get_Geld_Ernter();
		Nachricht = "";
		
	}
	else if (liste.size() == 0) {
		Welle += 1;
		Zeit = 0;
		Wellen_Funktion(liste, Welle, T1, T2, T3);
		Get_Geld_Ernter();
		Nachricht = "";
	}
}
void Update_Raumschiff_draw(list<shared_ptr<Raumschiff>>& liste) {
	auto i = liste.begin();
	while (i != liste.end()) {
		(*i)->draw();
		i++;
	}
}
void Update_Rakete_draw(list<Rakete>& liste) {
	auto i = liste.begin();
	while (i != liste.end()) {
		i->draw();
		i++;
	}
}
void Raketen_Funktion(list<Rakete>& liste, Rakete& Rakete, Raumschiff& Raumschiff,Erde Erde) {
	Rakete.Target_Objekt_Ptr = &Raumschiff;
	Rakete.rot = Erde.rot;
	liste.push_back(Rakete);
}
void draw_maus(int x, int y, list<shared_ptr<Raumschiff>>& liste, Gosu::Image Bild) {
	Check_Maus(x, y, liste, 100);
	if (bool_ziel == true) {
		Check_Maus(x, y, liste, 100).draw_markiert();
	}
}
void Laser_Schaden(list<shared_ptr<Raumschiff>>& liste, list<Rakete>& liste_Rakete, Laser& Laser) {
	auto i = liste.begin();
	double min_abstand = 1000;
	double rot = Laser.rot;

	while (i != liste.end()) {
		double dx = (*i)->pos_x - Laser.pos_x;
		double dy = (*i)->pos_y - Laser.pos_y;
		double abstand = sqrt((dx * dx) + (dy * dy));
		if (abstand <= min_abstand) {
			if ((rot - 1 <= (*i)->rot) && (rot + 1 >= (*i)->rot))
			{
				(*i)->Leben -= Laser.Schaden;
			}
		}
		i++;
	}

	if (Klick_maus_links && (rakete_auswahl == 5) && (geld >= 600) && (Laser.Schaden <= 5))
	{
		Laser.Schaden += 1;
		geld = geld - 600;
	}
	else if (Klick_maus_links && (rakete_auswahl == 5) && (geld < 600) && (Laser.Schaden <= 5))
	{
		Nachricht = "nicht genug Geld";
	}
	else if (Klick_maus_links && (rakete_auswahl == 5) && (geld < 600) && (Laser.Schaden >= 5))
	{
		Nachricht = "max Laser Power reached!!!";
	}
}


void Tastatur_Auswahl()
{
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

class GameWindow : public Gosu::Window
{
public:

	Gosu::Image Bild_Raumschiff1;
	Gosu::Image Bild_Raumschiff2;
	Gosu::Image Bild_Raumschiff3;
	Gosu::Image Bild_Rakete_1;
	Gosu::Image Bild_Rakete_2;
	Gosu::Image Bild_Rakete_3;
	Gosu::Image Bild_Rakete_1_rahmen;
	Gosu::Image Bild_Rakete_2_rahmen;
	Gosu::Image Bild_Rakete_3_rahmen;
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
	Gosu::Image Bild_Laser;
	Gosu::Image Bild_Laser_rahmen;
	Gosu::Font testfont;

	Erde Erde;
	Laser Laser;
	Raumschiff Typ1;
	Raumschiff Typ2;
	Raumschiff Typ3;
	list<shared_ptr<Raumschiff>> Raumschiff_Liste;
	double Zeit = 15;
	list<Rakete> Raketen_Liste;
	Rakete Rakete_1;
	Rakete Rakete_2;
	Rakete Rakete_3;

	Asteroid ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8, ast9, ast10;
	vector<Asteroid> Asteroiden_vector{ ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8, ast9, ast10 };



	GameWindow() : Window(Fenster_x, Fenster_y),
		Bild_Raumschiff1("R1.png"),
		Bild_Raumschiff2("R2.png"),
		Bild_Raumschiff3("R3.png"),
		Bild_Erde("Erde.png"),
		Bild_Rakete_1("M1.png"),
		Bild_Rakete_2("M2.png"),
		Bild_Rakete_3("M3.png"),
		Bild_Rakete_1_rahmen("M1_symbol.png"),
		Bild_Rakete_2_rahmen("M2_symbol.png"),
		Bild_Rakete_3_rahmen("M3_symbol.png"),
		Erde(Fenster_x / 2, Fenster_y / 2, nullptr, Bild_Erde, 0.2, 100),
		Typ1(500, 0, &Erde, &Bild_Raumschiff1, 1, 2),
		Typ2(600, 0, &Erde, &Bild_Raumschiff2, 2.5, 2),
		Typ3(700, 0, &Erde, &Bild_Raumschiff3, 0.5, 6),
		Rakete_1(Fenster_x / 2.0, Fenster_y / 2.0, nullptr, (Bild_Rakete_1), (10), 2, 2, Erde.rot),
		Rakete_2(Fenster_x / 2.0, Fenster_y / 2.0, nullptr, (Bild_Rakete_2), (8), 2, 2, Erde.rot),
		Rakete_3(Fenster_x / 2.0, Fenster_y / 2.0, nullptr, (Bild_Rakete_3), (5), 2, 6, Erde.rot),
		Ernter("Ernter.png"),

		Asteroid_1("Asteroid_2.png"),
		Asteroid_2("Asteroid_1.png"),
		Asteroid_1_full("Asteroid_2_full.png"),
		Asteroid_2_full("Asteroid_1_full.png"),
		Platzhalter("Platzhalter.png"),
		pfeil("pfeil.png"),

		rahmen("rahmen.png"),
		Bild_Laser("Laser.png"),
		Bild_Laser_rahmen("Laser_symbol.png"),

		Laser(Fenster_x / 2, Fenster_y / 2, nullptr, Bild_Laser, 0.2, 10, 0),

		ast1(900, 900, nullptr, Asteroid_1, -0.03, 0, 6, 210.0, Asteroid_1_full, 0),
		ast2(900, 900, nullptr, Asteroid_2, -0.04, 0, 8.7, 120.0, Asteroid_2_full, 0),
		ast3(900, 900, nullptr, Asteroid_1, -0.005, 0, 8, 30.0, Asteroid_1_full, 0),
		ast4(900, 900, nullptr, Asteroid_2, -0.01, 0, 7.9, 40.0, Asteroid_2_full, 0),
		ast5(900, 900, nullptr, Asteroid_1, -0.03, 0, 8.5, 250.0, Asteroid_1_full, 0),
		ast6(900, 900, nullptr, Asteroid_2, 0.09, 0, 6.2, 60.0, Asteroid_2_full, 0),
		ast7(900, 900, nullptr, Asteroid_1, 0.05, 0, 8.5, 270.0, Asteroid_1_full, 0),
		ast8(900, 900, nullptr, Asteroid_2, 0.08, 0, 7, 80.0, Asteroid_2_full, 0),
		ast9(900, 900, nullptr, Asteroid_1, 0.009, 0, 7.9, 90.0, Asteroid_1_full, 0),
		ast10(900, 900, nullptr, Asteroid_2, 0.1, 0, 7.3, 100.0, Asteroid_2_full, 0),


		testfont(20) {}


	void Vordergrund() {
		stringScore += to_string(Score);
		testfont.draw(stringScore, 70, 70, 1.0, 1.0, 1.0, Gosu::Color::WHITE);
		stringScore = "Score: ";
		stringgeld += to_string(geld);
		stringgeld += "$";
		testfont.draw(stringgeld, 1660, 70, 1.0, 2.0, 2.0, Gosu::Color::RED);
		stringgeld = "Geld: ";
		Bild_Rakete_1_rahmen.draw(1660.0, 130.0, 0.0, 0.165, 0.165);
		testfont.draw("SM-3       400$", 1730.0, 130.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
		Bild_Rakete_2_rahmen.draw(1660.0, 190.0, 0.0, 0.165, 0.165);
		testfont.draw("Sojus      400$", 1730.0, 190.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
		Bild_Rakete_3_rahmen.draw(1660.0, 250.0, 0.0, 0.165, 0.165);
		testfont.draw("Elon Musk  700$", 1730.0, 250.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
		Ernter.draw(1660.0, 310.0, 0.0, 0.165, 0.165);
		if (Anzahl_Ernter < 10)
		{
			testfont.draw("Miner	  300$", 1730.0, 310.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
		}
		else
		{
			testfont.draw("all Miners used", 1730.0, 310.0, 0.0, 1.0, 1.0, Gosu::Color::RED);
		}
		Bild_Laser_rahmen.draw(1660.0, 370.0, 0.0, 0.165, 0.165);
		if (Laser.Schaden <= 5)
		{
			testfont.draw("Laser Upgr. 600$", 1730.0, 370.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);
		}
		else
		{
			testfont.draw("Max. Power reached", 1730.0, 370.0, 0.0, 1.0, 1.0, Gosu::Color::RED);
		}
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
		testfont.draw("Erde: "+to_string(Erde.Leben)+"/100", 900.0, 1000.0, 0.0, 1.0, 1.0, Gosu::Color::WHITE);

	}

	void Asteroiden_Update(std::vector<Asteroid>& Asteroiden_vector) {
		if (Klick_maus_links && (rakete_auswahl == 4) && (geld >= 300) && (Anzahl_Ernter < 10))
		{
			Anzahl_Ernter = Anzahl_Ernter + 1;
			geld = geld - 300;
		}
		else if (Klick_maus_links && (rakete_auswahl == 4) && (geld < 300) && (Anzahl_Ernter < 10))
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
	void Restart()
	{
		Score, Welle = 0;
		geld = 5000;
		//bitte hier die Listen f¸r Raketen und Raumschiffe leeren 
		Erde.Leben = 100;
	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		if (Erde.Leben > 0)
		{
			Erde.draw();
			Laser.draw();
			Asteroiden_draw();
			Update_Raumschiff_draw(Raumschiff_Liste);
			Update_Rakete_draw(Raketen_Liste);
			Vordergrund();
			draw_maus(x_maus, y_maus, Raumschiff_Liste, rahmen);
		}
		else
		{
			stringScore = "Your Score: ";
			stringScore += to_string(Score);
			testfont.draw("GAME OVER", 500, 300, 1.0, 3.0, 3.0, Gosu::Color::RED);
			testfont.draw(stringScore, 500, 500, 1.0, 2.0, 2.0, Gosu::Color::WHITE);
			testfont.draw("Press Mouse Left to Restart", 500, 800, 1.0, 1.0, 1.0, Gosu::Color::WHITE);
			pfeil.draw(x_maus, y_maus, 0.0, 0.1, 0.1);
			
		}
	}



	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		x_maus = input().mouse_x();
		y_maus = input().mouse_y();
		if (Erde.Leben > 0)
		{
			Wellen_Update(Welle, Zeit, Raumschiff_Liste, Typ1, Typ2, Typ3);
			Update_Raumschiff(Raumschiff_Liste, Raketen_Liste, Typ1, Erde);
			Update_Rakete(Raketen_Liste);
			Zeiger_Update(Raketen_Liste, Raumschiff_Liste, Typ1, Typ1);
			Erde.rot_berechnen();
			
			Tastatur_Auswahl();
			if (Toggle_Maus_Links() == true) {
				Check_Maus(x_maus, y_maus, Raumschiff_Liste, 100);
				if (bool_ziel == true)
				{
					if ((rakete_auswahl == 1) && (geld >=100))
					{
						Raketen_Funktion(Raketen_Liste, Rakete_1, Check_Maus(x_maus, y_maus, Raumschiff_Liste, 100),Erde);
						geld -= 100;
					}
					else if ((rakete_auswahl == 2) && (geld >= 200))
					{
						Raketen_Funktion(Raketen_Liste, Rakete_2, Check_Maus(x_maus, y_maus, Raumschiff_Liste, 100),Erde);
						geld -= 200;
					}
					else if ((rakete_auswahl == 3) && (geld >= 400))
					{
						Raketen_Funktion(Raketen_Liste, Rakete_3, Check_Maus(x_maus, y_maus, Raumschiff_Liste, 100),Erde);
						geld -= 400;
					}
				}
			}
			Laser.rot_berechnen();
			Laser_Schaden(Raumschiff_Liste, Raketen_Liste, Laser);
			Asteroiden_Update(Asteroiden_vector);
		}
		else
		{
			if (Toggle_Maus_Links())
			{
				Restart();
			}
		}
	}
};

// C++ Hauptprogramm
int main()
{

	GameWindow window;
	window.show();


}