#include "RowTotals.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Common/Constant.h"
#include "Strings/Common/PlusConstant.h"
#include "Strings/Common/MinusConstant.h"

using namespace cocos2d;

// Obscure cached values with a cipher -- less confusing for those hacking the game if we hide cached values
const int RowTotals::CacheCipher = 0xdeadbeef;

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

	this->enemyBinaryTotalSocket = Sprite::create(HexusResources::RowTotalSocketBin);
	this->enemyDecimalTotalSocket = Sprite::create(HexusResources::RowTotalSocketDec);
	this->enemyHexTotalSocket = Sprite::create(HexusResources::RowTotalSocketHex);
	this->playerBinaryTotalSocket = Sprite::create(HexusResources::RowTotalSocketBin);
	this->playerDecimalTotalSocket = Sprite::create(HexusResources::RowTotalSocketDec);
	this->playerHexTotalSocket = Sprite::create(HexusResources::RowTotalSocketHex);

	this->enemyBinaryCardTotal = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_Constant::create());
	this->enemyDecimalCardTotal = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_Constant::create());
	this->enemyHexCardTotal = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_Constant::create());
	this->playerBinaryCardTotal = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_Constant::create());
	this->playerDecimalCardTotal = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_Constant::create());
	this->playerHexCardTotal = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_Constant::create());

	this->enemyBinaryCardIncreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_PlusConstant::create());
	this->enemyDecimalCardIncreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_PlusConstant::create());
	this->enemyHexCardIncreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_PlusConstant::create());
	this->playerBinaryCardIncreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_PlusConstant::create());
	this->playerDecimalCardIncreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_PlusConstant::create());
	this->playerHexCardIncreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_PlusConstant::create());

	this->enemyBinaryCardDecreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_MinusConstant::create());
	this->enemyDecimalCardDecreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_MinusConstant::create());
	this->enemyHexCardDecreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_MinusConstant::create());
	this->playerBinaryCardDecreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_MinusConstant::create());
	this->playerDecimalCardDecreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_MinusConstant::create());
	this->playerHexCardDecreaseLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, Strings::Common_MinusConstant::create());

	std::vector<LocalizedLabel*> deltaLabels = std::vector<LocalizedLabel*>({
		this->enemyBinaryCardIncreaseLabel,
		this->enemyDecimalCardIncreaseLabel,
		this->enemyHexCardIncreaseLabel,
		this->playerBinaryCardIncreaseLabel,
		this->playerDecimalCardIncreaseLabel,
		this->playerHexCardIncreaseLabel,

		this->enemyBinaryCardDecreaseLabel,
		this->enemyDecimalCardDecreaseLabel,
		this->enemyHexCardDecreaseLabel,
		this->playerBinaryCardDecreaseLabel,
		this->playerDecimalCardDecreaseLabel,
		this->playerHexCardDecreaseLabel,
		});

	std::vector<LocalizedLabel*> allLabels = std::vector<LocalizedLabel*>({
		this->enemyBinaryCardTotal,
		this->enemyDecimalCardTotal,
		this->enemyHexCardTotal,
		this->playerBinaryCardTotal,
		this->playerDecimalCardTotal,
		this->playerHexCardTotal,
	});

	for (auto it = deltaLabels.begin(); it != deltaLabels.end(); it++)
	{
		allLabels.push_back(*it);
		(*it)->setTextColor(Color4B::YELLOW);
		(*it)->setOpacity(0);
	}

	for (auto it = allLabels.begin(); it != allLabels.end(); it++)
	{
		(*it)->enableOutline(Color4B::BLACK, 3);
		(*it)->setAnchorPoint(Vec2(0.5f, 0.5f));
	}

	this->addChild(this->enemyBinaryTotalSocket);
	this->addChild(this->enemyDecimalTotalSocket);
	this->addChild(this->enemyHexTotalSocket);
	this->addChild(this->playerBinaryTotalSocket);
	this->addChild(this->playerDecimalTotalSocket);
	this->addChild(this->playerHexTotalSocket);

	this->enemyBinaryTotalSocket->addChild(this->enemyBinaryCardTotal);
	this->enemyDecimalTotalSocket->addChild(this->enemyDecimalCardTotal);
	this->enemyHexTotalSocket->addChild(this->enemyHexCardTotal);
	this->playerBinaryTotalSocket->addChild(this->playerBinaryCardTotal);
	this->playerDecimalTotalSocket->addChild(this->playerDecimalCardTotal);
	this->playerHexTotalSocket->addChild(this->playerHexCardTotal);

	for (auto it = deltaLabels.begin(); it != deltaLabels.end(); it++)
	{
		this->addChild(*it);
	}
}

