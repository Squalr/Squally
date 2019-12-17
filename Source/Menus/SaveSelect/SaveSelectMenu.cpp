#include "SaveSelectMenu.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Confirmation/ConfirmationMenu.h"
#include "Menus/MenuBackground.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

SaveSelectMenu* SaveSelectMenu::instance;

SaveSelectMenu* SaveSelectMenu::getInstance()
{
	if (SaveSelectMenu::instance == nullptr)
	{
		SaveSelectMenu::instance = new SaveSelectMenu();

		SaveSelectMenu::instance->autorelease();
		SaveSelectMenu::instance->initializeListeners();

		GlobalDirector::registerGlobalScene(SaveSelectMenu::instance);
	}

	return SaveSelectMenu::instance;
}

SaveSelectMenu::SaveSelectMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->setFadeSpeed(0.0f);

	this->backgroundNode = Node::create();
	this->saveSelectWindow = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->saveButtonNode = Node::create();
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, visibleSize.height);
	this->confirmationMenu = ConfirmationMenu::create();

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

	this->addChild(this->backgroundNode);
	this->addChild(this->saveSelectWindow);
	this->addChild(this->saveButtonNode);
	this->addChild(this->returnButton);
	this->addChild(this->closeButton);
	this->addChild(this->backdrop);
	this->addChild(this->confirmationMenu);
}

SaveSelectMenu::~SaveSelectMenu()
{
}

void SaveSelectMenu::onEnter()
{
	super::onEnter();

	this->backdrop->setVisible(false);
	this->backgroundNode->addChild(MenuBackground::claimInstance());
	this->buildSaveButtons();

	const float delay = 0.15f;
	const float duration = 0.5f;

	GameUtils::fadeInObject(this->saveSelectWindow, delay, duration);
	GameUtils::fadeInObject(this->saveGameButton0, delay, duration);
	GameUtils::fadeInObject(this->saveGameButton1, delay, duration);
	GameUtils::fadeInObject(this->saveGameButton2, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
}

void SaveSelectMenu::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}

		args->handle();

		this->goBack();
	});

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->goBack();
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->goBack();
	});
}

void SaveSelectMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->saveSelectWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->saveButtonNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 48.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 420.0f));
}

void SaveSelectMenu::buildSaveButtons()
{
	this->saveButtonNode->removeAllChildren();

	this->saveGameButton0 = this->buildSaveButton(0);
	this->saveGameButton1 = this->buildSaveButton(1);
	this->saveGameButton2 = this->buildSaveButton(2);

	this->saveButtonNode->addChild(this->saveGameButton0);
	this->saveButtonNode->addChild(this->saveGameButton1);
	this->saveButtonNode->addChild(this->saveGameButton2);

	this->saveGameButton0->setPosition(Vec2(0.0f, 192.0f));
	this->saveGameButton1->setPosition(Vec2(0.0f, 0.0f));
	this->saveGameButton2->setPosition(Vec2(0.0f, -192.0f));
}

ClickableTextNode* SaveSelectMenu::buildSaveButton(int profileId)
{
	const Size shadowSize = Size(-2.0f, -2.0f);
	const int shadowBlur = 2;
	const int hoverOutlineSize = 2;
	const Color3B textColor = Color3B::WHITE;
	const Color4B shadowColor = Color4B::BLACK;
	const Color3B highlightColor = Color3B::YELLOW;
	const Color4B glowColor = Color4B::ORANGE;

	bool hasSaveData = SaveManager::hasSaveProfile(profileId);
	LocalizedLabel*	saveGameLabel = nullptr;

	if (hasSaveData)
	{
		saveGameLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_SaveSelect_ContinueGame::create());
	}
	else
	{
		saveGameLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_SaveSelect_NewGame::create());
	}

	LocalizedLabel*	saveGameLabelHover = saveGameLabel->clone();
	
	saveGameLabel->setColor(textColor);
	saveGameLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGameLabel->enableGlow(shadowColor);

	saveGameLabelHover->setColor(highlightColor);
	saveGameLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	saveGameLabelHover->enableGlow(glowColor);

	ClickableTextNode* saveGameButton = ClickableTextNode::create(
		saveGameLabel,
		saveGameLabelHover,
		UIResources::Menus_SaveSelectMenu_Row,
		UIResources::Menus_SaveSelectMenu_RowSelected);

	saveGameButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		SaveManager::setActiveSaveProfile(profileId);
		this->loadSave();
	});

	if (hasSaveData)
	{
		Sprite* saveGameIcon = Sprite::create(hasSaveData ? UIResources::Menus_Icons_BookSpellsArcane : UIResources::Menus_Icons_Health);

		saveGameIcon->setAnchorPoint(Vec2(0.0f, 0.5f));
		saveGameIcon->setPosition(Vec2(-saveGameButton->getContentSize().width / 2.0f + 78.0f, 0.0f));
		saveGameButton->addChild(saveGameIcon);

		ClickableNode* deleteButton = this->buildDeleteButton(profileId);

		deleteButton->setPosition(Vec2(392.0f, -32.0f));

		saveGameButton->addChild(deleteButton);
	}

	return saveGameButton;
}

ClickableNode* SaveSelectMenu::buildDeleteButton(int profileId)
{
	ClickableNode* deleteButton = ClickableNode::create(UIResources::Menus_Buttons_TrashV2Button, UIResources::Menus_Buttons_TrashV2ButtonHover);

	deleteButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->confirmationMenu->showMessage(Strings::Menus_SaveSelect_ConfirmDelete::create(), [=]()
		{
			SaveManager::deleteAllProfileData(profileId);

			this->buildSaveButtons();

			this->backdrop->setVisible(false);
			GameUtils::focus(this);
		}, [=]()
		{
			this->backdrop->setVisible(false);
			GameUtils::focus(this);
		});

		this->backdrop->setVisible(true);
		GameUtils::focus(this->confirmationMenu);
	});

	return deleteButton;
}

void SaveSelectMenu::loadSave()
{
	bool isReload = SaveManager::hasProfileData(SaveKeys::SaveKeyMap);
	std::string mapFile = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyMap, Value(MapResources::EndianForest_Zone_1_0)).asString();
	
	PlatformerMap* map = PlatformerMap::create(mapFile);

	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(map));
}

void SaveSelectMenu::goBack()
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(TitleScreen::getInstance()));
}
