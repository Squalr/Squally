#include "StatsBars.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Huds/Components/EqDisplay.h"
#include "Scenes/Platformer/Level/Huds/Components/RuneBar.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

StatsBars* StatsBars::create(bool isFrameOnLeft, bool showExp)
{
	StatsBars* instance = new StatsBars(isFrameOnLeft, showExp);

	instance->autorelease();

	return instance;
}

StatsBars::StatsBars(bool isFrameOnLeft, bool showExp)
{
	const Vec2 fillOffset = Vec2(0.0f, 0.0f);

	this->isFrameOnLeft = isFrameOnLeft;
	this->showExp = showExp;
	this->target = nullptr;
	this->targetAsTimelineEntry = nullptr;
	this->frame = ClickableNode::create(this->showExp ? UIResources::HUD_FrameExtended : UIResources::HUD_Frame, this->showExp ? UIResources::HUD_FrameExtendedSelected : UIResources::HUD_FrameSelected);
	this->frameSelected = Sprite::create(UIResources::HUD_FrameSelected);
	this->emblemGlow = Sprite::create(UIResources::HUD_EmblemGlow);
	this->emblemNode = Node::create();
	this->healthBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_FillRed), fillOffset);
	this->manaBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_FillBlue), fillOffset);
	this->expBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_FillYellow), fillOffset);
	this->healthLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Common_XOverY::create());
	this->manaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Common_XOverY::create());
	this->expLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Common_XOverY::create());
	this->healthSprite = Sprite::create(UIResources::HUD_Heart);
	this->manaSprite = Sprite::create(UIResources::HUD_Pendant);
	this->expSprite = Sprite::create(UIResources::HUD_Star);
	this->healthNumerator = ConstantString::create("-");
	this->healthDenominator = ConstantString::create("-");
	this->manaNumerator = ConstantString::create("-");
	this->manaDenominator = ConstantString::create("-");
	this->expNumerator = ConstantString::create("-");
	this->expDenominator = ConstantString::create("-");
	this->eqDisplay = EqDisplay::create();
	this->runeBar = RuneBar::create();
	this->cachedExp = -1;
	this->cachedMaxExp = -1;
	this->cachedMana = -1;
	this->cachedMaxMana = -1;
	this->cachedHealth = -1;
	this->cachedMaxHealth = -1;

	this->healthLabel->setStringReplacementVariables({ this->healthNumerator, this->healthDenominator });
	this->manaLabel->setStringReplacementVariables({ this->manaNumerator, this->manaDenominator });
	this->expLabel->setStringReplacementVariables({ this->expNumerator, this->expDenominator });

	this->healthLabel->enableOutline(Color4B::BLACK, 2);
	this->manaLabel->enableOutline(Color4B::BLACK, 2);
	this->expLabel->enableOutline(Color4B::BLACK, 2);

	this->expBar->setVisible(this->showExp);
	this->expSprite->setVisible(this->showExp);
	this->runeBar->setVisible(false);
	this->eqDisplay->setVisible(false);
	this->frameSelected->setVisible(false);

	this->healthBar->addChild(this->healthLabel);
	this->manaBar->addChild(this->manaLabel);
	this->expBar->addChild(this->expLabel);
	this->addChild(this->frame);
	this->addChild(this->frameSelected);
	this->addChild(this->emblemGlow);
	this->addChild(this->emblemNode);
	this->addChild(this->healthBar);
	this->addChild(this->manaBar);
	this->addChild(this->manaSprite);
	this->addChild(this->expBar);
	this->addChild(this->expSprite);
	this->addChild(this->healthSprite);
	this->addChild(this->runeBar);
	this->addChild(this->eqDisplay);
}

StatsBars::~StatsBars()
{
}

void StatsBars::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void StatsBars::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float BarY = this->showExp ? 40.0f : 20.0f;
	const float TextOffset = 22.0f;
	const Vec2 SpriteOffset = Vec2(0.0f, 10.0f);
	const float BarInset = this->isFrameOnLeft ? 124.0f : -104.0f;
	const float ManaBarOffet = this->isFrameOnLeft ? 16.0f : -16.0f;
	const float ExpBarOffet = this->isFrameOnLeft ? 32.0f : -32.0f;
	const float EmblemOffset = this->isFrameOnLeft ? 64.0f : 112.0f;
	const float FrameOffset = this->isFrameOnLeft ? (this->frame->getContentSize().width / 2.0f) : 0.0f;
	const float EqOffset = this->isFrameOnLeft ? 64.0f : 112.0f;

	this->frame->setPosition(Vec2(FrameOffset, 0.0f));
	this->frameSelected->setPosition(Vec2(FrameOffset, 0.0f));
	this->emblemGlow->setPosition(Vec2(EmblemOffset, 16.0f));
	this->emblemNode->setPosition(Vec2(EmblemOffset, 16.0f));
	this->healthBar->setPosition(Vec2(BarInset + this->healthBar->getContentSize().width / 2.0f, BarY));
	this->healthSprite->setPosition(Vec2(BarInset + SpriteOffset.x, BarY + SpriteOffset.y));
	this->healthLabel->setPosition(Vec2(0.0f, TextOffset));
	this->manaBar->setPosition(Vec2(BarInset + this->manaBar->getContentSize().width / 2.0f + ManaBarOffet, BarY - 48.0f));
	this->manaSprite->setPosition(Vec2(BarInset + SpriteOffset.x + ManaBarOffet, BarY + SpriteOffset.y - 48.0f));
	this->manaLabel->setPosition(Vec2(0.0f, TextOffset));
	this->expBar->setPosition(Vec2(BarInset + this->expBar->getContentSize().width / 2.0f + ExpBarOffet, BarY - 96.0f));
	this->expSprite->setPosition(Vec2(BarInset + SpriteOffset.x + ExpBarOffet, BarY + SpriteOffset.y - 96.0f - 6.0f));
	this->expLabel->setPosition(Vec2(0.0f, TextOffset));
	this->runeBar->setPosition(306.0f, 36.0f);
	this->eqDisplay->setPosition(EqOffset, -32.0f);
}

