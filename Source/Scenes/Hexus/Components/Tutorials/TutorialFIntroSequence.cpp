#include "TutorialFIntroSequence.h"

TutorialFIntroSequence* TutorialFIntroSequence::create()
{
	TutorialFIntroSequence* instance = new TutorialFIntroSequence();

	instance->autorelease();

	return instance;
}

TutorialFIntroSequence::TutorialFIntroSequence() : TutorialBase(StateOverride::TutorialMode::TutorialF, GameState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->handCardsTutorialLabel = Label::createWithTTF("The 'MOV' card copies the attack from one of your cards to any other card! Use it to weaken your opponent!",
		Localization::getMainFont(),
		Localization::getFontSizeP(Localization::getMainFont()),
		Size(640.0f, 0.0f),
		cocos2d::TextHAlignment::CENTER
	);
	this->helpArrowHandCards = HelpArrow::create();

	Label* handCardsNextLabel = Label::createWithTTF("Got it!", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* handCardsNextLabelSelected = Label::createWithTTF("Got it!", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	handCardsNextLabel->enableOutline(Color4B::BLACK, 2);
	handCardsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->handCardsNextButton = TextMenuSprite::create(handCardsNextLabel, handCardsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->handCardsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->handCardsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->helpArrowHandCards->setRotation(0.0f);

	this->addChild(this->focusTakeOver);
	this->addChild(this->handCardsTutorialLabel);
	this->addChild(this->handCardsNextButton);
	this->addChild(this->helpArrowHandCards);
}

TutorialFIntroSequence::~TutorialFIntroSequence()
{
}

void TutorialFIntroSequence::onEnter()
{
	TutorialBase::onEnter();

	this->handCardsTutorialLabel->setOpacity(0);

	this->handCardsNextButton->disableInteraction(0);
}

void TutorialFIntroSequence::initializePositions()
{
	TutorialBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->handCardsTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 80.0f);
	this->handCardsNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 144.0f);
	this->helpArrowHandCards->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 288.0f));
}

void TutorialFIntroSequence::initializeListeners()
{
	TutorialBase::initializeListeners();
}

bool TutorialFIntroSequence::tryHijackState(GameState* gameState)
{
	this->initializeCallbacks(gameState);
	this->runTutorialHandCards(gameState);

	return true;
}

void TutorialFIntroSequence::onBeforeStateChange(GameState* gameState)
{
	TutorialBase::onBeforeStateChange(gameState);
}

void TutorialFIntroSequence::onAnyStateChange(GameState* gameState)
{
	TutorialBase::onAnyStateChange(gameState);
}

void TutorialFIntroSequence::initializeCallbacks(GameState* gameState)
{
	this->handCardsNextButton->setClickCallback([=](MenuSprite* menuSprite, MouseEvents::MouseEventArgs* args)
	{
		this->concludeTutorial(gameState);
	});
}

void TutorialFIntroSequence::runTutorialHandCards(GameState* gameState)
{
	this->handCardsNextButton->enableInteraction(0);
	this->handCardsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowHandCards->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->playerHand);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialFIntroSequence::concludeTutorial(GameState* gameState)
{
	this->handCardsNextButton->disableInteraction();
	this->handCardsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowHandCards->hidePointer();

	this->focusTakeOver->unfocus();
	this->unHijackState(gameState);
}
