#include "AddHelpMenu.h"

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

#include "Strings/Hexus/CardDescriptionsLong/Addition.h"
#include "Strings/Hexus/Cards/Effects/Overflow.h"

using namespace cocos2d;

AddHelpMenu* AddHelpMenu::create()
{
	AddHelpMenu* instance = new AddHelpMenu();

	instance->autorelease();

	return instance;
}

AddHelpMenu::AddHelpMenu()
{
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_CardDescriptionsLong_Addition::create(), Size(1200.0f, 0.0f));
	this->addCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Addition));
	this->previewCardA = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight, ToggleCard::ToggleModeUpDown::BinDec);
	this->previewCardB = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight, ToggleCard::ToggleModeUpDown::BinDec);
	this->attackFrameA = Sprite::create(HexusResources::HelperTextFrame);
	this->attackFrameB = Sprite::create(HexusResources::HelperTextFrame);
	this->attackFrameC = Sprite::create(HexusResources::HelperTextFrame);
	this->animatedLabelAValue = ConstantString::create();
	this->animatedLabelA = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelAValue);
	this->animatedLabelBValue = ConstantString::create();
	this->animatedLabelB = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelBValue);
	this->animatedLabelCValue = ConstantString::create();
	this->animatedLabelC = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->animatedLabelCValue);
	this->carryLabelValue = ConstantString::create();
	this->carryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M1, this->carryLabelValue);
	this->decimalOverflowSubtraction = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M2, ConstantString::create("-16"));

	this->description->enableOutline(Color4B::BLACK, 2);
	this->description->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->addCard->setScale(1.0f);
	this->animatedLabelA->enableOutline(Color4B::BLACK, 3);
	this->animatedLabelB->enableOutline(Color4B::BLACK, 3);
	this->animatedLabelC->enableOutline(Color4B::BLACK, 3);
	this->carryLabel->enableOutline(Color4B::BLACK, 3);
	this->decimalOverflowSubtraction->enableOutline(Color4B::BLACK, 3);
	this->decimalOverflowSubtraction->setColor(Color3B::RED);

	this->addCard->reveal();
	this->addCard->disableInteraction();
	this->previewCardA->autoCard->setCardScale(0.6f);
	this->previewCardB->autoCard->setCardScale(0.6f);
	this->previewCardA->autoCard->setDisplayType(AutoCard::DisplayType::Decimal);
	this->previewCardB->autoCard->setDisplayType(AutoCard::DisplayType::Decimal);

	this->previewCardA->autoCard->setAttack(5);
	this->previewCardB->autoCard->setAttack(3);

	this->addChild(this->description);
	this->addChild(this->addCard);
	this->addChild(this->previewCardA);
	this->addChild(this->previewCardB);
	this->addChild(this->attackFrameA);
	this->addChild(this->attackFrameB);
	this->addChild(this->attackFrameC);
	this->addChild(this->animatedLabelA);
	this->addChild(this->animatedLabelB);
	this->addChild(this->animatedLabelC);
	this->addChild(this->carryLabel);
	this->addChild(this->decimalOverflowSubtraction);
}

AddHelpMenu::~AddHelpMenu()
{
}

void AddHelpMenu::onEnter()
{
	super::onEnter();
}

void AddHelpMenu::initializePositions()
{
	super::initializePositions();

	const float offset = -80.0f;

	this->description->setPosition(Vec2(-1234 / 2.0f + 16.0f, 420.0f));
	this->attackFrameA->setPosition(Vec2(-196.0f, 144.0f + offset));
	this->attackFrameB->setPosition(Vec2(-196.0f, 0.0f + offset));
	this->attackFrameC->setPosition(Vec2(-196.0f, -144.0f + offset));
	this->animatedLabelA->setPosition(Vec2(-196.0f, 144.0f + offset));
	this->animatedLabelB->setPosition(Vec2(-196.0f, 0.0f + offset));
	this->animatedLabelC->setPosition(Vec2(-196.0f, -144.0f + offset));
	this->carryLabel->setPosition(Vec2(-196.0f, -144.0f + offset));
	this->previewCardA->setPosition(Vec2(-448.0f, 144.0f + offset));
	this->previewCardB->setPosition(Vec2(64.0f, 0.0f + offset));
	this->addCard->setPosition(Vec2(356.0f, 0.0f));
}

