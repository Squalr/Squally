#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class HexusArcade : public HackableObject
{
public:
	static HexusArcade* create(cocos2d::ValueMap& initProperties);

protected:
	HexusArcade(cocos2d::ValueMap& initProperties);
	~HexusArcade();

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef HackableObject super;

	cocos2d::Sprite* arcadeMachine;
};
