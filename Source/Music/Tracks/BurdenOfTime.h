#pragma once

#include "Engine/Sound/Music.h"

class BurdenOfTime : public Music
{
public:
	static BurdenOfTime* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	BurdenOfTime(cocos2d::ValueMap& properties);
	virtual ~BurdenOfTime();

private:
	typedef Music super;
};
