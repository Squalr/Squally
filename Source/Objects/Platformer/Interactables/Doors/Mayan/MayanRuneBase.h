#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class ConstantString;
class LocalizedLabel;

class MayanRuneBase : public GameObject
{
public:
	void loadAnswer(int answer);
	void runFX();
	void enableGem();
	void disableGem();

protected:
	MayanRuneBase(std::string emblemResource, std::string emblemResourceDisabled);
	virtual ~MayanRuneBase();

	void onEnter() override;
	void initializePositions() override;

	virtual cocos2d::Color4B getGemFontColor() = 0;

private:
	typedef GameObject super;
	
	cocos2d::Sprite* emblemFrame;
	cocos2d::Sprite* emblemFrameGlowing;
	cocos2d::Sprite* emblemDisabled;
	cocos2d::Sprite* emblem;
	ConstantString* answerString;
	LocalizedLabel* answerLabel;
};
