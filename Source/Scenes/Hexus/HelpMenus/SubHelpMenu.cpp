#include "SubHelpMenu.h"

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

#include "Strings/Hexus/CardDescriptionsLong/Subtract.h"
#include "Strings/Hexus/Cards/Effects/Overflow.h"

using namespace cocos2d;

SubHelpMenu* SubHelpMenu::create()
{
	SubHelpMenu* instance = new SubHelpMenu();

	instance->autorelease();

	return instance;
}

SubHelpMenu::SubHelpMenu()
{
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hexus_CardDescriptionsLong_Subtract::create(), Size(1200.0f, 0.0f));
	this->subCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Subtraction));
	this->previewCardB = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight, ToggleCard::ToggleModeUpDown::BinDec);
	this->previewCardA = ToggleCard::create(ToggleCard::ToggleModeLeftRight::LeftRight, ToggleCard::ToggleModeUpDown::BinDec);
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
	this->decimalUnderflowAddition = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M2, ConstantString::create("+16"));

	this->description->enableOutline(Color4B::BLACK, 2);
	this->description->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->subCard->setScale(1.0f);
	this->animatedLabelA->enableOutline(Color4B::BLACK, 3);
	this->animatedLabelB->enableOutline(Color4B::BLACK, 3);
	this->animatedLabelC->enableOutline(Color4B::BLACK, 3);
	this->carryLabel->enableOutline(Color4B::BLACK, 3);
	this->decimalUnderflowAddition->enableOutline(Color4B::BLACK, 3);
	this->decimalUnderflowAddition->setColor(Color3B::GREEN);

	this->subCard->reveal();
	this->subCard->disableInteraction();
	this->previewCardA->autoCard->setCardScale(0.6f);
	this->previewCardB->autoCard->setCardScale(0.6f);
	this->previewCardA->autoCard->setDisplayType(AutoCard::DisplayType::Decimal);
	this->previewCardB->autoCard->setDisplayType(AutoCard::DisplayType::Decimal);

	this->previewCardA->autoCard->setAttack(6);
	this->previewCardB->autoCard->setAttack(3);

	this->addChild(this->description);
	this->addChild(this->subCard);
	this->addChild(this->previewCardB);
	this->addChild(this->previewCardA);
	this->addChild(this->attackFrameA);
	this->addChild(this->attackFrameB);
	this->addChild(this->attackFrameC);
	this->addChild(this->animatedLabelB);
	this->addChild(this->animatedLabelA);
	this->addChild(this->animatedLabelC);
	this->addChild(this->carryLabel);
	this->addChild(this->decimalUnderflowAddition);
}

SubHelpMenu::~SubHelpMenu()
{
}

void SubHelpMenu::onEnter()
{
	super::onEnter();
}

void SubHelpMenu::initializePositions()
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
	this->carryLabel->setPosition(Vec2(-196.0f - 44.0f, 144.0f + offset));
	this->previewCardA->setPosition(Vec2(64.0f, 144.0f + offset));
	this->previewCardB->setPosition(Vec2(-448.0f, 0.0f + offset));
	this->subCard->setPosition(Vec2(356.0f, 0.0f));
}

void SubHelpMenu::initializeListeners()
{
	super::initializeListeners();

	this->previewCardB->setToggleAttackCallback([=](){ this->resetAnimation(); });
	this->previewCardA->setToggleAttackCallback([=](){ this->resetAnimation(); });

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

void SubHelpMenu::open()
{
	this->setVisible(true);

	this->stopAllActions();
	this->runAnimationLoop();
}

void SubHelpMenu::resetAnimation()
{
	this->stopAllActions();
	this->animatedLabelA->setOpacity(0);
	this->animatedLabelB->setOpacity(0);
	this->animatedLabelC->setOpacity(0);
	this->decimalUnderflowAddition->setOpacity(0);

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->runAnimationLoop();
		}),
		nullptr
	));
}

