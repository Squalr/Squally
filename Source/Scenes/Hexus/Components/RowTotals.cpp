#include "RowTotals.h"

// Obscure cached values with a cipher -- less confusing for those hacking the game if we hide cached values
const int RowTotals::cacheCipher = 0xdeadbeef;

RowTotals* RowTotals::create()
{
	RowTotals* instance = new RowTotals();

	instance->autorelease();

	return instance;
}

RowTotals::RowTotals()
{
	this->cachedEnemyBinaryTotal = 0;
	this->cachedEnemyDecimalTotal = 0;
	this->cachedEnemyHexTotal = 0;
	this->cachedPlayerBinaryTotal = 0;
	this->cachedPlayerDecimalTotal = 0;
	this->cachedPlayerHexTotal = 0;

	this->enemyBinaryCardTotal = Label::create("", Localization::getCodingFont(), 48.0f);
	this->enemyDecimalCardTotal = Label::create("", Localization::getCodingFont(), 48.0f);
	this->enemyHexCardTotal = Label::create("", Localization::getCodingFont(), 48.0f);
	this->playerBinaryCardTotal = Label::create("", Localization::getCodingFont(), 48.0f);
	this->playerDecimalCardTotal = Label::create("", Localization::getCodingFont(), 48.0f);
	this->playerHexCardTotal = Label::create("", Localization::getCodingFont(), 48.0f);

	this->enemyBinaryCardDeltaLabel = Label::create("", Localization::getCodingFont(), 48.0f);
	this->enemyDecimalCardDeltaLabel = Label::create("", Localization::getCodingFont(), 48.0f);
	this->enemyHexCardDeltaLabel = Label::create("", Localization::getCodingFont(), 48.0f);
	this->playerBinaryCardDeltaLabel = Label::create("", Localization::getCodingFont(), 48.0f);
	this->playerDecimalCardDeltaLabel = Label::create("", Localization::getCodingFont(), 48.0f);
	this->playerHexCardDeltaLabel = Label::create("", Localization::getCodingFont(), 48.0f);

	this->enemyBinaryCardTotal->enableOutline(Color4B::BLACK, 3);
	this->enemyDecimalCardTotal->enableOutline(Color4B::BLACK, 3);
	this->enemyHexCardTotal->enableOutline(Color4B::BLACK, 3);
	this->playerBinaryCardTotal->enableOutline(Color4B::BLACK, 3);
	this->playerDecimalCardTotal->enableOutline(Color4B::BLACK, 3);
	this->playerHexCardTotal->enableOutline(Color4B::BLACK, 3);

	this->enemyBinaryCardDeltaLabel->enableOutline(Color4B::BLACK, 3);
	this->enemyDecimalCardDeltaLabel->enableOutline(Color4B::BLACK, 3);
	this->enemyHexCardDeltaLabel->enableOutline(Color4B::BLACK, 3);
	this->playerBinaryCardDeltaLabel->enableOutline(Color4B::BLACK, 3);
	this->playerDecimalCardDeltaLabel->enableOutline(Color4B::BLACK, 3);
	this->playerHexCardDeltaLabel->enableOutline(Color4B::BLACK, 3);

	this->enemyBinaryCardTotal->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->enemyDecimalCardTotal->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->enemyHexCardTotal->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->playerBinaryCardTotal->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->playerDecimalCardTotal->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->playerHexCardTotal->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->enemyBinaryCardDeltaLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->enemyDecimalCardDeltaLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->enemyHexCardDeltaLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->playerBinaryCardDeltaLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->playerDecimalCardDeltaLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->playerHexCardDeltaLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->enemyBinaryCardDeltaLabel->setTextColor(Color4B::YELLOW);
	this->enemyDecimalCardDeltaLabel->setTextColor(Color4B::YELLOW);
	this->enemyHexCardDeltaLabel->setTextColor(Color4B::YELLOW);
	this->playerBinaryCardDeltaLabel->setTextColor(Color4B::YELLOW);
	this->playerDecimalCardDeltaLabel->setTextColor(Color4B::YELLOW);
	this->playerHexCardDeltaLabel->setTextColor(Color4B::YELLOW);

	this->addChild(this->enemyBinaryCardTotal);
	this->addChild(this->enemyDecimalCardTotal);
	this->addChild(this->enemyHexCardTotal);
	this->addChild(this->playerBinaryCardTotal);
	this->addChild(this->playerDecimalCardTotal);
	this->addChild(this->playerHexCardTotal);
	this->addChild(this->enemyBinaryCardDeltaLabel);
	this->addChild(this->enemyDecimalCardDeltaLabel);
	this->addChild(this->enemyHexCardDeltaLabel);
	this->addChild(this->playerBinaryCardDeltaLabel);
	this->addChild(this->playerDecimalCardDeltaLabel);
	this->addChild(this->playerHexCardDeltaLabel);
}

RowTotals::~RowTotals()
{
}

void RowTotals::onEnter()
{
	ComponentBase::onEnter();

	this->enemyBinaryCardDeltaLabel->setOpacity(0);
	this->enemyDecimalCardDeltaLabel->setOpacity(0);
	this->enemyHexCardDeltaLabel->setOpacity(0);
	this->playerBinaryCardDeltaLabel->setOpacity(0);
	this->playerDecimalCardDeltaLabel->setOpacity(0);
	this->playerHexCardDeltaLabel->setOpacity(0);
}

