#pragma once

#include "Engine/Sound/Music.h"

class Lacrimosa : public Music
{
public:
	static Lacrimosa* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	Lacrimosa(cocos2d::ValueMap& properties);
	virtual ~Lacrimosa();

private:
	typedef Music super;
};
