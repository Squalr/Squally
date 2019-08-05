#include "LanternGate.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Sound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Doors/PuzzleDoor/PuzzleDoorGenericPreview.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string LanternGate::MapKeyLanternGate = "lantern-gate";

LanternGate* LanternGate::create(ValueMap& initProperties)
{
	LanternGate* instance = new LanternGate(initProperties);

	instance->autorelease();

	return instance;
}

LanternGate::LanternGate(ValueMap& initProperties) : super(initProperties, Size(356.0f, 320.0f), Vec2(0.0f, 0.0f))
{
	this->gateRight = Sprite::create(ObjectResources::Doors_LanternGate_LanternOrangeRight);
	this->gateLeft = Sprite::create(ObjectResources::Doors_LanternGate_LanternOrangeLeft);

	this->addChild(this->gateRight);
	this->addChild(this->gateLeft);
}

LanternGate::~LanternGate()
{
}

void LanternGate::onEnter()
{
	super::onEnter();
}

void LanternGate::initializePositions()
{
	super::initializePositions();

	this->gateLeft->setPosition(Vec2(-160.0f, 16.0f));
	this->gateRight->setPosition(Vec2(160.0f, 16.0f));
}

void LanternGate::initializeListeners()
{
	super::initializeListeners();
}

Vec2 LanternGate::getButtonOffset()
{
	return Vec2(-286.0f, -128.0f);
}

HackablePreview* LanternGate::createDefaultPreview()
{
	return PuzzleDoorGenericPreview::create();
}

void LanternGate::lock(bool animate)
{
	super::lock(animate);
}

void LanternGate::unlock(bool animate)
{
	super::unlock(animate);
}
