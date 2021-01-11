#include "TutorialSelectMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

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
#include "Menus/MenuBackground.h"
#include "Menus/Tutorials/AssemblyEditingTab.h"
#include "Menus/Tutorials/HexEditingTab.h"
#include "Menus/Tutorials/HomeTab.h"
#include "Menus/Tutorials/MemoryEditingTab.h"
#include "Menus/Tutorials/PointersTab.h"
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

		GlobalDirector::RegisterGlobalScene(TutorialSelectMenu::getInstance());
	}

	return TutorialSelectMenu::instance;
}

TutorialSelectMenu::TutorialSelectMenu()
{
	this->background = Node::create();
	this->window = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->title = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_HackingTutorials::create());
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->homeTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconCrown, Strings::Menus_Tutorials_Home_Home::create());
	this->memoryEditingTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconWeapons, Strings::Menus_Tutorials_MemoryEditing_MemoryEditing::create());
	this->hexEditingTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconKey, Strings::Menus_Tutorials_HexEditing_HexEditing::create());
	this->pointersTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconShield, Strings::Menus_Tutorials_Pointers_Pointers::create());
	this->assemblyEditingTabButton = this->buildTabButton(UIResources::Menus_OptionsMenu_IconTrophy, Strings::Menus_Tutorials_AssemblyEditing_AssemblyEditing::create());
	this->homeTab = HomeTab::create();
	this->memoryEditingTab = MemoryEditingTab::create();
	this->hexEditingTab = HexEditingTab::create();
	this->pointersTab = PointersTab::create();
	this->assemblyEditingTab = AssemblyEditingTab::create();
	this->leftPanel = Node::create();
	this->rightPanel = Node::create();

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);

	returnLabelHover->setColor(Color3B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->title->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->title->enableGlow(Color4B::BLACK);

	this->leftPanel->addChild(this->homeTabButton);
	this->leftPanel->addChild(this->memoryEditingTabButton);
	this->leftPanel->addChild(this->hexEditingTabButton);
	this->leftPanel->addChild(this->pointersTabButton);
	this->leftPanel->addChild(this->assemblyEditingTabButton);
	this->rightPanel->addChild(this->homeTab);
	this->rightPanel->addChild(this->memoryEditingTab);
	this->rightPanel->addChild(this->hexEditingTab);
	this->rightPanel->addChild(this->pointersTab);
	this->rightPanel->addChild(this->assemblyEditingTab);
	this->addChild(this->background);
	this->addChild(this->window);
	this->addChild(this->leftPanel);
	this->addChild(this->rightPanel);
	this->addChild(this->title);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
}

TutorialSelectMenu::~TutorialSelectMenu()
{
}

void TutorialSelectMenu::onEnter()
{
	super::onEnter();

	this->background->addChild(MenuBackground::claimInstance());
	this->setActiveTab(Tab::Home);
}

void TutorialSelectMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->window->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->title->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 372.0f));
	this->leftPanel->setPosition(Vec2(visibleSize.width / 2.0f - 340.0f, visibleSize.height / 2.0f + 192.0f));
	this->rightPanel->setPosition(Vec2(visibleSize.width / 2.0f + 192.0f, visibleSize.height / 2.0f + 0.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
	
	const float Spacing = -66.0f;

	this->homeTabButton->setPosition(Vec2(0.0f, Spacing * 0.0f));
	this->memoryEditingTabButton->setPosition(Vec2(0.0f, Spacing * 1.0f));
	this->hexEditingTabButton->setPosition(Vec2(0.0f, Spacing * 2.0f));
	this->pointersTabButton->setPosition(Vec2(0.0f, Spacing * 3.0f));
	this->assemblyEditingTabButton->setPosition(Vec2(0.0f, Spacing * 4.0f));
}

void TutorialSelectMenu::initializeListeners()
{
	super::initializeListeners();

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->onReturnClick();  });
	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->onReturnClick();  });
	this->homeTabButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setActiveTab(Tab::Home); });
	this->memoryEditingTabButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setActiveTab(Tab::MemoryEditing); });
	this->hexEditingTabButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setActiveTab(Tab::HexEditing); });
	this->pointersTabButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setActiveTab(Tab::Pointers); });
	this->assemblyEditingTabButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setActiveTab(Tab::AssemblyEditing); });

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}

		args->handle();
		
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TitleScreen::getInstance(); }));
	});
}

void TutorialSelectMenu::setActiveTab(Tab tab)
{
	this->activeTab = tab;

	this->homeTab->setVisible(false);
	this->memoryEditingTab->setVisible(false);
	this->hexEditingTab->setVisible(false);
	this->pointersTab->setVisible(false);
	this->assemblyEditingTab->setVisible(false);

	switch(this->activeTab)
	{
		default:
		case Tab::Home:
		{
			this->homeTab->setVisible(true);
			break;
		}
		case Tab::MemoryEditing:
		{
			this->memoryEditingTab->setVisible(true);
			break;
		}
		case Tab::HexEditing:
		{
			this->hexEditingTab->setVisible(true);
			break;
		}
		case Tab::Pointers:
		{
			this->pointersTab->setVisible(true);
			break;
		}
		case Tab::AssemblyEditing:
		{
			this->assemblyEditingTab->setVisible(true);
			break;
		}
	}
}

void TutorialSelectMenu::onReturnClick()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TitleScreen::getInstance(); }));
}

ClickableTextNode* TutorialSelectMenu::buildTabButton(std::string iconResource, LocalizedString* localizedString)
{
	LocalizedLabel*	label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, localizedString);
	LocalizedLabel*	labelHover = label->clone();

	ClickableTextNode* button = ClickableTextNode::create(label, labelHover, UIResources::Menus_OptionsMenu_TabButton, UIResources::Menus_OptionsMenu_TabButtonSelected);
	button->setTextOffset(Vec2(32.0f, 0.0f));

	Sprite* icon = Sprite::create(iconResource);
	icon->setPosition(Vec2(-122.0f, 0.0f));

	button->addChild(icon);

	return button;
}
