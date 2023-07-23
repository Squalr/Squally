#include "Vanish.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Resources/FXResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

Vanish* Vanish::create(PlatformerEntity* caster)
{
	Vanish* instance = new Vanish(caster);

	instance->autorelease();

	return instance;
}

Vanish::Vanish(PlatformerEntity* caster)
	: super(caster, caster, UIResources::Menus_Icons_BookSpellsDark, AbilityType::Arcane, BuffData("vanish-skill"))
{
	this->aura = Sprite::create(FXResources::Auras_RuneAura3);

	this->aura->setColor(Color3B::PURPLE);

	this->addChild(this->aura);
}

Vanish::~Vanish()
{
}

void Vanish::onEnter()
{
	super::onEnter();

	this->aura->setOpacity(0);
	this->aura->runAction(Sequence::create(
		FadeTo::create(0.5f, 255),
		DelayTime::create(0.25f),
		FadeTo::create(0.5f, 0),
		CallFunc::create([=]()
		{
			CombatEvents::TriggerBeforeReturnToMap(CombatEvents::BeforeReturnToMapArgs(true));
			CombatEvents::TriggerReturnToMapRespawn();
		}),
		nullptr
	));
}
