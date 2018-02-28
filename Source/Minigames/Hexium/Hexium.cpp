#include "Hexium.h"

const std::string Hexium::HexiumGameStartEvent = "hexium_game_start_event";
const std::string Hexium::HexiumGameEndEvent = "hexium_game_end_event";

Hexium* Hexium::create()
{
	Hexium* hexium = new Hexium();

	hexium->autorelease();

	return hexium;
}

Hexium::Hexium()
{
	this->gameBackground = Sprite::create(Resources::Minigames_Hexium_Gameboard);
	this->emblem = Sprite::create(Resources::Minigames_Hexium_Emblem);

	this->playerDeck = Deck::create();
	this->playerHand = Hand::create();
	this->playerGraveyard = Deck::create();
	this->enemyDeck = Deck::create();
	this->enemyHand = Hand::create();
	this->enemyGraveyard = Deck::create();

	this->playerFrame = Sprite::create(Resources::Minigames_Hexium_AvatarFrame);
	this->playerPadDeck = Sprite::create(Resources::Minigames_Hexium_CardPad);
	this->playerPadGrave = Sprite::create(Resources::Minigames_Hexium_CardPad);
	this->playerSocketA = Sprite::create(Resources::Minigames_Hexium_Socket);
	this->playerSocketB = Sprite::create(Resources::Minigames_Hexium_Socket);
	this->playerSkullA = Sprite::create(Resources::Minigames_Hexium_Skull);
	this->playerSkullB = Sprite::create(Resources::Minigames_Hexium_Skull);

	this->enemyFrame = Sprite::create(Resources::Minigames_Hexium_AvatarFrame);
	this->enemyPadDeck = Sprite::create(Resources::Minigames_Hexium_CardPad);
	this->enemyPadGrave = Sprite::create(Resources::Minigames_Hexium_CardPad);
	this->enemySocketA = Sprite::create(Resources::Minigames_Hexium_Socket);
	this->enemySocketB = Sprite::create(Resources::Minigames_Hexium_Socket);
	this->enemySkullA = Sprite::create(Resources::Minigames_Hexium_Skull);
	this->enemySkullB = Sprite::create(Resources::Minigames_Hexium_Skull);

	this->playerPadDeck->setScale(Card::cardScale);
	this->playerPadGrave->setScale(Card::cardScale);
	this->enemyPadDeck->setScale(Card::cardScale);
	this->enemyPadGrave->setScale(Card::cardScale);

	this->enemyHand->setVisible(false);

	this->addChild(this->gameBackground);
	this->addChild(this->playerFrame);
	this->addChild(this->enemyFrame);
	this->addChild(this->playerPadDeck);
	this->addChild(this->playerPadGrave);
	this->addChild(this->enemyPadDeck);
	this->addChild(this->enemyPadGrave);
	this->addChild(this->playerSocketA);
	this->addChild(this->playerSocketB);
	this->addChild(this->playerSkullA);
	this->addChild(this->playerSkullB);
	this->addChild(this->enemySocketA);
	this->addChild(this->enemySocketB);
	this->addChild(this->enemySkullA);
	this->addChild(this->enemySkullB);
	this->addChild(this->emblem);

	this->addChild(this->playerGraveyard);
	this->addChild(this->enemyGraveyard);
	this->addChild(this->playerDeck);
	this->addChild(this->enemyDeck);
	this->addChild(this->playerHand);
	this->addChild(this->enemyHand);
}

Hexium::~Hexium()
{
}

void Hexium::onEnter()
{
	FadeScene::onEnter();

	this->initializePositions();
	this->initializeListeners();
	this->addChild(Mouse::claimInstance());
}

