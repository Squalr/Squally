#include "CipherChest.h"

#include "2d/CCActionInterval.h"
#include "2d/CCSprite.h"

#include "Engine/Input/Input.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Cipher/CipherPuzzleData.h"
#include "Scenes/Cipher/CipherPuzzleRegistry.h"
#include "Scenes/Platformer/Level/Physics//PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CipherChest::MapKey = "cipher-chest";
const std::string CipherChest::PropertyPuzzle = "puzzle";

CipherChest* CipherChest::create(ValueMap& properties)
{
	CipherChest* instance = new CipherChest(properties);

	instance->autorelease();

	return instance;
}

CipherChest::CipherChest(ValueMap& properties) : super(properties, CSize(128.0f, 112.0f))
{
	Sprite* chestOpenFrontSprite = Sprite::create(ObjectResources::Interactive_Chests_CipherChestOpened);
	Sprite* chestClosedSprite = Sprite::create(ObjectResources::Interactive_Chests_CipherChestClosed);
	this->cipherPuzzleData = this->buildPuzzleData();

	this->chestOpen->addChild(chestOpenFrontSprite);
	this->chestClosed->addChild(chestClosedSprite);

	if (this->cipherPuzzleData != nullptr)
	{
		this->addChild(this->cipherPuzzleData);
	}
}

CipherChest::~CipherChest()
{
}

void CipherChest::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CipherChest::initializePositions()
{
	super::initializePositions();
}

void CipherChest::initializeListeners()
{
	super::initializeListeners();
}

void CipherChest::onInteract(PlatformerEntity* interactingEntity)
{
	// Intentionally do not call super here. Overriding default behavior of giving items.
	if (this->cipherPuzzleData == nullptr)
	{
		return;
	}

	CipherEvents::TriggerOpenCipher(CipherEvents::CipherOpenArgs(this->cipherPuzzleData));
}

CipherPuzzleData* CipherChest::buildPuzzleData()
{
	std::string puzzleKey = GameUtils::getKeyOrDefault(this->properties, CipherChest::PropertyPuzzle, Value("")).asString();

	return CipherPuzzleRegistry::createPuzzleData(puzzleKey, [=](CipherPuzzleData* puzzleData)
	{
		this->unlockAndGiveItems();
	});
}
