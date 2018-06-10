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
	this->targetStack = new std::stack<Node*>();
	this->cameraScrollOffset = Vec2::ZERO;
	this->cameraBounds = Rect::ZERO;
}

LevelCamera::~LevelCamera()
{
	delete(this->targetStack);
}

void LevelCamera::onEnter()
{
	Node::onEnter();

	this->scheduleUpdate();
}

void LevelCamera::update(float dt)
{
	if (this->targetStack->size() > 0)
	{
		Vec2 targetPosition = this->targetStack->top()->getPosition();
		Size visibleSize = Director::getInstance()->getVisibleSize();

		// Handle camera scrolling from player traveling past scroll distance
		if (this->cameraPosition.x < targetPosition.x - this->cameraScrollOffset.x)
		{
			float idealPositionX = targetPosition.x - this->cameraScrollOffset.x;

			if (followSpeed.x <= 0.0f)
			{
				this->cameraPosition.x = idealPositionX;
			}
			else
			{
				float distance = idealPositionX - this->cameraPosition.x;
				this->cameraPosition.x = this->cameraPosition.x + distance * this->followSpeed.x;
			}
		}
		else if (this->cameraPosition.x > targetPosition.x + this->cameraScrollOffset.x)
		{
			float idealPositionX = targetPosition.x + this->cameraScrollOffset.x;

			if (followSpeed.x <= 0.0f)
			{
				this->cameraPosition.x = idealPositionX;
			}
			else
			{
				float distance = idealPositionX - this->cameraPosition.x;
				this->cameraPosition.x = this->cameraPosition.x + distance * this->followSpeed.x;
			}
		}

		if (this->cameraPosition.y < targetPosition.y - this->cameraScrollOffset.y)
		{
			float idealPositionY = targetPosition.y - this->cameraScrollOffset.y;

			if (followSpeed.y <= 0.0f)
			{
				this->cameraPosition.y = idealPositionY;
			}
			else
			{
				float distance = idealPositionY - this->cameraPosition.y;
				this->cameraPosition.y = this->cameraPosition.y + distance * this->followSpeed.y;
			}
		}
		else if (this->cameraPosition.y > targetPosition.y + this->cameraScrollOffset.y)
		{
			float idealPositionY = targetPosition.y + this->cameraScrollOffset.y;

			if (followSpeed.y <= 0.0f)
			{
				this->cameraPosition.y = idealPositionY;
			}
			else
			{
				float distance = idealPositionY - this->cameraPosition.y;
				this->cameraPosition.y = this->cameraPosition.y + distance * this->followSpeed.y;
			}
		}

		// Prevent camera from leaving level bounds
		this->cameraPosition.x = MathUtils::clamp(this->cameraPosition.x, this->cameraBounds.getMinX() + visibleSize.width / 2.0f, this->cameraBounds.getMaxX() + visibleSize.width / 2.0f);
		this->cameraPosition.y = MathUtils::clamp(this->cameraPosition.y, this->cameraBounds.getMinY() + visibleSize.height / 2.0f, this->cameraBounds.getMaxY() + visibleSize.height / 2.0f);

		this->setCameraPosition(this->cameraPosition);
	}
}

Vec2 LevelCamera::getCameraPosition()
{
	return Camera::getDefaultCamera()->getPosition();
}

void LevelCamera::setCameraPosition(Vec2 position)
{
	this->cameraPosition = position;
	Camera::getDefaultCamera()->setPosition(this->cameraPosition);
}

Rect LevelCamera::getBounds()
{
	return this->cameraBounds;
}

void LevelCamera::setBounds(Rect bounds)
{
	this->cameraBounds = bounds;
}

Vec2 LevelCamera::getScrollOffset()
{
	return this->cameraScrollOffset;
}

void LevelCamera::setScrollOffset(Vec2 offset)
{
	this->cameraScrollOffset = offset;
}

Vec2 LevelCamera::getFollowSpeed()
{
	return this->followSpeed;
}

void LevelCamera::setFollowSpeed(Vec2 speed)
{
	speed.x = MathUtils::clamp(speed.x, 0.0f, 1.0f);
	speed.y = MathUtils::clamp(speed.y, 0.0f, 1.0f);

	this->followSpeed = speed;
}

void LevelCamera::setTarget(Node* newTarget)
{
	this->clearTargets();
	this->pushTarget(newTarget);
	this->setCameraPosition(newTarget->getPosition());
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
