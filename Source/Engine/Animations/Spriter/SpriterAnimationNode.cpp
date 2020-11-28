#include "SpriterAnimationNode.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventAnimation.h"
#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventMainline.h"
#include "Engine/Animations/Spriter/SpriterAnimationParser.h"
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
	this->animationParts = std::map<int, cocos2d::Sprite*>();
	this->bones = std::map<int, cocos2d::Node*>();
	this->animationPartContainer = Node::create();
	this->timeline = SpriterAnimationTimeline::getInstance(animationResource);
	
	const SpriterData& spriterData = SpriterAnimationParser::Parse(animationResource);

	this->buildBones(spriterData);
	this->buildSprites(spriterData, animationResource);

	this->addChild(this->animationPartContainer);
}

SpriterAnimationNode::~SpriterAnimationNode()
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
				Node* bone = Node::create();

				// this->bones[objectInfo.name] = bone;

				this->animationPartContainer->addChild(bone);
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
			Sprite* sprite = Sprite::create(containingFolder + file.name);

			this->animationParts[file.id] = sprite;
			this->animationPartContainer->addChild(sprite);
		}
	}
}
