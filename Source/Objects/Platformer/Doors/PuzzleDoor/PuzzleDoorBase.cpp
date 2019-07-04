#include "PuzzleDoorBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Doors/PuzzleDoor/PuzzleDoorGenericPreview.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/Puzzles/Crystal/PuzzleIncrement/PuzzleIncrement.h"
#include "Strings/Hacking/Objects/Puzzles/Crystal/PuzzleIncrement/RegisterEcx.h"

using namespace cocos2d;

PuzzleDoorBase::PuzzleDoorBase(ValueMap& initProperties) : super(initProperties)
{
	this->back = Sprite::create(ObjectResources::Doors_PuzzleDoor_Back);
	this->door = Sprite::create(ObjectResources::Doors_PuzzleDoor_Door);
	this->front = Sprite::create(ObjectResources::Doors_PuzzleDoor_Front);
	this->indexString = ConstantString::create(std::to_string(0));
	this->truthString = ConstantString::create(std::to_string(0));
	this->hackableString = ConstantString::create(std::to_string(0));
	this->indexLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, this->indexString);
	this->truthLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, this->truthString);
	this->hackableLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, this->hackableString);
	this->isUnlocked = false;

	this->indexLabel->enableOutline(Color4B::BLACK, 4);
	this->truthLabel->enableOutline(Color4B::BLACK, 4);
	this->hackableLabel->enableOutline(Color4B::BLACK, 4);

	this->puzzleIndex = 0;

	this->addChild(this->back);
	this->addChild(this->door);
	this->addChild(this->front);
	this->addChild(this->indexLabel);
	this->addChild(this->truthLabel);
	this->addChild(this->hackableLabel);
}

PuzzleDoorBase::~PuzzleDoorBase()
{
}

void PuzzleDoorBase::onEnter()
{
	super::onEnter();
}

void PuzzleDoorBase::initializePositions()
{
	super::initializePositions();

	const Vec2 offset = Vec2(0.0f, -160.0f);

	this->back->setPosition(Vec2(0.0f, 72.0f) + offset);
	this->door->setPosition(Vec2(0.0f, 64.0f) + offset);
	this->front->setPosition(Vec2(0.0f, 144.0f) + offset);
	this->indexLabel->setPosition(Vec2(0.0f, 320.0f) + offset);
	this->truthLabel->setPosition(Vec2(288.0f, 112.0f) + offset);
	this->hackableLabel->setPosition(Vec2(-288.0f, 112.0f) + offset);
}

Vec2 PuzzleDoorBase::getButtonOffset()
{
	return Vec2(-128.0f, 128.0f);
}

HackablePreview* PuzzleDoorBase::createDefaultPreview()
{
	return PuzzleDoorGenericPreview::create();
}
