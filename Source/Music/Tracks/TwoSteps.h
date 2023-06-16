#pragma once

#include "Engine/Sound/Music.h"

class TwoSteps : public Music
{
public:
	static TwoSteps* create(cocos2d::ValueMap& properties);

	static const std::string TrackKey;

protected:
	TwoSteps(cocos2d::ValueMap& properties);
	virtual ~TwoSteps();

private:
	typedef Music super;
};
