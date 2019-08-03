#include "DebugScene.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/InputEvents.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Save/SaveManager.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"

#include "Resources/MapResources.h"
#include "Resources/MusicResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

DebugScene* DebugScene::instance = nullptr;

DebugScene* DebugScene::getInstance()
{
	if (DebugScene::instance == nullptr)
	{
		DebugScene::instance = new DebugScene();

		DebugScene::instance->autorelease();
		DebugScene::instance->initializeListeners();

		GlobalDirector::registerGlobalScene(DebugScene::getInstance());
	}

	return DebugScene::instance;
}

DebugScene::DebugScene()
{
	this->scrollPane = ScrollPane::create(Size(1280.0f, 768.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->chapterList = std::vector<ClickableTextNode*>();

	this->chapterList.push_back(this->buildDebugButton(MapResources::Dev_Cages));
	this->chapterList.push_back(this->buildDebugButton(MapResources::Dev_Quests));
	this->chapterList.push_back(this->buildDebugButton(MapResources::EndianForest_Zone_1_Town_Main));
	this->chapterList.push_back(this->buildDebugButton(MapResources::EndianForest_Zone_1_Town_Docks));
	this->chapterList.push_back(this->buildDebugButton(MapResources::EndianForest_Intro));
	this->chapterList.push_back(this->buildDebugButton(MapResources::EndianForest_Zone_1_0));
	this->chapterList.push_back(this->buildDebugButton(MapResources::EndianForest_Zone_1_1));
	this->chapterList.push_back(this->buildDebugButton(MapResources::EndianForest_Zone_1_2));

	for (auto it = this->chapterList.begin(); it != this->chapterList.end(); it++)
	{
		this->scrollPane->addChild(*it);
	}

	this->addChild(this->scrollPane);
}

DebugScene::~DebugScene()
{
}

void DebugScene::onEnter()
{
	super::onEnter();
}

void DebugScene::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	int index = 0;

	this->scrollPane->setPosition(Vec2(visibleSize / 2.0f));

	for (auto it = this->chapterList.begin(); it != this->chapterList.end(); it++, index++)
	{
		(*it)->setPosition(Vec2(0.0f, -128.0f - float(index) * 160.0f));
	}
}

void DebugScene::initializeListeners()
{
	super::initializeListeners();
}

ClickableTextNode* DebugScene::buildDebugButton(std::string mapResource, std::vector<std::string> mapArgs)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, ConstantString::create(mapResource));
	LocalizedLabel* labelSelected = label->clone();

	label->enableOutline(Color4B::BLACK, 2);
	labelSelected->enableOutline(Color4B::BLACK, 2);
	
	ClickableTextNode* clickableTextNode = ClickableTextNode::create(label, labelSelected, UIResources::Menus_MinigamesMenu_Banner, UIResources::Menus_MinigamesMenu_BannerHover);

	clickableTextNode->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		const int UNUSED_SAVE_PROFILE = 3;

		SaveManager::deleteAllProfileData(UNUSED_SAVE_PROFILE);
		SaveManager::setActiveSaveProfile(UNUSED_SAVE_PROFILE);
		PlatformerMap* map = PlatformerMap::create(mapResource, mapArgs);

		NavigationEvents::LoadScene(map);
	});

	return clickableTextNode;
}
