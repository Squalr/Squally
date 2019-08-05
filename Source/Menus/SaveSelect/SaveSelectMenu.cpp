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

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Back.h"
#include "Strings/Menus/SaveSelect/ConfirmDelete.h"
#include "Strings/Menus/SaveSelect/ContinueGame.h"
#include "Strings/Menus/SaveSelect/NewGame.h"

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
	this->buttonsNode = Node::create();
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, visibleSize.height);
	this->confirmationMenu = ConfirmationMenu::create();

	LocalizedLabel*	backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());
	LocalizedLabel*	backButtonLabelHover = backButtonLabel->clone();

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	this->addChild(this->backgroundNode);
	this->addChild(this->buttonsNode);
	this->addChild(this->backButton);
	this->addChild(this->backdrop);
	this->addChild(this->confirmationMenu);
}

SaveSelectMenu::~SaveSelectMenu()
{
}

void SaveSelectMenu::onEnter()
{
	super::onEnter();

	this->backgroundNode->addChild(MenuBackground::claimInstance());
	this->backdrop->setVisible(false);

	const float delay = 0.15f;
	const float duration = 0.5f;

	this->buildSaveButtons();

	GameUtils::fadeInObject(this->saveGameButton0, delay, duration);
	GameUtils::fadeInObject(this->saveGameButton1, delay, duration);
	GameUtils::fadeInObject(this->saveGameButton2, delay, duration);
	GameUtils::fadeInObject(this->backButton, delay, duration);

	this->scheduleUpdate();
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

		NavigationEvents::NavigateBack();
	});

	this->backButton->setMouseClickCallback(CC_CALLBACK_0(SaveSelectMenu::onBackClick, this));
}

void SaveSelectMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->buttonsNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
}

void SaveSelectMenu::buildSaveButtons()
{
	this->buttonsNode->removeAllChildren();

	this->saveGameButton0 = this->buildSaveButton(0);
	this->saveGameButton1 = this->buildSaveButton(1);
	this->saveGameButton2 = this->buildSaveButton(2);

	this->saveGameButton0->setPositionY(224.0f);
	this->saveGameButton1->setPositionY(0.0f);
	this->saveGameButton2->setPositionY(-224.0f);

	this->buttonsNode->addChild(this->saveGameButton0);
	this->buttonsNode->addChild(this->saveGameButton1);
	this->buttonsNode->addChild(this->saveGameButton2);
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
	const Vec2 labelOffset = Vec2(48.0f, 0.0f);

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
		UIResources::Menus_MinigamesMenu_Banner,
		UIResources::Menus_MinigamesMenu_BannerHover);

	saveGameButton->setTextOffset(labelOffset);

	Sprite* saveGameIcon = Sprite::create(hasSaveData ? UIResources::Menus_Icons_BookSpellsArcane : UIResources::Menus_Icons_Health);

	saveGameIcon->setAnchorPoint(Vec2(0.0f, 0.5f));
	saveGameIcon->setPosition(Vec2(-saveGameButton->getContentSize().width / 2.0f + 78.0f, 0.0f));

	saveGameButton->addChild(saveGameIcon);

	saveGameButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		SaveManager::setActiveSaveProfile(profileId);
		this->loadSave();
	});

	if (hasSaveData)
	{
		ClickableNode* deleteButton = this->buildDeleteButton(profileId);

		deleteButton->setPosition(Vec2(580.0f, 0.0f));

		saveGameButton->addChild(deleteButton);
	}

	return saveGameButton;
}

ClickableNode* SaveSelectMenu::buildDeleteButton(int profileId)
{
	ClickableNode* deleteButton = ClickableNode::create(UIResources::Menus_Buttons_DeleteButton, UIResources::Menus_Buttons_DeleteButtonHover);

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
	std::string mapFile = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyMap, Value(MapResources::EndianForest_Intro)).asString();
	ValueVector mapArgsVector = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyMapArgs, Value(ValueVector())).asValueVector();
	std::vector<std::string> mapArgs = std::vector<std::string>();

	for (auto it = mapArgsVector.begin(); it != mapArgsVector.end(); it++)
	{
		mapArgs.push_back((*it).asString());
	}

	PlatformerMap* map = PlatformerMap::create(mapFile, mapArgs);

	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(map));
}

void SaveSelectMenu::onBackClick()
{
	NavigationEvents::NavigateBack();
}
