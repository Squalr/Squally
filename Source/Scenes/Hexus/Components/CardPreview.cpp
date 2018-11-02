#include "CardPreview.h"

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

void CardPreview::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->previewPanel->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter, visibleSize.height / 2.0f + Config::previewOffsetY);
}

void CardPreview::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void CardPreview::onStateChange(GameState* gameState)
{
	ComponentBase::onStateChange(gameState);

	switch (gameState->stateType)
	{
		case GameState::StateType::Neutral:
		case GameState::StateType::SelectionStaged:
		case GameState::StateType::CombineStaged:
			this->initializeCallbacks(gameState);
			break;
		default:
			this->clearPreview();
			break;
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

				Label* binaryLabel = Label::create("BIN: " + HackUtils::toBinary4(attack), Localization::getCodingFont(), Localization::getFontSizeH2(Localization::getCodingFont()));
				Label* decimalLabel = Label::create("DEC: " + std::to_string(attack), Localization::getCodingFont(), Localization::getFontSizeH2(Localization::getCodingFont()));
				Label* hexLabel = Label::create("HEX: " + HackUtils::toHex(attack), Localization::getCodingFont(), Localization::getFontSizeH2(Localization::getCodingFont()));

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
				Label * specialLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeP(Localization::getCodingFont()));

				specialLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
				specialLabel->setTextColor(Card::specialColor);
				specialLabel->enableOutline(Color4B::BLACK, 2);
				specialLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, -96.0f));
				specialLabel->setDimensions(previewSprite->getContentSize().width - 16.0f, 0.0f);

				switch (card->cardData->cardType) {
				case CardData::CardType::Special_AND:
					specialLabel->setString("Select one of your cards and AND its value with another card, storing the value into the other card.");
					break;
				case CardData::CardType::Special_OR:
					specialLabel->setString("Select one of your cards and OR its value with another card, storing the value into the other card.");
					break;
				case CardData::CardType::Special_XOR:
					specialLabel->setString("Select one of your cards and XOR its value with another card, storing the value into the other card.");
					break;
				case CardData::CardType::Special_SHL:
					specialLabel->setString("Shift the bits left of all cards in a row.");
					break;
				case CardData::CardType::Special_SHR:
					specialLabel->setString("Shift the bits right of all cards in a row.");
					break;
				case CardData::CardType::Special_INV:
					specialLabel->setString("Invert all bits in a row.");
					break;
				case CardData::CardType::Special_FLIP1:
					specialLabel->setString("Flip the 1st bit of all cards in a row.");
					break;
				case CardData::CardType::Special_FLIP2:
					specialLabel->setString("Flip the 2nd bit of all cards in a row.");
					break;
				case CardData::CardType::Special_FLIP3:
					specialLabel->setString("Flip the 3rd bit of all cards in a row.");
					break;
				case CardData::CardType::Special_FLIP4:
					specialLabel->setString("Flip the 4th bit of all cards in a row.");
					break;
				case CardData::CardType::Special_ADD:
					specialLabel->setString("Select one of your cards and ADD its value to another card, storing the value into the other card.");
					break;
				case CardData::CardType::Special_SUB:
					specialLabel->setString("Select one of your cards and SUB its value from another card, storing the value into the other card.");
					break;
				default:
					break;
				}

				this->previewPanel->addChild(specialLabel);
				break;
			}
		}
	}
}
