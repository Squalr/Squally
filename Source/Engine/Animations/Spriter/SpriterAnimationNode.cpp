#include "SpriterAnimationNode.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventAnimation.h"
#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventMainline.h"
#include "Engine/Animations/Spriter/SpriterAnimationParser.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

SpriterAnimationNode* SpriterAnimationNode::create(const std::string& animationResource)
{
	SpriterAnimationNode* instance = new SpriterAnimationNode(animationResource);

	instance->autorelease();

	return instance;
}

SpriterAnimationNode::SpriterAnimationNode(const std::string& animationResource)
{
	this->animationParts = std::map<std::string, SpriterAnimationPart*>();
	this->animationPartContainer = Node::create();
	this->timeline = SpriterAnimationTimeline::getInstance(animationResource);
	
	const SpriterData& spriterData = SpriterAnimationParser::Parse(animationResource);

	this->timeline->registerAnimationNode(this);

	this->buildBones(spriterData);
	this->buildSprites(spriterData, animationResource);

	this->addChild(this->animationPartContainer);
}

SpriterAnimationNode::~SpriterAnimationNode()
{
	if (this->timeline != nullptr)
	{
		this->timeline->unregisterAnimationNode(this);
	}
}

void SpriterAnimationNode::advanceTimelineTime(float dt)
{
	this->previousTimelineTime = this->timelineTime;
	this->timelineTime += dt;
}

float SpriterAnimationNode::getPreviousTimelineTime()
{
	return this->previousTimelineTime;
}

float SpriterAnimationNode::getTimelineTime()
{
	return this->timelineTime;
}

SpriterAnimationPart* SpriterAnimationNode::getPartById(const std::string& name)
{
	if (this->animationParts.find(name) != this->animationParts.end())
	{
		return this->animationParts[name];
	}

	return nullptr;
}

void SpriterAnimationNode::playAnimation(std::string animation)
{

}

void SpriterAnimationNode::setFlippedX(bool isFlippedX)
{
	// TODO
}

void SpriterAnimationNode::buildBones(const SpriterData& spriterData)
{
	for (auto entities : spriterData.entities)
	{
		for (auto objectInfo : entities.objectInfo)
		{
			if (objectInfo.type == "bone")
			{
				SpriterAnimationPart* part = SpriterAnimationPart::create();

				this->animationParts[objectInfo.name] = part;
				this->animationPartContainer->addChild(part);
			}
		}
	}
}
void SpriterAnimationNode::buildSprites(const SpriterData& spriterData, const std::string& animationResource)
{
	std::string containingFolder = StrUtils::replaceAll(animationResource, "\\", "/");
	containingFolder = FileUtils::getInstance()->fullPathForFilename(animationResource);
	containingFolder = containingFolder.substr(0, containingFolder.find_last_of("/\\")) + "/";
	
	for (auto folders : spriterData.folders)
	{
		for (auto file : folders.files)
		{
			SpriterAnimationPart* part = SpriterAnimationPart::create();
			Sprite* sprite = Sprite::create(containingFolder + file.name);

			part->addChild(sprite);

			this->animationParts[file.name] = part;
			this->animationPartContainer->addChild(part);
		}
	}
}
