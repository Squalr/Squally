#include "RorHelpMenu.h"

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

#include "Strings/Hexus/CardDescriptionsLong/ShiftRightCircular.h"

using namespace cocos2d;

RorHelpMenu* RorHelpMenu::create()
{
	RorHelpMenu* instance = new RorHelpMenu();

	instance->autorelease();

	return instance;
}

RorHelpMenu::RorHelpMenu()
{
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_CardDescriptionsLong_ShiftRightCircular::create(), Size(1200.0f, 0.0f));
	this->rorCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular));
	this->previewCard = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight);
	this->attackFrame = Sprite::create(HexusResources::HelperTextFrame);
	this->animatedLabelValue = ConstantString::create();
	this->animatedLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelValue);

	this->description->enableOutline(Color4B::BLACK, 2);
	this->description->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->rorCard->setScale(1.0f);
	this->animatedLabel->enableOutline(Color4B::BLACK, 3);

	this->rorCard->reveal();
	this->rorCard->disableInteraction();
	this->previewCard->autoCard->setCardScale(0.6f);

	this->addChild(this->description);
	this->addChild(this->rorCard);
	this->addChild(this->previewCard);
	this->addChild(this->attackFrame);
	this->addChild(this->animatedLabel);
}

RorHelpMenu::~RorHelpMenu()
{
}

void RorHelpMenu::onEnter()
{
	super::onEnter();
}

void RorHelpMenu::initializePositions()
{
	super::initializePositions();

	this->description->setPosition(Vec2(-1234 / 2.0f + 16.0f, 420.0f));
	this->attackFrame->setPosition(Vec2(0.0f, -160.0f));
	this->animatedLabel->setPosition(Vec2(0.0f, -160.0f));
	this->rorCard->setPosition(Vec2(356.0f, 0.0f));
}

void RorHelpMenu::initializeListeners()
{
	super::initializeListeners();

	this->previewCard->setToggleAttackCallback([=](){ this->resetAnimation(); });
}

void RorHelpMenu::open()
{
	this->setVisible(true);

	this->stopAllActions();
	this->runAnimationLoop();
}

void RorHelpMenu::resetAnimation()
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

void RorHelpMenu::runAnimationLoop()
{
	this->initializePositions();

	const Vec2 shiftDist = Vec2(44.0f, -72.0f);
	const float circularShiftDist = -176.0f;
	const float relocateX = shiftDist.x + 132.0f;
	const float relocateY = -115.0f;
	
	this->previewCard->autoCard->activeCard->clearOperations();
	
	this->animatedLabelValue->setString(HackUtils::toBinary4(this->previewCard->autoCard->getAttack()));
	cocos2d::Sprite* relocatedLetter = this->animatedLabel->getLetter(3);
	Vec2 originalPosition = relocatedLetter->getPosition();
	
	// Restore opacity altered by resetting animation
	this->animatedLabel->runAction(FadeTo::create(0.25f, 255));

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->animatedLabel->runAction(MoveTo::create(0.75f, Vec2(shiftDist.x, -160.0f)));
		}),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			this->previewCard->autoCard->activeCard->addOperation(Card::Operation(Card::Operation::OperationType::ROR, 0b0001));
			this->previewCard->autoCard->activeCard->cardEffects->runEffect(this->rorCard->getCorrespondingCardEffect());
			
			Vec2 currentPosition = relocatedLetter->getPosition();
			relocatedLetter->runAction(MoveTo::create(0.5f, currentPosition + Vec2(0.0f, shiftDist.y)));
		}),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			Vec2 currentPosition = relocatedLetter->getPosition();
			relocatedLetter->runAction(MoveTo::create(0.5f, currentPosition + Vec2(circularShiftDist, 0.0f)));
		}),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			Vec2 currentPosition = relocatedLetter->getPosition();
			relocatedLetter->runAction(MoveTo::create(0.5f, currentPosition - Vec2(0.0f, shiftDist.y)));
		}),
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			relocatedLetter->setPosition(originalPosition);
			this->runAnimationLoop();
		}),
		nullptr
	));
}
