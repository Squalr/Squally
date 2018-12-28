#include "IsometricEntity.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

IsometricEntity::IsometricEntity(ValueMap* initProperties, std::string scmlResource, float scale, Vec2 offset, Size size) : HackableObject(initProperties)
{
	// TODO: Configurable/randomizable start direction (if any)
	this->movement = Vec2(0.0f, 0.0f);

	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->animationNode->setScale(scale);
	this->animationNode->playAnimation("Idle_NE");

	this->animationNode->setPosition(offset * scale);

	// Update width to be serialized
	if (this->properties != nullptr)
	{
		(*this->properties)[IsometricEntity::MapKeyWidth] = size.width * scale;
		(*this->properties)[IsometricEntity::MapKeyHeight] = size.height * scale;
	}

	this->addChild(this->animationNode);
}

IsometricEntity::~IsometricEntity()
{
}

void IsometricEntity::onEnter()
{
	HackableObject::onEnter();

	this->scheduleUpdate();
}

void IsometricEntity::update(float dt)
{
	HackableObject::update(dt);

	const float MOVE_SPEED = 256.0f;

	if (this->movement != Vec2::ZERO)
	{
		float angle = atan2(this->movement.y, this->movement.x);
		int octant = (int)std::round(8.0f * angle / (2.0f * M_PI) + 8.0f) % 8;

		switch (octant)
		{
			case 0:
			{
				this->animationNode->playAnimation("Idle_E");
				break;
			}
			case 1:
			{
				this->animationNode->playAnimation("Idle_NE");
				break;
			}
			case 2:
			{
				this->animationNode->playAnimation("Idle_N");
				break;
			}
			case 3:
			{
				this->animationNode->playAnimation("Idle_NW");
				break;
			}
			case 4:
			{
				this->animationNode->playAnimation("Idle_W");
				break;
			}
			case 5:
			{
				this->animationNode->playAnimation("Idle_SW");
				break;
			}
			case 6:
			{
				this->animationNode->playAnimation("Idle_S");
				break;
			}
			case 7:
			{
				this->animationNode->playAnimation("Idle_SE");
				break;
			}
			default:
			{
				this->animationNode->playAnimation("Idle_NW");
				break;
			}
		}

		this->movement.x *= 2.0f;
		this->setPosition(this->getPosition() + dt * this->movement * MOVE_SPEED);
	}
}
