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
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/EntityPreview.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float PlatformerEntity::MoveAcceleration = 5800.0f;
const Vec2 PlatformerEntity::SwimAcceleration = Vec2(8000.0f, 420.0f);
const Size PlatformerEntity::DefaultWeaponSize = Size(64.0f, 128.0f);
const float PlatformerEntity::SwimVerticalDrag = 0.93f;
const float PlatformerEntity::JumpVelocity = 7680.0f;

const int PlatformerEntity::FallBackMaxHealth = 10;
const int PlatformerEntity::FallBackMaxMana = 10;
const int PlatformerEntity::MaxRunes = 3;
const float PlatformerEntity::RuneCooldown = 24.0f;
const int PlatformerEntity::DefaultEq = 1;

const std::string PlatformerEntity::MapKeyPropertyState = "state";

PlatformerEntity::PlatformerEntity(
	ValueMap& properties, 
	std::string scmlResource,
	std::string emblemResource,
	PlatformerCollisionType collisionType,
	Size size,
	float scale, 
	Vec2 collisionOffset,
	int baseHealth,
	int baseSpecial,
	float hoverHeight,
	std::string inventorySaveKey,
	std::string equipmentSaveKey,
	std::string currencySaveKey
	) : super(properties)
{
	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->weaponCollision = nullptr;
	this->entityScale = scale;
	this->collisionType = collisionType;
	this->animationResource = scmlResource;
	this->emblemResource = emblemResource;
	this->isCinimaticHijacked = false;
	this->isPlatformerDisabled = false;
	this->state = GameUtils::getKeyOrDefault(this->properties, PlatformerEntity::MapKeyPropertyState, Value("")).asString();
	this->eq = 0;
	this->eqExperience = 0;
	this->entityCollisionOffset = this->entityScale * collisionOffset;
	
	this->entitySize = size * scale;
	
	this->entityCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(size, scale * 0.9f, 8.0f),
		(CollisionType)(int)this->collisionType,
		false,
		false
	);

	this->hexusOpponentData = nullptr;
	this->inventory = Inventory::create(inventorySaveKey);
	this->equipmentInventory = EquipmentInventory::create(equipmentSaveKey);
	this->currencyInventory = CurrencyInventory::create(currencySaveKey);
	this->speechBubble = SpeechBubble::create();
	this->attacks = std::vector<PlatformerAttack*>();
	this->spawnCoords = this->getPosition();
	this->clickHitbox = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);
	this->hoverHeight = hoverHeight;
	this->controlState = ControlState::Normal;
	this->movementSize = this->entitySize * this->entityScale + Size(0.0f, this->hoverHeight);

	this->hackButtonOffset = Vec2(this->entityCollisionOffset.x, this->entityCollisionOffset.y + this->hoverHeight + this->entitySize.height);

	this->animationNode->setScale(scale);
	this->animationNode->playAnimation("Idle");
	this->animationNode->setPositionY(this->hoverHeight / 2.0f);
	
	this->animationNode->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->clickHitbox->setContentSize(this->entitySize);
	this->clickHitbox->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->clickHitbox->disableInteraction();
	this->clickHitbox->setPosition(Vec2(this->movementSize.width / 2.0f, this->movementSize.height / 2.0f));

	if (GameUtils::keyExists(this->properties, PlatformerEntity::MapKeyFlipX))
	{
		this->animationNode->setFlippedX(this->properties[PlatformerEntity::MapKeyFlipX].asBool());
	}

	if (GameUtils::keyExists(this->properties, PlatformerEntity::MapKeyFlipY))
	{
		this->animationNode->setFlippedY(this->properties[PlatformerEntity::MapKeyFlipY].asBool());
	}

	this->maxHealth = baseHealth;
	this->maxMana = baseSpecial;

	this->health = this->maxHealth;
	this->mana = this->maxMana;
	this->runeCooldowns = std::vector<float>();

	for (int index = 0; index < PlatformerEntity::MaxRunes; index++)
	{
		this->runeCooldowns.push_back(0.0f);
	}

	this->addChild(this->entityCollision);
	this->addChild(this->animationNode);
	this->addChild(this->speechBubble);
	this->addChild(this->clickHitbox);
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

	this->rebuildWeaponCollision(PlatformerEntity::DefaultWeaponSize);

	this->scheduleUpdate();
}

