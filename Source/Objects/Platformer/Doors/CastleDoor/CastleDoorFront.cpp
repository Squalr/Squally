#include "CastleDoorFront.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CastleDoorFront::MapKeyCastleDoorFront = "castle-door-front";

CastleDoorFront* CastleDoorFront::create(ValueMap& initProperties)
{
	CastleDoorFront* instance = new CastleDoorFront(initProperties);

	instance->autorelease();

	return instance;
}

CastleDoorFront::CastleDoorFront(ValueMap& initProperties) : GameObject(initProperties)
{
	this->castleDoorFront = Sprite::create(ObjectResources::Doors_CastleGate_CASTLE_FRONT);

	this->isFlipped = GameUtils::getKeyOrDefault(initProperties, GameObject::MapKeyFlipX, Value(false)).asBool();

	this->castleDoorFront->setFlippedX(this->isFlipped);

	this->addChild(this->castleDoorFront);
}

CastleDoorFront::~CastleDoorFront()
{
}

void CastleDoorFront::onEnter()
{
	super::onEnter();
}

void CastleDoorFront::initializePositions()
{
	super::initializePositions();

	float flipMultiplier = this->isFlipped ? -1.0f : 1.0f;

	this->castleDoorFront->setPosition(Vec2(0.0f, -48.0f));

	this->castleDoorFront->setPositionX(this->castleDoorFront->getPositionX() * flipMultiplier);
}
