#pragma once

#include "Engine/Sound/Music.h"

class TheLetter : public Music
{
public:
	static TheLetter* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	TheLetter(cocos2d::ValueMap& properties);
	virtual ~TheLetter();

private:
	typedef Music super;
};
