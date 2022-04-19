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

	LocalizedString* getMusicName() const { return musicName; }
	LocalizedString* getArtistName() const { return artistName; }

protected:
	Music(std::string musicResource, LocalizedString* musicName, LocalizedString* artistName);
	virtual ~Music();
	
	void initializeListeners() override;
	void pause() override;
	void play(bool repeat = true, float startDelay = 0.0f) override;
	float getConfigVolume() override;
	void orphanMusic();
	bool isOrphaned();

private:
	typedef SoundBase super;
	friend class MusicPlayer;

	void cancelIfDelayed();

	bool orphaned = false;
	LocalizedString* musicName = nullptr;
	LocalizedString* artistName = nullptr;
};