RowTotals::~RowTotals()
{
}

void RowTotals::onEnter()
{
	super::onEnter();

	this->enemyBinaryCardIncreaseLabel->setOpacity(0);
	this->enemyDecimalCardIncreaseLabel->setOpacity(0);
	this->enemyHexCardIncreaseLabel->setOpacity(0);
	this->playerBinaryCardIncreaseLabel->setOpacity(0);
	this->playerDecimalCardIncreaseLabel->setOpacity(0);
	this->playerHexCardIncreaseLabel->setOpacity(0);

	this->enemyBinaryCardDecreaseLabel->setOpacity(0);
	this->enemyDecimalCardDecreaseLabel->setOpacity(0);
	this->enemyHexCardDecreaseLabel->setOpacity(0);
	this->playerBinaryCardDecreaseLabel->setOpacity(0);
	this->playerDecimalCardDecreaseLabel->setOpacity(0);
	this->playerHexCardDecreaseLabel->setOpacity(0);
}

void RowTotals::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyBinaryTotalSocket->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY);
	this->enemyDecimalTotalSocket->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY);
	this->enemyHexTotalSocket->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY);

	this->playerBinaryTotalSocket->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY);
	this->playerDecimalTotalSocket->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY);
	this->playerHexTotalSocket->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY);

	this->enemyBinaryCardTotal->setPosition(this->enemyBinaryTotalSocket->getContentSize() / 2.0f);
	this->enemyDecimalCardTotal->setPosition(this->enemyDecimalTotalSocket->getContentSize() / 2.0f);
	this->enemyHexCardTotal->setPosition(this->enemyHexTotalSocket->getContentSize() / 2.0f);

	this->playerBinaryCardTotal->setPosition(this->playerBinaryTotalSocket->getContentSize() / 2.0f);
	this->playerDecimalCardTotal->setPosition(this->playerDecimalTotalSocket->getContentSize() / 2.0f);
	this->playerHexCardTotal->setPosition(this->playerHexTotalSocket->getContentSize() / 2.0f);

	const float offsetX = 32.0f;

	this->playerBinaryCardIncreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY);
	this->playerDecimalCardIncreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY);
	this->playerHexCardIncreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY);

	this->playerBinaryCardDecreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY);
	this->playerDecimalCardDecreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY);
	this->playerHexCardDecreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY);

	this->enemyBinaryCardIncreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY);
	this->enemyDecimalCardIncreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY);
	this->enemyHexCardIncreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY);
	
	this->enemyBinaryCardDecreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY);
	this->enemyDecimalCardDecreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY);
	this->enemyHexCardDecreaseLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX + offsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY);
}

