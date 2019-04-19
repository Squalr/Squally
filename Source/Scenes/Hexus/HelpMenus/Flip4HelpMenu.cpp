#include "Flip4HelpMenu.h"

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

#include "Strings/Hexus/CardDescriptionsLong/Flip4.h"

using namespace cocos2d;

Flip4HelpMenu* Flip4HelpMenu::create()
{
	Flip4HelpMenu* instance = new Flip4HelpMenu();

	instance->autorelease();

	return instance;
}

Flip4HelpMenu::Flip4HelpMenu()
{
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_CardDescriptionsLong_Flip4::create(), Size(1200.0f, 0.0f));
	this->flip4Card = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Flip4));
	this->previewCard = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight);
	this->attackFrame = Sprite::create(HexusResources::HelperTextFrame);
	this->animatedLabelValue = ConstantString::create();
	this->animatedLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelValue);

	this->description->enableOutline(Color4B::BLACK, 2);
	this->description->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->flip4Card->setScale(1.0f);
	this->animatedLabel->enableOutline(Color4B::BLACK, 3);

	this->flip4Card->reveal();
	this->flip4Card->disableInteraction();
	this->previewCard->autoCard->setCardScale(0.6f);

	this->addChild(this->description);
	this->addChild(this->flip4Card);
	this->addChild(this->previewCard);
	this->addChild(this->attackFrame);
	this->addChild(this->animatedLabel);
}

Flip4HelpMenu::~Flip4HelpMenu()
{
}

void Flip4HelpMenu::onEnter()
{
	super::onEnter();
}

void Flip4HelpMenu::initializePositions()
{
	super::initializePositions();

	this->description->setPosition(Vec2(-1234 / 2.0f + 16.0f, 420.0f));
	this->attackFrame->setPosition(Vec2(0.0f, -160.0f));
	this->animatedLabel->setPosition(Vec2(0.0f, -160.0f));
	this->flip4Card->setPosition(Vec2(356.0f, 0.0f));
}

void Flip4HelpMenu::initializeListeners()
{
	super::initializeListeners();

	this->previewCard->setToggleCallback([=](){ this->resetAnimation(); });
}

void Flip4HelpMenu::open()
{
	this->setVisible(true);

	this->stopAllActions();
	this->runAnimationLoop();
}

void Flip4HelpMenu::resetAnimation()
{
	this->stopAllActions();
	this->animatedLabel->setOpacity(0);

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->runAnimationLoop();
		}),
		nullptr
	));
}

void Flip4HelpMenu::runAnimationLoop()
{
	this->initializePositions();
	
	this->previewCard->autoCard->activeCard->clearOperations();
	
	this->animatedLabelValue->setString(HackUtils::toBinary4(this->previewCard->autoCard->getAttack()));
	this->animatedLabel->getLetter(0)->setColor(Color3B::WHITE);
	
	// Restore opacity altered by resetting animation
	this->animatedLabel->runAction(FadeTo::create(0.25f, 255));

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			this->previewCard->autoCard->activeCard->addOperation(Card::Operation(Card::Operation::OperationType::XOR, 0b1000));
			this->previewCard->autoCard->activeCard->cardEffects->runEffect(this->flip4Card->getCorrespondingCardEffect());
			this->animatedLabelValue->setString(HackUtils::toBinary4(this->previewCard->autoCard->activeCard->getAttack()));
			
			if (this->previewCard->autoCard->activeCard->getOriginalAttack() & 0b1000)
			{
				this->animatedLabel->getLetter(0)->setColor(Color3B::RED);
			}
			else
			{
				this->animatedLabel->getLetter(0)->setColor(Color3B::GREEN);
			}
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			this->runAnimationLoop();
		}),
		nullptr
	));
}
