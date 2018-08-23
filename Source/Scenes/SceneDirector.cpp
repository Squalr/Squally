#include "SceneDirector.h"

SceneDirector* SceneDirector::instance = nullptr;

void SceneDirector::registerGlobalNode()
{
	if (SceneDirector::instance == nullptr)
	{
		SceneDirector::instance = new SceneDirector();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(SceneDirector::instance);
	}
}

SceneDirector::SceneDirector()
{
	this->sceneHistory = new std::stack<Scene*>();
	this->titleScreen = TitleScreen::create();
	this->tutorialScreen = TutorialScreen::create();
	this->storyMap = StoryMap::create();
	this->loadingScreen = LoadingScreen::create();
	this->map = nullptr;
	this->fight = Fight::create();
	this->optionsMenu = OptionsMenu::create();
	this->pauseMenu = PauseMenu::create();
	this->confirmationMenu = ConfirmationMenu::create();
	this->hexus = Hexus::create();

	// Start title screen first (TODO: Eventually splash screen? Do we want one?)
	GlobalDirector::getInstance()->loadScene(this->titleScreen);

	// Prevent disposal of game objects
	this->titleScreen->retain();
	this->tutorialScreen->retain();
	this->storyMap->retain();
	this->loadingScreen->retain();
	// this->map->retain(); // Initially nullptr -- do not retain
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

	EventListenerCustom* navigateCutsceneEventListener = EventListenerCustom::create(
		NavigationEvents::gameNavigateLoadCutsceneEvent,
		CC_CALLBACK_1(SceneDirector::onGameNavigateLoadCutscene, this)
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
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(navigateCutsceneEventListener, this);
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
		newScene = this->map;
		break;
	case NavigationEvents::GameScreen::Hexus:
		newScene = this->hexus;
		break;
	}

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	GlobalDirector::getInstance()->loadScene(newScene);
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

	GlobalDirector::getInstance()->loadScene(scene);
}

void SceneDirector::onGameNavigateConfirm(EventCustom* eventCustom)
{
	NavigationEvents::NavigateConfirmArgs* args = (NavigationEvents::NavigateConfirmArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->confirmationMenu->initialize(args->message, args->confirmCallback, args->cancelCallback);
	GlobalDirector::getInstance()->loadScene(this->confirmationMenu);
}

void SceneDirector::onGameNavigateLoadCutscene(EventCustom* eventCustom)
{
	NavigationEvents::NavigateLoadCutsceneArgs* args = (NavigationEvents::NavigateLoadCutsceneArgs*)(eventCustom->getUserData());

	switch (args->cutscene)
	{
	case NavigationEvents::CutsceneEnum::CutsceneCity:
		this->cutscene = City::create();
		break;
	case NavigationEvents::CutsceneEnum::CutsceneIntroSpace:
		this->cutscene = IntroSpace::create();
		break;
	case NavigationEvents::CutsceneEnum::CutsceneVaporWeb:
		this->cutscene = VaporWeb::create();
		break;
	default:
		break;
	}

	// Load the scene (don't add it to scene history -- it does not make sense to ever be able to navigate 'back' to a cutscene
	GlobalDirector::getInstance()->loadScene(this->cutscene);
}

void SceneDirector::onGameNavigateLoadLevel(EventCustom* eventCustom)
{
	NavigationEvents::NavigateLoadLevelArgs* args = (NavigationEvents::NavigateLoadLevelArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	GlobalDirector::getInstance()->loadScene(this->loadingScreen);
	this->loadingScreen->loadLevel(args->levelFile, [](SerializableMap* levelMap){ NavigationEvents::enterLevel(levelMap); });
}

void SceneDirector::onGameNavigateEnterLevel(EventCustom* eventCustom)
{
	NavigationEvents::NavigateEnterLevelArgs* args = (NavigationEvents::NavigateEnterLevelArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());

	// Destroy the current level object explicitly and re-create it
	if (this->map != nullptr)
	{
		this->map->release();
	}

	if (args->levelMap->isPlatformer()) {
		this->map = PlatformerMap::create();
	} 
	else if (args->levelMap->isIsometric()) {
		this->map = IsometricMap::create();
	}
	else {
		throw exception("Invalid Map Type Loaded");
	}

	this->map->retain();
	this->map->loadMap(args->levelMap);
	GlobalDirector::getInstance()->loadScene(this->map);
}

void SceneDirector::onGameNavigateFight(EventCustom* eventCustom)
{
	NavigationEvents::NavigateFightArgs* args = (NavigationEvents::NavigateFightArgs*)(eventCustom->getUserData());

	this->sceneHistory->push(Director::getInstance()->getRunningScene());
	this->fight->loadFight(args->squally, args->enemy);
	GlobalDirector::getInstance()->loadScene(this->fight);
}
