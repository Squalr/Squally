#include "SceneDirector.h"

SceneDirector* SceneDirector::create()
{
	SceneDirector* game = new SceneDirector();

	game->autorelease();

	return game;
}

SceneDirector::SceneDirector()
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
	this->hexus = Hexus::create();

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
	this->hexus->retain();
}

SceneDirector::~SceneDirector()
{
	delete(this->sceneHistory);
}

void SceneDirector::initializeEventListeners()
{
	EventListenerCustom* navigateNewEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateNewEvent,
		CC_CALLBACK_1(SceneDirector::onGameNavigateNew, this)
	);

	EventListenerCustom* navigateBackEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateBackEvent,
		CC_CALLBACK_1(SceneDirector::onGameNavigateBack, this)
	);

	EventListenerCustom* navigateNewLevelEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateLoadLevelEvent,
		CC_CALLBACK_1(SceneDirector::onGameNavigateLoadLevel, this)
	);

	EventListenerCustom* navigateEnterLevelEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateEnterLevelEvent,
		CC_CALLBACK_1(SceneDirector::onGameNavigateEnterLevel, this)
	);

	EventListenerCustom* navigateFightEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateFightEvent,
		CC_CALLBACK_1(SceneDirector::onGameNavigateFight, this)
	);

	EventListenerCustom* navigateConfirmEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateConfirmEvent,
		CC_CALLBACK_1(SceneDirector::onGameNavigateConfirm, this)
	);

	EventListenerCustom* hexiumGameStartListener = EventListenerCustom::create(
		HexusEvents::HexusGameStartEvent,
		CC_CALLBACK_1(Hexus::onGameStart, this->hexus)
	);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hexiumGameStartListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateNewEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateBackEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateNewLevelEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateEnterLevelEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateFightEventListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateConfirmEventListener, this);
}

void SceneDirector::onGameNavigateNew(EventCustom* eventCustom)
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
	case NavigationEvents::GameScreen::Hexus:
		newScene = this->hexus;
		break;
	}

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->loadScene(newScene);
}

void SceneDirector::onGameNavigateBack(EventCustom* eventCustom)
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

void SceneDirector::onGameNavigateConfirm(EventCustom* eventCustom)
{
	NavigationEvents::NavigateConfirmArgs* args = (NavigationEvents::NavigateConfirmArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->confirmationMenu->initialize(args->message, args->confirmCallback, args->cancelCallback);
	this->loadScene(this->confirmationMenu);
}

void SceneDirector::onGameNavigateLoadLevel(EventCustom* eventCustom)
{
	NavigationEvents::NavigateLoadLevelArgs* args = (NavigationEvents::NavigateLoadLevelArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->loadScene(this->loadingScreen);
	this->loadingScreen->loadLevel(args->levelFile, [](SerializableMap* levelMap){ NavigationEvents::enterLevel(levelMap); });
}

void SceneDirector::onGameNavigateEnterLevel(EventCustom* eventCustom)
{
	NavigationEvents::NavigateEnterLevelArgs* args = (NavigationEvents::NavigateEnterLevelArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());

	// Destroy the current level object explicitly and re-create it
	this->level->release();
	this->level = Level::create();
	this->level->retain();

	this->level->loadLevel(args->levelMap);
	this->loadScene(this->level);
}

void SceneDirector::onGameNavigateFight(EventCustom* eventCustom)
{
	NavigationEvents::NavigateFightArgs* args = (NavigationEvents::NavigateFightArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->fight->loadFight(args->player, args->enemy);
	this->loadScene(this->fight);
}

void SceneDirector::loadScene(Scene* scene)
{
	// Although this is counter-intuitive, add the Scene Director as a child to whichever scene is active.
	// This will allows for the Scene Director to listen for navigation events while the active scene runs.
	this->getParent()->removeChild(this);
	scene->addChild(this);
	Director::getInstance()->replaceScene(scene);
	this->initializeEventListeners();
}
