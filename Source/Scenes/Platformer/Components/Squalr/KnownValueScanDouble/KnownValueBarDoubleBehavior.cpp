#include "KnownValueBarDoubleBehavior.h"

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
#include "Engine/Utils/StrUtils.h"
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

double KnownValueBarDoubleBehavior::Health = 0;
const double KnownValueBarDoubleBehavior::MaxHealth = 100;

const std::string KnownValueBarDoubleBehavior::MapKey = "squalr-known-double";

KnownValueBarDoubleBehavior* KnownValueBarDoubleBehavior::create(GameObject* owner)
{
	KnownValueBarDoubleBehavior* instance = new KnownValueBarDoubleBehavior(owner);

	instance->autorelease();

	return instance;
}

KnownValueBarDoubleBehavior::KnownValueBarDoubleBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->deltaString = ConstantString::create("+0");
	this->deltaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, this->deltaString);
	this->healthString = ConstantString::create("-");
	this->healthLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_XOverY::create()
		->setStringReplacementVariables({ this->healthString, ConstantString::create(StrUtils::doubleToString(KnownValueBarDoubleBehavior::MaxHealth, 1)) }));
	this->healthBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_FillRed));
	this->spellAura = Sprite::create(FXResources::Auras_RuneAura3);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Heal1);

	this->healthLabel->setTextColor(Color4B::WHITE);
	this->healthLabel->enableOutline(Color4B::BLACK, 3);

	// Gain text
	this->deltaLabel->setTextColor(Color4B::RED);
	this->deltaLabel->enableOutline(Color4B::BLACK, 3);
	this->spellAura->setOpacity(0);

	this->setHealth(KnownValueBarDoubleBehavior::MaxHealth);

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

KnownValueBarDoubleBehavior::~KnownValueBarDoubleBehavior()
{
}

void KnownValueBarDoubleBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SqualrEvents::EventProjectileCollided, [=](EventCustom* eventCustom)
	{
		this->addHealth(-double(RandomHelper::random_real(13.0, 17.0)));
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

void KnownValueBarDoubleBehavior::onDisable()
{
	super::onDisable();
}

void KnownValueBarDoubleBehavior::update(float dt)
{
	super::update(dt);

	this->healthBar->setProgress(float(KnownValueBarDoubleBehavior::Health / KnownValueBarDoubleBehavior::MaxHealth));
	this->healthString->setString(StrUtils::doubleToString(KnownValueBarDoubleBehavior::Health, 1));

	if (KnownValueBarDoubleBehavior::Health <= 0)
	{
		this->onDeath();
	}
}

void KnownValueBarDoubleBehavior::addHealth(double delta)
{
	if (KnownValueBarDoubleBehavior::Health <= 0)
	{
		return;
	}

	// Round to 1 digit
	delta = double(int(delta * 10.0 + 0.5) / 10.0);

	std::string deltaStr = StrUtils::doubleToString(delta, 1);
	
	this->deltaLabel->setTextColor(delta < 0 ? Color4B::RED : Color4B::GREEN);
	this->deltaString->setString(delta < 0 ? deltaStr : ("+" + deltaStr));
	this->deltaLabel->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(1.0f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	this->setHealth(KnownValueBarDoubleBehavior::Health + delta);
}

void KnownValueBarDoubleBehavior::setHealth(double newHealth)
{
	// Round to 1 digit
	newHealth = double(int(newHealth * 10.0 + 0.5) / 10.0);

	if (newHealth <= KnownValueBarDoubleBehavior::MaxHealth / 2)
	{
		this->entity->getAnimations()->playAnimation("AttackCast1", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(1.0f));
		
		this->addHealth(KnownValueBarDoubleBehavior::MaxHealth - KnownValueBarDoubleBehavior::Health);
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
		KnownValueBarDoubleBehavior::Health = newHealth;
	}
}

void KnownValueBarDoubleBehavior::onDeath()
{
	this->entity->getAnimations()->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete, SmartAnimationNode::AnimParams(1.0f));

	SaveManager::SaveGlobalData(TutorialSaveKeys::SaveKeyKnownValueDouble, Value(true));

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
