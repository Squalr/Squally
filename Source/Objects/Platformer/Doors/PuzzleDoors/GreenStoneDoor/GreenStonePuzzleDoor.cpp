#include "GreenStonePuzzleDoor.h"

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
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Doors/PuzzleDoors/GreenStoneDoor/GreenStonePuzzleDoorGenericPreview.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const Vec2 GreenStonePuzzleDoor::Offset = Vec2(0.0f, -160.0f);

GreenStonePuzzleDoor::GreenStonePuzzleDoor(ValueMap& properties) : super(properties,
	Size(256.0f, 512.0f),
	GreenStonePuzzleDoor::Offset + Vec2(0.0f, 24.0f),
	GreenStonePuzzleDoor::Offset + Vec2(0.0f, 32.0f),
	GreenStonePuzzleDoor::Offset + Vec2(0.0f, 464.0f),
	GreenStonePuzzleDoor::Offset + Vec2(-288.0f, 104.0f),
	GreenStonePuzzleDoor::Offset + Vec2(284.0f, 104.0f),
	GreenStonePuzzleDoor::Offset + Vec2(-208.0f, 338.0f),
	136.0f,
	292.0f)
{
	this->back = Sprite::create(ObjectResources::Doors_PuzzleDoor_GreenStone_Back);
	this->door = Sprite::create(ObjectResources::Doors_PuzzleDoor_GreenStone_Door);
	this->front = Sprite::create(ObjectResources::Doors_PuzzleDoor_GreenStone_Front);
	this->doorOpenSound = WorldSound::create();

	this->backNode->addChild(this->back);
	this->doorNode->addChild(this->door);
	this->frontNode->addChild(this->front);
	this->addChild(this->doorOpenSound);
}

GreenStonePuzzleDoor::~GreenStonePuzzleDoor()
{
}

void GreenStonePuzzleDoor::onEnter()
{
	super::onEnter();
}

void GreenStonePuzzleDoor::initializePositions()
{
	super::initializePositions();

	this->back->setPosition(Vec2(0.0f, -104.0f));
	this->door->setPosition(Vec2(0.0f, 32.0f));
	this->front->setPosition(Vec2(0.0f, -24.0f));
	this->doorOpenSound->setPosition(GreenStonePuzzleDoor::Offset);
}

void GreenStonePuzzleDoor::initializeListeners()
{
	super::initializeListeners();
}

Vec2 GreenStonePuzzleDoor::getButtonOffset()
{
	return Vec2(-286.0f, -128.0f);
}

HackablePreview* GreenStonePuzzleDoor::createDefaultPreview()
{
	return GreenStonePuzzleDoorGenericPreview::create();
}
