#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "base.hpp"
#include "player.hpp"
//#include "bullet.hpp"
#include <iostream>
#include <fstream> // to read map files
#include <vector>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
//#include "enemy.hpp"
#include "base.hpp"


class game:public baseclass
{
	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *screen;
	//const int FPS = 60;
	ALLEGRO_BITMAP*  background, *block, *bul, *ene;	
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font;
	ALLEGRO_EVENT ev;

	//==============================================
	//SHELL VARIABLES
	//==============================================
	bool done;
	bool render;

	float gameTime;
	int frames;
	int gameFPS;


	al_rect camera;
	std::vector<std::vector<int> > map;
	//std::vector<bullet*> bullets;
	//std::vector<enemy*> enemies;

	bool direction[2]; // for x and y coordinates
	al_rect finish;
	ALLEGRO_BITMAP* load_image(const char* filename);
	void loadmap(const char* filename);
	void showmap();
	void handleEvents();
	bool running;
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	player* player1;
	bool bound;
	

public:
	game();
	~game();
	void start();
	//int showmenu(ALLEGRO_DISPLAY* screen); //shows he menu
	//void showMessage(const char* c);
};

