#include "UnknownValueBarBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/SqualrEvents.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

int UnknownValueBarBehavior::Health = 0;
const int UnknownValueBarBehavior::MaxHealth = 58;

const std::string UnknownValueBarBehavior::MapKey = "squalr-unknown-int";

UnknownValueBarBehavior* UnknownValueBarBehavior::create(GameObject* owner)
{
	UnknownValueBarBehavior* instance = new UnknownValueBarBehavior(owner);

	instance->autorelease();

	return instance;
}

UnknownValueBarBehavior::UnknownValueBarBehavior(GameObject* owner) : super(owner)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
	this->deltaString = ConstantString::create("+0");
	this->deltaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, deltaString);
	this->healthBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_HPBarFill));
	this->spellAura = Sprite::create(FXResources::Auras_RuneAura3);
	this->healSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Heal1);

	// Gain text
	this->deltaLabel->setTextColor(Color4B::RED);
	this->deltaLabel->enableOutline(Color4B::BLACK, 3);
	this->spellAura->setOpacity(0);

	this->setHealth(UnknownValueBarBehavior::MaxHealth);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->spellAura);
	this->addChild(this->healthBar);
	this->addChild(this->deltaLabel);
	this->addChild(this->healSound);
}

UnknownValueBarBehavior::~UnknownValueBarBehavior()
{
}

void UnknownValueBarBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SqualrEvents::EventFireballCollided, [=](EventCustom* eventCustom)
	{
		this->addHealth(-RandomHelper::random_int(6, 9));
	}));

	this->deltaLabel->setOpacity(0);

	const Vec2 entityCenter = this->entity->getEntityCenterPoint();
	const float offetY =  this->entity->getEntitySize().height / 2.0f + 96.0f;

	this->spellAura->setPosition(entityCenter + Vec2(0.0f, 32.0f));
	this->deltaLabel->setPosition(entityCenter + Vec2(0.0f, offetY + 48.0f));
	this->healthBar->setPosition(entityCenter + Vec2(0.0f, offetY));
}

void UnknownValueBarBehavior::onDisable()
{
	super::onDisable();
}

void UnknownValueBarBehavior::update(float dt)
{
	super::update(dt);

	this->healthBar->setProgress(float(UnknownValueBarBehavior::Health) / float(UnknownValueBarBehavior::MaxHealth));

	if (UnknownValueBarBehavior::Health <= 0)
	{
		this->onDeath();
	}
}

void UnknownValueBarBehavior::addHealth(int delta)
{
	if (UnknownValueBarBehavior::Health <= 0)
	{
		return;
	}
	
	this->deltaLabel->setTextColor(delta < 0 ? Color4B::RED : Color4B::GREEN);
	this->deltaString->setString(delta < 0 ? std::to_string(delta) : ("+" + std::to_string(delta)));
	this->deltaLabel->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(1.0f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	this->setHealth(UnknownValueBarBehavior::Health + delta);
}

void UnknownValueBarBehavior::setHealth(int newHealth)
{
	if (newHealth <= UnknownValueBarBehavior::MaxHealth / 2)
	{
		this->entity->getAnimations()->playAnimation("AttackCastSpell1", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(1.0f));
		
		this->addHealth(UnknownValueBarBehavior::MaxHealth - UnknownValueBarBehavior::Health);
		this->spellAura->runAction(Sequence::create(
			FadeTo::create(0.25f, 255),
			DelayTime::create(1.0f),
			FadeTo::create(0.25f, 0),
			nullptr
		));

		this->healSound->play(false, 0.25f);
	}
	else
	{
		UnknownValueBarBehavior::Health = newHealth;
	}
}

void UnknownValueBarBehavior::onDeath()
{
	this->entity->getAnimations()->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete, SmartAnimationNode::AnimParams(1.0f));
}
