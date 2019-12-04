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
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
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

	this->chapterList.push_back(this->buildDebugButton("Town", MapResources::EndianForest_Town_Main));
	this->chapterList.push_back(this->buildDebugButton("Liana", MapResources::EndianForest_Town_Liana));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_0 (EF)", MapResources::EndianForest_Zone_2_0));
	this->chapterList.push_back(this->buildDebugButton("Zone 2_1 (EF)", MapResources::EndianForest_Zone_2_1));
	this->chapterList.push_back(this->buildDebugButton("Zone 1_0 (EF)", MapResources::EndianForest_Zone_1_0));
	this->chapterList.push_back(this->buildDebugButton("Zone 1_1 (EF)", MapResources::EndianForest_Zone_1_1));
	this->chapterList.push_back(this->buildDebugButton("Zone 1_2 (EF)", MapResources::EndianForest_Zone_1_2));
	this->chapterList.push_back(this->buildDebugButton("Zone 3_1 (EF)", MapResources::EndianForest_Zone_3_1));
	this->chapterList.push_back(this->buildDebugButton("Mage's Prison", MapResources::EndianForest_Mages_Prison));
	this->chapterList.push_back(this->buildDebugButton("Mage's Guild",MapResources::EndianForest_Mages_Guild));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet", MapResources::EndianForest_Mages_Gauntlet_Entrance));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet #1", MapResources::EndianForest_Mages_Gauntlet_1));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet #2", MapResources::EndianForest_Mages_Gauntlet_2));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet #3", MapResources::EndianForest_Mages_Gauntlet_3));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet #4", MapResources::EndianForest_Mages_Gauntlet_4));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet #5", MapResources::EndianForest_Mages_Gauntlet_5));
	this->chapterList.push_back(this->buildDebugButton("Mage's Gauntlet #6", MapResources::EndianForest_Mages_Gauntlet_6));
	this->chapterList.push_back(this->buildDebugButton("Inn (EF)", MapResources::EndianForest_Town_Inn));
	this->chapterList.push_back(this->buildDebugButton("Alch (EF)", MapResources::EndianForest_Town_Alch));
	this->chapterList.push_back(this->buildDebugButton("Docks (EF)", MapResources::EndianForest_Town_Docks));
	this->chapterList.push_back(this->buildDebugButton("DBG Cages", MapResources::Dev_Cages));
	this->chapterList.push_back(this->buildDebugButton("DBG Quests", MapResources::Dev_Quests));

	for (auto it = this->chapterList.begin(); it != this->chapterList.end(); it++)
	{
		this->scrollPane->addChild(*it);
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

	for (auto it = this->chapterList.begin(); it != this->chapterList.end(); it++, index++)
	{
		(*it)->setPosition(Vec2(0.0f, -128.0f - float(index) * 180.0f));
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
		
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(TitleScreen::getInstance()));
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
		const int UNUSED_SAVE_PROFILE = 3;

		SaveManager::deleteAllProfileData(UNUSED_SAVE_PROFILE);
		SaveManager::setActiveSaveProfile(UNUSED_SAVE_PROFILE);
		PlatformerMap* map = PlatformerMap::create(mapResource);
		SaveManager::softSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKeyGuano));
		SaveManager::softSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));

		NavigationEvents::LoadScene(map);
	});

	return clickableTextNode;
}
