#include "CardPreview.h"

CardPreview* CardPreview::create()
{
	CardPreview* cardPreview = new CardPreview();

	cardPreview->autorelease();

	return cardPreview;
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
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void CardPreview::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->previewPanel->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter, visibleSize.height / 2.0f + Config::previewOffsetY);
}

void CardPreview::initializeListeners()
{
}

void CardPreview::onStateChange(GameState* gameState)
{
	switch (gameState->stateType) {
	case GameState::StateType::ControlNeutral:
		this->initializeCallbacks(gameState);
		break;
	}
}

void CardPreview::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
	gameState->enemyHand->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));

	gameState->playerBinaryCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
	gameState->playerDecimalCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
	gameState->playerHexCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));

	gameState->enemyBinaryCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
	gameState->enemyDecimalCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
	gameState->enemyHexCards->setMouseOverCallback(CC_CALLBACK_1(CardPreview::previewCard, this));
}

void CardPreview::previewCard(Card* card)
{
	if (card != this->currentPreviewCard)
	{
		this->currentPreviewCard = card;

		this->previewPanel->removeAllChildren();

		Sprite* previewSprite = Sprite::create(card->cardData->cardResourceFile);
		this->previewPanel->addChild(previewSprite);

		switch (card->cardData->cardType) {
		case CardData::CardType::Decimal:
		case CardData::CardType::Binary:
		case CardData::CardType::Hexidecimal:
		{
			int attack = card->getAttack();

			Label* binaryLabel = Label::create("BIN: " + HackUtils::toBinary4(attack), Resources::Fonts_UbuntuMono_Bold, 32);
			Label* decimalLabel = Label::create("DEC: " + std::to_string(attack), Resources::Fonts_UbuntuMono_Bold, 32);
			Label* hexLabel = Label::create("HEX: " + HackUtils::toHex(attack), Resources::Fonts_UbuntuMono_Bold, 32);

			binaryLabel->setAnchorPoint(Vec2::ZERO);
			decimalLabel->setAnchorPoint(Vec2::ZERO);
			hexLabel->setAnchorPoint(Vec2::ZERO);

			binaryLabel->setTextColor(Card::binaryColor);
			decimalLabel->setTextColor(Card::decimalColor);
			hexLabel->setTextColor(Card::hexColor);

			binaryLabel->enableOutline(Color4B::BLACK, 3);
			decimalLabel->enableOutline(Color4B::BLACK, 3);
			hexLabel->enableOutline(Color4B::BLACK, 3);

			binaryLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, -212.0f));
			decimalLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, -212.0f - 40.0f));
			hexLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, -212.0f - 80.0f));

			this->previewPanel->addChild(binaryLabel);
			this->previewPanel->addChild(decimalLabel);
			this->previewPanel->addChild(hexLabel);
		}
		break;
		default:
		{
			Label * specialLabel = Label::create("", Resources::Fonts_UbuntuMono_Bold, 28);

			specialLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
			specialLabel->setTextColor(Card::specialColor);
			specialLabel->enableOutline(Color4B::BLACK, 2);
			specialLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f - 32.0f, -172.0f));
			specialLabel->setDimensions(previewSprite->getContentSize().width + 64.0f, 0.0f);

			switch (card->cardData->cardType) {
			case CardData::CardType::Special_AND:
				specialLabel->setString("Sacrifice one of your cards on the field and AND it with all cards in a row of the same type.");
				break;
			case CardData::CardType::Special_OR:
				specialLabel->setString("Sacrifice one of your cards on the field and OR it with all cards in a row of the same type.");
				break;
			case CardData::CardType::Special_XOR:
				specialLabel->setString("Sacrifice one of your cards on the field and XOR it with all cards in a row of the same type.");
				break;
			case CardData::CardType::Special_SHL:
				specialLabel->setString("Shift the bits left of all cards in a row .");
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
				specialLabel->setString("Sacrifice one of your cards on the field and ADD it to two cards of the same type.");
				break;
			case CardData::CardType::Special_SUB:
				specialLabel->setString("Sacrifice one of your cards on the field and SUB it from two cards of the same type.");
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
