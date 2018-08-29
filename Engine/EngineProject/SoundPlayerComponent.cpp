#include "SoundPlayerComponent.h"


#include <irrKlang.h>

using namespace irrklang;




ISoundEngine* SoundPlayerComponent::soundDevice;


SoundPlayerComponent::SoundPlayerComponent()
{
	// start the sound engine with default parameters

	soundDevice = createIrrKlangDevice();

	/* uncomment for start sound */
	//ISound* sound = soundDevice->play2D("media/Runescape.mp3", true, false, true);
	//sound->setVolume(0.40);
	
}



SoundPlayerComponent::~SoundPlayerComponent()
{
}
