#include "TutorialSelectMenu.h"

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
#include "Entities/Platformer/Helpers/BalmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/MapResources.h"
#include "Resources/MusicResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TutorialSelectMenu* TutorialSelectMenu::instance = nullptr;

TutorialSelectMenu* TutorialSelectMenu::getInstance()
{
	if (TutorialSelectMenu::instance == nullptr)
	{
		TutorialSelectMenu::instance = new TutorialSelectMenu();

		TutorialSelectMenu::instance->autorelease();
		TutorialSelectMenu::instance->initializeListeners();

		GlobalDirector::registerGlobalScene(TutorialSelectMenu::getInstance());
	}

	return TutorialSelectMenu::instance;
}

TutorialSelectMenu::TutorialSelectMenu()
{
	this->title = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_HackingTutorials::create());
	this->disclaimer = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_HackingTutorials_Disclaimer::create());
	this->scrollPane = ScrollPane::create(Size(1280.0f, 768.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->chapterList = std::vector<ClickableTextNode*>();

	this->title->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->title->enableGlow(Color4B::BLACK);
	this->disclaimer->enableGlow(Color4B::BLACK);

	this->chapterList.push_back(this->buildTutorialButton("Tutorial I - Hex Editing", MapResources::Tutorials_UnknownValue1));
	this->chapterList.push_back(this->buildTutorialButton("Tutorial II - Exact value Scans", MapResources::Tutorials_UnknownValue1));
	this->chapterList.push_back(this->buildTutorialButton("Tutorial III - Unknown Value Scans 1", MapResources::Tutorials_UnknownValue1));
	this->chapterList.push_back(this->buildTutorialButton("Tutorial IV - Unknown Value Scans 2", MapResources::Tutorials_UnknownValue2));

	for (auto it = this->chapterList.begin(); it != this->chapterList.end(); it++)
	{
		this->scrollPane->addChild(*it);
	}

	this->addChild(this->scrollPane);
	this->addChild(this->title);
	this->addChild(this->disclaimer);
}

TutorialSelectMenu::~TutorialSelectMenu()
{
}

void TutorialSelectMenu::onEnter()
{
	super::onEnter();
}

void TutorialSelectMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	int index = 0;

	this->scrollPane->setPosition(Vec2(visibleSize / 2.0f));

	for (auto it = this->chapterList.begin(); it != this->chapterList.end(); it++, index++)
	{
		(*it)->setPosition(Vec2(0.0f, -128.0f - float(index) * 180.0f));
	}

	this->title->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 480.0f));
	this->disclaimer->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 480.0f - 56.0f));
}

void TutorialSelectMenu::initializeListeners()
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

ClickableTextNode* TutorialSelectMenu::buildTutorialButton(std::string displayName, std::string mapResource)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, ConstantString::create(displayName));
	LocalizedLabel* labelSelected = label->clone();

	label->enableOutline(Color4B::BLACK, 2);
	labelSelected->enableOutline(Color4B::BLACK, 2);
	
	ClickableTextNode* clickableTextNode = ClickableTextNode::create(label, labelSelected, UIResources::Menus_MinigamesMenu_Banner, UIResources::Menus_MinigamesMenu_BannerHover);

	clickableTextNode->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		const int UNUSED_SAVE_PROFILE = 99;

		SaveManager::deleteAllProfileData(UNUSED_SAVE_PROFILE);
		SaveManager::setActiveSaveProfile(UNUSED_SAVE_PROFILE);
		PlatformerMap* map = PlatformerMap::create(mapResource);

		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyBlessingOfWind, Value(true));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKeyGuano));
		// SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Snowman::MapKeySnowman));
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));

		NavigationEvents::LoadScene(map);
	});

	return clickableTextNode;
}
