#include "HexusPuzzleShrine.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsBody.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusPuzzleShrine::MapKeyHexusPuzzleShrine = "hexus-shrine";

HexusPuzzleShrine* HexusPuzzleShrine::create(ValueMap& properties)
{
	HexusPuzzleShrine* instance = new HexusPuzzleShrine(properties);

	instance->autorelease();

	return instance;
}

HexusPuzzleShrine::HexusPuzzleShrine(ValueMap& properties) : super(properties)
{
	this->shrine = Sprite::create(ObjectResources::Interactive_LifeStone);
	this->floatingPuzzle = Sprite::create(ObjectResources::Items_Misc_BOOK_1);
	this->floatContainer = Node::create();
	this->healSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal4);
	this->isAnimating = false;
	
	this->floatContainer->addChild(this->floatingPuzzle);
	this->addChild(this->shrine);
	this->addChild(this->floatContainer);
	this->addChild(this->healSound);
}

HexusPuzzleShrine::~HexusPuzzleShrine()
{
}

void HexusPuzzleShrine::onEnter()
{
	super::onEnter();

	this->floatingPuzzle->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(3.0f, Vec2(0.0f, -128.0f))),
		EaseSineInOut::create(MoveTo::create(3.0f, Vec2(0.0f, 0.0f))),
		nullptr
	)));
}

void HexusPuzzleShrine::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
}

void HexusPuzzleShrine::initializePositions()
{
	super::initializePositions();

	this->floatContainer->setPosition(Vec2(0.0f, 64.0f));
	this->shrine->setPosition(Vec2(0.0f, 0.0f));
}

void HexusPuzzleShrine::initializeListeners()
{
	super::initializeListeners();
}

void HexusPuzzleShrine::runHealAnimation(bool reRun)
{
	if (this->isAnimating && !reRun)
	{
		return;
	}

	if (!reRun)
	{
		this->healSound->play();
	}

	this->isAnimating = true;
}
