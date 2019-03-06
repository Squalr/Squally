#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class Animal : public HackableObject
{
public:

protected:
	typedef HackableObject super;
	Animal(cocos2d::ValueMap& initProperties);
	virtual ~Animal();

	cocos2d::Vec2 getButtonOffset() override;
	void update(float) override;

	cocos2d::Sprite* cage;
	cocos2d::Node* spriteNode;
};
