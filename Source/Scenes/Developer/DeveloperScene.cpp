#include "DeveloperScene.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/InputEvents.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/BallmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/UnderflowRuins/GuanoPetrified.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/MapResources.h"
#include "Resources/MusicResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

DeveloperScene* DeveloperScene::instance = nullptr;

DeveloperScene* DeveloperScene::getInstance()
{
	if (DeveloperScene::instance == nullptr)
	{
		DeveloperScene::instance = new DeveloperScene();

		DeveloperScene::instance->autorelease();
		DeveloperScene::instance->initializeListeners();

		GlobalDirector::registerGlobalScene(DeveloperScene::getInstance());
	}

	return DeveloperScene::instance;
}

DeveloperScene::DeveloperScene()
{
	this->scrollPane = ScrollPane::create(Size(1280.0f, 768.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->chapterList = std::vector<ClickableTextNode*>();

	this->chapterList.push_back(this->buildDebugButton("DBG Warp Depth", MapResources::Dev_WarpDepth));
	this->chapterList.push_back(this->buildDebugButton("DBG Notifications", MapResources::Dev_Items));
	this->chapterList.push_back(this->buildDebugButton("DBG Collision", MapResources::Dev_Collision));
	this->chapterList.push_back(this->buildDebugButton("DBG Positions", MapResources::Dev_PositionBug));
	this->chapterList.push_back(this->buildDebugButton("DBG Bounds", MapResources::Dev_Bounds));
	this->chapterList.push_back(this->buildDebugButton("DBG Animation Sequences", MapResources::Dev_AnimSeq));
	this->chapterList.push_back(this->buildDebugButton("DBG Combat", MapResources::Dev_Combat));
	this->chapterList.push_back(this->buildDebugButton("DBG Terrain", MapResources::Dev_Terrain));
	this->chapterList.push_back(this->buildDebugButton("==========", ""));
	this->chapterList.push_back(this->buildDebugButton("Warp Room (EF)", MapResources::EndianForest_Mages_Warp));
	this->chapterList.push_back(this->buildDebugButton("Warp Room (UR)", MapResources::UnderflowRuins_Mages_Warp));
	this->chapterList.push_back(this->buildDebugButton("Warp Room (DM)", MapResources::DataMines_Mages_Warp));
	this->chapterList.push_back(this->buildDebugButton("Warp Room (CV)", MapResources::CastleValgrind_Mages_Warp));
	this->chapterList.push_back(this->buildDebugButton("Warp Room (BP)", MapResources::BallmerPeaks_Mages_Warp));
	this->chapterList.push_back(this->buildDebugButton("Warp Room (DH)", MapResources::DaemonsHallow_Mages_Warp));
	this->chapterList.push_back(this->buildDebugButton("Warp Room (LC)", MapResources::LambdaCrypts_Mages_Warp));
	this->chapterList.push_back(this->buildDebugButton("Warp Room (VS)", MapResources::VoidStar_Mages_Warp));
	this->chapterList.push_back(this->buildDebugButton("==========", ""));
	this->chapterList.push_back(this->buildDebugButton("Zone_1_0 (DM)", MapResources::DataMines_Zone_1_0));
	this->chapterList.push_back(this->buildDebugButton("==========", ""));
	this->chapterList.push_back(this->buildDebugButton("Cleopatra (UR)", MapResources::UnderflowRuins_Home_Cleopatra));
	this->chapterList.push_back(this->buildDebugButton("Zone_3_8 (UR) Pyramid Boss vv", MapResources::UnderflowRuins_Zone_3_8));
	this->chapterList.push_back(this->buildDebugButton("Zone_3_7 (UR) Pyramid -->", MapResources::UnderflowRuins_Zone_3_7));
	this->chapterList.push_back(this->buildDebugButton("Zone_3_6 (UR) Pyramid >>^^", MapResources::UnderflowRuins_Zone_3_6));
	this->chapterList.push_back(this->buildDebugButton("Zone_3_5 (UR) Pyramid ^^^^", MapResources::UnderflowRuins_Zone_3_5));
	this->chapterList.push_back(this->buildDebugButton("Zone_3_4 (UR) Pyramid <<^^", MapResources::UnderflowRuins_Zone_3_4));
	this->chapterList.push_back(this->buildDebugButton("Zone_3_3 (UR) Pyramid <--", MapResources::UnderflowRuins_Zone_3_3));
	this->chapterList.push_back(this->buildDebugButton("Zone_3_2 (UR) Pyramid Interior", MapResources::UnderflowRuins_Zone_3_2));
	this->chapterList.push_back(this->buildDebugButton("Zone_3_1 (UR) Pyramid Top", MapResources::UnderflowRuins_Zone_3_1));
	this->chapterList.push_back(this->buildDebugButton("Zone_3_0 (UR) Pyramid", MapResources::UnderflowRuins_Zone_3_0));
	this->chapterList.push_back(this->buildDebugButton("Zone_2_7 (UR) Sky", MapResources::UnderflowRuins_Zone_2_7));
	this->chapterList.push_back(this->buildDebugButton("Zone_2_6 (UR) Exit", MapResources::UnderflowRuins_Zone_2_6));
	this->chapterList.push_back(this->buildDebugButton("Zone_2_5 (UR) Medusa", MapResources::UnderflowRuins_Zone_2_5));
	this->chapterList.push_back(this->buildDebugButton("Zone_2_4 (UR) Flame #2", MapResources::UnderflowRuins_Zone_2_4));
	this->chapterList.push_back(this->buildDebugButton("Zone_2_3 (UR) Flame #1", MapResources::UnderflowRuins_Zone_2_3));
	this->chapterList.push_back(this->buildDebugButton("Zone_2_2 (UR) Pass", MapResources::UnderflowRuins_Zone_2_2));
	this->chapterList.push_back(this->buildDebugButton("Zone_2_1 (UR) Puzzle", MapResources::UnderflowRuins_Zone_2_1));
	this->chapterList.push_back(this->buildDebugButton("Zone_2_0 (UR) Entrance", MapResources::UnderflowRuins_Zone_2_0));
	this->chapterList.push_back(this->buildDebugButton("Well (UR)", MapResources::UnderflowRuins_Town_Well));
	this->chapterList.push_back(this->buildDebugButton("Hera (UR)", MapResources::UnderflowRuins_Home_Hera));
	this->chapterList.push_back(this->buildDebugButton("Smith (UR)", MapResources::UnderflowRuins_Town_Smith));
	this->chapterList.push_back(this->buildDebugButton("Smith (DEV) (EF)", MapResources::UnderflowRuins_Town_Smith_Questless));
	this->chapterList.push_back(this->buildDebugButton("Alch (UR)", MapResources::UnderflowRuins_Town_Alch));
	this->chapterList.push_back(this->buildDebugButton("Alch (DEV) (EF)", MapResources::UnderflowRuins_Town_Alch_Questless));
	this->chapterList.push_back(this->buildDebugButton("Town (UR)", MapResources::UnderflowRuins_Town_Main));
	this->chapterList.push_back(this->buildDebugButton("Zone_1_3 (UR)", MapResources::UnderflowRuins_Zone_1_3));
	this->chapterList.push_back(this->buildDebugButton("Zone_1_2 (UR)", MapResources::UnderflowRuins_Zone_1_2));
	this->chapterList.push_back(this->buildDebugButton("Zone_1_1 (UR)", MapResources::UnderflowRuins_Zone_1_1));
	this->chapterList.push_back(this->buildDebugButton("Zone_1_0 (UR)", MapResources::UnderflowRuins_Zone_1_0));
	this->chapterList.push_back(this->buildDebugButton("Aphrodite (UR)", MapResources::UnderflowRuins_Home_Aphrodite));
	this->chapterList.push_back(this->buildDebugButton("Shoreline (UR)", MapResources::UnderflowRuins_Shoreline));
	this->chapterList.push_back(this->buildDebugButton("Docks (UR)", MapResources::UnderflowRuins_Town_Docks));
	this->chapterList.push_back(this->buildDebugButton("==========", ""));
	this->chapterList.push_back(this->buildDebugButton("Boat EF => UR", MapResources::EndianForest_Ship_Main));
	this->chapterList.push_back(this->buildDebugButton("Docks (EF)", MapResources::EndianForest_Town_Docks));
	this->chapterList.push_back(this->buildDebugButton("Elbridge", MapResources::EndianForest_Town_Main));
	this->chapterList.push_back(this->buildDebugButton("Inn (EF)", MapResources::EndianForest_Town_Inn));
	this->chapterList.push_back(this->buildDebugButton("Smith (EF)", MapResources::EndianForest_Town_Smith));
	this->chapterList.push_back(this->buildDebugButton("Alch (EF)", MapResources::EndianForest_Town_Alch));
	this->chapterList.push_back(this->buildDebugButton("Balmer's Peak", MapResources::BallmerPeaks_Town_Main));
	this->chapterList.push_back(this->buildDebugButton("Liana Back (EF)", MapResources::EndianForest_Town_Liana_Back));
	this->chapterList.push_back(this->buildDebugButton("Liana (EF)", MapResources::EndianForest_Town_Liana));
	this->chapterList.push_back(this->buildDebugButton("Ara (EF)", MapResources::EndianForest_Home_Ara));
	this->chapterList.push_back(this->buildDebugButton("Zone 3_7 (EF)", MapResources::EndianForest_Zone_3_7));
	this->chapterList.push_back(this->buildDebugButton("Zone 3_6 (EF)", MapResources::EndianForest_Zone_3_6));
	this->chapterList.push_back(this->buildDebugButton("Zone 3_5 (EF)", MapResources::EndianForest_Zone_3_5));
	this->chapterList.push_back(this->buildDebugButton("Zone 3_4 (EF)", MapResources::EndianForest_Zone_3_4));
	this->chapterList.push_back(this->buildDebugButton("Zone 3_Dev (EF)", MapResources::EndianForest_Zone_3_Dev));
	this->chapterList.push_back(this->buildDebugButton("Zone 3_3 (EF)", MapResources::EndianForest_Zone_3_3));
	this->chapterList.push_back(this->buildDebugButton("Zone 3_2 (EF)", MapResources::EndianForest_Zone_3_2));
	this->chapterList.push_back(this->buildDebugButton("Zone 3_1 (EF)", MapResources::EndianForest_Zone_3_1));
	this->chapterList.push_back(this->buildDebugButton("Zone 3_0 (EF)", MapResources::EndianForest_Zone_3_0));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_8 Temple (EF)", MapResources::EndianForest_Zone_2_8));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_7 Inner Sanctum Temple (EF)", MapResources::EndianForest_Zone_2_7));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_6 Temple (EF)", MapResources::EndianForest_Zone_2_6));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_5 Temple (EF)", MapResources::EndianForest_Zone_2_5));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_4_a Temple (EF)", MapResources::EndianForest_Zone_2_4_a));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_4 Temple (EF)", MapResources::EndianForest_Zone_2_4));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_3 (EF)", MapResources::EndianForest_Zone_2_3));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_2 (EF)", MapResources::EndianForest_Zone_2_2));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_1 (EF)", MapResources::EndianForest_Zone_2_1));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_0 (EF)", MapResources::EndianForest_Zone_2_0));
	this->chapterList.push_back(this->buildDebugButton("Zone 1_3 (EF)", MapResources::EndianForest_Zone_1_3));
	this->chapterList.push_back(this->buildDebugButton("Zone 1_2 (EF)", MapResources::EndianForest_Zone_1_2));
	this->chapterList.push_back(this->buildDebugButton("Zone 1_1 (EF)", MapResources::EndianForest_Zone_1_1));
	this->chapterList.push_back(this->buildDebugButton("Zone 1_0 (EF)", MapResources::EndianForest_Zone_1_0));
	this->chapterList.push_back(this->buildDebugButton("Guano's Cell", MapResources::EndianForest_Home_Guano));
	this->chapterList.push_back(this->buildDebugButton("Mage's Prison", MapResources::EndianForest_Mages_Prison));
	this->chapterList.push_back(this->buildDebugButton("Mage's Guild",MapResources::EndianForest_Mages_Guild));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet", MapResources::EndianForest_Mages_Gauntlet_Entrance));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet #1", MapResources::EndianForest_Mages_Gauntlet_1));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet #2", MapResources::EndianForest_Mages_Gauntlet_2));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet #3", MapResources::EndianForest_Mages_Gauntlet_3));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet #4", MapResources::EndianForest_Mages_Gauntlet_4));
	this->chapterList.push_back(this->buildDebugButton("DBG Cages", MapResources::Dev_Cages));
	this->chapterList.push_back(this->buildDebugButton("DBG Quests", MapResources::Dev_Quests));

	for (auto next : this->chapterList)
	{
		this->scrollPane->addChild(next);
	}

	this->addChild(this->scrollPane);
}

