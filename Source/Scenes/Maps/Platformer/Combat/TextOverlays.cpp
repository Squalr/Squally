#include "TextOverlays.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

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

	this->scheduleUpdate();
}

void TextOverlays::initializePositions()
{
	super::initializePositions();
}

void TextOverlays::initializeListeners()
{
	super::initializeListeners();


	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventDamageDelt, [=](EventCustom* args)
	{
		CombatEvents::DamageDeltArgs* damageArgs = static_cast<CombatEvents::DamageDeltArgs*>(args->getUserData());

		if (damageArgs != nullptr && damageArgs->target != nullptr)
		{
			ConstantString* amount = ConstantString::create(std::to_string(std::abs(damageArgs->delta)));
			LocalizedString* deltaString = damageArgs->delta < 0 ? (LocalizedString*)Strings::Generics_MinusConstant::create() : (LocalizedString*)Strings::Generics_PlusConstant::create();
			LocalizedLabel* deltaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M3, deltaString);

			deltaString->setStringReplacementVariables(amount);

			this->addChild(deltaLabel);

			deltaLabel->setPosition(damageArgs->target->getPosition() + Vec2(0.0f, damageArgs->target->getEntitySize().height + 16.0f));
			deltaLabel->enableOutline(Color4B::BLACK, 2);
			deltaLabel->setTextColor(damageArgs->delta < 0 ? Color4B::RED : Color4B::BLUE);

			deltaLabel->runAction(Sequence::create(
				FadeTo::create(2.0f, 0),
				nullptr
			));

			deltaLabel->runAction(Sequence::create(
				MoveTo::create(2.01f, deltaLabel->getPosition() + Vec2(0.0f, 128.0f)),
				CallFunc::create([=]()
				{
					this->removeChild(deltaLabel);
				}),
				nullptr
			));
		}
	}));
}

void TextOverlays::update(float dt)
{
	super::update(dt);
}
