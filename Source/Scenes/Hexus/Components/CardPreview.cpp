#include "CardPreview.h"

#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/HackUtils.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Strings/Generics/Empty.h"
#include "Strings/Hexus/BinLabel.h"
#include "Strings/Hexus/CardDescriptions/Addition.h"
#include "Strings/Hexus/CardDescriptions/BinStorm.h"
#include "Strings/Hexus/CardDescriptions/Clear.h"
#include "Strings/Hexus/CardDescriptions/DecStorm.h"
#include "Strings/Hexus/CardDescriptions/Flip1.h"
#include "Strings/Hexus/CardDescriptions/Flip2.h"
#include "Strings/Hexus/CardDescriptions/Flip3.h"
#include "Strings/Hexus/CardDescriptions/Flip4.h"
#include "Strings/Hexus/CardDescriptions/HexStorm.h"
#include "Strings/Hexus/CardDescriptions/Inverse.h"
#include "Strings/Hexus/CardDescriptions/LogicalAnd.h"
#include "Strings/Hexus/CardDescriptions/LogicalOr.h"
#include "Strings/Hexus/CardDescriptions/LogicalXor.h"
#include "Strings/Hexus/CardDescriptions/Mov.h"
#include "Strings/Hexus/CardDescriptions/ShiftLeft.h"
#include "Strings/Hexus/CardDescriptions/ShiftRight.h"
#include "Strings/Hexus/CardDescriptions/Subtract.h"
#include "Strings/Hexus/DecLabel.h"
#include "Strings/Hexus/HexLabel.h"

using namespace cocos2d;

CardPreview* CardPreview::create()
{
	CardPreview* instance = new CardPreview();

	instance->autorelease();

	return instance;
}

CardPreview::CardPreview()
{
	this->previewPanel = Node::create();
	this->currentPreviewCard = nullptr;

	this->addChild(this->previewPanel);
}

CardPreview::~CardPreview()
{
}

void CardPreview::onEnter()
{
	super::onEnter();

	this->clearPreview();
}

void CardPreview::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->previewPanel->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter, visibleSize.height / 2.0f + Config::previewOffsetY);
}

void CardPreview::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void CardPreview::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	switch (gameState->stateType)
	{
		case GameState::StateType::Neutral:
		{
			this->initializeCallbacks(gameState);
			break;
		}
		case GameState::StateType::SelectionStaged:
		case GameState::StateType::CombineStaged:
		{
			if (gameState->selectedHandCard == nullptr)
			{
				this->initializeCallbacks(gameState);
				break;
			}

			switch (gameState->selectedHandCard->cardData->cardType)
			{
				case CardData::CardType::Binary:
				case CardData::CardType::Decimal:
				case CardData::CardType::Hexidecimal:
				case CardData::CardType::Special_SHL:
				case CardData::CardType::Special_SHR:
				{
					// Do not enable intraction for rows when these card types are staged
					break;
				}
				default:
				{
					this->initializeCallbacks(gameState);
					break;
				}
			}

			break;
		}
		default:
		{
			this->clearPreview();
			break;
		}
	}
}

void CardPreview::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->enableRowCardInteraction();
	gameState->enemyHand->enableRowCardInteraction();

	gameState->playerHand->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
	gameState->enemyHand->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));

	gameState->playerBinaryCards->enableRowCardInteraction();
	gameState->playerDecimalCards->enableRowCardInteraction();
	gameState->playerHexCards->enableRowCardInteraction();

	gameState->playerBinaryCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
	gameState->playerDecimalCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
	gameState->playerHexCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));

	gameState->enemyBinaryCards->enableRowCardInteraction();
	gameState->enemyDecimalCards->enableRowCardInteraction();
	gameState->enemyHexCards->enableRowCardInteraction();

	gameState->enemyBinaryCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
	gameState->enemyDecimalCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
	gameState->enemyHexCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
}

void CardPreview::clearPreview()
{
	this->currentPreviewCard = nullptr;
	this->previewPanel->removeAllChildren();
}