void RowTotals::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void RowTotals::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);

	switch (gameState->stateType)
	{
		case GameState::StateType::GameStart:
		case GameState::StateType::GameEnd:
		case GameState::StateType::RoundStart:
		case GameState::StateType::RoundEnd:
		case GameState::StateType::TurnEnd:
		case GameState::StateType::OpponentTurnStart:
		case GameState::StateType::PlayerTurnStart:
		case GameState::StateType::Tutorial:
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

	if (newEnemyBinaryTotal != (this->cachedEnemyBinaryTotal ^ RowTotals::CacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newEnemyBinaryTotal - (this->cachedEnemyBinaryTotal ^ RowTotals::CacheCipher);

			this->runDeltaAnimation(delta >= 0 ? this->enemyBinaryCardIncreaseLabel : this->enemyBinaryCardDecreaseLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY, delta);
		}

		this->cachedEnemyBinaryTotal = newEnemyBinaryTotal ^ RowTotals::CacheCipher;
	}

	if (newEnemyDecimalTotal != (this->cachedEnemyDecimalTotal ^ RowTotals::CacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newEnemyDecimalTotal - (this->cachedEnemyDecimalTotal ^ RowTotals::CacheCipher);

			this->runDeltaAnimation(delta >= 0 ? this->enemyDecimalCardIncreaseLabel : this->enemyDecimalCardDecreaseLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY, delta);
		}
		
		this->cachedEnemyDecimalTotal = newEnemyDecimalTotal ^ RowTotals::CacheCipher;
	}

	if (newEnemyHexTotal != (this->cachedEnemyHexTotal ^ RowTotals::CacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newEnemyHexTotal - (this->cachedEnemyHexTotal ^ RowTotals::CacheCipher);

			this->runDeltaAnimation(delta >= 0 ? this->enemyHexCardIncreaseLabel : this->enemyHexCardDecreaseLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY, delta);
		}
		
		this->cachedEnemyHexTotal = newEnemyHexTotal ^ RowTotals::CacheCipher;
	}

	if (newPlayerBinaryTotal != (this->cachedPlayerBinaryTotal ^ RowTotals::CacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newPlayerBinaryTotal - (this->cachedPlayerBinaryTotal ^ RowTotals::CacheCipher);

			this->runDeltaAnimation(delta >= 0 ? this->playerBinaryCardIncreaseLabel : this->playerBinaryCardDecreaseLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY, delta);
		}

		this->cachedPlayerBinaryTotal = newPlayerBinaryTotal ^ RowTotals::CacheCipher;
	}

	if (newPlayerDecimalTotal != (this->cachedPlayerDecimalTotal ^ RowTotals::CacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newPlayerDecimalTotal - (this->cachedPlayerDecimalTotal ^ RowTotals::CacheCipher);

			this->runDeltaAnimation(delta >= 0 ? this->playerDecimalCardIncreaseLabel : this->playerDecimalCardDecreaseLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY, delta);
		}

		this->cachedPlayerDecimalTotal = newPlayerDecimalTotal ^ RowTotals::CacheCipher;
	}

	if (newPlayerHexTotal != (this->cachedPlayerHexTotal ^ RowTotals::CacheCipher))
	{
		if (displayDeltas)
		{
			int delta = newPlayerHexTotal - (this->cachedPlayerHexTotal ^ RowTotals::CacheCipher);

			this->runDeltaAnimation(delta >= 0 ? this->playerHexCardIncreaseLabel : this->playerHexCardDecreaseLabel, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY, delta);
		}

		this->cachedPlayerHexTotal = newPlayerHexTotal ^ RowTotals::CacheCipher;
	}
}

void RowTotals::updateTotals(GameState* gameState)
{
	this->playerBinaryCardTotal->setStringReplacementVariables(ConstantString::create(std::to_string(gameState->playerBinaryCards->getRowAttack())));
	this->playerDecimalCardTotal->setStringReplacementVariables(ConstantString::create(std::to_string(gameState->playerDecimalCards->getRowAttack())));
	this->playerHexCardTotal->setStringReplacementVariables(ConstantString::create(std::to_string(gameState->playerHexCards->getRowAttack())));
	this->enemyBinaryCardTotal->setStringReplacementVariables(ConstantString::create(std::to_string(gameState->enemyBinaryCards->getRowAttack())));
	this->enemyDecimalCardTotal->setStringReplacementVariables(ConstantString::create(std::to_string(gameState->enemyDecimalCards->getRowAttack())));
	this->enemyHexCardTotal->setStringReplacementVariables(ConstantString::create(std::to_string(gameState->enemyHexCards->getRowAttack())));
}

void RowTotals::runDeltaAnimation(LocalizedLabel* label, float startPositionY, int delta)
{
	const float floatOffsetY = 32.0f;

	ConstantString* valueString = ConstantString::create(std::to_string(std::abs(delta)));

	label->setStringReplacementVariables(valueString);

	label->setPositionY(startPositionY - floatOffsetY / 4.0f);
	label->setOpacity(255);
	label->setTextColor(delta < 0 ? Color4B::RED : Color4B::YELLOW);
	label->runAction(MoveTo::create(1.0f, Vec2(label->getPositionX(), startPositionY + (floatOffsetY * 3.0f) / 4.0f)));
	label->runAction(FadeTo::create(1.0f, 0));
}
