#include "FPS.hpp"


FPS::FPS(void):samples(0), curSample(0) 
{
}

void FPS::Init(int fps) 
{
	samples = fps;

	for (int i=0; i<samples; i++) 
	{
		frames[i] = 0;
	}
		curSample = 0;
}


void FPS::Update(int f) 
{
	frames[curSample] = f;
	++curSample;
	curSample %= samples;
}

int FPS::Get() 
{
	int ret = 0;
	for (int i=0; i<samples; ++i) 
	{
		ret += frames[i];
	}
		return ret;
}

FPS::~FPS(void)
{
}
