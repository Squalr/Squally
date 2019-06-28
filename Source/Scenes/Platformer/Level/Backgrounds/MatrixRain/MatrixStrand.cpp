#include "MatrixStrand.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Backgrounds/MatrixRain/MatrixLetter.h"

using namespace cocos2d;

const int MatrixStrand::MinLetterCount = 24;
const int MatrixStrand::MaxLetterCount = 80;
const float MatrixStrand::MovementSpeed = 128.0f;
const float MatrixStrand::StrandScale = 0.35f;
const float MatrixStrand::MinSpawnSpeed = 0.02f;
const float MatrixStrand::MaxSpawnSpeed = 0.20f;
const float MatrixStrand::OverFlowY = 256.0f;
const float MatrixStrand::UnderFlowY = 256.0f;
const float MatrixStrand::MinSpawnDistance = -256.0f;
const float MatrixStrand::MaxSpawnDistance = -512.0f;
const float MatrixStrand::InitializationDuration = 8.0f;

MatrixStrand* MatrixStrand::create(int strandIndex)
{
	MatrixStrand* matrixStrand = new MatrixStrand(strandIndex);

	matrixStrand->autorelease();

	return matrixStrand;
}

MatrixStrand::MatrixStrand(int strandIndex)
{
	this->letters = std::vector<MatrixLetter*>();
	this->letterCount = 0;
	this->elapsedDuration = 0.0f;

	for (int index = 0; index < MatrixStrand::MaxLetterCount; index++)
	{
		MatrixLetter* letter = MatrixLetter::create();

		letter->setPositionY((float)index * -(MatrixLetter::letterSize - 12));

		letters.push_back(letter);
		this->addChild(letter);
	}

	this->setCascadeOpacityEnabled(true);
	this->setScale(MatrixStrand::StrandScale);

	// Delayed start to prevent all strands from being created at the same time
	this->runAction(Sequence::create(
		DelayTime::create(float(strandIndex) * 0.15f),
		CallFunc::create([=]()
		{
			this->beginStrand();
			this->scheduleUpdate();
		}),
		nullptr
	));
}

MatrixStrand::~MatrixStrand()
{
}

void MatrixStrand::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void MatrixStrand::pause()
{
	// Ignore pause
}

void MatrixStrand::update(float dt)
{
	// Do not update if not visible (unless we're initializing things)
	if (!GameUtils::isVisible(this))
	{
		if (this->elapsedDuration < MatrixStrand::InitializationDuration)
		{
			this->elapsedDuration += dt;

			// Speed things up a bit
			dt *= 3.0f;
		}
		else
		{
			return;
		}
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Camera movement effect
	this->setPositionY(this->getPositionY() - dt * MovementSpeed / 4.0f);
	this->setPositionZ(this->getPositionZ() + dt * MovementSpeed);

	Vec2 screenCoords = GameUtils::getScreenBounds(this).origin;

	// Kill off-screen strands
	if (screenCoords.x < 0 - MatrixLetter::letterSize ||
		screenCoords.x > visibleSize.width + MatrixLetter::letterSize ||
		this->getPositionZ() > GameCamera::getInstance()->getCameraDistance() + 64.0f)
	{
		this->killStrand();
	}

	// Set darkness based on distance
	if (this->getPositionZ() < 0.0f)
	{
		this->setOpacity(255 * (1.0f - (this->getPositionZ() / MatrixStrand::MaxSpawnDistance)));
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
		MatrixLetter* letter = this->letters.at(this->currentLetterIndex);

		letter->spawn();

		this->currentLetterIndex++;
	}
}

void MatrixStrand::beginStrand()
{
	for (int index = 0; index < this->letterCount; index++)
	{
		MatrixLetter* letter = this->letters.at(index);

		letter->despawn();
	}

	// Initialize state
	this->randomizePosition();
	this->setLetterCount();

	this->currentLetterIndex = 0;
	this->spawnSpeed = RandomHelper::random_real(MatrixStrand::MinSpawnSpeed, MatrixStrand::MaxSpawnSpeed);

	// Set update callback
	CallFunc* onUpdate = CallFunc::create(CC_CALLBACK_0(MatrixStrand::nextStrandAction, this));
	this->runAction(RepeatForever::create(Sequence::create(onUpdate, DelayTime::create(this->spawnSpeed), nullptr)));
}

void MatrixStrand::killStrand()
{
	this->stopAllActions();
	this->beginStrand();
}

void MatrixStrand::setLetterCount()
{
	this->letterCount = RandomHelper::random_int(MatrixStrand::MinLetterCount, MatrixStrand::MaxLetterCount);
}

void MatrixStrand::randomizePosition()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec3 position;
	position.x = RandomHelper::random_real(0.0f, visibleSize.width);
	position.y = RandomHelper::random_real(visibleSize.height - MatrixStrand::UnderFlowY, visibleSize.height + MatrixStrand::OverFlowY);
	position.z = RandomHelper::random_real(MatrixStrand::MaxSpawnDistance, MatrixStrand::MinSpawnDistance);

	this->setPosition3D(position);
}
