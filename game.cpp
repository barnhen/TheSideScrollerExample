#include "game.hpp"

al_rect baseclass::coord; //we have to actually reserve memory for the static SDL_Rect from the baseclass


game::game()
{
	screen = NULL;
	background = NULL;
	block = NULL;
	bul = NULL;
	ene = NULL;


	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	event_queue = NULL;


	//==============================================
	//SHELL VARIABLES
	//==============================================
	done = false;
	render = false;
	running = true;

	gameTime = 0;
	frames = 0;
	gameFPS = 0;

	frameDelay = 4;

	baseclass::coord.x =  baseclass::coord.y = 0;
	baseclass::coord.w = SCREEN_WIDTH;
	baseclass::coord.h = SCREEN_HEIGHT;
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
	direction[0] = direction[1] = 0; // setting initial x, and y coord.
	//running = true;
	bound = false;
	//enemies.push_back(new enemy(ene, 100, 40, 1, 0));
	finish.x = 0;
	finish.y = 0;
	finish.w = 50;
	finish.h = 50;

	
}



game::~game(void)
{
	al_destroy_bitmap(block);
	al_destroy_bitmap(background);
	al_destroy_bitmap(bul);
	al_destroy_event_queue(event_queue);
	delete player1 ;
	//for (int i = 0; i < bullets.size(); i++)
	//{
	//	delete bullets[i];
	//}
	//for (int i = 0; i < enemies.size(); i++)
	//{
	//	delete enemies[i];
	//}
	al_destroy_font(font);
	//TTF_Quit();
	//SDL_Quit();
	al_destroy_display(screen);
}

ALLEGRO_BITMAP* game::load_image(const char* filename)
{
	ALLEGRO_BITMAP* tmp = al_load_bitmap(filename);  //load the BMP to a tmp variable
	//if (tmp == nullptr || tmp == NULL)
	//{
	//	std::cout<<"Couldn't load tmp image"<<std::endl;
	//}
	ALLEGRO_BITMAP* tmp2 = al_load_bitmap(filename); //change it to the format of the screen
	//if (tmp2 == nullptr || tmp2 == NULL)
	//{
	//	std::cout<<"Couldn't load tmp image"<<std::endl;
	//}
	//SDL_SetColorKey(tmp2,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format, 0x00,0xff,0xff));
	//SDL_FreeSurface(tmp);
	return tmp2; 
}

void game::handleEvents()
{

	
	//while(running)
	//{
	
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_start_timer(timer);

		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
				//case ALLEGRO_KEY_ESCAPE:
				//	running = false;
				//	return;
				case ALLEGRO_KEY_LEFT:
					direction[0]=1;
					player1->setMoving(true);
					break;
				case ALLEGRO_KEY_RIGHT:
					direction[1]=1;
					player1->setMoving(true);
					break;
				case ALLEGRO_KEY_SPACE:
					player1->setJump();
					break;
				case ALLEGRO_KEY_BACKSPACE:
					running = false;
					return;
				case ALLEGRO_KEY_F:
					//if (player1->getDirection() == 'r')
					//{
					//	bullets.push_back(new bullet(bul, 
					//			player1->getRect()->x + player1->getRect()->w, 
					//			player1->getRect()->y + 15, 5, 0));
					//}
					//else
					//{
					//	bullets.push_back(new bullet(bul, 
					//			player1->getRect()->x, 
					//			player1->getRect()->y + 15, -5, 0));
					//}
					break;
				case ALLEGRO_KEY_C:
					//bound = true;
					break;
				case ALLEGRO_KEY_ESCAPE:
					//int h = showmenu(screen);
					//if (h==1)
					//{
						running = false;
					//}
					break;
				//default:
				//	player1->setMoving(false);
				//	break;
			}
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_LEFT:
					direction[0]=0;
					player1->setMoving(false);
					break;
				case ALLEGRO_KEY_RIGHT:
					direction[1]=0;
					player1->setMoving(false);
					break;
				case ALLEGRO_KEY_BACKSPACE:
					running = false;
					return;
				case ALLEGRO_KEY_C:
					//bound = false;
					break;
				//default:
				//	player1->setMoving(false);
				//	break;

			}
			//break;
		}
		//==============================================
		//GAME UPDATE
		//==============================================
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			
			//UPDATE FPS===========
			frames++;
			if(al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

		//if(++frameCount >= frameDelay){
		//if(++curFrame >= maxFrame){
		//	curFrame = 0;

		//}
		//frameCount=0;
	
		//}


	}
	//else
	//{
	//	player1->setMoving(false);
	//	
	//}

}

