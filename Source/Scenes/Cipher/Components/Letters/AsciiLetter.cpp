#include "AsciiLetter.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/FontResources.h"

using namespace cocos2d;

const int AsciiLetter::LetterSize = 32;

AsciiLetter* AsciiLetter::create()
{
	AsciiLetter* matrixLetter = new AsciiLetter();

	matrixLetter->autorelease();

	return matrixLetter;
}

AsciiLetter::AsciiLetter()
{
	this->initWithFile(FontResources::Texture_AsciiTable);

	this->loadLetter((unsigned char)(0));

	this->setOpacity(0);
}

AsciiLetter::~AsciiLetter()
{
}

void AsciiLetter::loadLetter(unsigned char letter)
{
	Size spriteSheetSize = this->getTexture()->getContentSize();

	float x = float(letter % 16 * AsciiLetter::LetterSize);
	float y = float(letter / 16* AsciiLetter::LetterSize);

	this->setTextureRect(Rect(x, y, AsciiLetter::LetterSize, AsciiLetter::LetterSize));
}
