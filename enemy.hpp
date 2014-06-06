#pragma once
#include <allegro5\allegro.h>
#include<vector>
#include "base.hpp"

class enemy:public baseclass
{
	al_rect box;
	int xvel, yvel;
	ALLEGRO_BITMAP* image;
	bool ground;
	al_rect clips[2];
	double frame;

	public:
		enemy(ALLEGRO_BITMAP* img, int x, int y, int xVel, int yVel);
		void move(std::vector<std::vector<int> >& map);
		void show(ALLEGRO_DISPLAY* screen);
		al_rect* getRect();
};

