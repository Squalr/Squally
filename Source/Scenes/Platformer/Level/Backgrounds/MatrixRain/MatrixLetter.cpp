#include "MatrixLetter.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/FontResources.h"

using namespace cocos2d;

const Color3B MatrixLetter::LetterColor = Color3B(25, 242, 51);
const Color3B MatrixLetter::SpawnColor = Color3B::WHITE;
const Color4B MatrixLetter::GlowColor = Color4B::RED;// Color4B(25, 242, 51, 0xFF);

const int MatrixLetter::LetterSize = 48;

const float MatrixLetter::SpawnChangeRate = 0.1f;
const float MatrixLetter::SpawnTime = 0.5f;
const float MatrixLetter::FadeOutPercentage = 25.0f;
const float MatrixLetter::LetterChangePercentage = 25.0f;

MatrixLetter* MatrixLetter::create()
{
	MatrixLetter* instance = new MatrixLetter();

	instance->autorelease();

	return instance;
}

MatrixLetter::MatrixLetter()
{
	this->initWithFile(FontResources::Texture_AlienText);

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

void MatrixLetter::spawnImmediate()
{
	this->stopAllActions();
	this->setColor(MatrixLetter::LetterColor);
	this->setOpacity(255);
}

void MatrixLetter::spawn()
{
	this->stopAllActions();

	this->setColor(MatrixLetter::SpawnColor);

	// Restore color action
	this->runAction(TintTo::create(MatrixLetter::SpawnTime, MatrixLetter::LetterColor));

	FiniteTimeAction* fadeIn = FadeIn::create(0.1f);

	// Some letters fade in and then out over time
	if (RandomHelper::random_real(0.0f, 100.0f) < FadeOutPercentage)
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
	int repeatCount = (int)(MatrixLetter::SpawnTime / MatrixLetter::SpawnChangeRate) / 2;

	// Some letters do the normal spawn effect, and continue to have their letters change at a different rate
	if (RandomHelper::random_real(0.0f, 100.0f) < LetterChangePercentage)
	{
		float changeRate = RandomHelper::random_real(0.1f, 1.0f);

		this->runAction(RepeatForever::create(
			Sequence::create(
				DelayTime::create(changeRate),
				CallFunc::create([=]()
				{
					this->randomizeLetter();
				}),
				nullptr
			))
		);
	}
	else
	{
		// Run the normal letter change effect
		this->runAction(Repeat::create(
			Sequence::create(
				CallFunc::create([=]()
				{
					this->randomizeLetter();
				}),
				DelayTime::create(MatrixLetter::SpawnChangeRate),
				nullptr
			), repeatCount)
		);
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

	float x = float(RandomHelper::random_int(0, (int)(spriteSheetSize.width / MatrixLetter::LetterSize) - 1) *  MatrixLetter::LetterSize);
	float y = float(RandomHelper::random_int(0, (int)(spriteSheetSize.height / MatrixLetter::LetterSize) - 1) *  MatrixLetter::LetterSize);

	this->setTextureRect(Rect(x, y, MatrixLetter::LetterSize, MatrixLetter::LetterSize));
}
