#include "MatrixStrand.h"

const int MatrixStrand::minLetterCount = 24;
const int MatrixStrand::maxLetterCount = 80;
const float MatrixStrand::movementSpeed = 128.0f;
const float MatrixStrand::strandScale = 0.35f;
const float MatrixStrand::minSpawnSpeed = 0.02f;
const float MatrixStrand::maxSpawnSpeed = 0.20f;
const float MatrixStrand::overFlowX = 196.0f;
const float MatrixStrand::overFlowY = 256.0f;
const float MatrixStrand::underFlowY = 256.0f;
const float MatrixStrand::minSpawnDistance = -256.0f;
const float MatrixStrand::maxSpawnDistance = -512.0f; // -512.0f seems to be the max supported camera distance

MatrixStrand* MatrixStrand::create(int strandIndex)
{
	MatrixStrand* matrixStrand = new MatrixStrand(strandIndex);

	matrixStrand->autorelease();

	return matrixStrand;
}

MatrixStrand::MatrixStrand(int strandIndex)
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
	this->runAction(Sequence::create(DelayTime::create((float)strandIndex * 0.15f), CallFunc::create([matrixStrand]()
	{
		matrixStrand->beginStrand();
		matrixStrand->scheduleUpdate();
	}), nullptr));
}

MatrixStrand::~MatrixStrand()
{
	delete(this->letters);
}

void MatrixStrand::pause()
{
	// Ignore pause
}

void MatrixStrand::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Camera movement effect
	this->setPositionY(this->getPositionY() - dt * movementSpeed / 4.0f);
	this->setPositionZ(this->getPositionZ() + dt * movementSpeed);

	Vec2 realPosition = Director::getInstance()->getRunningScene()->getDefaultCamera()->projectGL(this->getPosition3D());

	// Kill off-screen strands
	if (realPosition.x < -MatrixLetter::letterSize ||
		realPosition.x > visibleSize.width + MatrixLetter::letterSize ||
		this->getPositionZ() > 960.0f)
	{
		this->killStrand();
	}

	// Set darkness based on distance
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
	for (int index = 0; index < this->letterCount; index++)
	{
		MatrixLetter* letter = this->letters->at(index);

		letter->despawn();
	}

	// Initialize state
	this->randomizePosition();
	this->setLetterCount();

	this->currentLetterIndex = 0;
	this->spawnSpeed = RandomHelper::random_real(MatrixStrand::minSpawnSpeed, MatrixStrand::maxSpawnSpeed);

	// Set update callback
	CallFunc* onUpdate = CallFunc::create(CC_CALLBACK_0(MatrixStrand::nextStrandAction, this));
	this->updateAction = RepeatForever::create(Sequence::create(onUpdate, DelayTime::create(this->spawnSpeed), nullptr));
	this->runAction(this->updateAction);
}

void MatrixStrand::endStrand()
{
	this->stopAllActions();

	// float speedPercent = (1.0f - (this->spawnSpeed - MatrixStrand::minSpawnSpeed) / (MatrixStrand::maxSpawnSpeed - MatrixStrand::minSpawnSpeed));
	float remainingDistance = 1024.0f - this->getPositionZ();
	float despawnTime = max(0.0f, remainingDistance / MatrixStrand::movementSpeed);

	this->runAction(Sequence::create(DelayTime::create(despawnTime),
		CallFunc::create(CC_CALLBACK_0(MatrixStrand::beginStrand, this)), nullptr));
}

void MatrixStrand::killStrand()
{
	this->stopAllActions();

	this->beginStrand();
}

void MatrixStrand::setLetterCount()
{
	this->letterCount = RandomHelper::random_int(MatrixStrand::minLetterCount, MatrixStrand::maxLetterCount);
}

void MatrixStrand::randomizePosition()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec3 position;
	position.x = RandomHelper::random_real(-MatrixStrand::overFlowX, visibleSize.width + MatrixStrand::overFlowX);
	position.y = RandomHelper::random_real(visibleSize.height - MatrixStrand::underFlowY, visibleSize.height + MatrixStrand::overFlowY);
	position.z = RandomHelper::random_real(MatrixStrand::maxSpawnDistance, MatrixStrand::minSpawnDistance);

	this->setPosition3D(position);
}
