#include "UnknownValueBarInt32Behavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/SqualrEvents.h"
#include "Menus/Tutorials/TutorialSelectMenu.h"
#include "Scenes/Tutorials/Save/TutorialSaveKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

int UnknownValueBarInt32Behavior::Health = 0;
const int UnknownValueBarInt32Behavior::MaxHealth = 58;

const std::string UnknownValueBarInt32Behavior::MapKey = "squalr-unknown-int";

UnknownValueBarInt32Behavior* UnknownValueBarInt32Behavior::create(GameObject* owner)
{
	UnknownValueBarInt32Behavior* instance = new UnknownValueBarInt32Behavior(owner);

	instance->autorelease();

	return instance;
}

UnknownValueBarInt32Behavior::UnknownValueBarInt32Behavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->deltaString = ConstantString::create("+0");
	this->deltaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, deltaString);
	this->healthBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_FillRed));
	this->spellAura = Sprite::create(FXResources::Auras_RuneAura3);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Heal1);

	// Gain text
	this->deltaLabel->setTextColor(Color4B::RED);
	this->deltaLabel->enableOutline(Color4B::BLACK, 3);
	this->spellAura->setOpacity(0);

	this->setHealth(UnknownValueBarInt32Behavior::MaxHealth);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->spellAura);
	this->addChild(this->healthBar);
	this->addChild(this->deltaLabel);
	this->addChild(this->healSound);
}

UnknownValueBarInt32Behavior::~UnknownValueBarInt32Behavior()
{
}

void UnknownValueBarInt32Behavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SqualrEvents::EventProjectileCollided, [=](EventCustom* eventCustom)
	{
		this->addHealth(-RandomHelper::random_int(6, 9));
	}));

	this->deltaLabel->setOpacity(0);

	const Vec2 entityCenter = this->entity->getEntityCenterPoint();
	const float offetY =  this->entity->getEntitySize().height / 2.0f + 96.0f;

	this->spellAura->setPosition(entityCenter + Vec2(0.0f, 32.0f));
	this->deltaLabel->setPosition(entityCenter + Vec2(0.0f, offetY + 48.0f));
	this->healthBar->setPosition(entityCenter + Vec2(0.0f, offetY));

	this->scheduleUpdate();
}

void UnknownValueBarInt32Behavior::onDisable()
{
	super::onDisable();
}

void UnknownValueBarInt32Behavior::update(float dt)
{
	super::update(dt);

	this->healthBar->setProgress(float(UnknownValueBarInt32Behavior::Health) / float(UnknownValueBarInt32Behavior::MaxHealth));

	if (UnknownValueBarInt32Behavior::Health <= 0)
	{
		this->onDeath();
	}
}

void UnknownValueBarInt32Behavior::addHealth(int delta)
{
	if (UnknownValueBarInt32Behavior::Health <= 0)
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

	this->setHealth(UnknownValueBarInt32Behavior::Health + delta);
}

void UnknownValueBarInt32Behavior::setHealth(int newHealth)
{
	if (newHealth <= UnknownValueBarInt32Behavior::MaxHealth / 2)
	{
		this->entity->getAnimations()->playAnimation("AttackCast1", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(1.0f));
		
		this->addHealth(UnknownValueBarInt32Behavior::MaxHealth - UnknownValueBarInt32Behavior::Health);
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
		UnknownValueBarInt32Behavior::Health = newHealth;
	}
}

void UnknownValueBarInt32Behavior::onDeath()
{
	this->entity->getAnimations()->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete, SmartAnimationNode::AnimParams(1.0f));
	
	SaveManager::SaveGlobalData(TutorialSaveKeys::SaveKeyUnknownValueInt, Value(true));

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
