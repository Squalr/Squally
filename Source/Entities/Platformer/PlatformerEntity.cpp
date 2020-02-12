#include "PlatformerEntity.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Deserializers/Platformer/PlatformerEntityDeserializer.h"
#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
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
const std::string PlatformerEntity::MapKeyBattleAttachedBehavior = "battle-behavior";

PlatformerEntity::PlatformerEntity(
	ValueMap& properties, 
	std::string entityName,
	std::string scmlResource,
	std::string emblemResource,
	Size size,
	float scale, 
	Vec2 collisionOffset,
	float hoverHeight
	) : super(properties)
{
	this->floatNode = Node::create();
	this->belowAnimationNode = Node::create();
	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->entityScale = scale * GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyScale, Value(1.0f)).asFloat();
	this->animationResource = scmlResource;
	this->emblemResource = emblemResource;
	this->entityName = entityName;
	this->state = GameUtils::getKeyOrDefault(this->properties, PlatformerEntity::MapKeyPropertyState, Value("")).asString();
	this->battleBehavior = entityName + "-combat," + GameUtils::getKeyOrDefault(this->properties, PlatformerEntity::MapKeyBattleAttachedBehavior, Value("")).asString();
	this->entityCollisionOffset = this->entityScale * collisionOffset;
	this->entitySize = size * this->entityScale;
	this->platformerEntityDeserializer = PlatformerEntityDeserializer::create();

	// Tag all entities by class to optimize object queries (ObjectEvents.h)
	this->addTag(PlatformerEntity::PlatformerEntityTag);
	this->addTag(PlatformerEntity::entityName);

	this->hexusOpponentData = nullptr;
	this->hoverHeight = hoverHeight;
	this->controlState = ControlState::Normal;
	this->controlStateOverride = ControlState::None;
	this->movementSize = this->entitySize + Size(0.0f, this->hoverHeight);

	this->hackButtonOffset = Vec2(this->entityCollisionOffset.x, this->entityCollisionOffset.y + this->hoverHeight + this->entitySize.height);

	this->animationNode->setScale(this->entityScale);
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
	this->addChild(this->platformerEntityDeserializer);
	this->addChild(this->floatNode);
}

PlatformerEntity::~PlatformerEntity()
{
}

void PlatformerEntity::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void PlatformerEntity::update(float dt)
{
	super::update(dt);

	this->optimizationHideOffscreenEntity();
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

std::string PlatformerEntity::getSwimAnimation()
{
	return "Swim";
}

std::string PlatformerEntity::getJumpAnimation()
{
	return "Jump";
}

PlatformerEntity::ControlState PlatformerEntity::getControlState()
{
	return (this->controlStateOverride == PlatformerEntity::ControlState::None) ? this->controlState : this->controlStateOverride;;
}

std::string PlatformerEntity::getBattleBehavior()
{
	return this->battleBehavior;
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

Vec2 PlatformerEntity::getEntityCenterPoint()
{
	Vec2 offset = this->getCollisionOffset();

	if (this->isFlippedY())
	{
		offset = Vec2(offset.x, -offset.y) - Vec2(0.0f, this->getMovementSize().height / 2.0f);
	}
	else
	{
		offset = offset + Vec2(0.0f, this->getMovementSize().height / 2.0f);
	}

	return offset;
}

float PlatformerEntity::getHoverHeight()
{
	return this->hoverHeight;
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

PlatformerEntity* PlatformerEntity::softClone()
{
	PlatformerEntity* softClone = nullptr;
	ValueMap properties = ValueMap();

	properties[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
	properties[GameObject::MapKeyName] = Value(this->entityName);
	properties[GameObject::MapKeyScale] = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyScale, Value(1.0f));
	properties[GameObject::MapKeyAttachedBehavior] = "disarmed";
	properties[GameObject::MapKeyQueryable] = Value(false);

	ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
		properties,
		[&] (ObjectDeserializer::ObjectDeserializationArgs deserializeArgs)
		{
			softClone = dynamic_cast<PlatformerEntity*>(deserializeArgs.gameObject);
		}
	);

	this->platformerEntityDeserializer->deserialize(&args);

	return softClone;
}

void PlatformerEntity::optimizationHideOffscreenEntity()
{
	float zoom = GameCamera::getInstance()->getCameraZoomOnTarget(this);
	static const Size Padding = Size(384.0f, 384.0f);
	Size clipSize = (Director::getInstance()->getVisibleSize() + Padding) * zoom;
	Rect cameraRect = Rect(GameCamera::getInstance()->getCameraPosition() - Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), clipSize);
	Rect thisRect = Rect(GameUtils::getWorldCoords(this), this->entitySize);

	if (cameraRect.intersectsRect(thisRect))
	{
		this->animationNode->enableRender();
	}
	else
	{
		this->animationNode->disableRender();
	}
}
