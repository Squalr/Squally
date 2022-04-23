#pragma once

#include "Engine/Sound/Music.h"

class Medieval : public Music
{
public:
	static Medieval* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	Medieval(cocos2d::ValueMap& properties);
	virtual ~Medieval();

private:
	typedef Music super;
};
