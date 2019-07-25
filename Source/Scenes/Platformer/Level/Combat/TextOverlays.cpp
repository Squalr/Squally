#include "TextOverlays.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/CombatEvents.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Blocked.h"
#include "Strings/Combat/Interrupted.h"
#include "Strings/Common/MinusConstant.h"
#include "Strings/Common/PlusConstant.h"

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

void TextOverlays::initializePositions()
{
	super::initializePositions();
}

void TextOverlays::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::BeforeSceneChangeEvent, [=](EventCustom* eventCustom)
	{
		this->removeAllChildren();
	}));

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
			LocalizedString* deltaString = args->damageOrHealing < 0 ? (LocalizedString*)Strings::Common_MinusConstant::create() : (LocalizedString*)Strings::Common_PlusConstant::create();
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

void TextOverlays::showExpBars(int expGain)
{
	static std::vector<int> currentTicks = std::vector<int>();
	int entityIndex = 0;

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerFriendly>([&](PlatformerFriendly* entity)
	{
		float startProgress = float(entity->getEqExperience()) / float(StatsTables::getExpRequiredAtLevel(entity->getEq()));
		bool didLevelUp = entity->addEqExperience(expGain);
		float endProgress = float(entity->getEqExperience()) / float(StatsTables::getExpRequiredAtLevel(entity->getEq()));

		const float fillDuration = 1.0f;
		const int updatesPerSecond = 60;
		const float interval = fillDuration / float(updatesPerSecond);
		const int ticks = int(fillDuration * float(updatesPerSecond));
		const float delay = 0.0f;

		while (currentTicks.size() <= entityIndex)
		{
			currentTicks.push_back(0);
		}

		currentTicks[entityIndex] = 0;

		ProgressBar* expProgressBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_ExpBarFill));

		if (!didLevelUp)
		{
			expProgressBar->setProgress(startProgress);

			expProgressBar->schedule([=](float dt)
			{
				float tickProgress = MathUtils::clamp(((float)currentTicks[entityIndex] / (float)ticks), 0.0f, 1.0f);

				expProgressBar->setProgress(startProgress + (endProgress - startProgress) * tickProgress);

				currentTicks[entityIndex]++;

			}, interval, ticks, delay, "EVENT_EXP_BAR_UPDATE");
		}
		else
		{
			this->runAction(Sequence::create(
				// Phase 1: Fill from start to max
				CallFunc::create([=]()
				{
					expProgressBar->setProgress(startProgress);

					expProgressBar->schedule([=](float dt)
					{
						float tickProgress = MathUtils::clamp(((float)currentTicks[entityIndex] / (float)ticks), 0.0f, 1.0f);

						expProgressBar->setProgress(startProgress + (1.0f - startProgress) * tickProgress);

						currentTicks[entityIndex]++;

					}, interval, ticks, delay, "EVENT_EXP_BAR_UPDATE");
				}),
				DelayTime::create(fillDuration + 0.1f),
				// Phase 2: Fill from 0 to end
				CallFunc::create([=]()
				{
					currentTicks[entityIndex] = 0;

					expProgressBar->schedule([=](float dt)
					{
						float tickProgress = MathUtils::clamp(((float)currentTicks[entityIndex] / (float)ticks), 0.0f, 1.0f);

						expProgressBar->setProgress(endProgress * tickProgress);

						currentTicks[entityIndex]++;

					}, interval, ticks, delay, "EVENT_EXP_BAR_UPDATE");
				}),
				nullptr
			));
		}

		// Gain text
		LocalizedString* deltaString = Strings::Common_PlusConstant::create();
		LocalizedLabel* deltaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, deltaString);

		deltaLabel->setTextColor(Color4B::YELLOW);
		deltaLabel->enableOutline(Color4B::BLACK, 2);
		deltaString->setStringReplacementVariables(ConstantString::create(std::to_string(expGain)));

		entity->getAnimations()->addChild(expProgressBar);
		entity->getAnimations()->addChild(deltaLabel);

		deltaLabel->setPosition(Vec2(0.0f, 208.0f));
		expProgressBar->setPosition(Vec2(0.0f, 160.0f));

		entityIndex++;
	}));
}

void TextOverlays::runLabelOverEntity(PlatformerEntity* target, LocalizedLabel* label)
{
	this->addChild(label);

	static const float LabelDuration = 2.0f;

	Vec2 targetPosition = GameUtils::getScreenBounds(target).origin;
	label->setPosition(label->getPosition() + targetPosition + Vec2(0.0f, target->getEntitySize().height + 16.0f));
	label->enableOutline(Color4B::BLACK, 2);

	label->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			label->runAction(FadeTo::create(LabelDuration, 0));
			label->runAction(MoveTo::create(LabelDuration, label->getPosition() + Vec2(0.0f, 128.0f)));
		}),
		DelayTime::create(LabelDuration + 0.5f),
		CallFunc::create([=]()
		{
			this->removeChild(label);
		}),
		nullptr
	));
}
