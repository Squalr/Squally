#include "IsometricEntity.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

IsometricEntity::IsometricEntity(ValueMap& properties, std::string scmlResource, float scale, Vec2 offset, Size size) : super(properties)
{
	// TODO: Configurable/randomizable start direction (if any)
	this->movement = Vec2(0.0f, 0.0f);

	this->underNode = Node::create();
	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->animationNode->setScale(scale);
	this->animationNode->playAnimation("Idle_NE", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f));

	this->animationNode->setPosition(offset * scale);

	float height = this->properties[super::MapKeyHeight].asFloat();

	this->setZSorted(true);

	// Update width to be serialized
	this->properties[super::MapKeyWidth] = size.width * scale;
	this->properties[super::MapKeyHeight] = size.height * scale;

	this->addChild(this->underNode);
	this->addChild(this->animationNode);
}

IsometricEntity::~IsometricEntity()
{
}

void IsometricEntity::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void IsometricEntity::update(float dt)
{
	super::update(dt);

	const float MOVE_SPEED = 256.0f;

	if (this->movement != Vec2::ZERO)
	{
		float angle = atan2(this->movement.y, this->movement.x);
		int octant = (int)std::round(8.0f * angle / (2.0f * M_PI) + 8.0f) % 8;

		switch (octant)
		{
			case 0:
			{
				this->animationNode->playAnimation("Idle_E", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f));
				break;
			}
			case 1:
			{
				this->animationNode->playAnimation("Idle_NE", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f));
				break;
			}
			case 2:
			{
				this->animationNode->playAnimation("Idle_N", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f));
				break;
			}
			case 3:
			{
				this->animationNode->playAnimation("Idle_NW", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f));
				break;
			}
			case 4:
			{
				this->animationNode->playAnimation("Idle_W", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f));
				break;
			}
			case 5:
			{
				this->animationNode->playAnimation("Idle_SW", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f));
				break;
			}
			case 6:
			{
				this->animationNode->playAnimation("Idle_S", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f));
				break;
			}
			case 7:
			{
				this->animationNode->playAnimation("Idle_SE", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f));
				break;
			}
			default:
			{
				this->animationNode->playAnimation("Idle_NW", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f));
				break;
			}
		}

		this->movement.x *= 2.0f;
		this->setPosition(this->getPosition() + dt * this->movement * MOVE_SPEED);
	}
}
