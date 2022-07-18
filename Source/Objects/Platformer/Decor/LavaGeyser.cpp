#include "LavaGeyser.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LavaGeyser::MapKey = "lava-geyser";
 const float LavaGeyser::BaseSize = 252.0f;
 const float LavaGeyser::MidSize = 350.0f;

LavaGeyser* LavaGeyser::create(ValueMap& properties)
{
	LavaGeyser* instance = new LavaGeyser(properties);
	
	instance->autorelease();

	return instance;
}

LavaGeyser::LavaGeyser(ValueMap& properties) : super(properties)
{
	CSize objectSize = CSize(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
	);
	this->baseAnimation = SmartAnimationSequenceNode::create();
	this->midAnimation = SmartAnimationSequenceNode::create();
	this->topAnimation = SmartAnimationSequenceNode::create();
	this->hitbox = CollisionObject::create(CollisionObject::createBox(CSize(224.0f, objectSize.height)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));

	this->midAnimation->setRepeatY(true);

	float midRange = objectSize.height - LavaGeyser::BaseSize;
	float overflow = std::fmodf(midRange, LavaGeyser::MidSize);

	this->midAnimation->setContentSize(CSize(objectSize.width, objectSize.height - LavaGeyser::BaseSize));
	this->midAnimation->setRepeatTilingOffset(Vec2(0.0f, LavaGeyser::MidSize - overflow));

	this->addChild(this->baseAnimation);
	this->addChild(this->midAnimation);
	this->addChild(this->topAnimation);
	this->addChild(this->hitbox);
}

LavaGeyser::~LavaGeyser()
{
}

void LavaGeyser::onEnter()
{
	super::onEnter();

	this->runAnimation();
}

void LavaGeyser::initializePositions()
{
	super::initializePositions();

	CSize objectSize = CSize(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
	);

	this->baseAnimation->setPositionY(-objectSize.height / 2.0f + LavaGeyser::BaseSize / 2.0f);
	this->midAnimation->setPositionY(LavaGeyser::BaseSize / 2.0f - 1.0f); // Small offset to hide seams
	this->topAnimation->setPositionY(objectSize.height / 2.0f - LavaGeyser::BaseSize / 2.0f + 64.0f);
}

void LavaGeyser::runAnimation()
{
	static const std::vector<std::string>& baseAnimationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(ObjectResources::Decor_LavaGeyser_Base_0000);
	static const std::vector<std::string>& midAnimationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(ObjectResources::Decor_LavaGeyser_Mid_0000);
	static const std::vector<std::string>& topAnimationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(ObjectResources::Decor_LavaGeyser_Head_0000);

	float animSpeed = RandomHelper::random_real(0.05f, 0.07f);
	this->baseAnimation->playAnimationRepeat(baseAnimationFiles, animSpeed);

	// Make the mid animation a function of the base anim to ensure they are kept in perfect sync
	this->baseAnimation->setSpriteChangeCallback([=](const std::string, int index)
	{
		this->midAnimation->playSingleFrame(midAnimationFiles, index, 0.0f);
	});

	this->topAnimation->playAnimationRepeat(topAnimationFiles, animSpeed + 0.03f);
}
