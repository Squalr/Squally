#pragma once

#include "Engine/Sound/Music.h"

class Medieval2 : public Music
{
public:
	static Medieval2* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	Medieval2(cocos2d::ValueMap& properties);
	virtual ~Medieval2();

private:
	typedef Music super;
};
