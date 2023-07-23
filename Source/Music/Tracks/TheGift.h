#pragma once

#include "Engine/Sound/Music.h"

class TheGift : public Music
{
public:
	static TheGift* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	TheGift(cocos2d::ValueMap& properties);
	virtual ~TheGift();

private:
	typedef Music super;
};
