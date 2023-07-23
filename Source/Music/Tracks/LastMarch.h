#pragma once

#include "Engine/Sound/Music.h"

class LastMarch : public Music
{
public:
	static LastMarch* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	LastMarch(cocos2d::ValueMap& properties);
	virtual ~LastMarch();

private:
	typedef Music super;
};