void SubHelpMenu::runAnimationLoop()
{
	this->initializePositions();
	
	this->previewCardA->autoCard->activeCard->clearOperations();

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
	this->decimalUnderflowAddition->setOpacity(0);

	int attackDiff = this->previewCardA->autoCard->getAttack() - this->previewCardB->autoCard->getAttack();

	switch(this->previewCardB->autoCard->getDisplayType())
	{
		default:
		case AutoCard::DisplayType::Decimal:
		{
			// Override w/ decimal values instead (we do this after binary so that the code above can reset opacity and color of all letters)
			this->animatedLabelAValue->setString(std::to_string(this->previewCardA->autoCard->getAttack()));
			this->animatedLabelBValue->setString(std::to_string(this->previewCardB->autoCard->getAttack()));
			this->animatedLabelCValue->setString(std::to_string(0));

			this->runAction(Sequence::create(
				CallFunc::create([=]()
				{
					this->runTrivialSubtraction([=]()
					{
						this->runAction(Sequence::create(
							DelayTime::create(0.5f),
							CallFunc::create([=]()
							{
								if (attackDiff < 0)
								{
									this->animatedLabelCValue->setString(std::to_string(attackDiff + 16));
									this->animatedLabelC->setColor(Color3B::WHITE);

									this->decimalUnderflowAddition->setPosition(this->animatedLabelC->getPosition() + Vec2(0.0f, 32.0f));
									this->decimalUnderflowAddition->setOpacity(255);
									this->decimalUnderflowAddition->runAction(FadeTo::create(0.75f, 0));
									this->decimalUnderflowAddition->runAction(MoveBy::create(0.75f, Vec2(0.0f, 64.0f)));
								}
							}),
							DelayTime::create(1.5f),
							CallFunc::create([=]()
							{
								this->runAnimationLoop();
							}),
							nullptr
						));
					});
				}),
				nullptr
			));

			break;
		}
		case AutoCard::DisplayType::Binary:
		{
			for (int index = 0; index < 4; index++)
			{
				this->animatedLabelA->getLetter(index)->setColor(Color3B::WHITE);
				this->animatedLabelB->getLetter(index)->setColor(Color3B::WHITE);
				this->animatedLabelC->getLetter(index)->setColor(Color3B::WHITE);
			}

			this->runAction(Sequence::create(
				DelayTime::create(1.5f),
				CallFunc::create([=]()
				{
					this->runCarryLoop();
				}),
				nullptr
			));
		}
	}
}

void SubHelpMenu::runTrivialSubtraction(std::function<void()> callback)
{
	switch(this->previewCardB->autoCard->getDisplayType())
	{
		default:
		case AutoCard::DisplayType::Decimal:
		{
			break;
		}
		case AutoCard::DisplayType::Binary:
		{
			// Phase 0: fix opacity on carry and the top row
			for (int index = 0; index < 4; index++)
			{
				this->animatedLabelA->getLetter(index)->setOpacity(255);
				this->carryLabel->getLetter(index)->setOpacity(0);
			}
			break;
		}
	}

	int attackDiff = this->previewCardA->autoCard->getAttack() - this->previewCardB->autoCard->getAttack();
	
	this->runAction(Sequence::create(
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			// Phase 1: Move all digits to half way point
			this->animatedLabelA->runAction(MoveBy::create(0.75f, Vec2(0.0f, -144.0f)));
			this->animatedLabelC->runAction(FadeTo::create(1.0f, 0));
		}),
		DelayTime::create(0.76f),
		CallFunc::create([=]()
		{
			this->animatedLabelA->setOpacity(0);

			switch(this->previewCardB->autoCard->getDisplayType())
			{
				default:
				case AutoCard::DisplayType::Decimal:
				{
					this->animatedLabelBValue->setString(std::to_string(attackDiff));

					if (attackDiff < 0)
					{
						this->animatedLabelB->setColor(Color3B::RED);
					}
					break;
				}
				case AutoCard::DisplayType::Binary:
				{
					this->animatedLabelBValue->setString(HackUtils::toBinary4(this->previewCardA->autoCard->activeCard->getAttack()));
					break;
				}
			}

			// Phase 2: Hide top row, update mid row, move to bottom
			this->animatedLabelB->setOpacity(255);
			this->animatedLabelB->runAction(MoveBy::create(0.75f, Vec2(0.0f, -144.0f)));
		}),
		DelayTime::create(0.76f),
		CallFunc::create([=]()
		{
			// Run card effect
			this->previewCardA->autoCard->activeCard->addOperation(Card::Operation(Card::Operation::OperationType::SUB, this->previewCardB->autoCard->getAttack()));
			this->previewCardA->autoCard->activeCard->cardEffects->runEffect(this->subCard->getCorrespondingCardEffect());

			if (attackDiff < 0)
			{
				this->previewCardA->autoCard->activeCard->runUnderflowEffect();
			}
			
			switch(this->previewCardB->autoCard->getDisplayType())
			{
				default:
				case AutoCard::DisplayType::Decimal:
				{
					this->animatedLabelCValue->setString(std::to_string(this->previewCardA->autoCard->activeCard->getAttack()));

					// Set sum label, including possible overflow
					this->animatedLabelCValue->setString(std::to_string(attackDiff));

					if (attackDiff < 0)
					{
						this->animatedLabelC->setColor(Color3B::RED);
					}
					break;
				}
				case AutoCard::DisplayType::Binary:
				{
					this->animatedLabelCValue->setString(HackUtils::toBinary4(this->previewCardA->autoCard->activeCard->getAttack()));

					for (int index = 0; index < 4; index++)
					{
						this->animatedLabelC->getLetter(index)->setOpacity(255);
					}
					break;
				}
			}
			
			this->animatedLabelA->setOpacity(0);
			this->animatedLabelB->setOpacity(0);
			this->animatedLabelC->setOpacity(255);
		}),
		CallFunc::create([=]()
		{
			if (callback != nullptr)
			{
				callback();
			}
		}),
		nullptr
	));
}

