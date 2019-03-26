#pragma once
#include "cocos/2d/CCSprite.h"
#include "cocos/base/ccTypes.h"

class AsciiLetter : public cocos2d::Sprite
{
public:
	static AsciiLetter* create(unsigned char letter);

	static const int LetterSize;
	static const int GridWidth;
	static const int GridHeight;

private:
	typedef cocos2d::Sprite super;
	AsciiLetter(unsigned char letter);
	~AsciiLetter();

	void loadLetter(unsigned char letter);
};
