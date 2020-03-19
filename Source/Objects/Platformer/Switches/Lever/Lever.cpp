#include "Lever.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string Lever::MapKey = "lever";

Lever* Lever::create(ValueMap& properties)
{
	Lever* instance = new Lever(properties);

	instance->autorelease();

	return instance;
}

Lever::Lever(ValueMap& properties) : super(properties, InteractObject::InteractType::Input, Size(177.0f, 205.0f), Vec2::ZERO)
{
	this->lever = SmartAnimationNode::create(ObjectResources::Switches_Lever_Animations);
	this->leverSound = WorldSound::create(SoundResources::Cipher_GearTurn);
	this->canPull = true;

	this->lever->setPositionY(-GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat() / 2.0f);

	this->addChild(this->lever);
	this->addChild(this->leverSound);
}

Lever::~Lever()
{
}

void Lever::initializePositions()
{
	super::initializePositions();
}

void Lever::initializeListeners()
{
	super::initializeListeners();
}

void Lever::onInteract()
{
	super::onInteract();

	if (!this->canPull)
	{
		return;
	}

	this->canPull = false;
	this->lever->clearAnimationPriority();
	this->leverSound->play();
	
	this->lever->playAnimation("PullBack", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
	{
		this->broadcastMapEvent(this->getSendEvent(), ValueMap());
		
		this->lever->clearAnimationPriority();
		this->lever->playAnimation("Reset", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
		{
			this->canPull = true;
			this->lever->clearAnimationPriority();
			this->lever->playAnimation();
		});
	});
}
