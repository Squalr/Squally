#include "Squally.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/EntityPreview.h"
#include "Entities/Platformer/Misc/DaemonsHallow/FlyBot.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/IsAliveClippy.h"
#include "Events/NavigationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Punch.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Inventory/PlayerCurrencyInventory.h"
#include "Scenes/Platformer/Inventory/PlayerEquipment.h"
#include "Scenes/Platformer/Inventory/PlayerInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Entities/Squally/IsAlive/IsAlive.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_IS_ALIVE 1

const std::string Squally::EventSquallyTrapped = "event-squally-trapped";

const float Squally::SquallyScale = 0.92f;
const int Squally::DefaultEq = 1;
const std::string Squally::MapKeySqually = "squally";
const std::string Squally::IdentifierIsAlive = "is-alive";
const int Squally::SquallyBaseHealth = 16;
const int Squally::SquallyBaseSpecial = 8;

Squally* Squally::deserialize(ValueMap& properties)
{
	Squally* instance = new Squally(properties);

	instance->autorelease();
	
	return instance;
}

Squally::Squally(ValueMap& properties) : super(properties,
	EntityResources::Squally_Animations,
	EntityResources::Squally_Emblem,
	PlatformerCollisionType::Player,
	Size(128.0f, 128.0f),
	Squally::SquallyScale,
	Vec2(0.0f, 24.0f),
	Squally::SquallyBaseHealth,
	Squally::SquallyBaseSpecial,
	Size(128.0f, 224.0f),
	24.0f)
{
	this->noCombatDuration = 0.0f;
	this->eq = 0;
	this->eqExperience = 0;
	this->cameraTrackTarget = Node::create();
	this->leftEyeController = SmartAnimationSequenceNode::create();
	this->rightEyeController = SmartAnimationSequenceNode::create();

	this->registerHackables();
	this->registerAttack(Punch::create(0.4f, 0.5f));

	this->currencyInventory = PlayerCurrencyInventory::getInstance();
	this->inventory = PlayerInventory::getInstance();

	this->leftEyeController->setVisible(false);
	this->rightEyeController->setVisible(false);

	this->addChild(this->cameraTrackTarget);
	this->addChild(this->leftEyeController);
	this->addChild(this->rightEyeController);
}

Squally::~Squally()
{
}

void Squally::onEnter()
{
	super::onEnter();

	this->noCombatDuration = 2.0f;

	this->loadState();
	this->updateWeaponVisual();
	this->runEyeBlinkLoop();

	// Request camera track player
	CameraTrackingData trackingData = CameraTrackingData(this->cameraTrackTarget, Vec2(128.0f, 96.0f));
	GameCamera::getInstance()->setTarget(trackingData, true);
}

void Squally::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	// Request HUD track player
	PlatformerEvents::TriggerHudTrackEntity(PlatformerEvents::HudTrackEntityArgs(this));
}

void Squally::onExit()
{
	super::onExit();

	PlatformerEvents::TriggerHudUntrackEntity(PlatformerEvents::HudTrackEntityArgs(this));

	this->saveState();
}

void Squally::initializeCollisionEvents()
{
	super::initializeCollisionEvents();

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyFlying }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->noCombatDuration > 0.0f || this->isDead())
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		this->noCombatDuration = 2.0f;
		this->saveState();
		
		PlatformerEnemy* enemy = dynamic_cast<PlatformerEnemy*>(collisionData.other->getParent());

		if (enemy != nullptr && !enemy->isDead() && enemy->getBattleMapResource() != "")
		{
			// TODO: First strike detection
			NavigationEvents::navigateCombat(NavigationEvents::NavigateCombatArgs(
				true,
				enemy->getUniqueIdentifier(),
				enemy->getBattleMapResource(),
				enemy->getBattleMapArgs(),
				{ Squally::MapKeySqually, SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value(FlyBot::MapKeyFlyBot)).asString() },
				enemy->getCombatEntityList()));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Damage, }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->isAlive())
		{
			this->killAndRespawn();
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
	
	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->isAlive())
		{
			AnimationPart* mouth = this->getAnimations()->getAnimationPart("mouth");
			
			mouth->replaceSprite(EntityResources::Squally_MOUTH_SWIMMING);
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->isAlive())
		{
			AnimationPart* mouth = this->getAnimations()->getAnimationPart("mouth");

			mouth->replaceSprite(EntityResources::Squally_MOUTH);
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::FriendlyNpc, }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Squally::initializePositions()
{
	super::initializePositions();

	this->cameraTrackTarget->setPosition(Vec2(0.0f, 128.0f));
}

