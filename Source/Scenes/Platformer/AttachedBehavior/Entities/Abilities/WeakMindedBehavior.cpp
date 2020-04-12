#include "WeakMindedBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackActivatedAbility.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/FXResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WeakMindedBehavior::MapKey = "weak-minded";

WeakMindedBehavior* WeakMindedBehavior::create(GameObject* owner)
{
	WeakMindedBehavior* instance = new WeakMindedBehavior(owner);

	instance->autorelease();

	return instance;
}

WeakMindedBehavior::WeakMindedBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->glowAnim = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->glowAnim = SmartAnimationSequenceNode::create();
		this->entity->addChild(this->glowAnim);
	}
}

WeakMindedBehavior::~WeakMindedBehavior()
{
}

void WeakMindedBehavior::onLoad()
{
	if (this->glowAnim != nullptr)
	{
		this->glowAnim->setPosition(this->entity->getCollisionOffset() + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f));
	}
	this->entity->registerHackAbility(HackActivatedAbility::create(
		"weak-minded",
		[=]()
		{
			this->onActivate();
		},[=]()
		{
			this->onDeactivate();
		},
		1,
		10.0f,
		HackableAttribute::HackBarColor::Purple,
		UIResources::Menus_Icons_Eye,
		Strings::Menus_Hacking_Abilities_WeakMinded::create(),
		nullptr,
		nullptr
	));
}

void WeakMindedBehavior::onDisable()
{
	super::onDisable();
}

void WeakMindedBehavior::onActivate()
{
	if (this->glowAnim != nullptr)
	{
		this->glowAnim->playAnimationRepeat(FXResources::WeakMinded_WeakMinded_0000, 0.06f);
	}

	if (this->entity != nullptr)
	{
		this->entity->setState(StateKeys::WeakMinded, Value(true));
	}
}

void WeakMindedBehavior::onDeactivate()
{
	if (this->glowAnim != nullptr)
	{
		this->glowAnim->stopAnimation();
	}

	if (this->entity != nullptr)
	{
		this->entity->setState(StateKeys::WeakMinded, Value(false));
	}
}
