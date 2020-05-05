#include "KnownValueBarInt32Behavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Engine/Events/NavigationEvents.h"
#include "Events/SqualrEvents.h"
#include "Menus/Tutorials/TutorialSelectMenu.h"
#include "Scenes/Tutorials/Save/TutorialSaveKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

int KnownValueBarInt32Behavior::Health = 0;
const int KnownValueBarInt32Behavior::MaxHealth = 100;

const std::string KnownValueBarInt32Behavior::MapKey = "squalr-known-int";

KnownValueBarInt32Behavior* KnownValueBarInt32Behavior::create(GameObject* owner)
{
	KnownValueBarInt32Behavior* instance = new KnownValueBarInt32Behavior(owner);

	instance->autorelease();

	return instance;
}

KnownValueBarInt32Behavior::KnownValueBarInt32Behavior(GameObject* owner) : super(owner)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
	this->deltaString = ConstantString::create("+0");
	this->deltaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, this->deltaString);
	this->healthString = ConstantString::create("-");
	this->healthLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_XOverY::create()
		->setStringReplacementVariables({ this->healthString, ConstantString::create(std::to_string(KnownValueBarInt32Behavior::MaxHealth)) }));
	this->healthBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_FillRed));
	this->spellAura = Sprite::create(FXResources::Auras_RuneAura3);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Heal1);

	this->healthLabel->setTextColor(Color4B::WHITE);
	this->healthLabel->enableOutline(Color4B::BLACK, 3);

	// Gain text
	this->deltaLabel->setTextColor(Color4B::RED);
	this->deltaLabel->enableOutline(Color4B::BLACK, 3);
	this->spellAura->setOpacity(0);

	this->setHealth(KnownValueBarInt32Behavior::MaxHealth);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->spellAura);
	this->addChild(this->healthBar);
	this->addChild(this->healthLabel);
	this->addChild(this->deltaLabel);
	this->addChild(this->healSound);
}

KnownValueBarInt32Behavior::~KnownValueBarInt32Behavior()
{
}

void KnownValueBarInt32Behavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SqualrEvents::EventProjectileCollided, [=](EventCustom* eventCustom)
	{
		this->addHealth(-RandomHelper::random_int(13, 17));
	}));

	this->deltaLabel->setOpacity(0);

	const Vec2 entityCenter = this->entity->getEntityCenterPoint();
	const float offetY =  this->entity->getEntitySize().height / 2.0f + 24.0f;

	this->spellAura->setPosition(entityCenter + Vec2(0.0f, 32.0f));
	this->healthLabel->setPosition(entityCenter + Vec2(0.0f, offetY + 24.0f));
	this->deltaLabel->setPosition(entityCenter + Vec2(0.0f, offetY + 48.0f + 24.0f));
	this->healthBar->setPosition(entityCenter + Vec2(0.0f, offetY));

	this->scheduleUpdate();
}

void KnownValueBarInt32Behavior::onDisable()
{
	super::onDisable();
}

void KnownValueBarInt32Behavior::update(float dt)
{
	super::update(dt);

	this->healthBar->setProgress(float(KnownValueBarInt32Behavior::Health) / float(KnownValueBarInt32Behavior::MaxHealth));
	this->healthString->setString(std::to_string(KnownValueBarInt32Behavior::Health));

	if (KnownValueBarInt32Behavior::Health <= 0)
	{
		this->onDeath();
	}
}

void KnownValueBarInt32Behavior::addHealth(int delta)
{
	if (KnownValueBarInt32Behavior::Health <= 0)
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

	this->setHealth(KnownValueBarInt32Behavior::Health + delta);
}

void KnownValueBarInt32Behavior::setHealth(int newHealth)
{
	if (newHealth <= KnownValueBarInt32Behavior::MaxHealth / 2)
	{
		this->entity->getAnimations()->playAnimation("AttackCast1", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(1.0f));
		
		this->addHealth(KnownValueBarInt32Behavior::MaxHealth - KnownValueBarInt32Behavior::Health);
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
		KnownValueBarInt32Behavior::Health = newHealth;
	}
}

void KnownValueBarInt32Behavior::onDeath()
{
	this->entity->getAnimations()->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete, SmartAnimationNode::AnimParams(1.0f));

	SaveManager::saveGlobalData(TutorialSaveKeys::SaveKeyKnownValueInt, Value(true));

	this->runAction(Sequence::create(
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
			{
				return TutorialSelectMenu::getInstance();
			}));
		}),
		nullptr
	));
}