void Squally::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(HackableEvents::EventRequestHackerModeEnable, [=](EventCustom*)
	{
		if (this->tryUseRune())
		{
			HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->getEq()));
		}
	}));

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_TAB }, [=](InputEvents::InputArgs* args)
	{
		args->handled = true;
		
		if (this->tryUseRune())
		{
			HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->getEq()));
		}
	});

	this->whenKeyPressedHackerMode({ EventKeyboard::KeyCode::KEY_TAB, EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		args->handled = true;

		HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->getEq()));
	});

	this->listenForMapEvent(Squally::EventSquallyTrapped, [=](ValueMap args)
	{
		for (auto it = this->codeList.begin(); it != this->codeList.end(); it++)
		{
			if ((*it)->getHackableCodeIdentifier() == Squally::IdentifierIsAlive)
			{
				(*it)->getClippy()->setIsEnabled(true);
			}
		}
	});
}

Vec2 Squally::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

float Squally::getFloatHeight()
{
	return 64.0f;
}

cocos2d::Vec2 Squally::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Squally::update(float dt)
{
	super::update(dt);

	if (this->noCombatDuration > 0.0f)
	{
		this->noCombatDuration -= dt;
	}

	if (this->isCinimaticHijacked || this->getIsPlatformerDisabled() || this->isDead())
	{
		return;
	}

	// Check for player suicide
	if (!this->isAliveSqually())
	{
		this->killAndRespawn();
	}

	//// Vec2 squallyPosition = GameUtils::getScreenBounds(this->animationNode).origin;
	//// this->animationNode->setFlippedX(squallyPosition.x > MouseState::getMousePosition().x);

	this->movement = Vec2::ZERO;

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->movement.x = -1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->movement.x = 1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_W) || Input::isPressed(EventKeyboard::KeyCode::KEY_SPACE))
	{
		this->movement.y = 1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_S))
	{
		this->movement.y = -1.0f;
	}

	if (this->movement != Vec2::ZERO)
	{
		// Soft save the player's position
		SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyPositionX, Value(this->getPositionX()));
		SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyPositionY, Value(this->getPositionY()));
	}
}

void Squally::performSwimAnimation()
{
	if (PlayerEquipment::getInstance()->getWeapon() != nullptr)
	{
		this->animationNode->playAnimation("SwimWithWeapon");
	}
	else
	{
		this->animationNode->playAnimation("Swim");
	}
}

void Squally::onHackerModeEnable()
{
	super::onHackerModeEnable();
}

void Squally::registerHackables()
{
	super::registerHackables();

	IsAliveClippy* isAliveClippy = IsAliveClippy::create();

	isAliveClippy->setIsEnabled(true);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_IS_ALIVE,
			HackableCode::LateBindData(
				Squally::IdentifierIsAlive,
				Strings::Hacking_Entities_Squally_IsAlive_IsAlive::create(),
				UIResources::Menus_Icons_Heart,
				EntityPreview::create(this),
				{
				},
				2,
				1.0f,
				isAliveClippy
			)
		},
	};

	auto isAliveSquallyFunc = &Squally::isAliveSqually;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)isAliveSquallyFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

NO_OPTIMIZE bool Squally::isAliveSqually()
{
	// The compiler will save EBP, we need to restore it before returning
	ASM(pop ZBP);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_IS_ALIVE);

	ASM(mov ZAX, 1);
	ASM(ret);

	HACKABLE_CODE_END();

	HACKABLES_STOP_SEARCH();

	// Just to make compiler stop crying
	return true;
}

