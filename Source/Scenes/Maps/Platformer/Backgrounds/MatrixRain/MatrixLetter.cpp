#include "MatrixLetter.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/FontResources.h"

using namespace cocos2d;

const Color3B MatrixLetter::letterColor = Color3B(25, 242, 51);
const Color3B MatrixLetter::spawnColor = Color3B::WHITE;
const Color4B MatrixLetter::glowColor = Color4B::RED;// Color4B(25, 242, 51, 0xFF);

const int MatrixLetter::letterSize = 48;

const float MatrixLetter::spawnChangeRate = 0.1f;
const float MatrixLetter::spawnTime = 0.5f;
const float MatrixLetter::fadeOutPercentage = 25.0f;
const float MatrixLetter::letterChangePercentage = 25.0f;

MatrixLetter* MatrixLetter::create()
{
	MatrixLetter* matrixLetter = new MatrixLetter();

	matrixLetter->autorelease();

	return matrixLetter;
}

MatrixLetter::MatrixLetter()
{
	this->initWithFile(FontResources::AlienText);

	this->randomizeLetter();

	this->setOpacity(0);
}

MatrixLetter::~MatrixLetter()
{
}

void MatrixLetter::pause()
{
	// Ignore pause
}

void MatrixLetter::spawn()
{
	this->stopAllActions();

	this->setColor(MatrixLetter::spawnColor);

	// Restore color action
	this->runAction(TintTo::create(MatrixLetter::spawnTime, MatrixLetter::letterColor));

	FiniteTimeAction* fadeIn = FadeIn::create(0.1f);

	// Some letters fade in and then out over time
	if (RandomHelper::random_real(0.0f, 100.0f) < fadeOutPercentage)
	{
		FiniteTimeAction* fadeOut = FadeOut::create(RandomHelper::random_real(1.0f, 5.0f));

		this->runAction(Sequence::create(fadeIn, fadeOut, nullptr));
	}
	else
	{
		// Remaining letters simply fade in normally
		this->runAction(fadeIn);
	}

	// While the letter is fading in, constantly change the letter

	auto randomizeLetterFunc = CC_CALLBACK_0(MatrixLetter::randomizeLetter, this);
	int repeatCount = (int)(MatrixLetter::spawnTime / MatrixLetter::spawnChangeRate) / 2;

	FiniteTimeAction* letterChangeSpawn = Repeat::create(Sequence::create(CallFunc::create([randomizeLetterFunc]()
	{
		randomizeLetterFunc();

	}), DelayTime::create(MatrixLetter::spawnChangeRate), nullptr), repeatCount);

	// Some letters do the normal spawn effect, and continue to have their letters change at a different rate
	if (RandomHelper::random_real(0.0f, 100.0f) < letterChangePercentage)
	{
		float changeRate = RandomHelper::random_real(0.1f, 1.0f);

		this->runAction(RepeatForever::create(Sequence::create(DelayTime::create(changeRate), CallFunc::create([randomizeLetterFunc]()
		{
			randomizeLetterFunc();

		}), nullptr)));
	}
	else
	{
		// Run the normal letter change effect
		this->runAction(letterChangeSpawn);
	}
}

void MatrixLetter::despawn()
{
	this->stopAllActions();
	this->setOpacity(0);
}

void MatrixLetter::randomizeLetter()
{
	Size spriteSheetSize = this->getTexture()->getContentSize();

	int x = RandomHelper::random_int(0, (int)(spriteSheetSize.width / MatrixLetter::letterSize) - 1) *  MatrixLetter::letterSize;
	int y = RandomHelper::random_int(0, (int)(spriteSheetSize.height / MatrixLetter::letterSize) - 1) *  MatrixLetter::letterSize;

	this->setTextureRect(Rect(x, y, MatrixLetter::letterSize, MatrixLetter::letterSize));
}
