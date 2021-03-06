#include "player.hpp"
//#include <allegro5\allegro_primitives.h>


player::player(ALLEGRO_BITMAP* img)
{
	image = img;
	box.x = 0;
	box.y = 0;
	box.w = 50;
	box.h = 50;

	xvel = 0;
	yvel = 0;

	flipped = false;

	//4 is the clips size
	//for (int i = 0; i < 4; i++)
	//{
	//	clips[i].x = i * 50;
	//	clips[i].y = 0;
	//	clips[i].w = clips[i].h = 50;
	//}
	ground = false;
	jump = false;
	direction = 'r';
	frame = 0.0;
	moving = false;
	health = 10;
		curFrame = 0;

	frameWidth = 50; //old 31.6
	frameHeight = 50; //old 32
	maxFrame = 2; // old 3
	animationRow = 1;
	frameCount = 0;
	frameDelay = 19;
	//al_init_primitives_addon();


}

void player::setJump()
{
	if (ground && !jump)
	{
		jump = true;
		ground = false;
		yvel =-17; //velocity from jumping from ground to mid-air until reaches 0 and it increase from 0 to more until reaches the ground
		box.y -= 5;
	}
	
}

int player::getHealth()
{
	return health;
}

void player::setHealth( int h)
{
	health = h;
}

char player::getDirection()
{
	return direction;
}
player::~player(void)
{
	al_destroy_bitmap(image);
}

al_rect* player::getRect()
{
	return &box;
}

int player::getXvel()
{
	return xvel;
}

void player::setXvel(int vel)
{
	xvel = vel;
}

void player::show(ALLEGRO_DISPLAY* screen)
{
	//char dx;
	//if(box.y < 0)
	//	box.y = 0;
	//else if(box.y > Height)
	//	box.y = HEIGHT;
	if (!moving)
	{
		//curFrame = 0;
		//xvel = 0;
		//yvel = 0;
	}
	else
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
	}

	// since there is no specific round function in cpp and cast in integer does round a value below and add 0.5 to round the upper value so everything above 0.5 will be 1 and everything below 0.5 will be zero.
	//SDL_BlitSurface(image, &clips[(int) (frame + 0.5)], screen, &box);
	std::cout<<"curFrame is "<<curFrame<<std::endl;
	std::cout<<"animationRow is "<<animationRow<<std::endl;
	fx = (curFrame) * (int)frameWidth;
	fy = animationRow * (int)frameHeight;

	//dx = getDirection();
	if (!flipped)
	{
		//Draws a scaled version of the given bitmap to the target bitmap.
		//	sx - source x
		//	sy - source y
		//	sw - source width
		//	sh - source height
		//	dx - destination x
		//	dy - destination y
		//	dw - destination width
		//	dh - destination height
		//	flags - same as foral_draw_bitmap
		//al_draw_scaled_bitmap(image, baseclass::coord.x, baseclass::coord.y, box.w, box.h, 
		//					  box.x, box.y, box.w * 2, box.h * 2,0);

		//al_draw_scaled_bitmap(image, box.x, box.y, box.w, box.h, 
							  //box.x, box.y, box.w * 2, box.h * 2,NULL);
		//al_draw_bitmap(image, box.x, box.y,NULL);
			al_draw_bitmap_region(image, fx, baseclass::coord.y, frameWidth, frameHeight,
				box.x, box.y, 0);	
		//al_draw_bitmap(image, fx, fy,NULL);


	}//if (direction = 'r')
	else if (flipped)
	{
		//Draws a scaled version of the given bitmap to the target bitmap.
		//	sx - source x
		//	sy - source y
		//	sw - source width
		//	sh - source height
		//	dx - destination x
		//	dy - destination y
		//	dw - destination width
		//	dh - destination height
		//	flags - same as foral_draw_bitmap
		al_draw_bitmap_region(image, fx, baseclass::coord.y, frameWidth, frameHeight,
			box.x, box.y, ALLEGRO_FLIP_HORIZONTAL);		
	}



}

void player::setMoving(bool b)
{
	moving = b;
}

void player::setDirection(char c)
{
	if ((c == 'r' || c == 'l') && direction != c)
	{
		direction = c;
		if (direction == 'r')
		{
			//frame = 0.0;
			flipped = false;
		}
		else
		{
			//frame = 1.6;
			flipped = true;
		}
	}
}

void player::move(const std::vector<std::vector<int> >& map)
{
	int start = ( baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
	int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / 50;
	
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
			al_rect destrect =  { j * 50 - baseclass::coord.x,i * 50, 50, 50 };
			
			if (collision(&box, &destrect))
			{
				nc = true;
				if(destrect.y >= box.y + box.h - 11)
				{
					ground = true;
					yvel= 0 ;
				}
				else if (destrect.y + destrect.h <= box.y + 11)
				{
					box.x++;
					yvel = 5; // this will be gravity
				}
				if (box.x + box.w >= destrect.x - 5 && 
					box.y + box.h >= destrect.y + 6 && 
					box.x + box.w <= destrect.x + 20)
				{
					xvel = 0;
					box.x--;

				}
				else if (box.x <= destrect.x + destrect.w &&
						 box.y + box.h >= destrect.y + 6)
				{
					xvel = 0;
					box.x++;
				}
			}
		}
	}
	if (!nc && !jump) // not colliding nor jumping
	{
		yvel=5;
	}
	if (jump && yvel < 5)
	{
		yvel++;
	}
	else
	{
		jump = false;
	}
	
	box.x += xvel;
	box.y += yvel;
	if (moving)
	{
		//curFrame+=1;
		//curFrame++;

	//	// workaround to loop in the spritesheet begin
	//	if (direction == 'r' && frame >= 1.4)
	//	{
	//		frame = 0.0;
	//	}
	//	else if (direction == 'l' && frame >=3.4)
	//	{
	//		frame = 1.5; // starts on the flipped side of player sprite
	//	}
	//	// workaround to loop in the spritesheet end
	}
	else
	{
		curFrame=0;
	}
	
}

//void player::FillRect(SDL_Surface* screen, int x, int y, int w, int h, int color) {
//	SDL_Rect rect = {x,y,w,h};
//	SDL_FillRect(screen, &rect, color);
//}