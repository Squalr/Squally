#include "StatsBars.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/UIResources.h"

#include "Strings/Generics/XOverY.h"

using namespace cocos2d;

StatsBars* StatsBars::create(bool isFrameOnLeft)
{
	StatsBars* instance = new StatsBars(isFrameOnLeft);

	instance->autorelease();

	return instance;
}

StatsBars::StatsBars(bool isFrameOnLeft)
{
	const Vec2 fillOffset = Vec2(0.0f, 0.0f);

	this->isFrameOnLeft = isFrameOnLeft;
	this->target = nullptr;
	this->statBackground = Sprite::create();
	this->frame = Sprite::create(UIResources::HUD_Frame);
	this->frameTop = Sprite::create(UIResources::HUD_FrameTop);
	this->healthBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_HPBarFill), fillOffset);
	this->manaBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_MPBarFill), fillOffset);
	this->healthLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Generics_XOverY::create());
	this->manaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Generics_XOverY::create());
	this->healthNumerator = ConstantString::create("-");
	this->healthDenominator = ConstantString::create("-");
	this->manaNumerator = ConstantString::create("-");
	this->manaDenominator = ConstantString::create("-");

	this->healthLabel->setStringReplacementVariables({ this->healthNumerator, this->healthDenominator });
	this->manaLabel->setStringReplacementVariables({ this->manaNumerator, this->manaDenominator });

	this->healthLabel->enableOutline(Color4B::BLACK, 2);
	this->manaLabel->enableOutline(Color4B::BLACK, 2);
	this->frame->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->frameTop->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->healthBar->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->manaBar->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->statBackground);
	this->healthBar->addChild(this->healthLabel);
	this->manaBar->addChild(this->manaLabel);
	this->addChild(this->frame);
	this->addChild(this->frameTop);
	this->addChild(this->healthBar);
	this->addChild(this->manaBar);
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

	float barInset = this->isFrameOnLeft ? 96.0f : 0.0f;
	float frameOffset = this->isFrameOnLeft ? 0.0f : (this->healthBar->getContentSize().width + 12.0f);

	this->statBackground->setPosition(Vec2(barInset + this->healthBar->getContentSize().width / 2.0f, -(this->healthBar->getContentSize().height + this->manaBar->getContentSize().height) / 2.0f));
	this->frame->setPosition(Vec2(frameOffset, -this->healthBar->getContentSize().height));
	this->frameTop->setPosition(Vec2(frameOffset, -this->healthBar->getContentSize().height));
	this->healthBar->setPosition(Vec2(barInset + this->healthBar->getContentSize().width / 2.0f, 0.0f));
	this->manaBar->setPosition(Vec2(barInset + this->manaBar->getContentSize().width / 2.0f, -this->healthBar->getContentSize().height));
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

	int health = this->target->getHealth();
	int maxHealth = this->target->getMaxHealth();
	float healthPercent = MathUtils::clamp((float)health / (maxHealth == 0 ? 1.0f : (float)maxHealth), 0.0f, 1.0f);
	this->healthNumerator->setString(std::to_string(health));
	this->healthDenominator->setString(std::to_string(maxHealth));

	this->healthBar->setProgress(healthPercent);

	int mana = this->target->getMana();
	int maxMana = this->target->getMaxMana();
	float manaPercent = MathUtils::clamp((float)mana / (maxMana == 0 ? 1.0f : (float)maxMana), 0.0f, 1.0f);
	this->manaNumerator->setString(std::to_string(mana));
	this->manaDenominator->setString(std::to_string(maxMana));

	this->manaBar->setProgress(manaPercent);
}

void StatsBars::setStatsTarget(PlatformerEntity* target)
{
	this->target = target;

	this->frame->removeAllChildren();

	if (this->target != nullptr)
	{
		Sprite* emblem = Sprite::create(target->getEmblemResource());

		this->frame->addChild(emblem);

		emblem->setFlippedX(!this->isFrameOnLeft);
		emblem->setPosition(this->frame->getContentSize() / 2.0f);
	}
}