void RowTotals::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerBinaryCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY);
	this->playerDecimalCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY);
	this->playerHexCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY);

	this->enemyBinaryCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY);
	this->enemyDecimalCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY);
	this->enemyHexCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY);

	const float offsetX = 32.0f;

	this->playerBinaryCardDeltaLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY);
	this->playerDecimalCardDeltaLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY);
	this->playerHexCardDeltaLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY);

	this->enemyBinaryCardDeltaLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY);
	this->enemyDecimalCardDeltaLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY);
	this->enemyHexCardDeltaLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY);
}

void RowTotals::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void RowTotals::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);

	switch (gameState->stateType)
	{
		case GameState::StateType::GameStart:
		case GameState::StateType::GameEnd:
		case GameState::StateType::RoundStart:
		case GameState::StateType::RoundEnd:
		case GameState::StateType::TurnEnd:
		case GameState::StateType::OpponentTurnStart:
		case GameState::StateType::PlayerTurnStart:
		{
			this->readNewTotals(gameState, false);
			break;
		}
		default:
		{
			this->readNewTotals(gameState, true);
			break;
		}
	}

	this->updateTotals(gameState);
}

void RowTotals::readNewTotals(GameState* gameState, bool displayDeltas)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int newPlayerBinaryTotal = gameState->playerBinaryCards->getRowAttack();
	int newPlayerDecimalTotal = gameState->playerDecimalCards->getRowAttack();
	int newPlayerHexTotal = gameState->playerHexCards->getRowAttack();
	int newEnemyBinaryTotal = gameState->enemyBinaryCards->getRowAttack();
	int newEnemyDecimalTotal = gameState->enemyDecimalCards->getRowAttack();
	int newEnemyHexTotal = gameState->enemyHexCards->getRowAttack();

	if (newEnemyBinaryTotal != (this->cachedEnemyBinaryTotal ^ RowTotals::cacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newEnemyBinaryTotal - (this->cachedEnemyBinaryTotal ^ RowTotals::cacheCipher);

			this->runDeltaAnimation(this->enemyBinaryCardDeltaLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY, delta);
		}

		this->cachedEnemyBinaryTotal = newEnemyBinaryTotal ^ RowTotals::cacheCipher;
	}

	if (newEnemyDecimalTotal != (this->cachedEnemyDecimalTotal ^ RowTotals::cacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newEnemyDecimalTotal - (this->cachedEnemyDecimalTotal ^ RowTotals::cacheCipher);

			this->runDeltaAnimation(this->enemyDecimalCardDeltaLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY, delta);
		}
		
		this->cachedEnemyDecimalTotal = newEnemyDecimalTotal ^ RowTotals::cacheCipher;
	}

	if (newEnemyHexTotal != (this->cachedEnemyHexTotal ^ RowTotals::cacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newEnemyHexTotal - (this->cachedEnemyHexTotal ^ RowTotals::cacheCipher);

			this->runDeltaAnimation(this->enemyHexCardDeltaLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY, delta);
		}
		
		this->cachedEnemyHexTotal = newEnemyHexTotal ^ RowTotals::cacheCipher;
	}

	if (newPlayerBinaryTotal != (this->cachedPlayerBinaryTotal ^ RowTotals::cacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newPlayerBinaryTotal - (this->cachedPlayerBinaryTotal ^ RowTotals::cacheCipher);

			this->runDeltaAnimation(this->playerBinaryCardDeltaLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY, delta);
		}

		this->cachedPlayerBinaryTotal = newPlayerBinaryTotal ^ RowTotals::cacheCipher;
	}

	if (newPlayerDecimalTotal != (this->cachedPlayerDecimalTotal ^ RowTotals::cacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newPlayerDecimalTotal - (this->cachedPlayerDecimalTotal ^ RowTotals::cacheCipher);

			this->runDeltaAnimation(this->playerDecimalCardDeltaLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY, delta);
		}

		this->cachedPlayerDecimalTotal = newPlayerDecimalTotal ^ RowTotals::cacheCipher;
	}

	if (newPlayerHexTotal != (this->cachedPlayerHexTotal ^ RowTotals::cacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newPlayerHexTotal - (this->cachedPlayerHexTotal ^ RowTotals::cacheCipher);

			this->runDeltaAnimation(this->playerHexCardDeltaLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY, delta);
		}

		this->cachedPlayerHexTotal = newPlayerHexTotal ^ RowTotals::cacheCipher;
	}
}

void RowTotals::updateTotals(GameState* gameState)
{
	this->playerBinaryCardTotal->setString(std::to_string(gameState->playerBinaryCards->getRowAttack()));
	this->playerDecimalCardTotal->setString(std::to_string(gameState->playerDecimalCards->getRowAttack()));
	this->playerHexCardTotal->setString(std::to_string(gameState->playerHexCards->getRowAttack()));
	this->enemyBinaryCardTotal->setString(std::to_string(gameState->enemyBinaryCards->getRowAttack()));
	this->enemyDecimalCardTotal->setString(std::to_string(gameState->enemyDecimalCards->getRowAttack()));
	this->enemyHexCardTotal->setString(std::to_string(gameState->enemyHexCards->getRowAttack()));
}

void RowTotals::runDeltaAnimation(Label* label, float startPositionY, int delta)
{
	const float floatOffsetY = 32.0f;

	label->setPositionY(startPositionY - floatOffsetY / 4.0f);
	label->setOpacity(255);
	label->setString((delta < 0 ? "-" : "+") + std::to_string(std::abs(delta)));
	label->setTextColor(delta < 0 ? Color4B::RED : Color4B::YELLOW);
	label->runAction(MoveTo::create(1.0f, Vec2(label->getPositionX(), startPositionY + (floatOffsetY * 3.0f) / 4.0f)));
	label->runAction(FadeTo::create(1.0f, 0));
}
