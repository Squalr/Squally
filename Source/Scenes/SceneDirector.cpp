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
	this->saveSelectMenu = SaveSelectMenu::create();
	this->minigamesMenu = MinigamesMenu::create();
	this->hexusChapterSelectMenu = HexusChapterSelectMenu::create();
	this->hexusDeckManagement = HexusDeckManagement::create();
	this->hexusRewardsMenu = HexusRewardsMenu::create();
	this->hexusStoreMenu = HexusStoreMenu::create();
	this->hexusOpponentMenuTraining = HexusOpponentMenuTraining::create();
	this->hexusOpponentMenuJungle = HexusOpponentMenuJungle::create();
	this->hexusOpponentMenuRuins = HexusOpponentMenuRuins::create();
	this->hexusOpponentMenuForest = HexusOpponentMenuForest::create();
	this->hexusOpponentMenuCaverns = HexusOpponentMenuCaverns::create();
	this->hexusOpponentMenuCastle = HexusOpponentMenuCastle::create();
	this->hexusOpponentMenuIceCaps = HexusOpponentMenuIceCaps::create();
	this->hexusOpponentMenuVolcano = HexusOpponentMenuVolcano::create();
	this->hexusOpponentMenuObelisk = HexusOpponentMenuObelisk::create();
	this->hexusOpponentMenuMech = HexusOpponentMenuMech::create();
	this->hexusPuzzlesMenu = HexusPuzzlesMenu::create();
	this->worldMap = WorldMap::create();
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
	this->saveSelectMenu->retain();
	this->minigamesMenu->retain();
	this->hexusChapterSelectMenu->retain();
	this->hexusDeckManagement->retain();
	this->hexusRewardsMenu->retain();
	this->hexusStoreMenu->retain();
	this->hexusOpponentMenuTraining->retain();
	this->hexusOpponentMenuJungle->retain();
	this->hexusOpponentMenuRuins->retain();
	this->hexusOpponentMenuForest->retain();
	this->hexusOpponentMenuCaverns->retain();
	this->hexusOpponentMenuCastle->retain();
	this->hexusOpponentMenuIceCaps->retain();
	this->hexusOpponentMenuVolcano->retain();
	this->hexusOpponentMenuObelisk->retain();
	this->hexusOpponentMenuMech->retain();
	this->hexusPuzzlesMenu->retain();
	this->worldMap->retain();
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

void SceneDirector::initializeListeners()
{
	GlobalNode::initializeListeners();

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

	EventListenerCustom* hexusGameStartListener = EventListenerCustom::create(
		HexusEvents::HexusGameStartEvent,
		CC_CALLBACK_1(Hexus::onGameStart, this->hexus)
	);

	EventListenerCustom* hexusShowRewardsListener = EventListenerCustom::create(
		HexusEvents::HexusShowRewardsEvent,
		CC_CALLBACK_1(HexusRewardsMenu::onRewardsOpen, this->hexusRewardsMenu)
	);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hexusGameStartListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hexusShowRewardsListener, this);
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
		case NavigationEvents::GameScreen::SaveSelect:
			newScene = this->saveSelectMenu;
			break;
		case NavigationEvents::GameScreen::Minigames:
			newScene = this->minigamesMenu;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus:
			newScene = this->hexusChapterSelectMenu;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Deck_Management:
			newScene = this->hexusDeckManagement;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Rewards:
			newScene = this->hexusRewardsMenu;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Store:
			newScene = this->hexusStoreMenu;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Training:
			newScene = this->hexusOpponentMenuTraining;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Jungle:
			newScene = this->hexusOpponentMenuJungle;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Ruins:
			newScene = this->hexusOpponentMenuRuins;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Forest:
			newScene = this->hexusOpponentMenuForest;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Caverns:
			newScene = this->hexusOpponentMenuCaverns;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Castle:
			newScene = this->hexusOpponentMenuCastle;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Chapter_IceCaps:
			newScene = this->hexusOpponentMenuIceCaps;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Volcano:
			newScene = this->hexusOpponentMenuVolcano;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Obelisk:
			newScene = this->hexusOpponentMenuObelisk;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Chapter_Mech:
			newScene = this->hexusOpponentMenuMech;
			break;
		case NavigationEvents::GameScreen::Minigames_Hexus_Puzzles:
			newScene = this->hexusPuzzlesMenu;
			break;
		case NavigationEvents::GameScreen::StoryMap:
			newScene = this->worldMap;
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
		default:
			return;
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

	this->cutscene = args->cutscene;
	this->cutscene->playCutscenes();

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
		throw std::runtime_error("Invalid Map Type Loaded");
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
