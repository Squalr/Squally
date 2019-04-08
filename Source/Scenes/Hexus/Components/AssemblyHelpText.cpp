#include "AssemblyHelpText.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/HackUtils.h"
#include "Events/HexusEvents.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/AssemblyHelpText.h"

using namespace cocos2d;

const std::string AssemblyHelpText::SourceOperand = "____";
const std::string AssemblyHelpText::DestOperand = "____";
const std::string AssemblyHelpText::ManyOperand = "*";

AssemblyHelpText* AssemblyHelpText::create()
{
	AssemblyHelpText* instance = new AssemblyHelpText();

	instance->autorelease();

	return instance;
}

AssemblyHelpText::AssemblyHelpText()
{
	this->assemblyHelpLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Hexus_AssemblyHelpText::create());
	this->operationString = ConstantString::create();
	this->sourceString = ConstantString::create();
	this->destinationString = ConstantString::create();
	this->gameState = nullptr;

	this->assemblyHelpLabel->enableOutline(Color4B::BLACK, 4);
	this->assemblyHelpLabel->setStringReplacementVariables({ this->operationString, this->sourceString, this->destinationString });
	
	this->addChild(this->assemblyHelpLabel);
}

AssemblyHelpText::~AssemblyHelpText()
{
}

void AssemblyHelpText::onEnter()
{
	super::onEnter();

	this->assemblyHelpLabel->setOpacity(0);
}

void AssemblyHelpText::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->assemblyHelpLabel->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY + 212.0f);
}

void AssemblyHelpText::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(HexusEvents::EventCardPreviewed, [=](EventCustom* eventCustom)
	{
		HexusEvents::CardPreviewArgs* args = static_cast<HexusEvents::CardPreviewArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->card != nullptr && this->gameState != nullptr && this->gameState->selectedHandCard != nullptr)
		{
			bool isMultiTarget = gameState->selectedHandCard->cardData->isMultiTargetCard();
			bool noDice = false;

			// Ignore mousing over hand cards
			for (auto it = this->gameState->playerHand->rowCards.begin(); it != this->gameState->playerHand->rowCards.end(); it++)
			{
				if (args->card == *it)
				{
					noDice = true;
					break;
				}
			}

			// Ignore self-mouseover
			if (args->card == this->gameState->selectedSourceCard)
			{
				noDice = true;
			}

			if (isMultiTarget)
			{
				this->sourceString->setString(HackUtils::toBinary4(gameState->selectedHandCard->cardData->getIntrinsicImmediate()));
				this->destinationString->setString(AssemblyHelpText::ManyOperand);
			}
			else if (this->gameState->selectedSourceCard == nullptr && !noDice)
			{
				this->sourceString->setString(HackUtils::toBinary4(args->card->getAttack()));
			}
			else if (this->gameState->selectedDestinationCard != nullptr)
			{
				this->destinationString->setString(HackUtils::toBinary4(this->gameState->selectedDestinationCard->getAttack()));
			}
			else if (noDice)
			{
				this->destinationString->setString(AssemblyHelpText::DestOperand);
			}
			else
			{
				this->destinationString->setString(HackUtils::toBinary4(args->card->getAttack()));
			}
		}
	}));

	this->addEventListener(EventListenerCustom::create(HexusEvents::EventCardMousedOut, [=](EventCustom* eventCustom)
	{
		bool isMultiTarget = this->gameState->selectedHandCard == nullptr ? false : gameState->selectedHandCard->cardData->isMultiTargetCard();

		if (!isMultiTarget)
		{
			if (this->gameState->selectedSourceCard == nullptr)
			{
				this->sourceString->setString(AssemblyHelpText::SourceOperand);
			}
			this->destinationString->setString(AssemblyHelpText::DestOperand);
		}
	}));
}

void AssemblyHelpText::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void AssemblyHelpText::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	this->gameState = gameState;

	if (gameState->turn != GameState::Turn::Player)
	{
		return;
	}

	switch (gameState->stateType)
	{
		case GameState::StateType::SelectionStaged:
		case GameState::StateType::CombineStaged:
		{
			if (gameState->selectedHandCard != nullptr)
			{
				switch(gameState->selectedHandCard->cardData->cardType)
				{
					case CardData::CardType::Special_AND:
					case CardData::CardType::Special_OR:
					case CardData::CardType::Special_XOR:
					case CardData::CardType::Special_MOV:
					case CardData::CardType::Special_SHL:
					case CardData::CardType::Special_SHR:
					case CardData::CardType::Special_ROL:
					case CardData::CardType::Special_ROR:
					case CardData::CardType::Special_NOT:
					case CardData::CardType::Special_FLIP1:
					case CardData::CardType::Special_FLIP2:
					case CardData::CardType::Special_FLIP3:
					case CardData::CardType::Special_FLIP4:
					case CardData::CardType::Special_ADD:
					case CardData::CardType::Special_SUB:
					{
						if (gameState->selectedHandCard == nullptr)
						{
							return;
						}

						bool isMultiTarget = gameState->selectedHandCard->cardData->isMultiTargetCard();
						
						std::string operation = gameState->selectedHandCard->cardData->getCardOperationString()->getString();
						std::string immediate = gameState->selectedSourceCard == nullptr ? AssemblyHelpText::SourceOperand : HackUtils::toBinary4(gameState->selectedSourceCard->getAttack());
						
						this->operationString->setString(operation);
						this->sourceString->setString(immediate);

						if (isMultiTarget)
						{
							this->sourceString->setString(HackUtils::toBinary4(gameState->selectedHandCard->cardData->getIntrinsicImmediate()));
							this->destinationString->setString(AssemblyHelpText::ManyOperand);
						}
						else if (this->gameState->selectedDestinationCard != nullptr)
						{
							this->destinationString->setString(HackUtils::toBinary4(this->gameState->selectedDestinationCard->getAttack()));
						}

						this->assemblyHelpLabel->runAction(FadeTo::create(0.5f, 255));
						break;
					}
					default:
					{
						break;
					}
				}
			}
			break;
		}
		default:
		{
			this->assemblyHelpLabel->runAction(FadeTo::create(0.5f, 0));
			break;
		}
	}
}
