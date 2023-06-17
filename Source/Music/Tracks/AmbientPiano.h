#pragma once

#include "Engine/Sound/Music.h"

class AmbientPiano : public Music
{
public:
	static AmbientPiano* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	AmbientPiano(cocos2d::ValueMap& properties);
	virtual ~AmbientPiano();

private:
	typedef Music super;
};