void Squally::saveState()
{
	ValueVector cooldowns = ValueVector();

	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		cooldowns.push_back(Value(this->getRuneCooldown(index)));
	}

	SaveManager::batchSaveProfileData({
		{ SaveKeys::SaveKeySquallyHeath, Value(this->getHealth()) },
		{ SaveKeys::SaveKeySquallyMana, Value(this->getMana()) },
		{ SaveKeys::SaveKeySquallyRuneCooldowns, Value(cooldowns) },
		{ SaveKeys::SaveKeySquallyEqExperience, Value(this->getEqExperience()) },
		{ SaveKeys::SaveKeySquallyEq, Value(this->getEq()) }
	});
}

void Squally::loadState()
{
	// Note: We just use the current value by default. This is normally the max if Squally was just constructed, but might also
	// Be a lower value (ie if created as injured for a cutscene)
	this->setHealth(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyHeath, Value(this->getHealth())).asInt());
	this->setMana(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyMana, Value(this->getMana())).asInt());
	this->setEq(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEq, Value(Squally::DefaultEq)).asInt());
	this->setEqExperience(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEqExperience, Value(this->getEqExperience())).asInt());

	ValueVector cooldowns = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyRuneCooldowns, Value(ValueVector())).asValueVector();

	for (int index = 0; index < std::min((int)cooldowns.size(), (int)this->getMaxRunes()); index++)
	{
		this->setRuneCooldown(index, cooldowns[index].asFloat());
	}
	
	this->setPosition(Vec2(
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionX, Value(this->getPositionX())).asFloat(),
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionY, Value(this->getPositionY())).asFloat()
	));

	// Save new defaults
	this->saveState();
}

void Squally::setEq(int eq)
{
	this->eq = eq;
}

int Squally::getEq()
{
	return this->eq;
}

void Squally::setEqExperience(int eqExperience)
{
	this->eqExperience = eqExperience;
}

void Squally::addEqExperience(int eqExperience)
{
	this->setEqExperience(this->getEqExperience() + eqExperience);
}

int Squally::getEqExperience()
{
	return this->eqExperience;
}

void Squally::updateWeaponVisual()
{
	Weapon* weapon = PlayerEquipment::getInstance()->getWeapon();

	if (weapon != nullptr)
	{
		AnimationPart* mainhand = this->getAnimations()->getAnimationPart("mainhand");
		
		if (mainhand != nullptr)
		{
			mainhand->replaceSprite(weapon->getIconResource());
			mainhand->setOffset(weapon->getDisplayOffset());
		}
	}
}

void Squally::runEyeBlinkLoop()
{
	const float BlinkSpeed = 0.0075f;
	const float EyesClosedDuration = 0.015f;
	const float TimeBetweenBlinks = 5.5f;
	
	this->leftEyeController->playAnimationAndReverseRepeat(EntityResources::Squally_Blink_EYE_L_Blink_0000, BlinkSpeed, EyesClosedDuration, BlinkSpeed, TimeBetweenBlinks);
	this->leftEyeController->getForwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* leftEye = this->getAnimations()->getAnimationPart("eye_left");
		
		if (leftEye != nullptr)
		{
			leftEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
	this->leftEyeController->getBackwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* leftEye = this->getAnimations()->getAnimationPart("eye_left");
		
		if (leftEye != nullptr)
		{
			leftEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
	this->rightEyeController->playAnimationAndReverseRepeat(EntityResources::Squally_Blink_EYE_L_Blink_0000, BlinkSpeed, EyesClosedDuration, BlinkSpeed, TimeBetweenBlinks);
	this->rightEyeController->getForwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* rightEye = this->getAnimations()->getAnimationPart("eye_right");
		
		if (rightEye != nullptr)
		{
			rightEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
	this->rightEyeController->getBackwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* rightEye = this->getAnimations()->getAnimationPart("eye_right");
		
		if (rightEye != nullptr)
		{
			rightEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
}
