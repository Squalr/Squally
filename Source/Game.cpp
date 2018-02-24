#include "Game.h"

Game* Game::create()
{
	Game* game = new Game();

	game->autorelease();

	return game;
}

Game::Game()
{
	this->sceneHistory = new std::stack<Scene*>();
	this->titleScreen = TitleScreen::create();
	this->tutorialScreen = TutorialScreen::create();
	this->storyMap = StoryMap::create();
	this->level = Level::create();
	this->optionsMenu = OptionsMenu::create();
	this->pauseMenu = PauseMenu::create();
	this->confirmationMenu = ConfirmationMenu::create();
	this->hexium = Hexium::create();

	// Start title screen first (TODO: Eventually splash screen? Do we want one?)
	this->titleScreen->addChild(this);
	Director::getInstance()->runWithScene(this->titleScreen);

	this->initializeEventListeners();

	// Prevent disposal of game objects
	this->titleScreen->retain();
	this->tutorialScreen->retain();
	this->storyMap->retain();
	this->level->retain();
	this->optionsMenu->retain();
	this->pauseMenu->retain();
	this->confirmationMenu->retain();
	this->hexium->retain();
}

Game::~Game()
{
	delete(this->sceneHistory);
}

void Game::initializeEventListeners()
{
	EventListenerCustom* navigateNewEventListener = EventListenerCustom::create(
		GameUtils::gameNavigateNewEvent,
		CC_CALLBACK_1(Game::onGameNavigateNew, this)
	);

	EventListenerCustom* navigateBackEventListener = EventListenerCustom::create(
		GameUtils::gameNavigateBackEvent,
		CC_CALLBACK_1(Game::onGameNavigateBack, this)
	);

	EventListenerCustom* navigateNewLevelEventListener = EventListenerCustom::create(
		GameUtils::gameNavigateNewLevelEvent,
		CC_CALLBACK_1(Game::onGameNavigateNewLevel, this)
	);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateNewEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateBackEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateNewLevelEventListener, this);
}

void Game::onGameNavigateNew(EventCustom* eventCustom)
{
	GameUtils::NavigateEventArgs* args = (GameUtils::NavigateEventArgs*)(eventCustom->getUserData());
	Scene* newScene = nullptr;

	switch (args->gameScreen)
	{
	case GameUtils::GameScreen::Title:
		newScene = this->titleScreen;
		break;
	case GameUtils::GameScreen::Tutorial:
		newScene = this->tutorialScreen;
		break;
	case GameUtils::GameScreen::StoryMap:
		newScene = this->storyMap;
		break;
	case GameUtils::GameScreen::Pause:
		newScene = this->pauseMenu;
		break;
	case GameUtils::GameScreen::Options:
		newScene = this->optionsMenu;
		break;
	case GameUtils::GameScreen::Confirm:
		newScene = this->confirmationMenu;
		break;
	case GameUtils::GameScreen::Level:
		newScene = this->level;
		break;
	case GameUtils::GameScreen::Hexium:
		newScene = this->hexium;
		break;
	}

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->loadScene(newScene);
}

void Game::onGameNavigateBack(EventCustom* eventCustom)
{
	GameUtils::NavigateBackEventArgs* args = (GameUtils::NavigateBackEventArgs*)(eventCustom->getUserData());

	Scene* scene = Director::getInstance()->getRunningScene();

	for (int index = 0; index < args->backCount; index++)
	{
		if (this->sceneHistory->size() <= 0)
		{
			break;
		}

		scene = this->sceneHistory->top();
		this->sceneHistory->pop();
	}

	this->loadScene(scene);
}

void Game::onGameNavigateConfirm(EventCustom* eventCustom)
{
	GameUtils::NavigateConfirmArgs* args = (GameUtils::NavigateConfirmArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->confirmationMenu->initialize(args->message, args->confirmCallback, args->cancelCallback);
	this->loadScene(this->confirmationMenu);
}

void Game::onGameNavigateNewLevel(EventCustom* eventCustom)
{
	GameUtils::NavigateNewLevelArgs* args = (GameUtils::NavigateNewLevelArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->level->loadLevel(args->levelFile);
	this->loadScene(this->level);
}

void Game::loadScene(Scene* scene)
{
	// Although this is counter-intuitive, add Game as a child to whichever scene is active.
	// This will allows for Game to listen for navigation events while the active scene runs.
	this->getParent()->removeChild(this);
	scene->addChild(this);
	Director::getInstance()->replaceScene(scene);
	this->initializeEventListeners();
}
