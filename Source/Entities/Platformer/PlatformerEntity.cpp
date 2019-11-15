#include "PlatformerEntity.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/EntityPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PlatformerEntity::MapKeyPropertyState = "state";
const std::string PlatformerEntity::PlatformerEntityTag = "platformer-entity";

PlatformerEntity::PlatformerEntity(
	ValueMap& properties, 
	std::string entityName,
	std::string scmlResource,
	std::string emblemResource,
	Size size,
	float scale, 
	Vec2 collisionOffset,
	float hoverHeight,
	std::string inventorySaveKey,
	std::string equipmentSaveKey,
	std::string currencySaveKey
	) : super(properties)
{
	this->floatNode = Node::create();
	this->belowAnimationNode = Node::create();
	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->entityScale = scale;
	this->animationResource = scmlResource;
	this->emblemResource = emblemResource;
	this->entityName = entityName;
	this->state = GameUtils::getKeyOrDefault(this->properties, PlatformerEntity::MapKeyPropertyState, Value("")).asString();
	this->entityCollisionOffset = this->entityScale * collisionOffset;
	this->entitySize = size * scale;

	// Tag all entities by class to optimize object queries (ObjectEvents.h)
	this->addTag(PlatformerEntity::PlatformerEntityTag);

	this->hexusOpponentData = nullptr;
	this->inventory = Inventory::create(inventorySaveKey);
	this->equipmentInventory = EquipmentInventory::create(equipmentSaveKey);
	this->currencyInventory = CurrencyInventory::create(currencySaveKey);
	this->speechBubble = SpeechBubble::create();
	this->hoverHeight = hoverHeight;
	this->controlState = ControlState::Normal;
	this->movementSize = this->entitySize + Size(0.0f, this->hoverHeight);

	this->hackButtonOffset = Vec2(this->entityCollisionOffset.x, this->entityCollisionOffset.y + this->hoverHeight + this->entitySize.height);

	this->animationNode->setScale(scale);
	this->animationNode->playAnimation();
	this->animationNode->setPositionY(this->hoverHeight / 2.0f);
	
	this->animationNode->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->animationNode->setFlippedX(this->isFlippedX());

	if (this->isFlippedY())
	{
		this->setRotation(180.0f);
	}

	this->floatNode->addChild(this->belowAnimationNode);
	this->floatNode->addChild(this->animationNode);
	this->addChild(this->floatNode);
	this->addChild(this->speechBubble);
	this->addChild(this->inventory);
	this->addChild(this->equipmentInventory);
	this->addChild(this->currencyInventory);
}

PlatformerEntity::~PlatformerEntity()
{
}

void PlatformerEntity::onEnter()
{
	super::onEnter();
}

void PlatformerEntity::initializePositions()
{
	super::initializePositions();

	Vec2 offset = this->getCollisionOffset() + Vec2(0.0f, this->getEntitySize().height + this->getHoverHeight() / 2.0f + 16.0f);

	this->speechBubble->setPosition(offset);
}

void PlatformerEntity::initializeListeners()
{
	super::initializeListeners();
}

Vec2 PlatformerEntity::getButtonOffset()
{
	return this->hackButtonOffset;
}

HackablePreview* PlatformerEntity::createDefaultPreview()
{
	return EntityPreview::create(this);
}

std::string PlatformerEntity::getEntityKey()
{
	return this->entityName;
}

float PlatformerEntity::getFloatHeight()
{
	return 0.0f;
}

void PlatformerEntity::performSwimAnimation()
{
	this->animationNode->playAnimation("Swim", SmartAnimationNode::AnimationPlayMode::Repeat, 0.75f);
}

void PlatformerEntity::performJumpAnimation()
{
	this->animationNode->playAnimation("Jump", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, 0.85f);
}

Node* PlatformerEntity::getFloatNode()
{
	return this->floatNode;
}

SmartAnimationNode* PlatformerEntity::getAnimations()
{
	return this->animationNode;
}

Size PlatformerEntity::getEntitySize()
{
	return this->entitySize;
}

Size PlatformerEntity::getMovementSize()
{
	return this->movementSize;
}

Vec2 PlatformerEntity::getCollisionOffset()
{
	return this->entityCollisionOffset;
}

float PlatformerEntity::getHoverHeight()
{
	return this->hoverHeight;
}

HexusOpponentData* PlatformerEntity::getHexusOpponentData()
{
	return this->hexusOpponentData;
}

Inventory* PlatformerEntity::getInventory()
{
	return this->inventory;
}

EquipmentInventory* PlatformerEntity::getEquipmentInventory()
{
	return this->equipmentInventory;
}

CurrencyInventory* PlatformerEntity::getCurrencyInventory()
{
	return this->currencyInventory;
}

float PlatformerEntity::getScale()
{
	return this->entityScale;
}

std::string PlatformerEntity::getAnimationResource()
{
	return this->animationResource;
}

std::string PlatformerEntity::getEmblemResource()
{
	return this->emblemResource;
}

bool PlatformerEntity::isFlippedX()
{
	return GameUtils::getKeyOrDefault(this->properties, PlatformerEntity::MapKeyFlipX, Value(false)).asBool();
}

bool PlatformerEntity::isFlippedY()
{
	return GameUtils::getKeyOrDefault(this->properties, PlatformerEntity::MapKeyFlipY, Value(false)).asBool();
}
