#include "LiftBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

const std::string LiftBase::PropertySpeed = "speed";

LiftBase::LiftBase(ValueMap& properties, Size collisionSize, std::string railArt) : super(properties)
{
    this->railingNode = Node::create();
    this->railing = Sprite::create(railArt);
    this->liftNode = Node::create();
    this->liftCollision = CollisionObject::create(
        CollisionObject::createBox(collisionSize),
        (int)PlatformerCollisionType::PassThrough,
        CollisionObject::Properties(false, false)
    );

    this->width = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat();
    this->height = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat();
    this->speedPer256px = GameUtils::getKeyOrDefault(this->properties, LiftBase::PropertySpeed, Value(1.0f)).asFloat();
    
    if (this->width >= this->height)
    {
        this->movementDirection = MovementDirection::LeftRight;
    }
    else
    {
        this->movementDirection = MovementDirection::UpDown;
    }

	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;

	switch(this->movementDirection)
	{
		default:
		case MovementDirection::LeftRight:
		{
			params.wrapS = GL_REPEAT;
		    this->railing->setTextureRect(Rect(0.0f, 0.0f, this->width, this->railing->getContentSize().height));
            this->liftCollision->setPosition(Vec2(-this->width / 2.0f, 0.0f));
			break;
		}
		case MovementDirection::UpDown:
		{
			params.wrapT = GL_REPEAT;
		    this->railing->setTextureRect(Rect(0.0f, 0.0f, this->railing->getContentSize().width, this->height));
            this->liftCollision->setPosition(Vec2(-this->height / 2.0f, 0.0f));
			break;
		}
	}
	
	if (this->railing->getTexture() != nullptr)
	{
		this->railing->getTexture()->setTexParameters(params);
	}

    this->liftCollision->addChild(this->liftNode);
    this->railingNode->addChild(this->railing);
    this->addChild(this->railingNode);
    this->addChild(this->liftCollision);
}

LiftBase::~LiftBase()
{
}

void LiftBase::initializePositions()
{
	super::initializePositions();

    const float Padding = this->getPadding();
    const float AdjustedSpeed = (this->movementDirection == MovementDirection::LeftRight ? this->width : this->height) / this->speedPer256px / 256.0f;
    const Vec2 StartPosition = this->movementDirection == MovementDirection::LeftRight ? Vec2(this->width / 2.0f - Padding, 0.0f) : Vec2(0.0f, this->height / 2.0f - Padding);

	this->liftCollision->setPosition(-StartPosition);
}

void LiftBase::onEnter()
{
    super::onEnter();
    
    if (this->speedPer256px != 0.0f)
    {
        const float Padding = this->getPadding();
        const float AdjustedSpeed = (this->movementDirection == MovementDirection::LeftRight ? this->width : this->height) / this->speedPer256px / 256.0f;
        const Vec2 StartPosition = this->movementDirection == MovementDirection::LeftRight ? Vec2(this->width / 2.0f - Padding, 0.0f) : Vec2(0.0f, this->height / 2.0f - Padding);

        this->liftCollision->runAction(RepeatForever::create(Sequence::create(
            MoveTo::create(AdjustedSpeed, StartPosition),
            MoveTo::create(AdjustedSpeed, -StartPosition),
            nullptr
        )));
    }
}

float LiftBase::getPadding()
{
    return 0.0f;
}