void PlatformerEntity::initializePositions()
{
	super::initializePositions();

	this->speechBubble->setPositionY(this->entitySize.height / 2.0f + 16.0f);
}

void PlatformerEntity::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventCinematicHijack, [=](EventCustom*)
	{
		this->isCinimaticHijacked = true;
	}));

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventCinematicRestore, [=](EventCustom*)
	{
		this->isCinimaticHijacked = false;
	}));
}

void PlatformerEntity::update(float dt)
{
	super::update(dt);

	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		if (this->getRuneCooldown(index) > 0.0f)
		{
			this->setRuneCooldown(index, this->getRuneCooldown(index) - dt);
		}
	}
}

Vec2 PlatformerEntity::getButtonOffset()
{
	return this->hackButtonOffset;
}

HackablePreview* PlatformerEntity::createDefaultPreview()
{
	return EntityPreview::create(this);
}

float PlatformerEntity::getFloatHeight()
{
	return 0.0f;
}

void PlatformerEntity::performSwimAnimation()
{
	this->animationNode->playAnimation("Swim");
}

void PlatformerEntity::performJumpAnimation()
{
	this->animationNode->playAnimation("Jump");
}

void PlatformerEntity::addHealth(int healthDelta)
{
	this->setHealth(this->getHealth() + healthDelta);
}

void PlatformerEntity::setHealth(int health)
{
	if (this->isDead())
	{
		return;
	}

	this->health = MathUtils::clamp(health, 0, this->maxHealth);

	if (this->health <= 0)
	{
		this->animationNode->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
	}
}

void PlatformerEntity::kill(bool loadDeadAnim)
{
	this->setHealth(0);

	if (loadDeadAnim)
	{
		this->animationNode->playAnimation("Dead", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
	}
}

void PlatformerEntity::revive()
{
	this->health = this->getMaxHealth();
	this->mana = this->getMaxMana();

	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		this->setRuneCooldown(index, 0.0f);
	}

	// Idle
	this->animationNode->playAnimation();
}

int PlatformerEntity::getHealth()
{
	return this->health;
}

int PlatformerEntity::getMaxHealth()
{
	return this->maxHealth;
}

bool PlatformerEntity::isAlive()
{
	return !this->isDead();
}

bool PlatformerEntity::isDead()
{
	return this->health <= 0;
}

int PlatformerEntity::getMana()
{
	return this->mana;
}

void PlatformerEntity::addMana(int manaDelta)
{
	this->setMana(this->getMana() + manaDelta);
}

void PlatformerEntity::setMana(int mana)
{
	this->mana = MathUtils::clamp(mana, 0, this->getMaxMana());
}

int PlatformerEntity::getMaxMana()
{
	return this->maxMana;
}

int PlatformerEntity::getAvailableRunes()
{
	int availableRunes = 0;

	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		if (this->getRuneCooldown(index) <= 0.0f)
		{
			availableRunes++;
		}
	}

	return availableRunes;
}

bool PlatformerEntity::tryUseRune()
{
	for (int index = this->getMaxRunes() - 1; index >= 0; index--)
	{
		if (this->getRuneCooldown(index) <= 0.0f)
		{
			PlatformerEvents::TriggerRuneConsumed(PlatformerEvents::RuneConsumedArgs(this, index));

			this->setRuneCooldown(index, PlatformerEntity::RuneCooldown);

			return true;
		}
	}

	return false;
}

float PlatformerEntity::getRuneCooldown(int runeIndex)
{
	int index = MathUtils::clamp(runeIndex, 0, this->getMaxRunes() - 1);

	return this->runeCooldowns[index];
}