void AddHelpMenu::initializeListeners()
{
	super::initializeListeners();

	this->previewCardA->setToggleAttackCallback([=](){ this->resetAnimation(); });
	this->previewCardB->setToggleAttackCallback([=](){ this->resetAnimation(); });

	this->previewCardA->setToggleDisplayTypeCallback([=]()
	{
		this->previewCardB->setDisplayType(this->previewCardA->autoCard->getDisplayType(), false);
		this->resetAnimation();
	});

	this->previewCardB->setToggleDisplayTypeCallback([=]()
	{
		this->previewCardA->setDisplayType(this->previewCardB->autoCard->getDisplayType(), false);
		this->resetAnimation();
	});
}

void AddHelpMenu::open()
{
	this->setVisible(true);

	this->stopAllActions();
	this->runAnimationLoop();
}

void AddHelpMenu::resetAnimation()
{
	this->stopAllActions();
	this->animatedLabelA->setOpacity(0);
	this->animatedLabelB->setOpacity(0);
	this->animatedLabelC->setOpacity(0);
	this->decimalOverflowSubtraction->setOpacity(0);

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->runAnimationLoop();
		}),
		nullptr
	));
}

void AddHelpMenu::runAnimationLoop()
{
	this->initializePositions();
	
	this->previewCardB->autoCard->activeCard->clearOperations();

	this->animatedLabelAValue->setString(HackUtils::toBinary4(this->previewCardA->autoCard->getAttack()));
	this->animatedLabelBValue->setString(HackUtils::toBinary4(this->previewCardB->autoCard->getAttack()));
	this->animatedLabelCValue->setString(HackUtils::toBinary4(0));
	this->carryLabelValue->setString(HackUtils::toBinary4(0));

	for (int index = 0; index < 4; index++)
	{
		this->animatedLabelA->getLetter(index)->runAction(FadeTo::create(0.25f, 255));
		this->animatedLabelB->getLetter(index)->runAction(FadeTo::create(0.25f, 255));
		this->animatedLabelC->getLetter(index)->runAction(FadeTo::create(0.25f, 255));
		this->carryLabel->getLetter(index)->runAction(FadeTo::create(0.25f, 0));
		this->animatedLabelA->getLetter(index)->setColor(Color3B::WHITE);
		this->animatedLabelB->getLetter(index)->setColor(Color3B::WHITE);
		this->animatedLabelC->getLetter(index)->setColor(Color3B::WHITE);
		this->carryLabel->getLetter(index)->setColor(Color3B::WHITE);
	}
	
	// Restore opacity altered by resetting animation
	this->animatedLabelA->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelB->runAction(FadeTo::create(0.25f, 255));
	this->animatedLabelC->runAction(FadeTo::create(0.25f, 255));
	this->carryLabel->setOpacity(0);
	this->decimalOverflowSubtraction->setOpacity(0);

	switch(this->previewCardA->autoCard->getDisplayType())
	{
		default:
		case AutoCard::DisplayType::Decimal:
		{
			// Override w/ decimal values instead (we do this after binary so that the code above can reset opacity and color of all letters)
			this->animatedLabelAValue->setString(std::to_string(this->previewCardA->autoCard->getAttack()));
			this->animatedLabelBValue->setString(std::to_string(this->previewCardB->autoCard->getAttack()));
			this->animatedLabelCValue->setString(std::to_string(0));

			int attackSum = this->previewCardA->autoCard->getAttack() + this->previewCardB->autoCard->getAttack();

			this->runAction(Sequence::create(
				DelayTime::create(1.0f),
				CallFunc::create([=]()
				{
					// Phase 1: Run card ord animation
					this->previewCardB->autoCard->activeCard->addOperation(Card::Operation(Card::Operation::OperationType::ADD, this->previewCardA->autoCard->getAttack()));
					this->previewCardB->autoCard->activeCard->cardEffects->runEffect(this->addCard->getCorrespondingCardEffect());

					// Set sum label, including possible overflow
					this->animatedLabelCValue->setString(std::to_string(attackSum));

					if (attackSum >= 16)
					{
						this->animatedLabelC->setColor(Color3B::RED);
						this->previewCardB->autoCard->activeCard->runOverflowEffect();
					}
				}),
				DelayTime::create(attackSum >= 16 ? 1.0f : 0.0f),
				CallFunc::create([=]()
				{
					if (attackSum >= 16)
					{
						this->animatedLabelCValue->setString(std::to_string(attackSum - 16));
						this->animatedLabelC->setColor(Color3B::WHITE);

						this->decimalOverflowSubtraction->setPosition(this->animatedLabelC->getPosition() + Vec2(0.0f, 32.0f));
						this->decimalOverflowSubtraction->setOpacity(255);
						this->decimalOverflowSubtraction->runAction(FadeTo::create(0.75f, 0));
						this->decimalOverflowSubtraction->runAction(MoveBy::create(0.75f, Vec2(0.0f, 64.0f)));
					}
				}),
				DelayTime::create(2.5f),
				CallFunc::create([=]()
				{
					this->runAnimationLoop();
				}),
				nullptr
			));

			break;
		}
		case AutoCard::DisplayType::Binary:
		{
			for (int index = 0; index < 4; index++)
			{
				if (this->animatedLabelAValue->getString()[index] == '0')
				{
					this->animatedLabelA->getLetter(index)->setColor(Color3B::GRAY);
				}
				else
				{
					this->animatedLabelA->getLetter(index)->setColor(Color3B::WHITE);
				}
				
				if (this->animatedLabelBValue->getString()[index] == '0')
				{
					this->animatedLabelB->getLetter(index)->setColor(Color3B::GRAY);
				}
				else
				{
					this->animatedLabelB->getLetter(index)->setColor(Color3B::WHITE);
				}

				if (this->animatedLabelCValue->getString()[index] == '0')
				{
					this->animatedLabelC->getLetter(index)->setColor(Color3B::GRAY);
				}
				else
				{
					this->animatedLabelC->getLetter(index)->setColor(Color3B::WHITE);
				}
			}

			bool hasCarry = ((this->previewCardA->autoCard->activeCard->getAttack() & this->previewCardB->autoCard->activeCard->getAttack()) != 0);
			bool hasZeros = ((this->previewCardA->autoCard->activeCard->getAttack() ^ 0b1111) != 0 || (this->previewCardB->autoCard->activeCard->getAttack() ^ 0b1111) != 0);

			this->runAction(Sequence::create(
				DelayTime::create(1.0f),
				CallFunc::create([=]()
				{
					// Phase 1: Run card ord animation
					this->previewCardB->autoCard->activeCard->addOperation(Card::Operation(Card::Operation::OperationType::ADD, this->previewCardA->autoCard->getAttack()));
					this->previewCardB->autoCard->activeCard->cardEffects->runEffect(this->addCard->getCorrespondingCardEffect());
				}),
				DelayTime::create(hasZeros ? 1.5f : 0.1f),
				CallFunc::create([=]()
				{
					// Phase 2, fade out all 0s, color all invalid 1s
					if (hasZeros)
					{
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
					}
				}),
				DelayTime::create(1.5f),
				CallFunc::create([=]()
				{
					// Phase 3: move all 1's to their places
					for (int index = 0; index < 4; index++)
					{
						if (this->animatedLabelAValue->getString()[index] == '1' && this->animatedLabelBValue->getString()[index] == '0')
						{
							this->animatedLabelA->getLetter(index)->runAction(MoveBy::create(1.0f, Vec2(0.0f, -144.0f * 2.0f)));
							this->animatedLabelC->getLetter(index)->runAction(FadeTo::create(0.75f, 0));
						}

						if (this->animatedLabelBValue->getString()[index] == '1' && this->animatedLabelAValue->getString()[index] == '0')
						{
							this->animatedLabelB->getLetter(index)->runAction(MoveBy::create(1.0f, Vec2(0.0f, -144.0f)));
							this->animatedLabelC->getLetter(index)->runAction(FadeTo::create(0.75f, 0));
						}
					}

					for (int index = 0; index < 4; index++)
					{
						if (this->animatedLabelAValue->getString()[index] == '1' && this->animatedLabelBValue->getString()[index] == '1')
						{
							this->animatedLabelA->getLetter(index)->runAction(MoveBy::create(1.0f, Vec2(0.0f, -144.0f * 2.0f)));
							this->animatedLabelB->getLetter(index)->runAction(MoveBy::create(1.0f, Vec2(0.0f, -144.0f)));
							this->animatedLabelC->getLetter(index)->runAction(FadeTo::create(0.75f, 0));
						}
					}
				}),
				DelayTime::create(1.0f),
				CallFunc::create([=]()
				{
					this->animatedLabelA->setOpacity(0);
					this->animatedLabelB->setOpacity(0);
					
					int carry = (this->previewCardA->autoCard->activeCard->getOriginalAttack() & this->previewCardB->autoCard->activeCard->getOriginalAttack());
					int currentResultValue = (this->previewCardA->autoCard->activeCard->getOriginalAttack() | this->previewCardB->autoCard->activeCard->getOriginalAttack());

					if (carry != 0)
					{
						this->runCarryLoop(currentResultValue ^ carry, carry);
					}
					else
					{
						this->runAnimationLoop();
					}
				}),
				nullptr
			));
			break;
		}
	}
}

