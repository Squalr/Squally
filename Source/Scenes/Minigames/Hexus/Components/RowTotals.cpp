#include "RowTotals.h"

RowTotals* RowTotals::create()
{
	RowTotals* rowTotals = new RowTotals();

	rowTotals->autorelease();

	return rowTotals;
}

RowTotals::RowTotals()
{
	this->enemyBinaryCardTotal = Label::create("", Resources::Fonts_UbuntuMono_Bold, 48.0f);
	this->enemyBinaryCardTotal->enableOutline(Color4B::BLACK, 3);
	this->enemyDecimalCardTotal = Label::create("", Resources::Fonts_UbuntuMono_Bold, 48.0f);
	this->enemyDecimalCardTotal->enableOutline(Color4B::BLACK, 3);
	this->enemyHexCardTotal = Label::create("", Resources::Fonts_UbuntuMono_Bold, 48.0f);
	this->enemyHexCardTotal->enableOutline(Color4B::BLACK, 3);
	this->playerBinaryCardTotal = Label::create("", Resources::Fonts_UbuntuMono_Bold, 48.0f);
	this->playerBinaryCardTotal->enableOutline(Color4B::BLACK, 3);
	this->playerDecimalCardTotal = Label::create("", Resources::Fonts_UbuntuMono_Bold, 48.0f);
	this->playerDecimalCardTotal->enableOutline(Color4B::BLACK, 3);
	this->playerHexCardTotal = Label::create("", Resources::Fonts_UbuntuMono_Bold, 48.0f);
	this->playerHexCardTotal->enableOutline(Color4B::BLACK, 3);

	this->addChild(this->enemyBinaryCardTotal);
	this->addChild(this->enemyDecimalCardTotal);
	this->addChild(this->enemyHexCardTotal);
	this->addChild(this->playerBinaryCardTotal);
	this->addChild(this->playerDecimalCardTotal);
	this->addChild(this->playerHexCardTotal);
}

RowTotals::~RowTotals()
{
}

void RowTotals::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void RowTotals::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerBinaryCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY - 0.0f);
	this->playerDecimalCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY - 0.0f);
	this->playerHexCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY - 0.0f);

	this->enemyBinaryCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY + 0.0f);
	this->enemyDecimalCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY + 0.0f);
	this->enemyHexCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY + 0.0f);
}

void RowTotals::initializeListeners()
{
}

void RowTotals::onStateChange(GameState* gameState)
{
	this->updateTotals(gameState);
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
