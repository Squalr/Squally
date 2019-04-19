#include "OrHelpMenu.h"

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

#include "Strings/Hexus/CardDescriptionsLong/LogicalOr.h"

using namespace cocos2d;

OrHelpMenu* OrHelpMenu::create()
{
	OrHelpMenu* instance = new OrHelpMenu();

	instance->autorelease();

	return instance;
}

OrHelpMenu::OrHelpMenu()
{
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_CardDescriptionsLong_LogicalOr::create(), Size(1200.0f, 0.0f));
	this->orCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr));
	this->previewCardA = ToggleCard::create(ToggleCard::ToggleMode::LeftRight);
	this->previewCardB = ToggleCard::create(ToggleCard::ToggleMode::LeftRight);
	this->attackFrameA = Sprite::create(HexusResources::HelperTextFrame);
	this->attackFrameB = Sprite::create(HexusResources::HelperTextFrame);
	this->attackFrameC = Sprite::create(HexusResources::HelperTextFrame);
	this->animatedLabelAValue = ConstantString::create();
	this->animatedLabelA = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelAValue);
	this->animatedLabelBValue = ConstantString::create();
	this->animatedLabelB = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelBValue);
	this->animatedLabelCValue = ConstantString::create();
	this->animatedLabelC = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelCValue);

	this->description->enableOutline(Color4B::BLACK, 2);
	this->description->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->orCard->setScale(1.0f);
	this->animatedLabelA->enableOutline(Color4B::BLACK, 3);
	this->animatedLabelB->enableOutline(Color4B::BLACK, 3);
	this->animatedLabelC->enableOutline(Color4B::BLACK, 3);

	this->orCard->reveal();
	this->orCard->disableInteraction();
	this->previewCardA->autoCard->setCardScale(0.6f);
	this->previewCardB->autoCard->setCardScale(0.6f);

	this->addChild(this->description);
	this->addChild(this->orCard);
	this->addChild(this->previewCardA);
	this->addChild(this->previewCardB);
	this->addChild(this->attackFrameA);
	this->addChild(this->attackFrameB);
	this->addChild(this->attackFrameC);
	this->addChild(this->animatedLabelA);
	this->addChild(this->animatedLabelB);
	this->addChild(this->animatedLabelC);
}

OrHelpMenu::~OrHelpMenu()
{
}

void OrHelpMenu::onEnter()
{
	super::onEnter();
}

void OrHelpMenu::initializePositions()
{
	super::initializePositions();

	const float offset = -64.0f;

	this->description->setPosition(Vec2(-1234 / 2.0f + 16.0f, 420.0f));
	this->attackFrameA->setPosition(Vec2(-196.0f, 144.0f + offset));
	this->attackFrameB->setPosition(Vec2(-196.0f, 0.0f + offset));
	this->attackFrameC->setPosition(Vec2(-196.0f, -144.0f + offset));
	this->animatedLabelA->setPosition(Vec2(-196.0f, 144.0f + offset));
	this->animatedLabelB->setPosition(Vec2(-196.0f, 0.0f + offset));
	this->animatedLabelC->setPosition(Vec2(-196.0f, -144.0f + offset));
	this->previewCardA->setPosition(Vec2(-448.0f, 144.0f + offset));
	this->previewCardB->setPosition(Vec2(64.0f, 0.0f + offset));
	this->orCard->setPosition(Vec2(356.0f, 0.0f));
}

void OrHelpMenu::initializeListeners()
{
	super::initializeListeners();

	this->previewCardA->setToggleCallback([=](){ this->resetAnimation(); });
	this->previewCardB->setToggleCallback([=](){ this->resetAnimation(); });
}

void OrHelpMenu::open()
{
	this->setVisible(true);

	this->stopAllActions();
	this->runAnimationLoop();
}

void OrHelpMenu::resetAnimation()
{
	this->stopAllActions();
	this->animatedLabelA->setOpacity(0);
	this->animatedLabelB->setOpacity(0);
	this->animatedLabelC->setOpacity(0);

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->runAnimationLoop();
		}),
		nullptr
	));
}

void OrHelpMenu::runAnimationLoop()
{
	this->initializePositions();
	
	this->previewCardB->autoCard->activeCard->clearOperations();
	
	this->animatedLabelAValue->setString(HackUtils::toBinary4(this->previewCardA->autoCard->getAttack()));
	this->animatedLabelBValue->setString(HackUtils::toBinary4(this->previewCardB->autoCard->getAttack()));
	this->animatedLabelCValue->setString(HackUtils::toBinary4(0));

	this->animatedLabelA->getLetter(0)->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelA->getLetter(1)->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelA->getLetter(2)->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelA->getLetter(3)->runAction(FadeTo::create(0.25f, 255));

	this->animatedLabelB->getLetter(0)->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelB->getLetter(1)->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelB->getLetter(2)->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelB->getLetter(3)->runAction(FadeTo::create(0.25f, 255));

	this->animatedLabelC->getLetter(0)->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelC->getLetter(1)->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelC->getLetter(2)->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelC->getLetter(3)->runAction(FadeTo::create(0.25f, 255));
	
	// Restore opacity altered by resetting animation
	this->animatedLabelA->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelB->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelC->runAction(FadeTo::create(0.25f, 255));

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			// Phase 1: Run card ord animation
			this->previewCardB->autoCard->activeCard->addOperation(Card::Operation(Card::Operation::OperationType::OR, this->previewCardA->autoCard->getAttack()));
			this->previewCardB->autoCard->activeCard->cardEffects->runEffect(this->orCard->getCorrespondingCardEffect());
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			// Phase 2, fade out all 0s
			for (int index = 0; index < 4; index++)
			{
				if (this->animatedLabelAValue->getString()[index] == '0')
				{
					this->animatedLabelA->getLetter(index)->runAction(FadeTo::create(0.25f, 0));
				}

				if (this->animatedLabelBValue->getString()[index] == '0')
				{
					this->animatedLabelB->getLetter(index)->runAction(FadeTo::create(0.25f, 0));
				}
			}
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			// Phase 3: move all 1s to their spot
			for (int index = 0; index < 4; index++)
			{
				if (this->animatedLabelAValue->getString()[index] == '1')
				{
					this->animatedLabelA->getLetter(index)->runAction(MoveBy::create(1.0f, Vec2(0.0f, -144.0f * 2.0f)));
				}

				if (this->animatedLabelBValue->getString()[index] == '1')
				{
					this->animatedLabelB->getLetter(index)->runAction(MoveBy::create(1.0f, Vec2(0.0f, -144.0f)));
				}

				if (this->animatedLabelAValue->getString()[index] == '1' || this->animatedLabelBValue->getString()[index] == '1')
				{
					this->animatedLabelC->getLetter(index)->runAction(FadeTo::create(0.75f, 0));
				}
			}
		}),
		DelayTime::create(2.5f),
		CallFunc::create([=]()
		{
			this->runAnimationLoop();
		}),
		nullptr
	));
}