DeveloperScene::~DeveloperScene()
{
}

void DeveloperScene::onEnter()
{
	super::onEnter();
}

void DeveloperScene::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	int index = 0;

	this->scrollPane->setPosition(Vec2(visibleSize / 2.0f));

	for (auto next : this->chapterList)
	{
		next->setPosition(Vec2(0.0f, -128.0f - float(index++) * 180.0f));
	}
}

void DeveloperScene::initializeListeners()
{
	super::initializeListeners();
	
	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();
		
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TitleScreen::getInstance(); }));
	});
}

ClickableTextNode* DeveloperScene::buildDebugButton(std::string displayName, std::string mapResource)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, ConstantString::create(displayName));
	LocalizedLabel* labelSelected = label->clone();

	label->enableOutline(Color4B::BLACK, 2);
	labelSelected->enableOutline(Color4B::BLACK, 2);
	
	ClickableTextNode* clickableTextNode = ClickableTextNode::create(label, labelSelected, UIResources::Menus_MinigamesMenu_Banner, UIResources::Menus_MinigamesMenu_BannerHover);

	clickableTextNode->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
		{
			const int UNUSED_SAVE_PROFILE = 99;

			SaveManager::deleteAllProfileData(UNUSED_SAVE_PROFILE);
			SaveManager::setActiveSaveProfile(UNUSED_SAVE_PROFILE);

			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWind, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWater, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKey));
			
			// SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(GuanoPetrified::MapKey));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
			
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyRespawnMap, Value(mapResource));

			return PlatformerMap::create(mapResource);
		}));
	});

	return clickableTextNode;
}
