#include "GameCamera.h"

GameCamera* GameCamera::cameraInstance = nullptr;

GameCamera* GameCamera::create()
{
	GameCamera* instance = new GameCamera();

	GameCamera::cameraInstance = instance;
	instance->autorelease();

	return instance;
}

GameCamera* GameCamera::getInstance()
{
	return GameCamera::cameraInstance;
}

GameCamera::GameCamera()
{
	this->targetStack = new std::stack<Node*>();
	this->cameraScrollOffset = Vec2::ZERO;
	this->cameraBounds = Rect::ZERO;

	this->defaultDistance = Director::getInstance()->getZEye();
}

GameCamera::~GameCamera()
{
	delete(this->targetStack);
}

void GameCamera::onEnter()
{
	Node::onEnter();

	this->scheduleUpdate();
}

void GameCamera::update(float dt)
{
	if (this->targetStack->size() > 0)
	{
		Vec2 targetPosition = this->targetStack->top()->getPosition() + Vec2(-320.0f, 256.0f);
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

float GameCamera::getCameraDistance()
{
	return Camera::getDefaultCamera()->getPositionZ();
}

void GameCamera::setCameraDistance(float distance)
{
	this->setPositionZ(distance - this->defaultDistance);
	Camera::getDefaultCamera()->setPositionZ(distance);
}

Vec2 GameCamera::getCameraPosition()
{
	return Camera::getDefaultCamera()->getPosition();
}

void GameCamera::setCameraPosition(Vec2 position)
{
	this->cameraPosition = position;
	Camera::getDefaultCamera()->setPosition(this->cameraPosition);
}

Rect GameCamera::getBounds()
{
	return this->cameraBounds;
}

void GameCamera::setBounds(Rect bounds)
{
	this->cameraBounds = bounds;
}

Vec2 GameCamera::getScrollOffset()
{
	return this->cameraScrollOffset;
}

void GameCamera::setScrollOffset(Vec2 offset)
{
	this->cameraScrollOffset = offset;
}

Vec2 GameCamera::getFollowSpeed()
{
	return this->followSpeed;
}

void GameCamera::setFollowSpeed(Vec2 speed)
{
	speed.x = MathUtils::clamp(speed.x, 0.0f, 1.0f);
	speed.y = MathUtils::clamp(speed.y, 0.0f, 1.0f);

	this->followSpeed = speed;
}

void GameCamera::setTarget(Node* newTarget)
{
	this->clearTargets();

	if (newTarget != nullptr)
	{
		this->pushTarget(newTarget);
		this->setCameraPosition(newTarget->getPosition());
	}
}

void GameCamera::pushTarget(Node* newTarget)
{
	this->targetStack->push(newTarget);
}

void GameCamera::popTarget()
{
	this->targetStack->pop();
}

void GameCamera::clearTargets()
{
	while(!this->targetStack->empty())
	{
		this->targetStack->pop();
	}
}