void game::loadmap(const char* filename)
{
	std::ifstream in (filename);
	if(!in.is_open())
	{
		std::cout<<"Problem loading the file"<<std::endl;
	}
	int width,height;
	in >> width;
	in >> height;
	int current; //current block tile number
	for (int i = 0; i < height; i++)
	{
		std::vector<int> vec;

		for (int j = 0; j < width; j++)
		{
			if(in.eof())
			{
				std::cout<<"File end has reached too soon"<<std::endl;;
				return;
			}
			
			in >> current;
		//	if (current == -1)
		//	{
		//		enemies.push_back(new enemy(ene, j* 50, i * 50, 1, 0));
				//vec.push_back(0);
		//	}
		//	else
		//	{
		//		if (current>=0 && current <=7)
		//		{
		//			if (current == 3)
		//			{
		//				finish.x = j * 50;
		//				finish.y = i * 50;
		//			}
					vec.push_back(current);
		//		}			
		//		else
		//		{
					//vec.push_back(0);
		//		}
			//}
		}
		map.push_back(vec);
	}
	in.close();
	std::cout<< finish.x << " " << finish.y << std::endl;
}


void game::showmap()
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

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < end; j++)
		{
			if (map[i][j] !=0)
			{
				//we calculate the position in the TileSet-1.bmp image
				al_rect blockrect = {
										//because coord of tileset begins with 0 and not 1 I have to do (tilesize * tilenumber) minus 1
										(map[i][j]-1) * baseclass::TILE_SIZE,0,baseclass::TILE_SIZE,baseclass::TILE_SIZE
									 };

				//destrect = destination rectangle and in the screen (so for example if the camera at 100px position and the tile is at 120px position, we show the tile at 20px position
				al_rect destrect = {
										j * baseclass::TILE_SIZE-baseclass::coord.x, i*50
									};
				//SDL_BlitSurface(block, &blockrect,screen,&destrect);
				al_draw_bitmap_region(block, blockrect.x,blockrect.y,blockrect.w,blockrect.h,destrect.x, destrect.y,0);
				//al_flip_display();

			}
		}

	}
}


