#include "Train.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Train::MapKey = "train";

Train* Train::create(cocos2d::ValueMap& properties)
{
	Train* instance = new Train(properties);

	instance->autorelease();

	return instance;
}

Train::Train(cocos2d::ValueMap& properties) : super(properties, CSize(1083.0f, 931.0f), false)
{
	this->parseDirection();
	this->mountSpeed = GameUtils::getKeyOrDefault(this->properties, Train::PropertySpeed, Value(512.0f)).asFloat();
	this->trainHead = SmartAnimationNode::create(ObjectResources::Transportation_Train_Animations, "Train_Red");
	this->bottomCollision = CollisionObject::create(
		CollisionObject::createBox(CSize(800.0f, 48.0f)),
		int(PlatformerCollisionType::PassThrough),
		CollisionObject::Properties(false, false)
	);

	this->trainHead->playAnimation("Large_Idle", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f, 0.0f, true));

	this->frontNode->addChild(this->bottomCollision);
	this->frontNode->addChild(this->trainHead);
}

Train::~Train()
{
}

void Train::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Train::initializePositions()
{
	super::initializePositions();

	this->bottomCollision->setPositionY(-420.0f);
}

void Train::initializeListeners()
{
	super::initializeListeners();
	
	this->interactCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::CartStop }, [=](CollisionData collisionData)
	{
		this->reverse();
		this->dismount();
		
		return CollisionResult::CollideWithPhysics;
	});
}

void Train::update(float dt)
{
	super::update(dt);

	this->moveMount(dt);
	this->faceEntityTowardsDirection();
	this->trainHead->setFlippedX(this->mountDirection != MountDirection::Left);
}

void Train::mount(PlatformerEntity* interactingEntity)
{
	super::mount(interactingEntity);

	CameraTrackingData* currentData = GameCamera::getInstance()->getCurrentTrackingData();

	GameCamera::getInstance()->setTarget(CameraTrackingData(
		this,
		Vec2(0.0f, 128.0f),
		Vec2::ZERO,
		CameraTrackingData::CameraScrollType::Rectangle,
		cocos2d::Vec2(0.015f, 0.015f),
		currentData ? currentData->zoom : 1.0f,
		nullptr,
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyTag, Value("")).asString()
	));
	
	this->trainHead->playAnimation("Large_Moving_On", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f, 0.0f, true));
	this->faceEntityTowardsDirection();

	this->isMoving = true;
}

void Train::dismount()
{
	super::dismount();
	
	this->isMoving = false;
}

Vec2 Train::getReparentPosition()
{
	return Vec2(0.0f, 1920.0f);
}
