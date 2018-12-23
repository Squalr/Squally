#include "TutorialBIntroSequence.h"

TutorialBIntroSequence* TutorialBIntroSequence::create()
{
	TutorialBIntroSequence* instance = new TutorialBIntroSequence();

	instance->autorelease();

	return instance;
}

TutorialBIntroSequence::TutorialBIntroSequence() : TutorialBase(StateOverride::TutorialMode::TutorialB, GameState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->scoreTotalsTutorialLabel = Label::createWithTTF("You already have a large lead over your opponent.",
		Localization::getMainFont(),
		Localization::getFontSizeP(Localization::getMainFont()),
		Size(420.0f, 0.0f)
	);
	this->handCardsTutorialLabel = Label::createWithTTF("You'll want to save your cards for the next round.",
		Localization::getMainFont(),
		Localization::getFontSizeP(Localization::getMainFont()),
		Size(640.0f, 0.0f),
		cocos2d::TextHAlignment::CENTER
	);
	this->lastStandTutorialLabel = Label::createWithTTF("Your best option is to simply defend yourself until the next round!",
		Localization::getMainFont(),
		Localization::getFontSizeP(Localization::getMainFont()),
		Size(640.0f, 0.0f),
		cocos2d::TextHAlignment::CENTER
	);
	this->helpArrowScoreTotals = HelpArrow::create();
	this->helpArrowHandCards = HelpArrow::create();
	this->helpArrowLastStand = HelpArrow::create();

	Label* scoreTotalsNextLabel = Label::createWithTTF("Next", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* scoreTotalsNextLabelSelected = Label::createWithTTF("Next", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	scoreTotalsNextLabel->enableOutline(Color4B::BLACK, 2);
	scoreTotalsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->scoreTotalsNextButton = TextMenuSprite::create(scoreTotalsNextLabel, scoreTotalsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	Label* handCardsNextLabel = Label::createWithTTF("Next", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* handCardsNextLabelSelected = Label::createWithTTF("Next", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	handCardsNextLabel->enableOutline(Color4B::BLACK, 2);
	handCardsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->handCardsNextButton = TextMenuSprite::create(handCardsNextLabel, handCardsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	Label* lastStandNextLabel = Label::createWithTTF("Got it!", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* lastStandNextLabelSelected = Label::createWithTTF("Got it!", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	lastStandNextLabel->enableOutline(Color4B::BLACK, 2);
	lastStandNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->lastStandNextButton = TextMenuSprite::create(lastStandNextLabel, lastStandNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->scoreTotalsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->handCardsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->lastStandTutorialLabel->enableOutline(Color4B::BLACK, 2);

	this->scoreTotalsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->handCardsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->lastStandTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->helpArrowScoreTotals->setRotation(-90.0f);
	this->helpArrowHandCards->setRotation(0.0f);
	this->helpArrowLastStand->setRotation(0.0f);

	this->addChild(this->focusTakeOver);
	this->addChild(this->scoreTotalsTutorialLabel);
	this->addChild(this->handCardsTutorialLabel);
	this->addChild(this->lastStandTutorialLabel);

	this->addChild(this->scoreTotalsNextButton);
	this->addChild(this->handCardsNextButton);
	this->addChild(this->lastStandNextButton);

	this->addChild(this->helpArrowScoreTotals);
	this->addChild(this->helpArrowHandCards);
	this->addChild(this->helpArrowLastStand);
}

TutorialBIntroSequence::~TutorialBIntroSequence()
{
}

void TutorialBIntroSequence::onEnter()
{
	TutorialBase::onEnter();

	this->scoreTotalsTutorialLabel->setOpacity(0);
	this->handCardsTutorialLabel->setOpacity(0);
	this->lastStandTutorialLabel->setOpacity(0);

	this->scoreTotalsNextButton->disableInteraction(0);
	this->handCardsNextButton->disableInteraction(0);
	this->lastStandNextButton->disableInteraction(0);
}

void TutorialBIntroSequence::initializePositions()
{
	TutorialBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->scoreTotalsTutorialLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 32.0f);
	this->handCardsTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 80.0f);
	this->lastStandTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + 32.0f);
	
	this->scoreTotalsNextButton->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 32.0f);
	this->handCardsNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 144.0f);
	this->lastStandNextButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - 32.0f);
	
	this->helpArrowScoreTotals->setPosition(Vec2(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX - 144.0f, visibleSize.height / 2.0f - Config::totalAttackOffsetY));
	this->helpArrowHandCards->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 288.0f));
	this->helpArrowLastStand->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + 144.0f);
}

void TutorialBIntroSequence::initializeListeners()
{
	TutorialBase::initializeListeners();
}

bool TutorialBIntroSequence::tryHijackState(GameState* gameState)
{
	this->initializeCallbacks(gameState);
	this->runTutorialScoreTotal(gameState);

	return true;
}

void TutorialBIntroSequence::onBeforeStateChange(GameState* gameState)
{
	TutorialBase::onBeforeStateChange(gameState);
}

void TutorialBIntroSequence::onAnyStateChange(GameState* gameState)
{
	TutorialBase::onAnyStateChange(gameState);
}

void TutorialBIntroSequence::initializeCallbacks(GameState* gameState)
{
	this->scoreTotalsNextButton->setClickCallback([=](MenuSprite* menuSprite, MouseEvents::MouseEventArgs* args)
	{
		this->runTutorialHandCards(gameState);
	});
	this->handCardsNextButton->setClickCallback([=](MenuSprite* menuSprite, MouseEvents::MouseEventArgs* args)
	{
		this->runTutorialLastStand(gameState);
	});
	this->lastStandNextButton->setClickCallback([=](MenuSprite* menuSprite, MouseEvents::MouseEventArgs* args)
	{
		this->concludeTutorial(gameState);
	});
}

void TutorialBIntroSequence::runTutorialScoreTotal(GameState* gameState)
{
	this->scoreTotalsNextButton->enableInteraction(0);
	this->scoreTotalsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->scoreTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowScoreTotals->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->scoreTotalPointer);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialBIntroSequence::runTutorialHandCards(GameState* gameState)
{
	this->scoreTotalsNextButton->disableInteraction();
	this->scoreTotalsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->scoreTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowScoreTotals->hidePointer();

	this->handCardsNextButton->enableInteraction(0);
	this->handCardsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowHandCards->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->playerHand);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialBIntroSequence::runTutorialLastStand(GameState* gameState)
{
	this->handCardsNextButton->disableInteraction();
	this->handCardsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowHandCards->hidePointer();

	this->lastStandNextButton->enableInteraction(0);
	this->lastStandNextButton->runAction(FadeTo::create(0.25f, 255));
	this->lastStandTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowLastStand->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->lastStandButtonPointer);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialBIntroSequence::concludeTutorial(GameState* gameState)
{
	this->lastStandNextButton->disableInteraction();
	this->lastStandNextButton->runAction(FadeTo::create(0.25f, 0));
	this->lastStandTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowLastStand->hidePointer();

	this->focusTakeOver->unfocus();
	this->unHijackState(gameState);
}
