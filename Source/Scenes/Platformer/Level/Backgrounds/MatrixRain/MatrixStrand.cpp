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
	this->currentLetterIndex = 0;
	this->isAlive = true;

	for (int index = 0; index < MatrixStrand::MaxLetterCount; index++)
	{
		MatrixLetter* letter = MatrixLetter::create();

		letter->setPositionY((float)index * -(MatrixLetter::LetterSize - 12));

		this->letters.push_back(letter);
		this->addChild(letter);
	}

	this->setCascadeOpacityEnabled(true);
	this->setScale(MatrixStrand::StrandScale);
	this->randomizeInitialState(strandIndex);
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
	// Do not update if not visible
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	this->elapsedDuration += dt;

	if (this->elapsedDuration > this->spawnSpeed)
	{
		this->elapsedDuration = 0.0f;
		this->nextStrandAction();
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Camera movement effect
	this->setPositionY(this->getPositionY() - dt * MovementSpeed / 4.0f);
	this->setPositionZ(this->getPositionZ() + dt * MovementSpeed);

	Vec2 screenCoords = GameUtils::getScreenBounds(this).origin;

	// Kill off-screen strands
	if (screenCoords.x < 0 - MatrixLetter::LetterSize ||
		screenCoords.x > visibleSize.width + MatrixLetter::LetterSize ||
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
		
		MatrixLetter* letter = this->letters[this->currentLetterIndex];

		letter->spawn();

		this->currentLetterIndex++;
	}
}

void MatrixStrand::beginStrand()
{
	for (int index = 0; index < this->letterCount; index++)
	{
		MatrixLetter* letter = this->letters[index];

		letter->despawn();
	}

	// Initialize state
	this->randomizeState(true);

	this->currentLetterIndex = 0;
	this->isAlive = true;
}

void MatrixStrand::killStrand()
{
	this->isAlive = false;
	
	// Just start the new strand immediately
	this->beginStrand();
}

void MatrixStrand::randomizeInitialState(int strandIndex)
{
	this->randomizeState(false);
	this->isAlive = true;

	// 40% chance to start out completely formed
	if (RandomHelper::random_real(0.0f, 1.0f) < 0.4f)
	{
		this->currentLetterIndex = this->letterCount;

		for (int index = 0; index < this->letterCount; index++)
		{
			this->letters[index]->spawnImmediate();
		}
	}
	// 50% of remaining will start partially formed already 
	else if (RandomHelper::random_real(0.0f, 1.0f) < 0.5f)
	{
		// Otherwise, we start the strand somewhere in the middle
		this->currentLetterIndex = RandomHelper::random_int(0, this->letterCount);

		for (int index = 0; index < this->currentLetterIndex; index++)
		{
			this->letters[index]->spawnImmediate();
		}
	}
}

void MatrixStrand::randomizeState(bool spawnInRange)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec3 position;
	position.x = RandomHelper::random_real(0.0f, visibleSize.width);
	position.y = RandomHelper::random_real(visibleSize.height - MatrixStrand::UnderFlowY, visibleSize.height + MatrixStrand::OverFlowY);
	
	if (spawnInRange)
	{
		position.z = RandomHelper::random_real(MatrixStrand::MaxSpawnDistance, MatrixStrand::MinSpawnDistance);
	}
	else
	{
		position.z = RandomHelper::random_real(MatrixStrand::MaxSpawnDistance, GameCamera::getInstance()->getCameraDistance());
	}
	
	this->setPosition3D(position);

	this->letterCount = RandomHelper::random_int(MatrixStrand::MinLetterCount, MatrixStrand::MaxLetterCount);
	this->spawnSpeed = RandomHelper::random_real(MatrixStrand::MinSpawnSpeed, MatrixStrand::MaxSpawnSpeed);
}
