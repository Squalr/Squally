#include "MovHelpMenu.h"

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

#include "Strings/Hexus/CardDescriptionsLong/Mov.h"

using namespace cocos2d;

MovHelpMenu* MovHelpMenu::create()
{
	MovHelpMenu* instance = new MovHelpMenu();

	instance->autorelease();

	return instance;
}

MovHelpMenu::MovHelpMenu()
{
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_CardDescriptionsLong_Mov::create(), Size(1200.0f, 0.0f));
	this->movCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Mov));
	this->previewCardA = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight, ToggleCard::ToggleModeUpDown::BinDecHex);
	this->previewCardB = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight, ToggleCard::ToggleModeUpDown::BinDecHex);
	this->attackFrameA = Sprite::create(HexusResources::HelperTextFrame);
	this->attackFrameB = Sprite::create(HexusResources::HelperTextFrame);
	this->animatedLabelAValue = ConstantString::create();
	this->animatedLabelA = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelAValue);
	this->animatedLabelBValue = ConstantString::create();
	this->animatedLabelB = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelBValue);

	this->description->enableOutline(Color4B::BLACK, 2);
	this->description->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->movCard->setScale(1.0f);
	this->animatedLabelA->enableOutline(Color4B::BLACK, 3);
	this->animatedLabelB->enableOutline(Color4B::BLACK, 3);

	this->movCard->reveal();
	this->movCard->disableInteraction();
	this->previewCardA->autoCard->setCardScale(0.6f);
	this->previewCardB->autoCard->setCardScale(0.6f);

	this->previewCardA->autoCard->setAttack(5);
	this->previewCardB->autoCard->setAttack(3);

	this->addChild(this->description);
	this->addChild(this->movCard);
	this->addChild(this->previewCardA);
	this->addChild(this->previewCardB);
	this->addChild(this->attackFrameA);
	this->addChild(this->attackFrameB);
	this->addChild(this->animatedLabelA);
	this->addChild(this->animatedLabelB);
}

MovHelpMenu::~MovHelpMenu()
{
}

void MovHelpMenu::onEnter()
{
	super::onEnter();
}

void MovHelpMenu::initializePositions()
{
	super::initializePositions();

	const float offset = -96.0f;

	this->description->setPosition(Vec2(-1234 / 2.0f + 16.0f, 420.0f));
	this->attackFrameA->setPosition(Vec2(-196.0f, 144.0f + offset));
	this->attackFrameB->setPosition(Vec2(-196.0f, 0.0f + offset));
	this->animatedLabelA->setPosition(Vec2(-196.0f, 144.0f + offset));
	this->animatedLabelB->setPosition(Vec2(-196.0f, 0.0f + offset));
	this->previewCardA->setPosition(Vec2(-448.0f, 144.0f + offset));
	this->previewCardB->setPosition(Vec2(64.0f, 0.0f + offset));
	this->movCard->setPosition(Vec2(356.0f, 0.0f));
}

void MovHelpMenu::initializeListeners()
{
	super::initializeListeners();

	this->previewCardA->setToggleAttackCallback([=](){ this->resetAnimation(); });
	this->previewCardB->setToggleAttackCallback([=](){ this->resetAnimation(); });

	this->previewCardB->setToggleDisplayTypeCallback([=]()
	{
		this->previewCardA->setDisplayType(this->previewCardB->autoCard->getDisplayType(), false);
		this->resetAnimation();
	});

	this->previewCardA->setToggleDisplayTypeCallback([=]()
	{
		this->previewCardB->setDisplayType(this->previewCardA->autoCard->getDisplayType(), false);
		this->resetAnimation();
	});
}

void MovHelpMenu::open()
{
	this->setVisible(true);

	this->stopAllActions();
	this->runAnimationLoop();
}

void MovHelpMenu::resetAnimation()
{
	this->stopAllActions();
	this->animatedLabelA->setOpacity(0);
	this->animatedLabelB->setOpacity(0);

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->runAnimationLoop();
		}),
		nullptr
	));
}

void MovHelpMenu::runAnimationLoop()
{
	this->initializePositions();
	
	switch (this->previewCardA->autoCard->getDisplayType())
	{
		case AutoCard::DisplayType::Binary:
		{
			this->animatedLabelAValue->setString(HackUtils::toBinary4(this->previewCardA->autoCard->getAttack()));
			this->animatedLabelBValue->setString(HackUtils::toBinary4(this->previewCardB->autoCard->getAttack()));
			break;
		}
		case AutoCard::DisplayType::Decimal:
		{
			this->animatedLabelAValue->setString(std::to_string(this->previewCardA->autoCard->getAttack()));
			this->animatedLabelBValue->setString(std::to_string(this->previewCardB->autoCard->getAttack()));
			break;
		}
		case AutoCard::DisplayType::Hex:
		{
			this->animatedLabelAValue->setString(HackUtils::toHex(this->previewCardA->autoCard->getAttack()));
			this->animatedLabelBValue->setString(HackUtils::toHex(this->previewCardB->autoCard->getAttack()));
			break;
		}
	}

	this->previewCardB->autoCard->activeCard->clearOperations();
	
	// Restore opacity altered by resetting animation
	this->animatedLabelA->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelB->runAction(FadeTo::create(0.25f, 255));

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			// Phase 1: Run card mov animation
			this->previewCardB->autoCard->activeCard->addOperation(Card::Operation(Card::Operation::OperationType::MOV, this->previewCardA->autoCard->getAttack()));
			this->previewCardB->autoCard->activeCard->cardEffects->runEffect(this->movCard->getCorrespondingCardEffect());
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			// Phase 2: Move the top string to the bottom
			this->animatedLabelA->runAction(MoveBy::create(1.0f, Vec2(0.0f, -144.0f)));
			this->animatedLabelB->runAction(FadeTo::create(0.75f, 0));
		}),
		DelayTime::create(2.0f),
		CallFunc::create([=]()
		{
			this->runAnimationLoop();
		}),
		nullptr
	));
}
