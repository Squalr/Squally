#include "SpriterAnimationNode.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Animations/Spriter/SpriterAnimationParser.h"
#include "Engine/Animations/Spriter/SpriterAnimationTimelineEventAnimation.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

SpriterAnimationNode* SpriterAnimationNode::create(std::string animationResource)
{
	SpriterAnimationNode* instance = new SpriterAnimationNode(animationResource);

	instance->autorelease();

	return instance;
}

SpriterAnimationNode::SpriterAnimationNode(std::string animationResource)
{
	this->animationParts = std::map<int, cocos2d::Sprite*>();
	this->bones = std::map<std::string, cocos2d::Node*>();
	this->animationPartContainer = Node::create();
	this->animations = std::map<std::string, SpriterAnimationTimelineEventAnimation*>();

	this->loadAnimationData(animationResource);

	this->addChild(this->animationPartContainer);
}

void SpriterAnimationNode::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void SpriterAnimationNode::update(float dt)
{
	super::update(dt);

	this->currentTime += dt;
}

void SpriterAnimationNode::setFlippedX(bool isFlippedX)
{
	// TODO
}

void SpriterAnimationNode::loadAnimationData(std::string animationResource)
{
	SpriterData spriterData = SpriterAnimationParser::Parse(animationResource);
	
	std::string containingFolder = StrUtils::replaceAll(animationResource, "\\", "/");
	containingFolder = FileUtils::getInstance()->fullPathForFilename(animationResource);
	containingFolder = containingFolder.substr(0, containingFolder.find_last_of("/\\")) + "/";

	for (auto folders : spriterData.folders)
	{
		for (auto file : folders.files)
		{
			Sprite* sprite = Sprite::create(containingFolder + file.name);

			this->animationParts[file.id] = sprite;
			this->animationPartContainer->addChild(sprite);
		}
	}

	for (auto entities : spriterData.entities)
	{
		for (auto objectInfo : entities.objectInfo)
		{
			if (objectInfo.type == "bone")
			{
				Node* bone = Node::create();

				this->bones[objectInfo.name] = bone;

				this->animationPartContainer->addChild(bone);
			}
		}
	}

	for (auto entities : spriterData.entities)
	{
		for (auto animation : entities.animations)
		{
			SpriterAnimationTimelineEventAnimation* animationTimeline = SpriterAnimationTimelineEventAnimation::create(this, animation);

			this->animations[animation.name] = animationTimeline;

			this->addChild(animationTimeline);
		}
	}
}
