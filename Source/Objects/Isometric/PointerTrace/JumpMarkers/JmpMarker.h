#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class JmpMarker : public HackableObject
{
protected:
	JmpMarker(cocos2d::ValueMap& initProperties);
	~JmpMarker();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackableObject super;
};
