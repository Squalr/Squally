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

	this->addChild(this->focusTakeOver);
}

TutorialAHelper::~TutorialAHelper()
{
}

void TutorialAHelper::onEnter()
{
	ComponentBase::onEnter();
}

void TutorialAHelper::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
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
	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			std::vector<Node*> focusTargets = std::vector<Node*>();
			focusTargets.push_back(gameState->playerDeck);
			this->focusTakeOver->focus(focusTargets);
		}),
		DelayTime::create(2.0f),
		CallFunc::create([=]()
		{
			std::vector<Node*> focusTargets = std::vector<Node*>();
			focusTargets.push_back(gameState->playerHand);
			this->focusTakeOver->focus(focusTargets);
		}),
		nullptr
	));
}
