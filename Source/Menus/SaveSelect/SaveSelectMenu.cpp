#include "SaveSelectMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"
#include "cocos/base/CCValue.h"

#include "Deserializers/Platformer/PlatformerEntityDeserializer.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Menus/Confirmation/ConfirmationMenu.h"
#include "Menus/MenuBackground.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/Collectables.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/HexusResources.h"
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
	this->setFadeSpeed(0.0f);

	this->backgroundNode = Node::create();
	this->saveSelectWindow = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->saveButtonNode = Node::create();
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_SaveSelect_SelectASave::create());
	this->confirmationMenu = ConfirmationMenu::create();
	this->platformerEntityDeserializer = PlatformerEntityDeserializer::create();

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

	this->titleLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->titleLabel->enableGlow(Color4B::BLACK);

	this->addChild(this->platformerEntityDeserializer);
	this->addChild(this->backgroundNode);
	this->addChild(this->saveSelectWindow);
	this->addChild(this->titleLabel);
	this->addChild(this->saveButtonNode);
	this->addChild(this->returnButton);
	this->addChild(this->closeButton);
	this->addChild(this->confirmationMenu);
}

SaveSelectMenu::~SaveSelectMenu()
{
}

void SaveSelectMenu::onEnter()
{
	super::onEnter();

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
	GameUtils::fadeInObject(this->titleLabel, delay, duration);
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
	this->titleLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 372.0f));
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
		saveGameLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Empty::create());
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
		saveGameButton->addChild(this->buildSaveGameContent(profileId));
		saveGameButton->addChild(this->buildDeleteButton(profileId));
	}

	return saveGameButton;
}

Node* SaveSelectMenu::buildSaveGameContent(int profileId)
{
	// Temporarily set the active profile
	SaveManager::setActiveSaveProfile(profileId);

	int squallyEq = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEq, Value(1)).asInt();
	Node* content = Node::create();
	Node* squallyAvatar = this->buildEntityFrame(Squally::create(), Vec2(-32.0f, -32.0f), squallyEq);
	std::string helperName = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value("")).asString();

	squallyAvatar->setPosition(Vec2(-356.0f, 0.0f));

	content->addChild(squallyAvatar);

	if (!helperName.empty())
	{
		
		ValueMap properties = ValueMap();

		SaveManager::SaveProfileData(SaveKeys::SaveKeyHelperName, Value(helperName));
		
		properties[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
		properties[GameObject::MapKeyName] = Value(helperName);
		// properties[GameObject::MapKeyFlipX] = Value(true);

		ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
			properties,
			[=] (ObjectDeserializer::ObjectDeserializationArgs deserializeArgs)
			{
				PlatformerEntity* helper = dynamic_cast<PlatformerEntity*>(deserializeArgs.gameObject);

				if (helper != nullptr)
				{
					Node* helperAvatar = this->buildEntityFrame(helper, Vec2::ZERO, 0);

					helperAvatar->setPosition(Vec2(-356.0f + 160.0f, 0.0f));

					content->addChild(helperAvatar);
				}
			}
		);

		this->platformerEntityDeserializer->deserialize(&args);
	}

	LocalizedString* collectablesCount = Strings::Common_XOverY::create();
	LocalizedLabel* collectablesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, collectablesCount);
	Sprite* collectablesIcon = Sprite::create(UIResources::Menus_SaveSelectMenu_CollectablesIcon);

	collectablesCount->setStringReplacementVariables({
		ConstantString::create(std::to_string(Collectables::getCollectedAnimalCount())),
		ConstantString::create(std::to_string(Collectables::getCollectedAnimalTotal()))
	});
	
	collectablesIcon->setAnchorPoint(Vec2(1.0f, 0.5f));
	collectablesLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	collectablesLabel->enableOutline(Color4B::BLACK, 2);

	collectablesLabel->setPosition(Vec2(356.0f + 16.0f, -64.0f));
	collectablesIcon->setPosition(Vec2(356.0f + 16.0f - 12.0f, -64.0f));

	content->addChild(collectablesLabel);
	content->addChild(collectablesIcon);

	return content;
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

			GameUtils::focus(this);
		}, [=]()
		{
			GameUtils::focus(this);
		});
		
		GameUtils::focus(this->confirmationMenu);
	});

	deleteButton->setPosition(Vec2(512.0f, 0.0f));

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

Node* SaveSelectMenu::buildEntityFrame(PlatformerEntity* entity, Vec2 offsetAdjustment, int eq)
{
	if (entity == nullptr)
	{
		return Node::create();
	}

	Node* content = Node::create();
	Node* entityContent = Node::create();
	Sprite* entityFrame = Sprite::create(UIResources::Menus_SaveSelectMenu_AvatarFrame);
	std::string backgroundResource = this->getBackgroundResourceForCurrentSaveProfile();

	SmartClippingNode* entityClip = SmartClippingNode::create(entityContent, Size(128.0f, 128.0f));
	Sprite* backgroundSqually = Sprite::create(backgroundResource);

	entity->setPosition(entity->getDialogueOffset() + Vec2(-16.0f, -80.0f) + offsetAdjustment);

	entityContent->addChild(backgroundSqually);
	entityContent->addChild(entity);
	content->addChild(entityClip);
	content->addChild(entityFrame);
	
	if (eq > 0)
	{
		Sprite* eqFrame = Sprite::create(UIResources::HUD_LevelFrame);
		LocalizedLabel* eqLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(std::to_string(eq)));
		
		eqFrame->setPosition(Vec2(0.0f, -64.0f));
		eqLabel->setPosition(Vec2(0.0f, -64.0f));
		eqLabel->enableOutline(Color4B::BLACK, 2);

		content->addChild(eqFrame);
		content->addChild(eqLabel);
	}

	return content;
}

std::string SaveSelectMenu::getBackgroundResourceForCurrentSaveProfile()
{
	std::string currentMap = StrUtils::toLower(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyMap, Value("")).asString());

	if (StrUtils::contains(currentMap, "underflowruins", true))
	{
		return HexusResources::Menus_HexusFrameUnderflowRuins;
	}
	else if (StrUtils::contains(currentMap, "seasharpcaverns", true))
	{
		return HexusResources::Menus_HexusFrameSeaSharpCaverns;
	}
	else if (StrUtils::contains(currentMap, "castlevalgrind", true))
	{
		return HexusResources::Menus_HexusFrameCastleValgrind;
	}
	else if (StrUtils::contains(currentMap, "balmerPeaks", true))
	{
		return HexusResources::Menus_HexusFrameBalmerPeaks;
	}
	else if (StrUtils::contains(currentMap, "daemonshallow", true))
	{
		return HexusResources::Menus_HexusFrameDaemonsHallow;
	}
	else if (StrUtils::contains(currentMap, "lambdacrypts", true))
	{
		return HexusResources::Menus_HexusFrameLambdaCrypts;
	}
	else if (StrUtils::contains(currentMap, "voidStar", true))
	{
		return HexusResources::Menus_HexusFrameVoidStar;
	}
	else
	{
		return HexusResources::Menus_HexusFrameEndianForest;
	}
}
