#include "ShlHelpMenu.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/HackUtils.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardEffects.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/HelpMenus/AutoCard.h"
#include "Scenes/Hexus/HelpMenus/ToggleCard.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/CardDescriptionsLong/ShiftLeft.h"

using namespace cocos2d;

ShlHelpMenu* ShlHelpMenu::create()
{
	ShlHelpMenu* instance = new ShlHelpMenu();

	instance->autorelease();

	return instance;
}

ShlHelpMenu::ShlHelpMenu()
{
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_CardDescriptionsLong_ShiftLeft::create(), Size(1200.0f, 0.0f));
	this->rolCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft));
	this->previewCard = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight);
	this->attackFrame = Sprite::create(HexusResources::HelperTextFrame);
	this->animatedLabelValue = ConstantString::create();
	this->newZero = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, ConstantString::create("0"));
	this->animatedLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelValue);

	this->description->enableOutline(Color4B::BLACK, 2);
	this->description->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->rolCard->setScale(1.0f);
	this->newZero->enableOutline(Color4B::BLACK, 3);
	this->animatedLabel->enableOutline(Color4B::BLACK, 3);

	this->rolCard->reveal();
	this->rolCard->disableInteraction();
	this->previewCard->autoCard->setCardScale(0.6f);

	this->addChild(this->description);
	this->addChild(this->rolCard);
	this->addChild(this->previewCard);
	this->addChild(this->attackFrame);
	this->addChild(this->animatedLabel);
	this->addChild(this->newZero);
}

ShlHelpMenu::~ShlHelpMenu()
{
}

void ShlHelpMenu::onEnter()
{
	super::onEnter();

	this->newZero->getLetter(0)->setOpacity(0);
}

void ShlHelpMenu::initializePositions()
{
	super::initializePositions();

	this->description->setPosition(Vec2(-1234 / 2.0f + 16.0f, 420.0f));
	this->attackFrame->setPosition(Vec2(0.0f, -160.0f));
	this->animatedLabel->setPosition(Vec2(0.0f, -160.0f));
	this->newZero->setPosition(Vec2(0.0f, 0.0f));
	this->rolCard->setPosition(Vec2(356.0f, 0.0f));
}

void ShlHelpMenu::initializeListeners()
{
	super::initializeListeners();

	this->previewCard->setToggleAttackCallback([=](){ this->resetAnimation(); });
}

void ShlHelpMenu::open()
{
	this->setVisible(true);

	this->stopAllActions();
	this->runAnimationLoop();
}

void ShlHelpMenu::resetAnimation()
{
	this->stopAllActions();
	this->animatedLabel->setOpacity(0);
	this->newZero->setOpacity(0);

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->runAnimationLoop();
		}),
		nullptr
	));
}

void ShlHelpMenu::runAnimationLoop()
{
	this->initializePositions();

	const Vec2 travelDist = Vec2(-44.0f, -128.0f);
	const float newZeroX = travelDist.x + 132.0f;
	const float newZeroY = -115.0f;
	
	this->previewCard->autoCard->activeCard->clearOperations();
	
	this->animatedLabelValue->setString(HackUtils::toBinary4(this->previewCard->autoCard->getAttack()));
	this->animatedLabel->getLetter(0)->setColor(Color3B::WHITE);
	this->animatedLabel->getLetter(0)->setOpacity(255);
	this->newZero->getLetter(0)->setOpacity(0);
	
	// Restore opacity altered by resetting animation
	this->animatedLabel->runAction(FadeTo::create(0.25f, 255));
	this->newZero->runAction(FadeTo::create(0.25f, 255));

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->animatedLabel->runAction(MoveTo::create(0.75f, Vec2(travelDist.x, -160.0f)));
		}),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			this->newZero->getLetter(0)->setPosition(Vec2(newZeroX, newZeroY + travelDist.y));
			this->newZero->getLetter(0)->runAction(MoveTo::create(0.5f, Vec2(newZeroX, newZeroY)));
			this->newZero->getLetter(0)->runAction(FadeTo::create(0.5f, 255));
			this->animatedLabel->getLetter(0)->setColor(Color3B::RED);
		}),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			this->previewCard->autoCard->activeCard->addOperation(Card::Operation(Card::Operation::OperationType::SHL, 0b0001));
			this->previewCard->autoCard->activeCard->cardEffects->runEffect(this->rolCard->getCorrespondingCardEffect());

			if (this->previewCard->autoCard->activeCard->getOriginalAttack() >= 0b1000)
			{
				this->previewCard->autoCard->activeCard->runOverflowEffect();
			}
			
			Vec2 originalPosition = this->animatedLabel->getLetter(0)->getPosition();

			this->animatedLabel->getLetter(0)->runAction(FadeTo::create(0.25f, 0));
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			this->runAnimationLoop();
		}),
		nullptr
	));
}
