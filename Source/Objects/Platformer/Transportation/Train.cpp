#include "Train.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Train::MapKey = "train";
const std::string Train::PropertyLocomotiveSize = "locomotive-size";
const std::string Train::PropertyColor = "color";
const std::string Train::PropertySegments = "segments";
const std::string Train::PropertyIsIdling = "is-idling";

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
	this->isIdling = GameUtils::getKeyOrDefault(this->properties, Train::PropertyIsIdling, Value(true)).asBool();
	this->bottomCollision = CollisionObject::create(
		CollisionObject::createBox(CSize(800.0f, 48.0f)),
		int(PlatformerCollisionType::PassThrough),
		CollisionObject::Properties(false, false)
	);
	this->idleSfx = WorldSound::create(SoundResources::Platformer_FX_Train_Idle);
	this->motionSfx = WorldSound::create(SoundResources::Platformer_FX_Train_Moving);
	this->isIdling = GameUtils::getKeyOrDefault(this->properties, Train::PropertyIsIdling, Value(true)).asBool();

	std::string locomotiveSize = GameUtils::getKeyOrDefault(this->properties, Train::PropertyLocomotiveSize, Value("")).asString();
	std::string colorStr = GameUtils::getKeyOrDefault(this->properties, Train::PropertyColor, Value("")).asString();

	if (colorStr == "red")
	{
		this->color = TrainColor::Red;
	}
	else if (colorStr == "blue")
	{
		this->color = TrainColor::Blue;
	}
	else // if (colorStr == "black")
	{
		this->color = TrainColor::Black;
	}

	if (locomotiveSize == "large")
	{
		this->locomotiveSize = LocomotiveSize::Large;
	}
	else if (locomotiveSize == "small")
	{
		this->locomotiveSize = LocomotiveSize::Small;
	}
	else // if (locomotiveSize == "medium")
	{
		this->locomotiveSize = LocomotiveSize::Medium;
	}

	std::string locomotiveAnimationName = "Train_";

	switch(this->color)
	{
		case TrainColor::Red: locomotiveAnimationName += "Red_"; break;
		case TrainColor::Blue: locomotiveAnimationName += "Blue_"; break;
		default: case TrainColor::Black: locomotiveAnimationName += "Black_"; break;
	}

	switch(this->locomotiveSize)
	{
		case LocomotiveSize::Large: locomotiveAnimationName += "Large"; break;
		case LocomotiveSize::Small: locomotiveAnimationName += "Small"; break;
		default: case LocomotiveSize::Medium: locomotiveAnimationName += "Medium"; break;
	}

	this->locomotive = SmartAnimationNode::create(ObjectResources::Transportation_Train_Animations, locomotiveAnimationName);

	std::vector<std::string> segments = StrUtils::splitOn(GameUtils::getKeyOrDefault(this->properties, Train::PropertySegments, Value("")).asString(), ",", false);

	for (const std::string& segment : segments)
	{
		std::string segmentName = "";
		float segmentSize = 100.0f;

		if (segment == "coal")
		{
			segmentSize = 240.0f;
			segmentName = "Coal_";

			switch(this->color)
			{
				case TrainColor::Red: segmentName += "Red"; break;
				case TrainColor::Blue: segmentName += "Blue"; break;
				default: case TrainColor::Black: segmentName += "Black"; break;
			}
		}
		else if (segment == "wagon-l")
		{
			segmentSize = 825.0f;
			segmentName = "Wagon_";

			switch(this->color)
			{
				case TrainColor::Red: segmentName += "Red_"; break;
				case TrainColor::Blue: segmentName += "Blue_"; break;
				default: case TrainColor::Black: segmentName += "Brown_"; break;
			}

			segmentName += "Large";
		}
		else if (segment == "wagon-s")
		{
			segmentSize = 610.0f;
			segmentName = "Wagon_";

			switch(this->color)
			{
				case TrainColor::Red: segmentName += "Red_"; break;
				case TrainColor::Blue: segmentName += "Blue_"; break;
				default: case TrainColor::Black: segmentName += "Brown_"; break;
			}

			segmentName += "Small";
		}

		SmartAnimationNode* segmentAnims = SmartAnimationNode::create(ObjectResources::Transportation_Train_Animations, segmentName);

		this->segments.push_back(std::make_tuple(segmentAnims, segmentSize));
		this->frontNode->addChild(segmentAnims);
	}

	if (this->isIdling)
	{
		this->locomotive->playAnimation("Idle_On", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f, 0.0f, true));
	}
	else
	{
		this->locomotive->playAnimation("Idle", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f, 0.0f, true));
	}

	this->frontNode->addChild(this->bottomCollision);
	this->frontNode->addChild(this->locomotive);
	this->addChild(this->idleSfx);
	this->addChild(this->motionSfx);
}

Train::~Train()
{
}

void Train::onEnter()
{
	super::onEnter();
	
	if (this->isIdling)
	{
		this->idleSfx->play(true);
	}

	this->scheduleUpdate();
}

void Train::initializePositions()
{
	super::initializePositions();

	this->bottomCollision->setPositionY(-420.0f);
	this->positionTrainSegments();
}

void Train::initializeListeners()
{
	super::initializeListeners();
	
	this->interactCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::CartStop }, [=](CollisionData collisionData)
	{
		this->reverse();
		this->dismountAll();
		
		return CollisionResult::CollideWithPhysics;
	});
}

void Train::update(float dt)
{
	super::update(dt);

	this->moveMount(dt);
	this->faceEntityTowardsDirection();
	this->locomotive->setFlippedX(this->mountDirection != MountDirection::Left);

	if (this->cachedMountDirection != this->mountDirection)
	{
		this->cachedMountDirection = this->mountDirection;
		this->positionTrainSegments();
	}
}

void Train::positionTrainSegments()
{
	static const float TrainSize = 490.0f;
	float directionMultiplier = this->mountDirection == MountDirection::Left ? 1.0f : -1.0f;
	float cumulativeOffset = TrainSize * directionMultiplier;
	
	for (const auto& segment : this->segments)
	{
		SmartAnimationNode* segmentAnimations = std::get<0>(segment);
		float segmentSize = std::get<1>(segment);

		if (segmentAnimations != nullptr)
		{
			cumulativeOffset += segmentSize * directionMultiplier;
			segmentAnimations->setPositionX(cumulativeOffset);
			cumulativeOffset += segmentSize * directionMultiplier;
		}
	}
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
	
	this->locomotive->playAnimation("Moving_On", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f, 0.0f, true));
	
	for (const auto& segment : this->segments)
	{
		SmartAnimationNode* segmentAnimations = std::get<0>(segment);
		
		segmentAnimations->playAnimation("Moving", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f, 0.0f, true));
	}

	this->faceEntityTowardsDirection();

	this->isMoving = true;
	this->motionSfx->play(true);
}

void Train::dismount(PlatformerEntity* entity)
{
	super::dismount(entity);
	
	this->isMoving = false;
}

Vec2 Train::getReparentPosition()
{
	return Vec2(0.0f, 1920.0f);
}
