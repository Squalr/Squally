#include "TextOverlays.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Strings/Combat/Blocked.h"
#include "Strings/Combat/Interrupted.h"
#include "Strings/Generics/MinusConstant.h"
#include "Strings/Generics/PlusConstant.h"

using namespace cocos2d;

TextOverlays* TextOverlays::create()
{
	TextOverlays* instance = new TextOverlays();

	instance->autorelease();

	return instance;
}

TextOverlays::TextOverlays()
{
}

void TextOverlays::onEnter()
{
	super::onEnter();
}

void TextOverlays::onExit()
{
	super::onExit();

	this->removeAllChildren();
}

void TextOverlays::initializePositions()
{
	super::initializePositions();
}

void TextOverlays::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventCastInterrupt, [=](EventCustom* eventCustom)
	{
		CombatEvents::CastInterruptArgs* args = static_cast<CombatEvents::CastInterruptArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target != nullptr)
		{
			LocalizedLabel* interruptLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Combat_Interrupted::create());

			interruptLabel->setTextColor(Color4B::ORANGE);
			interruptLabel->setPosition(Vec2(0.0f, 64.0f));

			this->runLabelOverEntity(args->target, interruptLabel);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventCastBlocked, [=](EventCustom* eventCustom)
	{
		CombatEvents::CastBlockedArgs* args = static_cast<CombatEvents::CastBlockedArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target != nullptr)
		{
			LocalizedLabel* blockedLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Combat_Blocked::create());

			blockedLabel->setTextColor(Color4B::ORANGE);
			blockedLabel->setPosition(Vec2(0.0f, 64.0f));

			this->runLabelOverEntity(args->target, blockedLabel);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventDamageOrHealingDelt, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingDeltArgs* args = static_cast<CombatEvents::DamageOrHealingDeltArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target != nullptr)
		{
			ConstantString* amount = ConstantString::create(std::to_string(std::abs(args->damageOrHealing)));
			LocalizedString* deltaString = args->damageOrHealing < 0 ? (LocalizedString*)Strings::Generics_MinusConstant::create() : (LocalizedString*)Strings::Generics_PlusConstant::create();
			LocalizedLabel* deltaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, deltaString);

			deltaLabel->setTextColor(args->damageOrHealing < 0 ? Color4B::RED : Color4B::GREEN);
			deltaString->setStringReplacementVariables(amount);

			this->runLabelOverEntity(args->target, deltaLabel);
		}
	}));
}

void TextOverlays::update(float dt)
{
	super::update(dt);
}

void TextOverlays::runLabelOverEntity(PlatformerEntity* target, LocalizedLabel* label)
{
	this->addChild(label);

	static const float LabelDuration = 2.0f;

	Vec3 targetPosition = GameUtils::getWorldCoords3D(target);
	label->setPosition3D(label->getPosition3D() + targetPosition + Vec3(0.0f, target->getEntitySize().height + 16.0f, 0.0f));
	label->enableOutline(Color4B::BLACK, 2);

	label->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			label->runAction(FadeTo::create(LabelDuration, 0));
			label->runAction(MoveTo::create(LabelDuration, label->getPosition3D() + Vec3(0.0f, 128.0f, 0.0f)));
		}),
		DelayTime::create(LabelDuration + 0.5f),
		CallFunc::create([=]()
		{
			this->removeChild(label);
		}),
		nullptr
	));
}
