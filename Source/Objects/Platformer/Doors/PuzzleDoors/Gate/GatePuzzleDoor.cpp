#include "GatePuzzleDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Sound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Doors/PuzzleDoors/Gate/GatePuzzleDoorGenericPreview.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const Vec2 GatePuzzleDoor::Offset = Vec2(0.0f, -160.0f);

GatePuzzleDoor::GatePuzzleDoor(ValueMap& properties) : super(properties,
	Size(256.0f, 512.0f),
	GatePuzzleDoor::Offset + Vec2(0.0f, 24.0f),
	GatePuzzleDoor::Offset + Vec2(0.0f, 32.0f),
	GatePuzzleDoor::Offset + Vec2(0.0f, 464.0f),
	GatePuzzleDoor::Offset + Vec2(-288.0f, 104.0f),
	GatePuzzleDoor::Offset + Vec2(284.0f, 104.0f),
	GatePuzzleDoor::Offset + Vec2(-208.0f, 338.0f),
	136.0f,
	384.0f)
{
	this->door = Sprite::create(ObjectResources::Doors_PuzzleDoor_Gate_Gate);
	this->front = Sprite::create(ObjectResources::Doors_PuzzleDoor_Gate_Front);
	this->doorOpenSound = Sound::create();

	this->doorNode->addChild(this->door);
	this->frontNode->addChild(this->front);
	this->addChild(this->doorOpenSound);
}

GatePuzzleDoor::~GatePuzzleDoor()
{
}

void GatePuzzleDoor::onEnter()
{
	super::onEnter();
}

void GatePuzzleDoor::initializePositions()
{
	super::initializePositions();

	this->door->setPosition(Vec2(0.0f, 32.0f));
	this->front->setPosition(Vec2(0.0f, -24.0f));
	this->doorOpenSound->setPosition(GatePuzzleDoor::Offset);
}

void GatePuzzleDoor::initializeListeners()
{
	super::initializeListeners();
}

Vec2 GatePuzzleDoor::getButtonOffset()
{
	return Vec2(-286.0f, -128.0f);
}

HackablePreview* GatePuzzleDoor::createDefaultPreview()
{
	return GatePuzzleDoorGenericPreview::create();
}
