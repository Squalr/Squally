#include "MineWheel.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MineWheel::MapKey = "mine-wheel";
const std::string MineWheel::PropertySpeed = "speed";
const int MineWheel::BucketCount = 5;

MineWheel* MineWheel::create(ValueMap& properties)
{
	MineWheel* instance = new MineWheel(properties);
	
	instance->autorelease();

	return instance;
}

MineWheel::MineWheel(ValueMap& properties) : super(properties)
{
	this->wheel = Sprite::create(ObjectResources::Physics_MineWheel_Wheel);
	this->cranes = std::vector<Node*>();
	this->elapsed = 0.0f;
	this->speed = GameUtils::getKeyOrDefault(this->properties, MineWheel::PropertySpeed, Value(1.0f)).asFloat();

	std::vector<MineWheel::BucketType> ordering = this->createOrdering(MineWheel::BucketCount);

	for (int index = 0; index < MineWheel::BucketCount; index++)
	{
		this->cranes.push_back(this->createBucket(ordering[index]));
	}

	this->addChild(this->wheel);

	for (auto next : this->cranes)
	{
		this->addChild(next);
	}
}

MineWheel::~MineWheel()
{
}

void MineWheel::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void MineWheel::update(float dt)
{
	super::update(dt);

	this->elapsed += dt;

	this->positionBuckets();
}

void MineWheel::initializePositions()
{
	super::initializePositions();

	this->positionBuckets();
}

void MineWheel::positionBuckets()
{
	if (this->cranes.empty())
	{
		return;
	}
	
	const float AngleStep = (float(M_PI) * 2.0f) / ((float)(this->cranes.size()));
	const float RotationsPerSecond = (this->elapsed * float(M_PI) / 8.0f) * this->speed;
	float currentAngle = float(M_PI) / 2.0f + RotationsPerSecond;

	this->wheel->setRotation(currentAngle * 180.0f / float(M_PI));

	for (auto crane : this->cranes)
	{
		crane->setRotation(currentAngle * 180.0f / float(M_PI));
		currentAngle += AngleStep;
	}
}

std::vector<MineWheel::BucketType> MineWheel::createOrdering(int count)
{
	std::vector<BucketType> buckets = std::vector<BucketType>();

	for (int index = 0; index < count; index++)
	{
		buckets.push_back(BucketType(index % int(BucketType::MAX)));
	}

	std::random_device rd1;
	std::mt19937 g1(rd1());

	std::shuffle(buckets.begin(), buckets.end(), g1);

	return buckets;
}

Node* MineWheel::createBucket(BucketType bucketType)
{
	Node* container = Node::create();
	Sprite* fill = nullptr;
	Sprite* bucket = Sprite::create(ObjectResources::Physics_MineWheel_Crane);

	switch(bucketType)
	{
		default:
		case BucketType::Empty:
		{
			break;
		}
		case BucketType::Fill1:
		{
			fill = Sprite::create(ObjectResources::Physics_MineWheel_Fill1);
			fill->setPosition(Vec2(-16.0f, 64.0f));
			break;
		}
		case BucketType::Fill2:
		{
			fill = Sprite::create(ObjectResources::Physics_MineWheel_Fill2);
			fill->setPosition(Vec2(-12.0f, 64.0f));
			break;
		}
		case BucketType::Fill3:
		{
			fill = Sprite::create(ObjectResources::Physics_MineWheel_Fill3);
			fill->setPosition(Vec2(-16.0f, 64.0f));
			break;
		}
	}

	container->setContentSize(bucket->getContentSize());
	container->setAnchorPoint(Vec2(0.868f, 0.782f));

	if (fill != nullptr)
	{
		container->addChild(fill);
	}

	container->addChild(bucket);

	return container;
}
