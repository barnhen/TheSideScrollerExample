#pragma once
#include <allegro5\allegro.h>
class FPS
{ 
protected:
	int frames[256];
	int samples;
	int curSample;
public:
	FPS(void);
	void Init(int fps);
	void Update(int f);
	int Get();
	void Draw(ALLEGRO_BITMAP *buffer);
	~FPS(void);
};

