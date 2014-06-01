#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "al_rect.hpp"



class baseclass
{
protected:
	bool collision(al_rect* rec1, al_rect* rec2);
public:
	static al_rect coord;//coord variable, store the absolute coordinate of the screen, so if I go a 1000px it will be a 1000px
    //actual memory will be reserved in the game.cpp
	
	static const int TILE_SIZE=50;
	ALLEGRO_TIMER *timer;
	void al_getTicks();


};