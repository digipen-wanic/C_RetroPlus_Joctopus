#include "stdafx.h"

#include <fmod_errors.h>
#include "SoundManager.h"
#include "Engine.h"


void FMOD_Assert(FMOD_RESULT result) 
{
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
	}
}

SoundManager::SoundManager()
	: BetaObject("SoundManager"), numSounds(0), numBanks(0), musicVolume(1.0f), effectsVolume(1.0f), audioFilePath("Audio/"), bankFilePath("Banks/"), eventPrefix("event:/")
{

	FMOD_Assert(FMOD::Studio::System::create(&studioSystem));

	FMOD_Assert(studioSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));

	FMOD_Assert(studioSystem->getLowLevelSystem(&system));

	FMOD_Assert(system->createChannelGroup("SoundEffects", &effectsChannelGroup));
}

SoundManager::~SoundManager()
{
	FMOD_Assert(studioSystem->release());
}


void SoundManager::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	FMOD_Assert(studioSystem->update());
}

void SoundManager::Shutdown()
{
	for (unsigned i = 0; i < numSounds; i++)
	{
		FMOD_Assert(soundList[i]->release());
	}

	for (unsigned i = 0; i < numBanks; i++)
	{
		FMOD_Assert(bankList[i]->unload());
	}

	numSounds = 0;
	numBanks = 0;
}

void SoundManager::AddEffect(const std::string& filename)
{
	AddSound(filename, FMOD_DEFAULT);
}

void SoundManager::AddMusic(const std::string& filename)
{
	AddSound(filename, FMOD_DEFAULT | FMOD_LOOP_NORMAL);
}

void SoundManager::AddBank(const std::string& filename)
{
	if (numBanks < maxNumBanks)
	{
		std::string fullFilename = Engine::GetInstance().GetFilePath() + audioFilePath + bankFilePath + filename;

		FMOD::Studio::Bank* bank;

		FMOD_Assert(studioSystem->loadBankFile(fullFilename.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank));

		bankList[numBanks] = bank;
		numBanks++;
	}

}

FMOD::Channel* SoundManager::PlaySound(const std::string& soundName)
{
	FMOD_MODE mode;
	char cstring[100];

	for (unsigned i = 0; i < numSounds; i++)
	{
		FMOD_Assert(soundList[i]->getName(cstring, 100));
		std::string currName(cstring);

		if (currName == soundName)
		{
			FMOD_Assert(soundList[i]->getMode(&mode));

			if (mode & FMOD_CREATESTREAM)
			{
				return PlayMusic(soundList[i]);
			}
			else
			{
				return PlayEffect(soundList[i]);
			}

		}
	}

	return nullptr;

}

FMOD::Studio::EventInstance* SoundManager::PlayEvent(const std::string& eventName)
{
	std::string fullName = eventPrefix + eventName;
	FMOD::Studio::EventDescription* description;
	FMOD::Studio::EventInstance* instance;

	FMOD_Assert(studioSystem->getEvent(fullName.c_str(), &description));
	FMOD_Assert(description->createInstance(&instance));
	return instance;

}

void SoundManager::SetMusicVolume(float volume)
{
	musicVolume = volume;
	if (musicChannel != nullptr)
	{
		FMOD_Assert(musicChannel->setVolume(musicVolume));
	}
}

void SoundManager::SetEffectsVolume(float volume)
{
	effectsVolume = volume;
	FMOD_Assert(effectsChannelGroup->setVolume(effectsVolume));
}

float SoundManager::GetMusicVolume() const
{
	return musicVolume;
}

float SoundManager::GetEffectsVolume() const
{
	return effectsVolume;
}

FMOD::Channel* SoundManager::PlayEffect(FMOD::Sound* sound) const
{
	FMOD::Channel* channel;
	FMOD_Assert(system->playSound(sound, effectsChannelGroup, false, &channel));
	return channel;
}

FMOD::Channel* SoundManager::PlayMusic(FMOD::Sound* sound)
{
	if (musicChannel != nullptr)
	{
		FMOD_Assert(musicChannel->stop());
	}
		FMOD_Assert(system->playSound(sound, nullptr, false, &musicChannel));
		return musicChannel;
}

void SoundManager::AddSound(const std::string& filename, FMOD_MODE mode)
{
	if (numSounds < maxNumSounds)
	{
		std::string path = "Assets/" + audioFilePath + filename;
		FMOD::Sound* sound;

		FMOD_Assert(system->createSound(path.c_str(), mode, 0, &sound));

		soundList[numSounds] = sound;
		numSounds++;
	}

}


