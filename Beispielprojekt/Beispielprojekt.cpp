#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "Vektor2d.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image bild;
	GameWindow()
		: Window(800, 600)
		, bild("rakete.png")
	{
		set_caption("Gosu Tutorial Game mit Git");
	}
	int x = 0;
	int y = 0;
	int rot_x = 0;
	int rot_y = 0;

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		bild.draw_rot(x, y, 0.0,
			rot_y,
			0.5, 5*sin(1+rot_x*0.1));
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		y = input().mouse_y();
		x = input().mouse_x();
		if (input().down(Gosu::MS_LEFT)) {
			rot_y -= 5;
		}
		if (input().down(Gosu::MS_RIGHT)) {
			rot_y += 5;
		}
		if (input().down(Gosu::MS_RIGHT)) {
			rot_x += 1;
		}
		if (input().down(Gosu::MS_LEFT)) {
			rot_x -= 1;
		}
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