void AddHelpMenu::runCarryLoop(int currentResultValue, int carry)
{
	if (carry == 0)
	{
		this->runAction(Sequence::create(
			DelayTime::create(1.5f),
			CallFunc::create([=]()
			{
				this->runAnimationLoop();
			}),
			nullptr
		));
		return;
	}

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			// Phase 4: cascade double 1's (indicated by carry bit set) into 2s
			this->animatedLabelCValue->setString(HackUtils::toBinary4(currentResultValue));
			this->carryLabelValue->setString(HackUtils::toBinary4(carry));
			std::string cascadeString = this->animatedLabelCValue->getString();

			for (int index = 0; index < 4; index++)
			{
				if (this->carryLabelValue->getString()[index] == '1')
				{
					cascadeString[index] = '2';

					this->animatedLabelC->getLetter(index)->setColor(Color3B::WHITE);
					this->animatedLabelC->getLetter(index)->setOpacity(255);
				}

				if (cascadeString[index] == '0')
				{
					this->animatedLabelC->getLetter(index)->setColor(Color3B::GRAY);
				}
				else
				{
					this->animatedLabelC->getLetter(index)->setColor(Color3B::WHITE);
				}
				
				this->animatedLabelC->getLetter(index)->setOpacity(255);
				this->carryLabel->getLetter(index)->setOpacity(0);
			}

			this->animatedLabelCValue->setString(cascadeString);
		}),
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			// Phase 5: Move carry string to position, update result string
			std::string resultString = this->animatedLabelCValue->getString();

			this->carryLabel->setOpacity(255);

			for (int index = 0; index < 4; index++)
			{
				if (this->carryLabelValue->getString()[index] == '1')
				{
					this->carryLabel->getLetter(index)->runAction(MoveBy::create(0.5f, Vec2(-44.0f, 64.0f)));
					this->carryLabel->getLetter(index)->setOpacity(255);
					resultString[index] = '0';
					this->animatedLabelC->getLetter(index)->setColor(Color3B::GRAY);
				}
				else
				{
					this->carryLabel->getLetter(index)->setOpacity(0);
				}
			}

			this->animatedLabelCValue->setString(resultString);
		}),
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			// Phase 6: move all carry's to their places
			for (int index = 0; index < 4; index++)
			{
				if (this->carryLabelValue->getString()[index] == '1')
				{
					this->carryLabel->getLetter(index)->runAction(MoveBy::create(0.5f, Vec2(0.0f, -64.0f)));

					if (index == 0)
					{
						this->carryLabel->getLetter(index)->runAction(TintTo::create(0.25f, Color3B::RED));
					}
					else if (index > 0 && this->animatedLabelCValue->getString()[index - 1] == '0')
					{
						this->animatedLabelC->getLetter(index - 1)->runAction(FadeTo::create(0.25f, 0));
					}
				}
			}
		}),
		DelayTime::create(0.51f),
		CallFunc::create([=]()
		{
			int nextCarry = (carry << 1) & (currentResultValue);

			this->runCarryLoop(currentResultValue ^ (carry << 1), nextCarry);
		}),
		nullptr
	));
}
