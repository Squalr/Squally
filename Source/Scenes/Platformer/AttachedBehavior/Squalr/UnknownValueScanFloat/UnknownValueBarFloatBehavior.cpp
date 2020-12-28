#include "UnknownValueBarFloatBehavior.h"

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

float UnknownValueBarFloatBehavior::Health = 0;
const float UnknownValueBarFloatBehavior::MaxHealth = 72;

const std::string UnknownValueBarFloatBehavior::MapKey = "squalr-unknown-float";

UnknownValueBarFloatBehavior* UnknownValueBarFloatBehavior::create(GameObject* owner)
{
	UnknownValueBarFloatBehavior* instance = new UnknownValueBarFloatBehavior(owner);

	instance->autorelease();

	return instance;
}

UnknownValueBarFloatBehavior::UnknownValueBarFloatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->deltaString = ConstantString::create("+0");
	this->deltaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, this->deltaString);
	this->healthBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_FillRed));
	this->spellAura = Sprite::create(FXResources::Auras_RuneAura3);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Heal1);

	// Gain text
	this->deltaLabel->setTextColor(Color4B::RED);
	this->deltaLabel->enableOutline(Color4B::BLACK, 3);
	this->spellAura->setOpacity(0);

	this->setHealth(UnknownValueBarFloatBehavior::MaxHealth);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->spellAura);
	this->addChild(this->healthBar);
	this->addChild(this->deltaLabel);
	this->addChild(this->healSound);
}

UnknownValueBarFloatBehavior::~UnknownValueBarFloatBehavior()
{
}

void UnknownValueBarFloatBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SqualrEvents::EventProjectileCollided, [=](EventCustom* eventCustom)
	{
		this->addHealth(-float(RandomHelper::random_real(8.0, 13.0)));
	}));

	this->deltaLabel->setOpacity(0);

	const Vec2 entityCenter = this->entity->getEntityCenterPoint();
	const float offetY =  this->entity->getEntitySize().height / 2.0f + 24.0f;

	this->spellAura->setPosition(entityCenter + Vec2(0.0f, 32.0f));
	this->deltaLabel->setPosition(entityCenter + Vec2(0.0f, offetY + 48.0f + 24.0f));
	this->healthBar->setPosition(entityCenter + Vec2(0.0f, offetY));

	this->scheduleUpdate();
}

void UnknownValueBarFloatBehavior::onDisable()
{
	super::onDisable();
}

void UnknownValueBarFloatBehavior::update(float dt)
{
	super::update(dt);

	this->healthBar->setProgress(float(UnknownValueBarFloatBehavior::Health) / float(UnknownValueBarFloatBehavior::MaxHealth));

	if (UnknownValueBarFloatBehavior::Health <= 0)
	{
		this->onDeath();
	}
}

void UnknownValueBarFloatBehavior::addHealth(float delta)
{
	if (UnknownValueBarFloatBehavior::Health <= 0)
	{
		return;
	}

	// Round to 1 digit
	delta = float(int(delta * 10.0f + 0.5f) / 10.0f);

	std::string deltaStr = StrUtils::floatToString(delta, 1);
	
	this->deltaLabel->setTextColor(delta < 0 ? Color4B::RED : Color4B::GREEN);
	this->deltaString->setString(delta < 0 ? deltaStr : ("+" + deltaStr));
	this->deltaLabel->runAction(Sequence::create(
		FadeTo::create(0.25f, 255),
		DelayTime::create(1.0f),
		FadeTo::create(0.25f, 0),
		nullptr
	));

	this->setHealth(UnknownValueBarFloatBehavior::Health + delta);
}

void UnknownValueBarFloatBehavior::setHealth(float newHealth)
{
	// Round to 1 digit
	newHealth = float(int(newHealth * 10.0f + 0.5f) / 10.0f);

	if (newHealth <= UnknownValueBarFloatBehavior::MaxHealth / 2)
	{
		this->entity->getAnimations()->playAnimation("AttackCast1", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(1.0f));
		
		this->addHealth(UnknownValueBarFloatBehavior::MaxHealth - UnknownValueBarFloatBehavior::Health);
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
		UnknownValueBarFloatBehavior::Health = newHealth;
	}
}

void UnknownValueBarFloatBehavior::onDeath()
{
	this->entity->getAnimations()->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete, SmartAnimationNode::AnimParams(1.0f));

	SaveManager::SaveGlobalData(TutorialSaveKeys::SaveKeyUnknownValueFloat, Value(true));

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
