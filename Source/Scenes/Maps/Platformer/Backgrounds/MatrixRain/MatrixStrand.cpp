#include "MatrixStrand.h"

const int MatrixStrand::minLetterCount = 24;
const int MatrixStrand::maxLetterCount = 80;
const float MatrixStrand::movementSpeed = 128.0f;
const float MatrixStrand::strandScale = 0.35f;
const float MatrixStrand::minSpawnSpeed = 0.02f;
const float MatrixStrand::maxSpawnSpeed = 0.20f;
const float MatrixStrand::overFlowY = 256.0f;
const float MatrixStrand::underFlowY = 256.0f;
const float MatrixStrand::minSpawnDistance = -256.0f;
const float MatrixStrand::maxSpawnDistance = -512.0f;

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

void MatrixStrand::onEnter()
{
	Node::onEnter();

	this->scheduleUpdate();
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

	// TODO: Bounds checking should be updated to be the projected 3d => 2d X position. This seems to not be working as intended after the camera updates.

	// Kill off-screen strands
	if (this->getPositionX() < 0 - MatrixLetter::letterSize ||
		this->getPositionX() > visibleSize.width + MatrixLetter::letterSize ||
		this->getPositionZ() > Director::getInstance()->getRunningScene()->getDefaultCamera()->getPositionZ() + 64.0f)
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
	position.x = RandomHelper::random_real(0.0f, visibleSize.width);
	position.y = RandomHelper::random_real(visibleSize.height - MatrixStrand::underFlowY, visibleSize.height + MatrixStrand::overFlowY);
	position.z = RandomHelper::random_real(MatrixStrand::maxSpawnDistance, MatrixStrand::minSpawnDistance);

	this->setPosition3D(position);
}
