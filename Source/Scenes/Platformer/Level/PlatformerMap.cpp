#include "PlatformerMap.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Deserializers/Deserializers.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/GameMap.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Cipher.h"
#include "Scenes/Platformer/Level/Huds/Components/CurrencyDisplay.h"
#include "Scenes/Platformer/Level/Huds/Components/RuneBar.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"
#include "Scenes/Platformer/Level/Huds/GameHud.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

PlatformerMap* PlatformerMap::create(std::string mapResource, std::vector<std::string> mapArgs, bool isReload)
{
	PlatformerMap* instance = new PlatformerMap();

	instance->autorelease();

	// Clear any intra-map save-state
	if (isReload)
	{
		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionX);
		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionY);
	}

	instance->loadMap(mapResource, mapArgs);

	return instance;
}

PlatformerMap::PlatformerMap() : super(true)
{
	if (!PlatformerMap::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->gameHud = GameHud::create();
	this->cipher = Cipher::create();

	this->addLayerDeserializers({
			BackgroundDeserializer::create(),
			MusicDeserializer::create(),
			PhysicsDeserializer::create(),
			ObjectLayerDeserializer::create({
				{ CollisionDeserializer::MapKeyTypeCollision, CollisionDeserializer::create() },
				{ PlatformerDecorDeserializer::MapKeyTypeDecor, PlatformerDecorDeserializer::create() },
				{ PlatformerEntityDeserializer::MapKeyTypeEntity, PlatformerEntityDeserializer::create() },
				{ PlatformerObjectDeserializer::MapKeyTypeObject, PlatformerObjectDeserializer::create() },
				{ PlatformerTerrainDeserializer::MapKeyTypeTerrain, PlatformerTerrainDeserializer::create() },
			}),
			WeatherDeserializer::create()
		}
	);

	this->getPhysicsWorld()->setAutoStep(false);

	this->hackerModeVisibleHud->addChild(this->gameHud);
	this->menuHud->addChild(this->cipher);
}

PlatformerMap::~PlatformerMap()
{
}

void PlatformerMap::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void PlatformerMap::onExit()
{
	super::onExit();

	SaveManager::save();
}

void PlatformerMap::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void PlatformerMap::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventOpenCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherLoadArgs* args = static_cast<CipherEvents::CipherLoadArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->menuBackDrop->setOpacity(196);
			this->cipher->setVisible(true);
			this->cipher->openCipher(args->cipherPuzzleData);
			GameUtils::focus(this->cipher);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventExitCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherExitArgs* args = static_cast<CipherEvents::CipherExitArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->menuBackDrop->setOpacity(0);
			this->cipher->setVisible(false);
			GameUtils::focus(this);
		}
	}));
}

void PlatformerMap::update(float dt)
{
	super::update(dt);

	// Fixed step seems to prevent some really obnoxious bugs where a poor frame-rate can cause the time delta to build up, causing objects to go flying
	this->getPhysicsWorld()->step(1.0f / 60.0f);
}

void PlatformerMap::loadMap(std::string mapResource, std::vector<std::string> args)
{
	ValueVector argsVector = ValueVector();

	for (auto it = args.begin(); it != args.end(); it++)
	{
		argsVector.push_back(Value(*it));
	}

	SaveManager::batchSaveProfileData({
		{ SaveKeys::SaveKeyMap, Value(mapResource) },
		{ SaveKeys::SaveKeyMapArgs, Value(argsVector) }
	});

	super::loadMap(mapResource, args);
}