void PlatformerEntity::setRuneCooldown(int runeIndex, float cooldown)
{
	int index = MathUtils::clamp(runeIndex, 0, this->getMaxRunes() - 1);

	this->runeCooldowns[index] = MathUtils::clamp(cooldown, 0.0f, PlatformerEntity::RuneCooldown);
}

int PlatformerEntity::getMaxRunes()
{
	return PlatformerEntity::MaxRunes;
}

void PlatformerEntity::setEq(int eq)
{
	this->eq = eq;
}

int PlatformerEntity::getEq()
{
	return this->eq;
}

bool PlatformerEntity::setEqExperience(int eqExperience)
{
	int expToLevel = StatsTables::getExpRequiredAtLevel(this->getEq());

	this->eqExperience = eqExperience;

	if (this->eqExperience >= expToLevel)
	{
		// Level up!
		this->setEq(this->getEq() + 1);
		
		// Recurse to handle potential over-leveling
		this->setEqExperience(this->eqExperience - expToLevel);

		return true;
	}

	return false;
}

bool PlatformerEntity::addEqExperience(int eqExperience)
{
	return this->setEqExperience(this->getEqExperience() + eqExperience);
}

int PlatformerEntity::getEqExperience()
{
	return this->eqExperience;
}

bool PlatformerEntity::getIsPlatformerDisabled()
{
	return this->isPlatformerDisabled;
}

void PlatformerEntity::disablePlatformerControls()
{
	this->isPlatformerDisabled = true;
}

SmartAnimationNode* PlatformerEntity::getAnimations()
{
	return this->animationNode;
}

Size PlatformerEntity::getEntitySize()
{
	return this->entitySize;
}

HexusOpponentData* PlatformerEntity::getHexusOpponentData()
{
	return this->hexusOpponentData;
}

void PlatformerEntity::killAndRespawn()
{
	this->setHealth(0);

	this->runAction(Sequence::create(
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			this->setPosition(this->spawnCoords);
			this->entityCollision->setPosition(Vec2::ZERO);

			this->revive();
		}),
		nullptr
	));
}

std::vector<PlatformerAttack*> PlatformerEntity::getAttacks()
{
	return this->attacks;
}

std::vector<PlatformerAttack*> PlatformerEntity::getAvailableAttacks()
{
	std::vector<PlatformerAttack*> availableAttacks = std::vector<PlatformerAttack*>();

	for (auto it = this->attacks.begin(); it != this->attacks.end(); it++)
	{
		if ((*it)->getSpecialCost() <= this->getMana())
		{
			availableAttacks.push_back(*it);
		}
	}

	return availableAttacks;
}

std::vector<PlatformerAttack*> PlatformerEntity::cloneAttacks()
{
	std::vector<PlatformerAttack*> attacksClone = std::vector<PlatformerAttack*>();

	for (auto it = this->attacks.begin(); it != this->attacks.end(); it++)
	{
		attacksClone.push_back((*it)->clone());
	}

	return attacksClone;
}

Inventory* PlatformerEntity::getInventory()
{
	return this->inventory;
}

CurrencyInventory* PlatformerEntity::getCurrencyInventory()
{
	return this->currencyInventory;
}

void PlatformerEntity::rebuildWeaponCollision(Size size)
{
	AnimationPart* mainhand = this->animationNode->getAnimationPart("mainhand");

	if (mainhand == nullptr)
	{
		return;
	}

	PlatformerCollisionType weaponType = this->collisionType == PlatformerCollisionType::Player ? PlatformerCollisionType::PlayerWeapon : 
		(this->collisionType == PlatformerCollisionType::Enemy ? PlatformerCollisionType::EnemyWeapon : PlatformerCollisionType::None);

	mainhand->removeTrackingObject(this->weaponCollision);

	this->weaponCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(size, 1.0f, 8.0f),
		(int)weaponType,
		false,
		false
	);

	this->weaponCollision->setPhysicsEnabled(false);
	mainhand->addTrackingObject(this->weaponCollision);
}

void PlatformerEntity::registerAttack(PlatformerAttack* attack)
{
	this->addChild(attack);
	this->attacks.push_back(attack);
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
