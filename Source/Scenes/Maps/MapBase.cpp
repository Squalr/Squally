#include "MapBase.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerMouse.h"
#include "cocos/base/CCEventMouse.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/UI/HUD/DeveloperHud.h"
#include "Engine/UI/HUD/HackerModeHud.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/Confirmation/ConfirmationMenu.h"
#include "Menus/Dialog/DialogMenu.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Scenes/Maps/Platformer/Backgrounds/MatrixRain/MatrixRain.h"

#include "Resources/BackgroundResources.h"
#include "Resources/ShaderResources.h"

using namespace cocos2d;

bool MapBase::hackerMode = false;

MapBase::MapBase()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->map = nullptr;;
	this->mapNode = Node::create();

	this->pauseMenu = PauseMenu::create();
	this->optionsMenu = OptionsMenu::create();
	this->confirmationMenu = ConfirmationMenu::create();
	this->menuBackDrop = Hud::create();
	this->developerHud = DeveloperHud::create();
	this->hud = Hud::create();

	this->hackerModeGlow = Hud::create();
	this->hackerModeRain = MatrixRain::create();
	this->hackerModeHud = HackerModeHud::create(CC_CALLBACK_0(MapBase::toggleHackerMode, this));
	
	Sprite* glow = Sprite::create(BackgroundResources::MatrixRain_HackerModeBackground);
	glow->setAnchorPoint(Vec2::ZERO);

	this->hackerModeGlow->addChild(glow);
	this->hackerModeGlow->setAnchorPoint(Vec2::ZERO);

	this->hackerModeGlow->setVisible(false);
	this->hackerModeRain->setVisible(false);
	this->hackerModeHud->setVisible(false);

	this->menuBackDrop->addChild(LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height));

	this->developerHud->setVisible(false);

	this->addChild(this->hackerModeRain);
	this->addChild(this->hackerModeHud);
	this->addChild(this->mapNode);
	this->addChild(this->hud);
	this->addChild(this->developerHud);
	this->addChild(this->hackerModeGlow);
	this->addChild(this->menuBackDrop);
	this->addChild(this->pauseMenu);
	this->addChild(this->optionsMenu);
	this->addChild(this->confirmationMenu);
}

MapBase::~MapBase()
{
}

void MapBase::onEnter()
{
	GlobalScene::onEnter();

	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(false);
	this->confirmationMenu->setVisible(false);
}

void MapBase::resume(void)
{
	if (MapBase::hackerMode)
	{
		this->toggleHackerMode();
	}

	GlobalScene::resume();
}

void MapBase::initializeListeners()
{
	GlobalScene::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	keyboardListener->onKeyPressed = (CC_CALLBACK_2(MapBase::onKeyPressed, this));
	mouseListener->onMouseScroll = CC_CALLBACK_1(MapBase::onMouseWheelScroll, this);

	this->optionsMenu->setBackClickCallback(CC_CALLBACK_0(MapBase::onOptionsExit, this));
	this->pauseMenu->setResumeCallback(CC_CALLBACK_0(MapBase::onResumeClick, this));
	this->pauseMenu->setOptionsCallback(CC_CALLBACK_0(MapBase::onOptionsClick, this));
	this->pauseMenu->setExitCallback(CC_CALLBACK_0(MapBase::onExitClick, this));

	this->addEventListener(keyboardListener);
	this->addEventListener(mouseListener);
}

void MapBase::onMouseWheelScroll(EventMouse* event)
{
	if (this->isDeveloperModeEnabled())
	{
		float delta = event->getScrollY() * 64.0f;
		GameCamera::getInstance()->setCameraDistance(GameCamera::getInstance()->getCameraDistance() + delta);
	}
}

void MapBase::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isFocused(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			this->openPauseMenu();
			event->stopPropagation();
			break;
		}
		case EventKeyboard::KeyCode::KEY_TAB:
		{
			this->toggleHackerMode();
			event->stopPropagation();
			break;
		}
		default:
		{
			break;
		}
	}
}

void MapBase::loadMap(SerializableMap* serializableMap)
{
	this->map = serializableMap;
	this->mapNode->removeAllChildren();

	if (this->map != nullptr)
	{
		GameUtils::changeParent(this->map, this->mapNode, false);
		GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));
	}

	this->developerHud->loadMap(serializableMap);
}

void MapBase::onDeveloperModeEnable()
{
	if (this->map != nullptr)
	{
		this->map->setCollisionLayersVisible(true);
	}

	this->developerHud->setVisible(true);

	if (this->getPhysicsWorld() != nullptr)
	{
		this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
	
	Director::getInstance()->setDisplayStats(true);
}

void MapBase::onDeveloperModeDisable()
{
	if (this->map != nullptr)
	{
		this->map->setCollisionLayersVisible(false);
	}

	this->developerHud->setVisible(false);
	
	if (this->getPhysicsWorld() != nullptr)
	{
		this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}

	Director::getInstance()->setDisplayStats(false);
}

void MapBase::onHackerModeEnable()
{
	this->map->hackerModeEnable();
	this->mapNode->setVisible(true);
	this->hud->setVisible(false);

	this->hackerModeGlow->setVisible(true);
	this->hackerModeRain->setVisible(true);
	this->hackerModeHud->setVisible(true);

	GameUtils::focus(this->hackerModeHud);
}

void MapBase::onHackerModeDisable()
{
	this->map->hackerModeDisable();
	this->mapNode->setVisible(true);
	this->hud->setVisible(true);

	this->hackerModeGlow->setVisible(false);
	this->hackerModeRain->setVisible(false);
	this->hackerModeHud->setVisible(false);

	GameUtils::resumeAll();
}

void MapBase::toggleHackerMode()
{
	MapBase::hackerMode = !MapBase::hackerMode;

	if (MapBase::hackerMode)
	{
		this->onHackerModeEnable();
	}
	else
	{
		this->onHackerModeDisable();
	}
}

void MapBase::onOptionsExit()
{
	this->optionsMenu->setVisible(false);
	this->openPauseMenu();
}

void MapBase::openPauseMenu()
{
	this->menuBackDrop->setOpacity(196);
	this->pauseMenu->setVisible(true);
	GameUtils::focus(this->pauseMenu);
}

void MapBase::onResumeClick()
{
	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	GameUtils::focus(this);
}

void MapBase::onOptionsClick()
{
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(true);
	GameUtils::focus(this->optionsMenu);
}

void MapBase::onExitClick()
{
	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	NavigationEvents::navigateTitle();
}