void SubHelpMenu::runCarryLoop()
{
	bool hasCarry = false;
	static std::string* topString = new std::string();
	static std::string* ghostStringTop = new std::string();

	for (int index = 0; index < 4; index++)
	{
		if (this->animatedLabelAValue->getString()[index] == '0' && this->animatedLabelBValue->getString()[index] == '1')
		{
			hasCarry = true;
		}
	}

	if (!hasCarry)
	{
		this->runTrivialSubtraction([=]()
		{
			this->runAction(Sequence::create(
				DelayTime::create(1.5f),
				CallFunc::create([=]()
				{
					this->runAnimationLoop();
				}),
				nullptr
			));
		});
		return;
	}

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			// Clear carry between each iteration
			this->carryLabel->setOpacity(255);
			this->carryLabelValue->setString(HackUtils::toBinary4(0b0000));

			for (int index = 0; index < 4; index++)
			{
				this->carryLabel->getLetter(index)->setOpacity(0);
				this->animatedLabelA->getLetter(index)->setOpacity(255);
			}

			std::vector<bool> used { false, false, false, false };
			std::string carryString = this->carryLabelValue->getString();
			*topString = this->animatedLabelAValue->getString();
			*ghostStringTop = *topString;

			// Phase 1: Search for carries
			for (int index = 0; index < 4; index++)
			{
				// Bad column! Create a carry
				if (this->animatedLabelAValue->getString()[index] == '0' && this->animatedLabelBValue->getString()[index] == '1')
				{
					bool found = false;

					for (int searchIndex = index - 1; searchIndex >= 0; searchIndex--)
					{
						if (used[searchIndex])
						{
							found = true;
							break;
						}

						if (this->animatedLabelAValue->getString()[searchIndex] == '1' || this->animatedLabelAValue->getString()[searchIndex] == '2')
						{
							used[searchIndex] = true;
							used[searchIndex + 1] = true;
							carryString[searchIndex + 1] = '2';
							(*topString)[searchIndex + 1] = '2';
							(*topString)[searchIndex]--;
							(*ghostStringTop)[searchIndex + 1] = '0';
							(*ghostStringTop)[searchIndex]--;
							this->animatedLabelA->getLetter(searchIndex + 1)->runAction(FadeTo::create(0.25, 0));
							this->carryLabel->getLetter(searchIndex + 1)->setOpacity(255);
							this->carryLabel->getLetter(searchIndex + 1)->runAction(MoveBy::create(0.5f, Vec2(44.0f, 0.0f)));

							found = true;
							break;
						}
					}

					if (!found)
					{
						used[0] = true;
						
						// No carry found! Underflow!
						this->carryLabel->getLetter(0)->setOpacity(255);
						carryString[0] = '1';
						this->carryLabel->getLetter(0)->runAction(MoveBy::create(0.5f, Vec2(44.0f, 0.0f)));

						// This is the new bit getting shifted in
						(*topString)[0] = '2';
						(*ghostStringTop)[0] = '0';
						this->animatedLabelA->getLetter(0)->runAction(FadeTo::create(0.25f, 0));
					}

					this->carryLabelValue->setString(carryString);
					this->animatedLabelAValue->setString(*topString);
				}
			}

			// Temporarily set back to the "ghost string" so that 0s fading out can complete
			this->animatedLabelAValue->setString(*ghostStringTop);
		}),
		DelayTime::create(0.51f),
		CallFunc::create([=]()
		{
			// Restore the true string
			this->animatedLabelAValue->setString(*topString);
		}),
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->runCarryLoop();
		}),
		nullptr
	));
}
