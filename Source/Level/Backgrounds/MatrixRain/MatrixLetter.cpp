#include "MatrixLetter.h"

const Color3B MatrixLetter::letterColor = Color3B(25, 242, 51);
const Color3B MatrixLetter::spawnColor = Color3B::WHITE;


const float MatrixLetter::spawnChangeRate = 0.1f;
const float MatrixLetter::spawnTime = 0.5f;
const float MatrixLetter::fadeOutPercentage = 25.0f;
const float MatrixLetter::letterChangePercentage = 5.0f;

MatrixLetter* MatrixLetter::create()
{
	MatrixLetter* matrixLetter = new MatrixLetter();

	matrixLetter->autorelease();

	return matrixLetter;
}

MatrixLetter::MatrixLetter()
{
	this->letter = Label::create(this->generateLetter(), Resources::Fonts_Alien_li, 24);

	this->letter->setTextColor(Color4B(0xFF, 0xFF, 0xFF, 0xFF));
	this->letter->setOpacity(0);

	this->addChild(this->letter);
}

MatrixLetter::~MatrixLetter()
{
}

void MatrixLetter::spawn()
{
	this->letter->stopAllActions();

	this->letter->setColor(MatrixLetter::spawnColor);

	// Restore color action
	this->letter->runAction(TintTo::create(MatrixLetter::spawnTime, MatrixLetter::letterColor));

	FiniteTimeAction* fadeIn = FadeIn::create(0.1f);

	// Some letters fade in and then out over time
	if (RandomHelper::random_real(0.0f, 100.0f) < fadeOutPercentage)
	{
		FiniteTimeAction* fadeOut = FadeOut::create(RandomHelper::random_real(1.0f, 5.0f));

		this->letter->runAction(Sequence::create(fadeIn, fadeOut, nullptr));
	}
	else
	{
		// Remaining letters simply fade in normally
		this->letter->runAction(fadeIn);
	}

	// While the letter is fading in, constantly change the letter
	Label* letterLabel = this->letter;
	auto newLetterFunc = CC_CALLBACK_0(MatrixLetter::generateLetter, this);
	int repeatCount = (int)(MatrixLetter::spawnTime / MatrixLetter::spawnChangeRate) / 2;

	FiniteTimeAction* letterChangeSpawn = Repeat::create(Sequence::create(CallFunc::create([letterLabel, newLetterFunc]()
	{
		letterLabel->setString(newLetterFunc());

	}), DelayTime::create(MatrixLetter::spawnChangeRate), nullptr), repeatCount);

	// Some letters do the normal spawn effect, and continue to have their letters change at a different rate
	if (RandomHelper::random_real(0.0f, 100.0f) < letterChangePercentage)
	{
		float changeRate = RandomHelper::random_real(0.1f, 1.0f);

		return;
		this->letter->runAction(Sequence::create(letterChangeSpawn, RepeatForever::create(Sequence::create(DelayTime::create(changeRate), CallFunc::create([letterLabel, newLetterFunc]()
		{
			letterLabel->setString(newLetterFunc());

		}), nullptr)), nullptr));
	}
	else
	{
		// Run the normal letter change effect
		this->letter->runAction(letterChangeSpawn);
	}
}

void MatrixLetter::despawn(float despawnTime)
{
	this->letter->runAction(FadeOut::create(despawnTime));
}

std::string MatrixLetter::generateLetter()
{
	int min = (int)'a';
	int max = (int)'z';

	char letter = (char)RandomHelper::random_int(min, max);

	std::string letterString(&letter, 1);

	return letterString;
}
