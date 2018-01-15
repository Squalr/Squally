#include "MatrixStrand.h"

const int MatrixStrand::minLetterCount = 64;
const int MatrixStrand::maxLetterCount = 80;
const float MatrixStrand::movementSpeed = 128.0f;
const float MatrixStrand::strandScale = 0.4f;
const float MatrixStrand::minSpawnSpeed = 0.01f;
const float MatrixStrand::maxSpawnSpeed = 0.25f;
const float MatrixStrand::minSpawnDistance = -256.0f;
const float MatrixStrand::maxSpawnDistance = -512.0f; // -512.0f seems to be the max supported camera distance

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

		letter->setPositionY((float)index * -(MatrixLetter::letterSize - 12));

		letters->push_back(letter);
		this->addChild(letter);
	}

	this->setCascadeOpacityEnabled(true);
	this->setScale(MatrixStrand::strandScale);

	// Delayed start to prevent all strands from being created at the same time
	MatrixStrand* matrixStrand = this;
	this->runAction(Sequence::create(DelayTime::create(RandomHelper::random_real(0.0f, 8.0f)), CallFunc::create([matrixStrand]()
	{
		matrixStrand->beginStrand();
		matrixStrand->scheduleUpdate();
	}), nullptr));
}

MatrixStrand::~MatrixStrand()
{
	delete(this->letters);
}

void MatrixStrand::update(float dt)
{
	this->setPositionZ(this->getPositionZ() + dt * movementSpeed);

	if (this->getPositionZ() < 0.0f)
	{
		this->setOpacity(255 * (1.0f - (this->getPositionZ() / MatrixStrand::maxSpawnDistance)));
	}
	else
	{
		this->setOpacity(255);
	}
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

	float despawnTime = RandomHelper::random_real(2.0f, 6.0f);

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

	const float overFlowX = 256.0f;
	const float overFlowY = 312.0f;

	Vec3 position;
	position.x = RandomHelper::random_real(-overFlowX, visibleSize.width + overFlowX);
	position.y = RandomHelper::random_real(visibleSize.height * (0.80f), visibleSize.height + overFlowY);
	position.z = RandomHelper::random_real(MatrixStrand::maxSpawnDistance, MatrixStrand::minSpawnDistance);

	this->setPosition3D(position);
}

float MatrixStrand::getUpdateSpeed()
{
	return RandomHelper::random_real(MatrixStrand::minSpawnSpeed, MatrixStrand::maxSpawnSpeed);
}
