#pragma once

#include "Engine/Sound/Music.h"

class LittleFootsteps : public Music
{
public:
	static LittleFootsteps* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	LittleFootsteps(cocos2d::ValueMap& properties);
	virtual ~LittleFootsteps();

private:
	typedef Music super;
};
