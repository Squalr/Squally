#pragma once

#include "Engine/Sound/Music.h"

class Artrium : public Music
{
public:
	static Artrium* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	Artrium(cocos2d::ValueMap& properties);
	virtual ~Artrium();

private:
	typedef Music super;
};
