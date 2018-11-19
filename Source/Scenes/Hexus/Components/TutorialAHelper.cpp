#include "TutorialAHelper.h"

TutorialAHelper* TutorialAHelper::create()
{
	TutorialAHelper* instance = new TutorialAHelper();

	instance->autorelease();

	return instance;
}

TutorialAHelper::TutorialAHelper()
{
	this->focusTakeOver = FocusTakeOver::create();
	this->scoreTotalsTutorialLabel = Label::create("The objective is simple. Whoever has the higher score wins the round.",
		Localization::getMainFont(),
		Localization::getFontSizeH3(Localization::getMainFont()),
		Size(320.0f, 0.0f),
		cocos2d::TextHAlignment::CENTER
	);
	this->lossDisplayTutorialLabel = Label::create("Each player starts the game with 2 lives. Whoever has the lowest score at the end of a round loses a life.",
		Localization::getMainFont(),
		Localization::getFontSizeH3(Localization::getMainFont()),
		Size(320.0f, 0.0f),
		cocos2d::TextHAlignment::CENTER
	);
	this->rowTotalsTutorialLabel = Label::create("Increase your score by playing cards onto rows.",
		Localization::getMainFont(),
		Localization::getFontSizeH3(Localization::getMainFont()),
		Size(320.0f, 0.0f),
		cocos2d::TextHAlignment::CENTER
	);
	this->handCardsTutorialLabel = Label::create("Give it a shot! Play some cards.",
		Localization::getMainFont(),
		Localization::getFontSizeH3(Localization::getMainFont()),
		Size(320.0f, 0.0f),
		cocos2d::TextHAlignment::CENTER
	);

	this->addChild(this->focusTakeOver);
	this->addChild(this->scoreTotalsTutorialLabel);
	this->addChild(this->lossDisplayTutorialLabel);
	this->addChild(this->rowTotalsTutorialLabel);
	this->addChild(this->handCardsTutorialLabel);
}

TutorialAHelper::~TutorialAHelper()
{
}

void TutorialAHelper::onEnter()
{
	ComponentBase::onEnter();

	this->scoreTotalsTutorialLabel->setOpacity(0);
	this->lossDisplayTutorialLabel->setOpacity(0);
	this->rowTotalsTutorialLabel->setOpacity(0);
	this->handCardsTutorialLabel->setOpacity(0);
}

void TutorialAHelper::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->scoreTotalsTutorialLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f);
	this->lossDisplayTutorialLabel->setPosition(visibleSize.width / 2.0f - 320.0f, visibleSize.height / 2.0f);
	this->rowTotalsTutorialLabel->setPosition(visibleSize.width / 2.0f - 128.0f, visibleSize.height / 2.0f);
	this->handCardsTutorialLabel->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 256.0f);
}

void TutorialAHelper::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void TutorialAHelper::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);

	switch (gameState->stateType)
	{
		case GameState::StateType::Tutorial:
		{
			switch (gameState->tutorialMode)
			{
				case StateOverride::TutorialMode::TutorialA:
				{
					this->runTutorial(gameState);
					break;
				}
				default:
				{
					break;
				}
			}
		}
		default:
		{
			break;
		}
	}
}

void TutorialAHelper::runTutorial(GameState* gameState)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			std::vector<Node*> focusTargets = std::vector<Node*>();
			focusTargets.push_back(gameState->scoreTotalPointer);
			this->focusTakeOver->focus(focusTargets);
			this->scoreTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
		}),
		DelayTime::create(5.0f),
		CallFunc::create([=]()
		{
			this->scoreTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
			std::vector<Node*> focusTargets = std::vector<Node*>();
			focusTargets.push_back(gameState->lossesDisplayPointer);
			this->focusTakeOver->focus(focusTargets);
			this->lossDisplayTutorialLabel->runAction(FadeTo::create(0.25f, 255));
		}),
		DelayTime::create(5.0f),
		CallFunc::create([=]()
		{
			this->lossDisplayTutorialLabel->runAction(FadeTo::create(0.25f, 0));
			std::vector<Node*> focusTargets = std::vector<Node*>();
			focusTargets.push_back(gameState->rowTotalsPointer);
			focusTargets.push_back(gameState->enemyBinaryCards);
			focusTargets.push_back(gameState->enemyDecimalCards);
			focusTargets.push_back(gameState->enemyHexCards);
			focusTargets.push_back(gameState->playerBinaryCards);
			focusTargets.push_back(gameState->playerDecimalCards);
			focusTargets.push_back(gameState->playerHexCards);
			this->focusTakeOver->focus(focusTargets);
			this->rowTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
		}),
		DelayTime::create(5.0f),
		CallFunc::create([=]()
		{
			this->rowTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
			std::vector<Node*> focusTargets = std::vector<Node*>();
			focusTargets.push_back(gameState->playerHand);
			this->focusTakeOver->focus(focusTargets);
			this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
		}),
		DelayTime::create(5.0f),
		CallFunc::create([=]()
		{
			this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
			this->focusTakeOver->unfocus();
			gameState->updateState(gameState, GameState::StateType::Neutral);
		}),
		nullptr
	));
}
