#pragma once

#include <allegro5\allegro.h>
#include <iostream>
#include <vector>
#include "base.hpp"

class player:baseclass
{
	al_rect box;
	ALLEGRO_BITMAP* image;
	int xvel, yvel;
	//al_rect clips[4];
	bool ground, jump;
	char direction;
	double frame;
	bool moving;
	int health;
public:
	player(ALLEGRO_BITMAP* img);
	~player(void);
	al_rect* getRect();
	void setXvel(int vel);
	int getXvel();
	void move(const std::vector<std::vector<int> >& map);
	void show (ALLEGRO_DISPLAY* screen);
	void setJump();
	void setMoving(bool b);
	void setDirection(char c);
	char getDirection();
	int getHealth();
	void setHealth(int h);

	//void FillRect(ALLEGRO_DISPLAY* screen, int x, int y, int w, int h, int color);
};

