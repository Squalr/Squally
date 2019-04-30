#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class RegisterCrystal : public HackableObject
{
public:
	int getValue();
	int getOffset();

	static const std::string MapKeyRegisterOffset;
	static const std::string MapKeyRegisterValue;

protected:
	RegisterCrystal(cocos2d::ValueMap& initProperties);
	~RegisterCrystal();

	void onEnter() override;
	void initializePositions() override;

	cocos2d::Node* crystalNode;

private:
	typedef HackableObject super;

	int value;
	int offset;

	cocos2d::Sprite* shadow;
};