void game::start()
{
	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if(!al_init())										//initialize Allegro
		std::cout<<"Could not initialize allegro"<<std::endl;

	int start;
	screen = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);			//create our display object
	if(!screen)										//test display object
		std::cout<<"Could not create display"<<std::endl;

	//==============================================
	//ADDON INSTALL
	//==============================================
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	//al_install_audio();
	//al_init_acodec_addon();
	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	imgPlayer = al_load_bitmap("player.fw.png");
	player1 = new player(imgPlayer);

	block = load_image("TileSet-1.bmp");
	background=load_image("background.bmp");
	//bul = load_image("bullet.bmp");
	//ene = load_image("enemy.bmp");
	font = al_load_font("arial.ttf", 20, 0);


	loadmap("map.map");
	srand(time(NULL));
	gameTime = al_current_time();

	while(running)
	{
	//	start = SDL_GetTicks();
		start = (int)timer;
		render = true;
		handleEvents();
		if (direction[0])
		{
			player1->setDirection('l');
			if(player1->getRect()->x > 0)
			{
				player1 -> setXvel(-1);
			}
			else
			{
				player1->setXvel(0);
				camera.x--;
				baseclass::coord.x--;
			}
			if (camera.x < 0)
			{
				camera.x = 2000 - SCREEN_WIDTH;
			}
		}

		else if (direction[1])
		{
			player1->setDirection('r');
			if (player1->getRect()->x < 80) // so the player cannot movrt far left on the border left
			{
				player1->setXvel(1);
			}
			else
			{
				player1->setXvel(0);
				camera.x++;
				baseclass::coord.x++;
			}
			if (camera.x >= 2000 - SCREEN_WIDTH)
			{
				camera.x = 0;
			}
		}
		// if does not press any key
		else
		{
			player1->setXvel(0);
		}

	//			//collision detection begin
		int str = ( baseclass::coord.x - (baseclass::coord.x % baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
		int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / TILE_SIZE;
	
		if (start < 0)
		{
			start=0;
		}
		if (end > map[0].size())
		{
			end = map[0].size();
		}
		std::cout<<"map[0].size() is "<<map[0].size()<<std::endl;
		std::cout<<"end is "<<end<<std::endl;
		bool nc = false; // non collision

		for (int i = 0; i < map.size(); i++)
		{
			for (int j = str; j < map      .size(); j++)
			{
				//std::cout<<"j is "<<j<<std::endl;
				if(map[i][j] == 0)
					continue;
				al_rect destrect =  { j * 50 - baseclass::coord.x,i * 50, 50, 50 };
	//			//for (int g = 0; g < bullets.size(); g++)
	//			//{
	//			//	if (collision(bullets[g]->getRect(), &destrect))
	//			//	{
	//			//		delete bullets[g];
	//			//		bullets.erase(bullets.begin() + g);
	//			//	}

				//}
			}
		}



		//collision detection end


		//for (int i = 0; i < bullets.size(); i++)
		//{
		//	if (bullets[i]->getRect()->x >=  screen->w ||
		//		bullets[i]->getRect()->x <= 0)
		//	{
		//		delete bullets[i];
		//		bullets.erase(bullets.begin() + i);
		//	}
		//}

		//for (int i = 0; i < bullets.size(); i++)
		//{
		//	for (int j = 0; j < enemies.size(); j++)
		//	{
		//		//relative coord to the screen
		//		SDL_Rect tmprect = {enemies[j]->getRect()->x - baseclass::coord.x,
		//			enemies[j]->getRect()->y, 50, 50};

		//		// if we collide bullet to the enemy it disappear
		//		if (collision(&tmprect, bullets[i]->getRect()))
		//		{
		//			delete enemies[j];
		//			delete bullets[i];
		//			enemies.erase(enemies.begin() + j);
		//			bullets.erase(bullets.begin() + i);
		//		}
		//	}
		//}




		//enemy colliding to the player
		//for (int j = 0; j < enemies.size(); j ++)
		//{
		//	//relative coord to the screen
		//	SDL_Rect tmprect = {enemies[j]->getRect()->x - baseclass::coord.x,
		//		enemies[j]->getRect()->y, 50, 50};

		//	// if we collide bullet to the enemy it disappear
		//	if (collision(&tmprect, player1->getRect()))
		//	{
		//		// if the bottom of player is greater or equal than the top of the enemy and if the player foot is over the enemy head (10 pixel down the enemy head)
		//		if (player1->getRect()->y + player1->getRect()->h >= enemies[j]->getRect()->y &&
		//			player1->getRect()->y + player1->getRect()->h <= enemies[j]->getRect()->y + 10 )
		//		{
		//			delete enemies[j];
		//			enemies.erase(enemies.begin()+j);
		//		}
		//		else
		//		{
		//			//colliding will decrese player's health
		//			player1->setHealth(player1->getHealth() - 1);
		//		}
		//	}
		//}

					


		

		player1->move(map);

		//for (int i = 0; i < bullets.size(); i++)
		//{
		//	bullets[i]->move();
		//}

		//for (int i = 0; i < enemies.size(); i++)
		//{
		//	enemies[i]->move(map);
		//}


		//SDL_BlitSurface(background,&camera,screen,NULL);
		//player1->show(screen);

		//for (int i = 0; i < bullets.size(); i++)
		//{
		//	bullets[i]->show(screen);
		//}
		//for (int i = 0; i < enemies.size(); i++)
		//{
		//	enemies[i]->show(screen);
		//}

		//drawing collision
		//if (bound)
		//{
		//		player1->FillRect(screen, player1->getRect()->x + 15, player1->getRect()->y, 20, player1->getRect()->h, 0xFF66CC);
		//}

		//al_flip_display();

		// if health is lower or euqal to zero or player has jumped into the cliff
	//	if (player1->getHealth() <= 0 ||
	//		player1->getRect()->y >= screen->h)
	//	{
	//		running = false;
	//		//std::cout<<"game over!" <<std::endl;
	//		showMessage("game over");
	//		SDL_Delay(1000);
	//	}

	//	SDL_Rect tmprect = {finish.x - coord.x, finish.y, 50, 50};
	//	if (collision(player1->getRect(), &tmprect))
	//	{
	//		running = false;
	//		showMessage("You Win");
	//		SDL_Delay(1000);
	//	}

	//	if (1000/30 > (SDL_GetTicks()- start)) //regulating the 30 fps
	//	{
	//		SDL_Delay(1000/30-(SDL_GetTicks() - start));
	//	}

		//==============================================
		//RENDER
		//==============================================
		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			al_draw_bitmap_region(background,camera.x,camera.y,camera.w,camera.h,0,0,0);
			showmap();
			player1->show(screen);
			al_draw_textf(font, al_map_rgb(255, 255, 0), 5, 5, 0, "FPS: %i", gameFPS); // display game FPS on screen


			//FLIP BUFFERS========================
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));

		}


	}
}