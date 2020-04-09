#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;
class Music;

// Wrapper object for music, as music objects behave a little irregularly due to their global nature.
class Track : public SmartNode
{
public:
	virtual void push(float delay = 0.0f);
	virtual void play(float delay = 0.0f);
	virtual void pop();

	LocalizedString* getTrackName();
	LocalizedString* getArtistName();
	std::string getTrackResource();

protected:
	Track(std::string musicResource, LocalizedString* trackName, LocalizedString* artistName);
	virtual ~Track();

	void initializeListeners() override;

private:
	typedef SmartNode super;

	Music* music;
	LocalizedString* trackName;
	LocalizedString* artistName;
};
