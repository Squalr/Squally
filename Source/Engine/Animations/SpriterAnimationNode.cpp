#include "SpriterAnimationNode.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Animations/SpriterAnimationParser.h"
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
	this->animationPartContainer = Node::create();

	this->loadAnimationData(animationResource);

	this->addChild(this->animationPartContainer);
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

			this->animationParts.push_back(sprite);

			this->animationPartContainer->addChild(sprite);
		}
	}
}
