#include "MatrixStrand.h"

MatrixStrand* MatrixStrand::create()
{
	MatrixStrand* matrixStrand = new MatrixStrand();

	matrixStrand->autorelease();

	return matrixStrand;
}

MatrixStrand::MatrixStrand()
{
	this->updateAction = nullptr;
	this->letters = new std::vector<MatrixLetter*>();

	for (int index = 0; index < MatrixStrand::maxLetterCount; index++)
	{
		MatrixLetter* letter = MatrixLetter::create();

		letter->setPositionY((float)index * -16.0f);

		letters->push_back(letter);
		this->addChild(letter);
	}

	this->beginStrand();
}

MatrixStrand::~MatrixStrand()
{
	delete(this->letters);
}

void MatrixStrand::nextStrandAction()
{
	if (this->currentLetterIndex < MatrixStrand::letterCount)
	{
		MatrixLetter* letter = this->letters->at(this->currentLetterIndex);

		letter->spawn();

		this->currentLetterIndex++;
	}
	else
	{
		this->endStrand();
	}
}

void MatrixStrand::beginStrand()
{
	// Stop update callback
	if (this->updateAction != nullptr)
	{
		this->stopAction(this->updateAction);
	}

	// Initialize state
	this->randomizePosition();
	this->setLetterCount();

	this->currentLetterIndex = 0;

	// Set update callback
	CallFunc* onUpdate = CallFunc::create(CC_CALLBACK_0(MatrixStrand::nextStrandAction, this));
	this->updateAction = RepeatForever::create(Sequence::create(onUpdate, DelayTime::create(this->getUpdateSpeed()), nullptr));
	this->runAction(this->updateAction);
}

void MatrixStrand::endStrand()
{
	// Stop update callback
	if (this->updateAction != nullptr)
	{
		this->stopAction(this->updateAction);
	}

	float despawnTime = RandomHelper::random_real(5.0f, 8.0f);

	for (int index = 0; index < this->letterCount; index++)
	{
		MatrixLetter* letter = this->letters->at(index);

		letter->despawn(despawnTime);
	}

	this->runAction(Sequence::create(DelayTime::create(despawnTime + 0.5f), CallFunc::create(CC_CALLBACK_0(MatrixStrand::beginStrand, this)), nullptr));
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

float MatrixStrand::getUpdateSpeed()
{
	return RandomHelper::random_real(0.05f, 0.25f);
}
