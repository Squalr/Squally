#include "CardPreview.h"

#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/HackUtils.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CardPreview* CardPreview::create()
{
	CardPreview* instance = new CardPreview();

	instance->autorelease();

	return instance;
}

CardPreview::CardPreview()
{
	this->cardPad = Sprite::create(HexusResources::CardPad);
	this->previewPanel = Node::create();
	this->currentPreviewData = PreviewData();
	this->previewCache = std::map<std::string, PreviewData>();

	LocalizedLabel* helpLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Help::create());
	LocalizedLabel* helpLabelSelected = helpLabel->clone();

	helpLabel->enableOutline(Color4B::BLACK, 2);
	helpLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->helpButton = ClickableTextNode::create(
		helpLabel,
		helpLabelSelected,
		UIResources::Menus_Buttons_SmallGenericButton,
		UIResources::Menus_Buttons_SmallGenericButtonSelected
	);

	this->addChild(this->cardPad);
	this->addChild(this->previewPanel);
	this->addChild(this->helpButton);
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

	this->helpButton->setPosition(Vec2(0.0f, -212.0f));
}

void CardPreview::setHelpClickCallback(std::function<void(CardData*)> onHelpClick)
{
	this->onHelpClick = onHelpClick;

	this->helpButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->onHelpClick != nullptr)
		{
			this->onHelpClick(this->currentPreviewData.cardData);
		}
	});
}

void CardPreview::clearPreview()
{
	this->previewCard(nullptr);
}

void CardPreview::previewCard(Card* card)
{
	this->helpButton->setVisible(false);
	
	if (this->currentPreviewData.previewNode != nullptr)
	{
		this->currentPreviewData.previewNode->setVisible(false);
	}

	if (card == nullptr)
	{
		return;
	}

	this->previewCardData(card->cardData, card);
}

void CardPreview::previewCardData(CardData* cardData, Card* card)
{
	if (this->currentPreviewData.previewNode != nullptr)
	{
		this->currentPreviewData.previewNode->setVisible(false);
	}

	if (this->previewCache.find(cardData->getCardKey()) != this->previewCache.end())
	{
		this->currentPreviewData = this->previewCache[cardData->getCardKey()];
	}
	else
	{
		this->currentPreviewData = this->constructPreview(cardData, card);
		this->previewCache[cardData->getCardKey()] = this->currentPreviewData;
		this->previewPanel->addChild(this->currentPreviewData.previewNode);
	}

	this->updatePreview(this->currentPreviewData, card);
	this->currentPreviewData.previewNode->setVisible(true);
	
	switch (cardData->getCardType())
	{
		case CardData::CardType::Decimal:
		case CardData::CardType::Binary:
		case CardData::CardType::Hexidecimal:
		case CardData::CardType::Special_MOV:
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
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
			this->helpButton->setVisible(true);
			break;
		}
		default:
		{
			this->helpButton->setVisible(false);
			break;
		}
	}
}

void CardPreview::updatePreview(PreviewData previewData, Card* refCard)
{
	int originalAttack = previewData.cardData->getAttack();
	int attack = (refCard == nullptr) ? originalAttack : refCard->getAttack();

	switch (previewData.cardData->getCardType())
	{
		case CardData::CardType::Decimal:
		case CardData::CardType::Binary:
		case CardData::CardType::Hexidecimal:
		{
			if (previewData.binStrRef != nullptr)
			{
				previewData.binStrRef->setString(HackUtils::toBinary4(attack));
			}

			if (previewData.decStrRef != nullptr)
			{
				previewData.decStrRef->setString(std::to_string(attack));
			}

			if (previewData.hexStrRef != nullptr)
			{
				previewData.hexStrRef->setString(HackUtils::toHex(attack));
			}
		}
		default:
		{
			break;
		}
	}
}

