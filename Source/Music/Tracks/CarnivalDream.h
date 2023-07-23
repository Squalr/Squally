#pragma once

#include "Engine/Sound/Music.h"

class CarnivalDream : public Music
{
public:
	static CarnivalDream* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	CarnivalDream(cocos2d::ValueMap& properties);
	virtual ~CarnivalDream();

private:
	typedef Music super;
};