void CardPreview::previewCard(Card* card)
{
	if (card != this->currentPreviewCard)
	{
		this->currentPreviewCard = card;
		this->previewPanel->removeAllChildren();

		if (card == nullptr)
		{
			return;
		}

		Sprite* previewSprite = Sprite::create(card->cardData->cardResourceFile);
		this->previewPanel->addChild(previewSprite);

		switch (card->cardData->cardType)
		{
			case CardData::CardType::Decimal:
			case CardData::CardType::Binary:
			case CardData::CardType::Hexidecimal:
			{
				int attack = card->getAttack();

				LocalizedLabel* binaryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Hexus_BinLabel::create());
				LocalizedLabel* decimalLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Hexus_DecLabel::create());
				LocalizedLabel* hexLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Hexus_HexLabel::create());

				ConstantString* binaryString = ConstantString::create(HackUtils::toBinary4(attack));
				ConstantString* decimalString = ConstantString::create(std::to_string(attack));
				ConstantString* hexString = ConstantString::create(HackUtils::toHex(attack));

				binaryLabel->setStringReplacementVariables(binaryString);
				decimalLabel->setStringReplacementVariables(decimalString);
				hexLabel->setStringReplacementVariables(hexString);

				binaryLabel->setAnchorPoint(Vec2::ZERO);
				decimalLabel->setAnchorPoint(Vec2::ZERO);
				hexLabel->setAnchorPoint(Vec2::ZERO);

				binaryLabel->setTextColor(Card::binaryColor);
				decimalLabel->setTextColor(Card::decimalColor);
				hexLabel->setTextColor(Card::hexColor);

				binaryLabel->enableOutline(Color4B::BLACK, 3);
				decimalLabel->enableOutline(Color4B::BLACK, 3);
				hexLabel->enableOutline(Color4B::BLACK, 3);

				const float yOffset = -72.0f;

				binaryLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, yOffset));
				decimalLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, yOffset - 40.0f));
				hexLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, yOffset - 80.0f));

				this->previewPanel->addChild(binaryLabel);
				this->previewPanel->addChild(decimalLabel);
				this->previewPanel->addChild(hexLabel);

				break;
			}
			default:
			{
				LocalizedLabel* specialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Generics_Empty::create());

				specialLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
				specialLabel->setTextColor(Card::specialColor);
				specialLabel->enableOutline(Color4B::BLACK, 2);
				specialLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, -160.0f));
				specialLabel->setDimensions(previewSprite->getContentSize().width - 16.0f, 0.0f);

				// TODO: Not a fan of allocating memory at runtime like this by calling create, maybe this is fine though
				switch (card->cardData->cardType)
				{
					case CardData::CardType::Special_MOV:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Mov::create());
						break;
					}
					case CardData::CardType::Special_AND:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_LogicalAnd::create());
						break;
					}
					case CardData::CardType::Special_OR:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_LogicalOr::create());
						break;
					}
					case CardData::CardType::Special_XOR:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_LogicalXor::create());
						break;
					}
					case CardData::CardType::Special_SHL:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_ShiftLeft::create());
						break;
					}
					case CardData::CardType::Special_SHR:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_ShiftRight::create());
						break;
					}
					case CardData::CardType::Special_INV:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Inverse::create());
						break;
					}
					case CardData::CardType::Special_FLIP1:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Flip1::create());
						break;
					}
					case CardData::CardType::Special_FLIP2:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Flip2::create());
						break;
					}
					case CardData::CardType::Special_FLIP3:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Flip3::create());
						break;
					}
					case CardData::CardType::Special_FLIP4:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Flip4::create());
						break;
					}
					case CardData::CardType::Special_ADD:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Addition::create());
						break;
					}
					case CardData::CardType::Special_SUB:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Subtract::create());
						break;
					}
					case CardData::CardType::Special_ENV_CLEAR:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Subtract::create());
						break;
					}
					case CardData::CardType::Special_ENV_BIN_STORM:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_BinStorm::create());
						break;
					}
					case CardData::CardType::Special_ENV_DEC_STORM:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_DecStorm::create());
						break;
					}
					case CardData::CardType::Special_ENV_HEX_STORM:
					{
						specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_HexStorm::create());
						break;
					}
					default:
					{
						break;
					}
				}

				this->previewPanel->addChild(specialLabel);
				break;
			}
		}
	}
}
