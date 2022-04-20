#pragma once

#include "Engine/Sound/SoundBase.h"

class LocalizedString;

class Music : public SoundBase
{
public:
	Music* clone();
	
	void unfreeze() override;
	void pushTrack(float delay = 0.5f);
	void popTrack();

	LocalizedString* cloneMusicName() const { return musicName != nullptr ? musicName->clone() : nullptr; }
	LocalizedString* cloneArtistName() const { return artistName != nullptr ? artistName->clone() : nullptr; }

protected:
	Music(std::string musicResource, LocalizedString* musicName, LocalizedString* artistName, bool initializeSoundBuffers = false);
	virtual ~Music();
	
	void initializeListeners() override;
	void pause() override;
	void play(bool repeat = true, float startDelay = 0.0f) override;
	float getConfigVolume() override;

private:
	typedef SoundBase super;
	friend class MusicPlayer;

	LocalizedString* musicName = nullptr;
	LocalizedString* artistName = nullptr;
};
