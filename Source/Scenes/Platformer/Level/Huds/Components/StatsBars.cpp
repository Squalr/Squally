#include "StatsBars.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ProgressBar.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Huds/Components/EqDisplay.h"
#include "Scenes/Platformer/Level/Huds/Components/RuneBar.h"

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
	this->frame = Sprite::create(UIResources::HUD_Frame);
	this->emblemGlow = Sprite::create(UIResources::HUD_EmblemGlow);
	this->emblemNode = Node::create();
	this->healthBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_HPBarFill), fillOffset);
	this->manaBar = ProgressBar::create(Sprite::create(UIResources::HUD_StatFrame), Sprite::create(UIResources::HUD_MPBarFill), fillOffset);
	this->healthLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Generics_XOverY::create());
	this->manaLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Generics_XOverY::create());
	this->healthSprite = Sprite::create(UIResources::HUD_Heart);
	this->manaSprite = Sprite::create(UIResources::HUD_Pendant);
	this->healthNumerator = ConstantString::create("-");
	this->healthDenominator = ConstantString::create("-");
	this->manaNumerator = ConstantString::create("-");
	this->manaDenominator = ConstantString::create("-");
	this->eqDisplay = EqDisplay::create();
	this->runeBar = RuneBar::create();

	this->healthLabel->setStringReplacementVariables({ this->healthNumerator, this->healthDenominator });
	this->manaLabel->setStringReplacementVariables({ this->manaNumerator, this->manaDenominator });

	this->healthLabel->enableOutline(Color4B::BLACK, 2);
	this->manaLabel->enableOutline(Color4B::BLACK, 2);

	this->runeBar->setVisible(false);
	this->eqDisplay->setVisible(false);

	this->healthBar->addChild(this->healthLabel);
	this->manaBar->addChild(this->manaLabel);
	this->addChild(this->frame);
	this->addChild(this->emblemGlow);
	this->addChild(this->emblemNode);
	this->addChild(this->healthBar);
	this->addChild(this->manaBar);
	this->addChild(this->manaSprite);
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

	const float barY = 20.0f;
	const Vec2 spriteOffset = Vec2(0.0f, 10.0f);
	float barInset = this->isFrameOnLeft ? 124.0f : -104.0f;
	float manaBarOffet = this->isFrameOnLeft ? 16.0f : -16.0f;
	float emblemOffset = this->isFrameOnLeft ? 64.0f : 112.0f;
	float frameOffset = this->isFrameOnLeft ? (this->frame->getContentSize().width / 2.0f) : 0.0f;
	float eqOffset = this->isFrameOnLeft ? 64.0f : 112.0f;

	this->frame->setPosition(Vec2(frameOffset, 0.0f));
	this->emblemGlow->setPosition(Vec2(emblemOffset, 16.0f));
	this->emblemNode->setPosition(Vec2(emblemOffset, 16.0f));
	this->healthBar->setPosition(Vec2(barInset + this->healthBar->getContentSize().width / 2.0f, barY));
	this->healthSprite->setPosition(Vec2(barInset + spriteOffset.x, barY + spriteOffset.y));
	this->healthLabel->setPosition(Vec2(0.0f, 22.0f));
	this->manaBar->setPosition(Vec2(barInset + this->manaBar->getContentSize().width / 2.0f + manaBarOffet, barY - 48.0f));
	this->manaSprite->setPosition(Vec2(barInset + spriteOffset.x + manaBarOffet, barY + spriteOffset.y - 48.0f));
	this->manaLabel->setPosition(Vec2(0.0f, 22.0f));
	this->runeBar->setPosition(306.0f, 36.0f);
	this->eqDisplay->setPosition(eqOffset, -32.0f);
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

	bool isSqually = dynamic_cast<Squally*>(target) != nullptr;

	this->eqDisplay->setStatsTarget(isSqually ? static_cast<Squally*>(target) : nullptr);
	this->runeBar->setStatsTarget(isSqually ? static_cast<Squally*>(target) : nullptr);

	this->emblemNode->removeAllChildren();

	if (this->target != nullptr)
	{
		Sprite* emblem = Sprite::create(target->getEmblemResource());

		this->emblemNode->addChild(emblem);

		emblem->setFlippedX(!this->isFrameOnLeft);
	}
}
