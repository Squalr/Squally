#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class ConstantString;
class LocalizedLabel;

class MayanRuneBase : public HackableObject
{
public:
	void loadAnswer(int answer);
	void runFX();
	void hideText();
	void showText();
	void enableGem();
	void disableGem();

protected:
	MayanRuneBase(std::string emblemResource, std::string emblemResourceDisabled);
	virtual ~MayanRuneBase();

	void onEnter() override;
	void initializePositions() override;

	virtual cocos2d::Color4B getGemFontColor() = 0;

private:
	typedef HackableObject super;
	
	cocos2d::Sprite* emblemFrame;
	cocos2d::Sprite* emblemFrameGlowing;
	cocos2d::Sprite* emblemDisabled;
	cocos2d::Sprite* emblem;
	ConstantString* answerString;
	LocalizedLabel* answerLabel;
};
