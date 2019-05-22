#include "DensityObject.h"

#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"


using namespace cocos2d;

const std::string DensityObject::MapKeyDensity = "density";
const float DensityObject::DensityFloatSpeed = 3.0f;

DensityObject::DensityObject(ValueMap& initProperties) : super(initProperties)
{
	this->contentNode = Node::create();

	this->heightRange = GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyHeight, Value(128.0f)).asFloat();
	this->loadedDensity = GameUtils::getKeyOrDefault(this->properties, DensityObject::MapKeyDensity, Value(1.0f)).asFloat();
	this->currentDensity = this->loadedDensity;

	this->contentNode->setRotation(GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyRotation, Value(0.0f)).asFloat());
	
	this->addChild(this->contentNode);
}

DensityObject::~DensityObject()
{
}

void DensityObject::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void DensityObject::initializePositions()
{
	super::initializePositions();
}

void DensityObject::update(float dt)
{
	super::update(dt);

	// Smooth density
	float targetDensity = this->getDensity();
	float delta = ((this->currentDensity + targetDensity) / 2.0f - this->currentDensity) * dt * DensityObject::DensityFloatSpeed;
	this->currentDensity += delta;

	float actualHeightRange = this->heightRange - this->getObjectHeight();
	this->contentNode->setPositionY(actualHeightRange / 2.0f - actualHeightRange * this->currentDensity);
}