CardPreview::PreviewData CardPreview::constructPreview(CardData* cardData, Card* card)
{
	if (cardData == nullptr)
	{
		return PreviewData();
	}

	Node* preview = Node::create();
	ConstantString* binStrRef = nullptr;
	ConstantString* decStrRef = nullptr;
	ConstantString* hexStrRef = nullptr;
	LocalizedLabel* binLabelRef = nullptr;
	LocalizedLabel* decLabelRef = nullptr;
	LocalizedLabel* hexLabelRef = nullptr;
	Card* cardClone = card == nullptr ? nullptr : card->clone(false);

	if (cardClone != nullptr)
	{
		cardClone->setScale(1.0f);
		cardClone->reveal();
		cardClone->hideUI();

		preview->addChild(cardClone);
	}

	switch (cardData->getCardType())
	{
		case CardData::CardType::Decimal:
		case CardData::CardType::Binary:
		case CardData::CardType::Hexidecimal:
		{
			int attack = card == nullptr ? cardData->getAttack() : card->getAttack();

			// Show special effects
			if (cardData->getCardKey() == CardKeys::Binary0 
				|| cardData->getCardKey() == CardKeys::Decimal0 
				|| cardData->getCardKey() == CardKeys::Hex0
				|| cardData->getCardKey() == CardKeys::Decimal1
				|| cardData->getCardKey() == CardKeys::Hex1)
			{
				LocalizedLabel* specialLabel = nullptr;
				
				if (cardData->getCardKey() == CardKeys::Binary0)
				{
					specialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_CardDescriptions_NoDestroyEffect::create());
				}
				else if (cardData->getCardKey() == CardKeys::Decimal0)
				{
					specialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_CardDescriptions_DrawEffect::create());
				}
				else if (cardData->getCardKey() == CardKeys::Hex0)
				{
					specialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_CardDescriptions_TurnGainsEffect::create());
				}
				else if (cardData->getCardKey() == CardKeys::Decimal1)
				{
					specialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_CardDescriptions_ReturnAfterRound::create());
				}
				else if (cardData->getCardKey() == CardKeys::Hex1)
				{
					specialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_CardDescriptions_Horde::create());
				}
				
				specialLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
				specialLabel->setTextColor(Card::SpecialColor);
				specialLabel->enableOutline(Color4B::BLACK, 2);

				if (cardClone != nullptr)
				{
					specialLabel->setPosition(Vec2(-cardClone->getContentSize().width / 2.0f + 8.0f, 160.0f));
					specialLabel->setDimensions(cardClone->getContentSize().width - 16.0f, 0.0f);
				}

				preview->addChild(specialLabel);
			}

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

			binaryLabel->setTextColor(Card::BinaryColor);
			decimalLabel->setTextColor(Card::DecimalColor);
			hexLabel->setTextColor(Card::HexColor);

			binaryLabel->enableOutline(Color4B::BLACK, 3);
			decimalLabel->enableOutline(Color4B::BLACK, 3);
			hexLabel->enableOutline(Color4B::BLACK, 3);

			const float yOffset = -72.0f;

			if (cardClone != nullptr)
			{
				binaryLabel->setPosition(Vec2(-cardClone->getContentSize().width / 2.0f + 8.0f, yOffset));
				decimalLabel->setPosition(Vec2(-cardClone->getContentSize().width / 2.0f + 8.0f, yOffset - 40.0f));
				hexLabel->setPosition(Vec2(-cardClone->getContentSize().width / 2.0f + 8.0f, yOffset - 80.0f));
			}

			binStrRef = binaryString;
			decStrRef = decimalString;
			hexStrRef = hexString;
			binLabelRef = binaryLabel;
			decLabelRef = decimalLabel;
			hexLabelRef = hexLabel;

			preview->addChild(binaryLabel);
			preview->addChild(decimalLabel);
			preview->addChild(hexLabel);

			break;
		}
		default:
		{
			LocalizedLabel* specialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Common_Empty::create());

			specialLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
			specialLabel->setTextColor(Card::SpecialColor);
			specialLabel->enableOutline(Color4B::BLACK, 2);
			
			if (cardClone != nullptr)
			{
				specialLabel->setPosition(Vec2(-cardClone->getContentSize().width / 2.0f + 8.0f, -160.0f));
				specialLabel->setDimensions(cardClone->getContentSize().width - 16.0f, 0.0f);
			}

			switch (cardData->getCardType())
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
				case CardData::CardType::Special_ROL:
				{
					specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_ShiftLeftCircular::create());
					break;
				}
				case CardData::CardType::Special_ROR:
				{
					specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_ShiftRightCircular::create());
					break;
				}
				case CardData::CardType::Special_NOT:
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
				case CardData::CardType::Special_SUDDEN_DEATH:
				{
					specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_SuddenDeath::create());
					break;
				}
				case CardData::CardType::Special_GREED:
				{
					specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Greed::create());
					break;
				}
				case CardData::CardType::Special_ABSORB:
				{
					specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Absorb::create());
					break;
				}
				case CardData::CardType::Special_KILL:
				{
					specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Kill::create());
					break;
				}
				case CardData::CardType::Special_RETURN_TO_HAND:
				{
					specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_ReturnToHand::create());
					break;
				}
				case CardData::CardType::Special_STEAL:
				{
					specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Steal::create());
					break;
				}
				case CardData::CardType::Special_BONUS_MOVES:
				{
					specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_BonusMoves::create());
					break;
				}
				case CardData::CardType::Special_PEEK:
				{
					specialLabel->setLocalizedString(Strings::Hexus_CardDescriptions_Peek::create());
					break;
				}
				default:
				{
					break;
				}
			}

			preview->addChild(specialLabel);
			break;
		}
	}

	return PreviewData(cardClone, cardData, preview, binStrRef, decStrRef, hexStrRef, binLabelRef, decLabelRef, hexLabelRef);
}
