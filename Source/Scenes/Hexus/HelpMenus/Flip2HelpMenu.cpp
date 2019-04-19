#include "Flip2HelpMenu.h"

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

#include "Strings/Hexus/CardDescriptionsLong/Flip2.h"

using namespace cocos2d;

Flip2HelpMenu* Flip2HelpMenu::create()
{
	Flip2HelpMenu* instance = new Flip2HelpMenu();

	instance->autorelease();

	return instance;
}

Flip2HelpMenu::Flip2HelpMenu()
{
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_CardDescriptionsLong_Flip2::create(), Size(1200.0f, 0.0f));
	this->flip2Card = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Flip2));
	this->previewCard = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight);
	this->attackFrame = Sprite::create(HexusResources::HelperTextFrame);
	this->animatedLabelValue = ConstantString::create();
	this->animatedLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelValue);

	this->description->enableOutline(Color4B::BLACK, 2);
	this->description->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->flip2Card->setScale(1.0f);
	this->animatedLabel->enableOutline(Color4B::BLACK, 3);

	this->flip2Card->reveal();
	this->flip2Card->disableInteraction();
	this->previewCard->autoCard->setCardScale(0.6f);

	this->addChild(this->description);
	this->addChild(this->flip2Card);
	this->addChild(this->previewCard);
	this->addChild(this->attackFrame);
	this->addChild(this->animatedLabel);
}

Flip2HelpMenu::~Flip2HelpMenu()
{
}

void Flip2HelpMenu::onEnter()
{
	super::onEnter();
}

void Flip2HelpMenu::initializePositions()
{
	super::initializePositions();

	this->description->setPosition(Vec2(-1234 / 2.0f + 16.0f, 420.0f));
	this->attackFrame->setPosition(Vec2(0.0f, -160.0f));
	this->animatedLabel->setPosition(Vec2(0.0f, -160.0f));
	this->flip2Card->setPosition(Vec2(356.0f, 0.0f));
}

void Flip2HelpMenu::initializeListeners()
{
	super::initializeListeners();

	this->previewCard->setToggleCallback([=](){ this->resetAnimation(); });
}

void Flip2HelpMenu::open()
{
	this->setVisible(true);

	this->stopAllActions();
	this->runAnimationLoop();
}

void Flip2HelpMenu::resetAnimation()
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

void Flip2HelpMenu::runAnimationLoop()
{
	this->initializePositions();
	
	this->previewCard->autoCard->activeCard->clearOperations();
	
	this->animatedLabelValue->setString(HackUtils::toBinary4(this->previewCard->autoCard->getAttack()));
	this->animatedLabel->getLetter(2)->setColor(Color3B::WHITE);
	
	// Restore opacity altered by resetting animation
	this->animatedLabel->runAction(FadeTo::create(0.25f, 255));

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			this->previewCard->autoCard->activeCard->addOperation(Card::Operation(Card::Operation::OperationType::XOR, 0b0010));
			this->previewCard->autoCard->activeCard->cardEffects->runEffect(this->flip2Card->getCorrespondingCardEffect());
			this->animatedLabelValue->setString(HackUtils::toBinary4(this->previewCard->autoCard->activeCard->getAttack()));
			
			if (this->previewCard->autoCard->activeCard->getOriginalAttack() & 0b0010)
			{
				this->animatedLabel->getLetter(2)->setColor(Color3B::RED);
			}
			else
			{
				this->animatedLabel->getLetter(2)->setColor(Color3B::GREEN);
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
