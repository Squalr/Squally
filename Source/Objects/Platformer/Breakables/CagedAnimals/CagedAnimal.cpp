#include "CagedAnimal.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Events/NotificationEvents.h"

#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CagedAnimal::CagedAnimal(ValueMap& properties, std::string saveKey) : super(properties, 1)
{
	this->animalNode = Node::create();
	this->shineFx = Sprite::create(ObjectResources::Collectables_Animals_CollectShine);
	this->saveKey = saveKey;
	this->alreadyCollected = false;

	this->shineFx->setOpacity(0);

	this->animalNode->addChild(this->shineFx);
	this->contentNode->addChild(this->animalNode);
}

CagedAnimal::~CagedAnimal()
{
}

void CagedAnimal::onEnter()
{
	super::onEnter();

	if (SaveManager::getProfileDataOrDefault(this->saveKey, Value(false)).asBool())
	{
		this->alreadyCollected = true;
		this->animalNode->setVisible(false);
		this->shineFx->setVisible(false);
	}
}

void CagedAnimal::initializePositions()
{
	super::initializePositions();

	this->animalNode->setPosition(Vec2(0.0f, 0.0f));
}

void CagedAnimal::initializeListeners()
{
	super::initializeListeners();
}

Vec2 CagedAnimal::getButtonOffset()
{
	return Vec2(0.0f, 96.0f);
}

void CagedAnimal::onBreak()
{
	super::onBreak();

	if (this->alreadyCollected)
	{
		return;
	}

	SaveManager::SaveProfileData(this->saveKey, Value(true));

	NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
		Strings::Menus_Notifications_CreatureRescued::create(),
		this->getAnimalName(),
		this->getSpriteResource(),
		SoundResources::Notifications_NotificationGood1
	));

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		this,
		this->animalNode,
		ObjectEvents::SpawnMethod::TopMost,
		ObjectEvents::PositionMode::Retain,
		[&]()
		{
		},
		[&]()
		{
		}
	));

	this->shineFx->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(2.0f),
		FadeTo::create(0.25f, 0),
		nullptr
	));
	this->shineFx->runAction(Repeat::create(RotateBy::create(4.0f, 360.0f), 2));

	this->animalNode->runAction(Sequence::create(
		MoveBy::create(1.0f, Vec2(0.0f, 128.0f)),
		DelayTime::create(1.25f),
		FadeTo::create(0.25f, 0),
		nullptr
	));
}
