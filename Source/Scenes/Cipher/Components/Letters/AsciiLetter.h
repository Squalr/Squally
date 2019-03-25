#pragma once
#include "cocos/2d/CCSprite.h"
#include "cocos/base/ccTypes.h"

class AsciiLetter : public cocos2d::Sprite
{
public:
	static AsciiLetter* create();

	static const int LetterSize;

private:
	typedef cocos2d::Sprite super;
	AsciiLetter();
	~AsciiLetter();

	void loadLetter(unsigned char letter);
};
