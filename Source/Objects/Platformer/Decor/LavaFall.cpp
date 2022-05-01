#include "LavaFall.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LavaFall::MapKey = "lava-fall";

LavaFall* LavaFall::create(ValueMap& properties)
{
	LavaFall* instance = new LavaFall(properties);
	
	instance->autorelease();

	return instance;
}

LavaFall::LavaFall(ValueMap& properties) : super(properties)
{
	this->baseAnimation = SmartAnimationSequenceNode::create();
	this->fallAnimation = SmartAnimationSequenceNode::create();

	this->addChild(this->baseAnimation);
	this->addChild(this->fallAnimation);
}

LavaFall::~LavaFall()
{
}

void LavaFall::onEnter()
{
	super::onEnter();

	this->runAnimation();
}

void LavaFall::initializePositions()
{
	super::initializePositions();

	CSize objectSize = CSize(
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
	);

	this->fallAnimation->setContentSize(objectSize);
	this->fallAnimation->setRepeatY(true);
	this->baseAnimation->setPositionY(-objectSize.height / 2.0f - 32.0f);
}

void LavaFall::runAnimation()
{
	const std::vector<std::string>& fallAnimationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(ObjectResources::Decor_LavaFall_Fall_0000);
	const std::vector<std::string>& baseAnimationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(ObjectResources::Decor_LavaFall_Base_0000);

	float baseSpeed = RandomHelper::random_real(0.05f, 0.07f);
	this->fallAnimation->playAnimationRepeat(fallAnimationFiles, baseSpeed);
	this->baseAnimation->playAnimationRepeat(baseAnimationFiles, baseSpeed);
}