void Hexium::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float rightColumnCenter = 780.0f;
	const float leftColumnCenter = -712.0f;
	const float centerColumnCenter = 64.0f;
	const float emblemOffsetX = -84.0f;
	const float frameOffsetX = -72.0f;
	const float frameOffsetY = 368.0f;
	const float deckOffsetY = 420.0f;
	const float handOffsetY = 472.0f;
	const float graveyardOffsetY = 196.0f;
	const float socketOffsetY = 236.0f;
	const float socketAOffsetX = 64.0f;
	const float socketBOffsetX = socketAOffsetX + 112.0f;

	this->gameBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->emblem->setPosition(visibleSize.width / 2.0f + leftColumnCenter + emblemOffsetX, visibleSize.height / 2.0f);
	this->playerFrame->setPosition(visibleSize.width / 2.0f + leftColumnCenter + frameOffsetX, visibleSize.height / 2.0f - frameOffsetY);
	this->enemyFrame->setPosition(visibleSize.width / 2.0f + leftColumnCenter + frameOffsetX, visibleSize.height / 2.0f + frameOffsetY);
	this->playerPadDeck->setPosition(visibleSize.width / 2.0f + rightColumnCenter, visibleSize.height / 2.0f - deckOffsetY);
	this->playerPadGrave->setPosition(visibleSize.width / 2.0f + rightColumnCenter, visibleSize.height / 2.0f - graveyardOffsetY);
	this->enemyPadDeck->setPosition(visibleSize.width / 2.0f + rightColumnCenter, visibleSize.height / 2.0f + deckOffsetY);
	this->enemyPadGrave->setPosition(visibleSize.width / 2.0f + rightColumnCenter, visibleSize.height / 2.0f + graveyardOffsetY);
	this->playerSocketA->setPosition(visibleSize.width / 2.0f + leftColumnCenter + socketAOffsetX, visibleSize.height / 2.0f - socketOffsetY);
	this->playerSocketB->setPosition(visibleSize.width / 2.0f + leftColumnCenter + socketBOffsetX, visibleSize.height / 2.0f - socketOffsetY);
	this->playerSkullA->setPosition(visibleSize.width / 2.0f + leftColumnCenter + socketAOffsetX, visibleSize.height / 2.0f - socketOffsetY);
	this->playerSkullB->setPosition(visibleSize.width / 2.0f + leftColumnCenter + socketBOffsetX, visibleSize.height / 2.0f - socketOffsetY);
	this->enemySocketA->setPosition(visibleSize.width / 2.0f + leftColumnCenter + socketAOffsetX, visibleSize.height / 2.0f + socketOffsetY);
	this->enemySocketB->setPosition(visibleSize.width / 2.0f + leftColumnCenter + socketBOffsetX, visibleSize.height / 2.0f + socketOffsetY);
	this->enemySkullA->setPosition(visibleSize.width / 2.0f + leftColumnCenter + socketAOffsetX, visibleSize.height / 2.0f + socketOffsetY);
	this->enemySkullB->setPosition(visibleSize.width / 2.0f + leftColumnCenter + socketBOffsetX, visibleSize.height / 2.0f + socketOffsetY);

	this->enemyGraveyard->setPosition(visibleSize.width / 2.0f + rightColumnCenter, visibleSize.height / 2.0f + graveyardOffsetY);
	this->playerGraveyard->setPosition(visibleSize.width / 2.0f + rightColumnCenter, visibleSize.height / 2.0f - graveyardOffsetY);
	this->enemyHand->setPosition(visibleSize.width / 2.0f + centerColumnCenter, visibleSize.height / 2.0f + handOffsetY);
	this->playerHand->setPosition(visibleSize.width / 2.0f + centerColumnCenter, visibleSize.height / 2.0f - handOffsetY);
	this->playerDeck->setPosition(visibleSize.width / 2.0f + rightColumnCenter, visibleSize.height / 2.0f - deckOffsetY);
	this->enemyDeck->setPosition(visibleSize.width / 2.0f + rightColumnCenter, visibleSize.height / 2.0f + deckOffsetY);
}

void Hexium::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Hexium::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hexium::onGameStart(EventCustom* eventCustom)
{
	Hexium::HexiumGameEventArgs* args = (Hexium::HexiumGameEventArgs*)(eventCustom->getUserData());

	this->playerGraveyard->clear();
	this->enemyGraveyard->clear();
	this->playerHand->clear();
	this->enemyHand->clear();
	this->playerDeck->clear();
	this->enemyDeck->clear();

	args->playerDeck->copyTo(this->playerDeck);
	args->enemyDeck->copyTo(this->enemyDeck);

	this->gameStart();

	GameUtils::navigate(GameUtils::GameScreen::Hexium);
}

void Hexium::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!this->isRunning() || !this->isVisible())
	{
		return;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		GameUtils::navigateBack();
		event->stopPropagation();
		break;
	}
}

void Hexium::onClose(MenuSprite* menuSprite)
{
	GameUtils::navigateBack();
}

void Hexium::gameStart()
{
	this->playerLosses = 0;
	this->enemyLosses = 0;
	this->allowControl = false;

	this->randomizeTurn();
}

void Hexium::randomizeTurn()
{
	const float turnAnimationDelay = 2.0f;

	if (RandomHelper::random_real(0.0f, 1.0f) > 0.5f)
	{
		this->turn = Turn::Player;
	}
	else
	{
		this->turn = Turn::Enemy;
	}

	// TEMP DEBUG:
	this->turn = Turn::Player;

	this->runAction(Sequence::create(
		DelayTime::create(turnAnimationDelay),
		CallFunc::create(CC_CALLBACK_0(Hexium::drawCard, this)),
		nullptr
	));
}

void Hexium::drawCard()
{
	switch (turn)
	{
	case Turn::Enemy:
		if (!this->enemyDeck->hasCards())
		{
			this->yieldControl();
			return;
		}
		break;
	case Turn::Player:
	default:
		if (!this->playerDeck->hasCards())
		{
			this->yieldControl();
			return;
		}
		break;
	}

	switch (turn)
	{
	case Turn::Enemy:
		// Simply insert the card directly into the enemy hand for the enemy
		enemyHand->insertCard(this->enemyDeck->drawCard(), 0.0f);
		break;
	case Turn::Player:
	default:
		Card * card = this->playerDeck->drawCard();
		Hand * hand = this->playerHand;
		float cardDrawDelay = 3.0f;
		float cardInsertDelay = 3.0f;

		GameUtils::changeParent(card, this, true);

		this->runAction(Sequence::create(
			CallFunc::create(CC_CALLBACK_0(Card::doDrawAnimation, card, cardDrawDelay)),
			DelayTime::create(cardDrawDelay),
			CallFunc::create(CC_CALLBACK_0(Hand::insertCard, hand, card, cardInsertDelay)),
			DelayTime::create(cardInsertDelay),
			CallFunc::create(CC_CALLBACK_0(Hexium::yieldControl, this)),
			nullptr
		));
		break;
	}
}

void Hexium::yieldControl()
{
	this->allowControl = true;
}

void Hexium::endTurn()
{

}

