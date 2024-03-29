#include "AsciiLetter.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/FontResources.h"

using namespace cocos2d;

const int AsciiLetter::LetterSize = 48;
const int AsciiLetter::GridWidth = 16;
const int AsciiLetter::GridHeight = 16;

AsciiLetter* AsciiLetter::create()
{
	return AsciiLetter::create((unsigned char)(0));
}

AsciiLetter* AsciiLetter::create(unsigned char letter)
{
	AsciiLetter* instance = new AsciiLetter(letter);

	instance->autorelease();

	return instance;
}

AsciiLetter::AsciiLetter(unsigned char letter)
{
	this->initWithFile(FontResources::Texture_AsciiTable);

	this->loadLetter(letter);
}

AsciiLetter::~AsciiLetter()
{
}

void AsciiLetter::loadLetter(unsigned char letter)
{
	Texture2D* texture = this->getTexture();

	if (texture == nullptr)
	{
		return;
	}

	CSize spriteSheetSize = texture->getContentSize();

	float x = float((letter % AsciiLetter::GridWidth) * AsciiLetter::LetterSize);
	float y = float((letter / AsciiLetter::GridHeight) * AsciiLetter::LetterSize);

	this->setTextureRect(CRect(x, y, AsciiLetter::LetterSize, AsciiLetter::LetterSize));
}
