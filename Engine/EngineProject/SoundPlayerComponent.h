#pragma once
#include <ik_ISoundEngine.h>

#define WALKING 0
#define HIT 1

class SoundPlayerComponent
{
public:
	static irrklang::ISoundEngine* soundDevice;
	
	SoundPlayerComponent();
	~SoundPlayerComponent();
};

