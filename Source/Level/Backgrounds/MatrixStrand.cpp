#include "MatrixStrand.h"

MatrixStrand* MatrixStrand::create()
{
	MatrixStrand* matrixStrand = new MatrixStrand();

	matrixStrand->autorelease();

	return matrixStrand;
}

MatrixStrand::MatrixStrand()
{
	this->randomizePosition();

	this->letters = new std::vector<Label*>();

	for (int index = 0; index < MatrixStrand::maxLetterCount; index++)
	{
		Label* letter = Label::create(this->generateLetter(), Resources::Fonts_Alien_li, 24);

		letter->setTextColor(Color4B(25, 242, 51, 255));
		letter->setPositionY((float)index * -28.0f);

		letters->push_back(letter);
		this->addChild(letter);
	}

	this->scheduleUpdate();
}

MatrixStrand::~MatrixStrand()
{
}

void MatrixStrand::update(float dt)
{

}

void MatrixStrand::setLetterCount()
{
	this->letterCount = RandomHelper::random_int(MatrixStrand::minLetterCount, MatrixStrand::maxLetterCount);
}

void MatrixStrand::randomizePosition()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float overFlowX = 32.0f;
	const float overFlowY = 128.0f;

	Vec2 position;
	position.x = RandomHelper::random_real(-overFlowX, visibleSize.width + overFlowX);
	position.y = RandomHelper::random_real(visibleSize.height * 3 / 4, visibleSize.height + overFlowY);

	this->setPosition(position);

}

std::string MatrixStrand::generateLetter()
{
	int min = (int)'a';
	int max = (int)'z';

	char letter = (char)RandomHelper::random_int(min, max);

	std::string letterString(&letter, 1);

	return letterString;
}
