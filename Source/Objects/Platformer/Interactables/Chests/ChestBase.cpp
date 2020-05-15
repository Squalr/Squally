#include "ChestBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Input/Input.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CipherEvents.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Objects/Platformer/ItemPools/ChestPools/ChestPoolDeserializer.h"
#include "Objects/Platformer/ItemPools/ErrorPool.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ChestBase::PropertyRewardPool = "reward-pool";
const std::string ChestBase::SaveKeyIsOpen = "SAVE_KEY_IS_OPEN";

ChestBase::ChestBase(ValueMap& properties, Size interactSize) : super(properties, InteractObject::InteractType::Input, interactSize, Vec2::ZERO)
{
	this->chestOpen = Node::create();
	this->chestClosed = Node::create();
	this->chestPool = nullptr;

	this->chestOpenArgs = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyArgs, Value("")).asString();

	ChestPoolDeserializer* chestPoolDeserializer = ChestPoolDeserializer::create();

	ValueMap valueMap = ValueMap();

	valueMap[GameObject::MapKeyType] = ChestPoolDeserializer::MapKeyTypeChestPool;
	valueMap[GameObject::MapKeyName] = GameUtils::getKeyOrDefault(this->properties, ChestBase::PropertyRewardPool, Value("")).asString();

	ObjectDeserializer::ObjectDeserializationRequestArgs deserializeArgs = ObjectDeserializer::ObjectDeserializationRequestArgs(valueMap, [=](ObjectDeserializer::ObjectDeserializationArgs args)
	{
		this->chestPool = static_cast<MinMaxPool*>(args.gameObject);
		this->addChild(this->chestPool);
	});

	chestPoolDeserializer->deserialize(&deserializeArgs);

	this->addChild(this->chestClosed);
	this->addChild(this->chestOpen);
}

ChestBase::~ChestBase()
{
}

void ChestBase::onEnter()
{
	super::onEnter();

	if (this->loadObjectStateOrDefault(ChestBase::SaveKeyIsOpen, Value(false)).asBool())
	{
		this->open(false);
	}
	else
	{
		this->close();
	}
}

void ChestBase::initializePositions()
{
	super::initializePositions();
}

void ChestBase::initializeListeners()
{
	super::initializeListeners();

	this->setInteractCallback([=]()
	{
		return this->tryOpen();
	});
}
		
bool ChestBase::tryOpen()
{
	this->unlockAndGiveItems();

	return true;
}

void ChestBase::unlockAndGiveItems()
{
	this->open(true);

	if (this->chestPool == nullptr)
	{
		this->chestPool = ErrorPool::create();
		this->addChild(this->chestPool);
	}

	PlatformerEvents::TriggerGiveItemsFromPool(PlatformerEvents::GiveItemsFromPoolArgs(this->chestPool));
}

void ChestBase::open(bool doSave)
{
	this->chestOpen->setVisible(true);
	this->chestClosed->setVisible(false);

	if (doSave)
	{
		this->saveObjectState(ChestBase::SaveKeyIsOpen, Value(true));
	}

	this->disable();
}

void ChestBase::close()
{
	this->chestOpen->setVisible(false);
	this->chestClosed->setVisible(true);

	this->enable();
}

