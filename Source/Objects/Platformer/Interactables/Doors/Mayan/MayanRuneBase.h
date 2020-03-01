#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class MayanRuneBase : public GameObject
{
public:
	void runFX();
	void enableGem();
	void disableGem();

protected:
	MayanRuneBase(std::string emblemResource, std::string emblemResourceDisabled);
	virtual ~MayanRuneBase();

private:
	typedef GameObject super;

	cocos2d::Sprite* emblemFrame;
	cocos2d::Sprite* emblemDisabled;
	cocos2d::Sprite* emblem;
};
