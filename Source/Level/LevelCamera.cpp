#include "LevelCamera.h"

LevelCamera* LevelCamera::cameraInstance = nullptr;

LevelCamera* LevelCamera::create()
{
	LevelCamera* instance = new LevelCamera();

	LevelCamera::cameraInstance = instance;
	instance->autorelease();

	return instance;
}

LevelCamera* LevelCamera::getInstance()
{
	return LevelCamera::cameraInstance;
}

LevelCamera::LevelCamera()
{
	this->cameraPosition = Vec2::ZERO;
	this->targetStack = new std::stack<Node*>();
	this->cameraScrollOffset = Vec2::ZERO;
	this->cameraBounds = Rect::ZERO;

	this->scheduleUpdate();
}

LevelCamera::~LevelCamera()
{
	delete(this->targetStack);
}

void LevelCamera::update(float dt)
{
	if (this->targetStack->size() > 0)
	{
		Vec2 targetPosition = this->targetStack->top()->getPosition();
		Size visibleSize = Director::getInstance()->getVisibleSize();

		// Handle camera scrolling from player traveling past scroll distance
		if (this->cameraPosition.x < targetPosition.x - this->cameraScrollOffset.x - visibleSize.width / 2)
		{
			this->cameraPosition.x = targetPosition.x - this->cameraScrollOffset.x - visibleSize.width / 2;
		}
		else if (this->cameraPosition.x > targetPosition.x + this->cameraScrollOffset.x - visibleSize.width / 2)
		{
			this->cameraPosition.x = targetPosition.x + this->cameraScrollOffset.x - visibleSize.width / 2;
		}

		if (this->cameraPosition.y < targetPosition.y - this->cameraScrollOffset.y - visibleSize.height / 2)
		{
			this->cameraPosition.y = targetPosition.y - this->cameraScrollOffset.y - visibleSize.height / 2;
		}
		else if (this->cameraPosition.y > targetPosition.y + this->cameraScrollOffset.y - visibleSize.height / 2)
		{
			this->cameraPosition.y = targetPosition.y + this->cameraScrollOffset.y - visibleSize.height / 2;
		}

		// Prevent camera from leaving level bounds
		this->cameraPosition.x = std::min(this->cameraPosition.x, this->cameraBounds.getMaxX() - visibleSize.width);
		this->cameraPosition.x = std::max(this->cameraPosition.x, this->cameraBounds.getMinX());

		this->cameraPosition.y = std::min(this->cameraPosition.y, this->cameraBounds.getMaxY() - visibleSize.height);
		this->cameraPosition.y = std::max(this->cameraPosition.y, this->cameraBounds.getMinY());
	}
}

void LevelCamera::setBounds(Rect bounds)
{
	this->cameraBounds = bounds;
}

void LevelCamera::setScrollOffset(Vec2 offset)
{
	this->cameraScrollOffset = offset;
}

void LevelCamera::setTarget(Node* newTarget)
{
	this->clearTargets();
	this->pushTarget(newTarget);
}

void LevelCamera::pushTarget(Node* newTarget)
{
	this->targetStack->push(newTarget);
}

void LevelCamera::popTarget()
{
	this->targetStack->pop();
}

void LevelCamera::clearTargets()
{
	while(!this->targetStack->empty())
	{
		this->targetStack->pop();
	}
}

Vec2 LevelCamera::getCameraPosition()
{
	return this->cameraPosition;
}
