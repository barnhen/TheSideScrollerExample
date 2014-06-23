#include "Misc.hpp"
#include "game.hpp"


Misc::Misc(void)
{
	theFont = al_load_font("arial.ttf", 12, 0);

}


Misc::~Misc(void)
{
	al_destroy_font(theFont);

}

//void Misc::ShowDebugMode(void)
//{
//	al_init_font_addon();
//	al_init_ttf_addon();
//	game g;
//	//al_init_font_addon();
//	//al_init_ttf_addon();
//	theFont = al_load_font("arial.ttf", 20, 0);
//	al_draw_textf(theFont, al_map_rgb(255, 255, 0), 5, 5, 0, "FPS: %i", g.GetGameFPS()); // display game FPS on screen
//
//}
