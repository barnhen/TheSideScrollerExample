#include "enemy.hpp"
#include <iostream>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

enemy::enemy(ALLEGRO_BITMAP* img, int x, int y, int xVel, int yVel)
{
	image = img; 
	box.x = x;
	box.y = y;
	box.w = al_get_bitmap_width(image)/2;
	box.h = al_get_bitmap_height(image);
	xvel = xVel;
	yvel = yVel;
	maxFrame = 2; // old 3
	animationRow = 1;
	frameCount = 0;
	frameDelay = 19;
	ground = false;
	for (int i = 0; i < 2; i++)
	{
		clips[i].x = i* 50; // 50 is the enemy height frame
		clips[i].y = 0;
		clips[i].w = clips[i].h = 50; // 50 is the enemy height frame
	}
	frame = 0.0;
	curFrame = 1;
	frameWidth = 50; //old 31.6
	frameHeight = 50; //old 32

}

void enemy::show(ALLEGRO_DISPLAY* screen)
{
	std::cout<<"frameCount->"<<frameCount<<std::endl;
	std::cout<<"frameDelay->"<<frameDelay<<std::endl;
	if(++frameCount >= frameDelay){
		//std::cout<<"frameCount->"<<frameCount<<std::endl;
		//std::cout<<"frameDelay->"<<frameDelay<<std::endl;
		if(++curFrame >= maxFrame){
			curFrame = 0;

		}
		frameCount=0;
	}
	al_rect tmp = {box.x -coord.x,box.y,50, 50}; // must do this way to be relative coordinate	
	int fx = (curFrame) * (int)frameWidth;
	int fy = animationRow * (int)frameHeight;

	//SDL_BlitSurface(image, &clips[(int) (frame + 0.5) ], screen, &tmp);
	//al_draw_bitmap_region(image, tmp.x,tmp.y,tmp.w,tmp.h, fx, fy,0);
	ALLEGRO_FONT *theFont= al_load_font("arial.ttf", 12, 0);
	al_draw_textf(theFont, al_map_rgb(255, 255, 0), 5, 65, 0, "enemy FX: %i", fx);
	al_draw_textf(theFont, al_map_rgb(255, 255, 0), 85, 65, 0, "enemy FY: %i", fy);
	al_draw_textf(theFont, al_map_rgb(255, 255, 0), 165, 65, 0, "enemy box.x: %i", box.x);
	al_draw_textf(theFont, al_map_rgb(255, 255, 0), 265, 65, 0, "enemy box.y: %i", box.y);
	al_draw_textf(theFont, al_map_rgb(255, 255, 0), 365, 65, 0, "enemy tmp.w: %i", tmp.w);
	al_draw_textf(theFont, al_map_rgb(255, 255, 0), 465, 65, 0, "enemy tmp.h: %i", tmp.h);




	al_draw_bitmap_region(image, fx, coord.y, tmp.w,tmp.h,enemy::box.x,enemy::box.y, 0);

}


al_rect* enemy::getRect()
{
	return &box;
}

void enemy::move(std::vector<std::vector<int> >& map)
{
	int start = ( baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE - 2;
	int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / 50 + 2;
	
	if (start < 0)
	{
		start=0;
	}
	if (end > map[0].size())
	{
		end = map[0].size();
	}
	bool nc = false; // non collision

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = start; j < end; j++)
		{
			if(map[i][j] == 0)
				continue;
			al_rect destrect =  { j * 50, i * 50, 50, 50 };
			if (collision(&box, &destrect))
			{
				if(destrect.y >= box.y + box.h - 11)
				{
					ground = true;
					yvel= 0;
					nc = true;
				}
				//else if (destrect.y + destrect.h <= box.y + 11)
				//{
				//	xvel =- xvel;
				//}
				//if (box.x + box.w >= destrect.x - 5 && 
				//	box.y + box.h >= destrect.y + 6 && 
				//	box.x + box.w <= destrect.x + 20)
				//{
				//	xvel =- xvel;

				//}		
				else
				{
					xvel =- xvel;
				}
			}
		}
	}
	if (!nc) // not colliding
	{
		yvel=5;
	}
	
	box.x += xvel;
	box.y += yvel;

	frame+=0.1;

	if (frame >= 1.4)
	{
		frame = 0.0;
	}
	
}