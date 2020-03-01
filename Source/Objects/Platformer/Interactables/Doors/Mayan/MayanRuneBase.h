#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class MayanRuneBase : public HackableObject
{
public:
	virtual int runGem(int currentIndex) = 0;
	void runFX();
	void enableGem();
	void disableGem();

protected:
	MayanRuneBase(std::string emblemResource, std::string emblemResourceDisabled);
	virtual ~MayanRuneBase();

private:
	typedef HackableObject super;

	cocos2d::Sprite* emblemFrame;
	cocos2d::Sprite* emblemDisabled;
	cocos2d::Sprite* emblem;
};
