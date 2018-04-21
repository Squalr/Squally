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
	this->loadingScreen = LoadingScreen::create();
	this->level = Level::create();
	this->fight = Fight::create();
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
	this->loadingScreen->retain();
	this->level->retain();
	this->fight->retain();
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
		NavigationEvents::gameNavigateNewEvent,
		CC_CALLBACK_1(Game::onGameNavigateNew, this)
	);

	EventListenerCustom* navigateBackEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateBackEvent,
		CC_CALLBACK_1(Game::onGameNavigateBack, this)
	);

	EventListenerCustom* navigateNewLevelEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateLoadLevelEvent,
		CC_CALLBACK_1(Game::onGameNavigateLoadLevel, this)
	);

	EventListenerCustom* navigateEnterLevelEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateEnterLevelEvent,
		CC_CALLBACK_1(Game::onGameNavigateEnterLevel, this)
	);

	EventListenerCustom* navigateFightEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateFightEvent,
		CC_CALLBACK_1(Game::onGameNavigateFight, this)
	);

	EventListenerCustom* navigateConfirmEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateConfirmEvent,
		CC_CALLBACK_1(Game::onGameNavigateConfirm, this)
	);

	EventListenerCustom* hexiumGameStartListener = EventListenerCustom::create(
		HexusEvents::HexusGameStartEvent,
		CC_CALLBACK_1(Hexium::onGameStart, this->hexium)
	);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hexiumGameStartListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateNewEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateBackEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateNewLevelEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateEnterLevelEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateFightEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateConfirmEventListener, this);
}

void Game::onGameNavigateNew(EventCustom* eventCustom)
{
	NavigationEvents::NavigateEventArgs* args = (NavigationEvents::NavigateEventArgs*)(eventCustom->getUserData());
	Scene* newScene = nullptr;

	switch (args->gameScreen)
	{
	case NavigationEvents::GameScreen::Title:
		newScene = this->titleScreen;
		break;
	case NavigationEvents::GameScreen::Tutorial:
		newScene = this->tutorialScreen;
		break;
	case NavigationEvents::GameScreen::StoryMap:
		newScene = this->storyMap;
		break;
	case NavigationEvents::GameScreen::Pause:
		newScene = this->pauseMenu;
		break;
	case NavigationEvents::GameScreen::Options:
		newScene = this->optionsMenu;
		break;
	case NavigationEvents::GameScreen::Confirm:
		newScene = this->confirmationMenu;
		break;
	case NavigationEvents::GameScreen::Loading:
		newScene = this->loadingScreen;
		break;
	case NavigationEvents::GameScreen::Level:
		newScene = this->level;
		break;
	case NavigationEvents::GameScreen::Hexium:
		newScene = this->hexium;
		break;
	}

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->loadScene(newScene);
}

void Game::onGameNavigateBack(EventCustom* eventCustom)
{
	NavigationEvents::NavigateBackEventArgs* args = (NavigationEvents::NavigateBackEventArgs*)(eventCustom->getUserData());

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
	NavigationEvents::NavigateConfirmArgs* args = (NavigationEvents::NavigateConfirmArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->confirmationMenu->initialize(args->message, args->confirmCallback, args->cancelCallback);
	this->loadScene(this->confirmationMenu);
}

void Game::onGameNavigateLoadLevel(EventCustom* eventCustom)
{
	NavigationEvents::NavigateLoadLevelArgs* args = (NavigationEvents::NavigateLoadLevelArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->loadScene(this->loadingScreen);
	this->loadingScreen->loadLevel(args->levelFile);
}

void Game::onGameNavigateEnterLevel(EventCustom* eventCustom)
{
	NavigationEvents::NavigateEnterLevelArgs* args = (NavigationEvents::NavigateEnterLevelArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->level->loadLevel(args->levelMap);
	this->loadScene(this->level);
}

void Game::onGameNavigateFight(EventCustom* eventCustom)
{
	NavigationEvents::NavigateFightArgs* args = (NavigationEvents::NavigateFightArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->fight->loadFight(args->player, args->enemy);
	this->loadScene(this->fight);
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
