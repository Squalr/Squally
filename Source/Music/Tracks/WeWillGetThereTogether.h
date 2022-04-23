#pragma once

#include "Engine/Sound/Music.h"

class WeWillGetThereTogether : public Music
{
public:
	static WeWillGetThereTogether* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	WeWillGetThereTogether(cocos2d::ValueMap& properties);
	virtual ~WeWillGetThereTogether();

private:
	typedef Music super;
};
