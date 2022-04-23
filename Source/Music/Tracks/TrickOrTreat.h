#pragma once

#include "Engine/Sound/Music.h"

class TrickOrTreat : public Music
{
public:
	static TrickOrTreat* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	TrickOrTreat(cocos2d::ValueMap& properties);
	virtual ~TrickOrTreat();

private:
	typedef Music super;
};