void StatsBars::initializeListeners()
{
	super::initializeListeners();
}

void StatsBars::update(float dt)
{
	super::update(dt);

	if (this->target == nullptr)
	{
		return;
	}

	int health = this->target->getStateOrDefaultInt(StateKeys::Health, 0);
	int maxHealth = this->target->getStateOrDefaultInt(StateKeys::MaxHealth, 0);
	int mana = this->target->getStateOrDefaultInt(StateKeys::Mana, 0);
	int maxMana = this->target->getStateOrDefaultInt(StateKeys::MaxMana, 0);

	if (this->cachedHealth != health || this->cachedMaxHealth != maxHealth)
	{
		float healthPercent = MathUtils::clamp((float)health / (maxHealth == 0 ? 1.0f : (float)maxHealth), 0.0f, 1.0f);
		this->healthNumerator->setString(std::to_string(health));
		this->healthDenominator->setString(std::to_string(maxHealth));
		this->healthBar->setProgress(healthPercent);

		this->cachedHealth = health;
		this->cachedMaxHealth = maxHealth;
	}

	if (this->cachedMana != mana || this->cachedMaxMana != maxMana)
	{
		float manaPercent = MathUtils::clamp((float)mana / (maxMana == 0 ? 1.0f : (float)maxMana), 0.0f, 1.0f);
		this->manaNumerator->setString(std::to_string(mana));
		this->manaDenominator->setString(std::to_string(maxMana));
		this->manaBar->setProgress(manaPercent);

		this->cachedMana = mana;
		this->cachedMaxMana = maxMana;
	}

	if (this->showExp)
	{
		int exp = this->target->getStateOrDefaultInt(StateKeys::EqExperience, 0);
		int maxExp = StatsTables::getExpRequiredAtLevel(this->target);

		if (this->cachedExp != exp || this->cachedMaxExp != maxExp)
		{
			float expPercent = MathUtils::clamp((float)exp / (maxExp == 0 ? 1.0f : (float)maxExp), 0.0f, 1.0f);
			this->expNumerator->setString(std::to_string(exp));
			this->expDenominator->setString(std::to_string(maxExp));
			this->expBar->setProgress(expPercent);

			this->cachedExp = exp;
			this->cachedMaxExp = maxExp;
		}
	}
}

void StatsBars::setSelected(bool isSelected)
{
	this->frame->setVisible(!isSelected);
	this->frameSelected->setVisible(isSelected);
}

void StatsBars::setStatsTargetAsTimelineEntry(TimelineEntry* targetAsTimelineEntry)
{
	this->targetAsTimelineEntry = targetAsTimelineEntry;

	this->setStatsTarget(this->targetAsTimelineEntry == nullptr ? nullptr : this->targetAsTimelineEntry->getEntity());
}

TimelineEntry* StatsBars::getStatsTargetAsTimelineEntry()
{
	return this->targetAsTimelineEntry;
}

void StatsBars::setStatsTarget(PlatformerEntity* target)
{
	this->target = target;

	bool isSqually = dynamic_cast<Squally*>(target) != nullptr;
	bool isFriendly = dynamic_cast<PlatformerFriendly*>(target) != nullptr;

	this->eqDisplay->setStatsTarget(isFriendly ? target : nullptr);
	this->runeBar->setStatsTarget((!this->showExp && isSqually) ? target : nullptr);

	this->emblemNode->removeAllChildren();

	if (this->target != nullptr)
	{
		Sprite* emblem = Sprite::create(target->getEmblemResource());

		this->emblemNode->addChild(emblem);

		emblem->setFlippedX(!this->isFrameOnLeft);
	}
}

PlatformerEntity* StatsBars::getStatsTarget()
{
	return this->target;
}

void StatsBars::enableInteraction()
{
	this->frame->enableInteraction();
}

void StatsBars::disableInteraction()
{
	this->frame->disableInteraction();
}

void StatsBars::setClickCallback(std::function<void(PlatformerEntity*)> onClickCallback)
{
	if (onClickCallback == nullptr)
	{
		this->frame->setMouseClickCallback(nullptr);
	}
	else
	{
		this->frame->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
		{
			onClickCallback(this->target);
		});
	}
}
