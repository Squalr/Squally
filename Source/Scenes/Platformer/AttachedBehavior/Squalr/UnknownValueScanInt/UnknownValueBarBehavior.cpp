#include "UnknownValueBarBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/SqualrEvents.h"

#include "Resources/FXResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

int UnknownValueBarBehavior::Health = 0;
const int UnknownValueBarBehavior::MaxHealth = 78;

const std::string UnknownValueBarBehavior::MapKeyAttachedBehavior = "squalr-unknown-int";

UnknownValueBarBehavior* UnknownValueBarBehavior::create(GameObject* owner)
{
	UnknownValueBarBehavior* instance = new UnknownValueBarBehavior(owner);

	instance->autorelease();

	return instance;
}

UnknownValueBarBehavior::UnknownValueBarBehavior(GameObject* owner) : super(owner)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
	this->deltaString = Strings::Common_PlusConstant::create();
	this->deltaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, deltaString);
	this->healthBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_HPBarFill));
	this->spellAura = Sprite::create(FXResources::Auras_RuneAura3);

	// Gain text
	this->deltaLabel->setTextColor(Color4B::RED);
	this->deltaLabel->enableOutline(Color4B::BLACK, 2);
	this->spellAura->setOpacity(0);

	this->setHealth(UnknownValueBarBehavior::MaxHealth);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->spellAura);
	this->addChild(this->healthBar);
	this->addChild(this->deltaLabel);
}

UnknownValueBarBehavior::~UnknownValueBarBehavior()
{
}

void UnknownValueBarBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SqualrEvents::EventFireballCollided, [=](EventCustom* eventCustom)
	{
		this->addHealth(-RandomHelper::random_int(5, 9));
	}));

	this->deltaLabel->setOpacity(0);

	const Vec2 entityCenter = this->entity->getEntityCenterPoint();
	const float offetY =  this->entity->getEntitySize().height / 2.0f + 96.0f;

	this->deltaLabel->setPosition(entityCenter + Vec2(0.0f, offetY + 48.0f));
	this->healthBar->setPosition(entityCenter + Vec2(0.0f, offetY));
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
	this->setHealth(UnknownValueBarBehavior::Health + delta);
}

void UnknownValueBarBehavior::setHealth(int newHealth)
{
	UnknownValueBarBehavior::Health = newHealth;

	if (UnknownValueBarBehavior::Health <= UnknownValueBarBehavior::MaxHealth / 2)
	{
		this->entity->getAnimations()->playAnimation("AttackCastSpell1", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, 1.0f);

		this->spellAura->runAction(Sequence::create(
			FadeTo::create(0.25f, 255),
			DelayTime::create(1.0f),
			FadeTo::create(0.25f, 0),
			nullptr
		));
		
		this->runAction(Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create([=]()
			{
				this->setHealth(UnknownValueBarBehavior::MaxHealth);
			}),
			nullptr
		));
	}
}

void UnknownValueBarBehavior::onDeath()
{
}
