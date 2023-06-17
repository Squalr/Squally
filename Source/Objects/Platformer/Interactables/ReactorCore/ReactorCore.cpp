#include "ReactorCore.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Cutscenes/CutscenesMenu.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReactorCore::MapKey = "reactor";

ReactorCore* ReactorCore::create(ValueMap& properties)
{
	ReactorCore* instance = new ReactorCore(properties);

	instance->autorelease();

	return instance;
}

ReactorCore::ReactorCore(ValueMap& properties) : super(properties, InteractObject::InteractType::None, CSize(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()))
{
	this->reactorSfx = WorldSound::create(); //SoundResources::Platformer_FX_ServerRoom
	this->reactorHitSfx = WorldSound::create(SoundResources::Platformer_Objects_PotBreak_PotSmash1);
	this->reactorCore = Sprite::create(ObjectResources::Interactive_ReactorCore_Reactor);
	this->reactorPad = Sprite::create(ObjectResources::Interactive_ReactorCore_ReactorPad);
	this->reactorCasePristine = Sprite::create(ObjectResources::Interactive_ReactorCore_ReactorCase);
	this->reactorCaseCracked1 = Sprite::create(ObjectResources::Interactive_ReactorCore_ReactorCaseCracked1);
	this->reactorCaseCracked2 = Sprite::create(ObjectResources::Interactive_ReactorCore_ReactorCaseCracked2);
	this->reactorCaseCracked3 = Sprite::create(ObjectResources::Interactive_ReactorCore_ReactorCaseCracked3);
	this->reactorCaseCracked4 = Sprite::create(ObjectResources::Interactive_ReactorCore_ReactorCaseCracked4);
	
	this->contentNode->addChild(this->reactorCore);
	this->contentNode->addChild(this->reactorPad);
	this->contentNode->addChild(this->reactorCasePristine);
	this->contentNode->addChild(this->reactorCaseCracked1);
	this->contentNode->addChild(this->reactorCaseCracked2);
	this->contentNode->addChild(this->reactorCaseCracked3);
	this->contentNode->addChild(this->reactorCaseCracked4);
	this->addChild(this->reactorSfx);
	this->addChild(this->reactorHitSfx);
}

ReactorCore::~ReactorCore()
{
}

void ReactorCore::onEnter()
{
	super::onEnter();

	this->updateCracks();

	this->interactCollision->whenCollidesWith({ (int)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData collisionData)
	{
		this->reactorHitSfx->play();
		this->crackedLevel++;
		this->updateCracks();

		return CollisionResult::DoNothing;
	});
}

void ReactorCore::initializePositions()
{
	super::initializePositions();

	const float HighY = -350.0f;
	const float LowY = -370.0f;

	this->reactorPad->setPositionY(LowY);
	this->reactorPad->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0.0f, HighY))),
		EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0.0f, LowY))),
		nullptr
	)));;

	this->reactorCore->setPositionY(-16.0f);
	this->reactorCore->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(1.75f, Vec2(0.0f, 16.0f))),
		EaseSineInOut::create(MoveTo::create(1.75f, Vec2(0.0f, -16.0f))),
		nullptr
	)));;
}

void ReactorCore::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);
}

void ReactorCore::updateCracks()
{
	this->reactorCasePristine->setVisible(false);
	this->reactorCaseCracked1->setVisible(false);
	this->reactorCaseCracked2->setVisible(false);
	this->reactorCaseCracked3->setVisible(false);
	this->reactorCaseCracked4->setVisible(false);

	switch(this->crackedLevel)
	{
		case 0:
		{
			this->reactorCasePristine->setVisible(true);
			break;
		}
		case 1:
		{
			this->reactorCaseCracked1->setVisible(true);
			break;
		}
		case 2:
		{
			this->reactorCaseCracked2->setVisible(true);
			break;
		}
		case 3:
		{
			this->reactorCaseCracked3->setVisible(true);
			break;
		}
		default:
		{
			this->reactorCaseCracked4->setVisible(true);
			PlatformerEvents::TriggerPlayCutscene(PlatformerEvents::CutsceneArgs(Cutscene::Credits));
			break;
		}
	}
}
