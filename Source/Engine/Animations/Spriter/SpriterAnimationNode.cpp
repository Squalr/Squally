#include "SpriterAnimationNode.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventAnimation.h"
#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventMainline.h"
#include "Engine/Animations/Spriter/SpriterAnimationParser.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

const std::string SpriterAnimationNode::DefaultAnimationEntityName = "Entity";
const std::string SpriterAnimationNode::DefaultAnimationName = "Idle";

SpriterAnimationNode* SpriterAnimationNode::create(const std::string& animationResource)
{
	SpriterAnimationNode* instance = new SpriterAnimationNode(animationResource);

	instance->autorelease();

	return instance;
}

SpriterAnimationNode::SpriterAnimationNode(const std::string& animationResource)
{
	this->bones = std::map<std::string, std::map<std::string, SpriterAnimationPart*>>();
	this->boneIdMap = std::map<int, SpriterAnimationPart*>();
	this->sprites = std::map<std::string, std::map<std::string, SpriterAnimationPart*>>();
	this->spriteIdMap = std::map<int, SpriterAnimationPart*>();
	this->animationPartContainer = Node::create();
	this->timeline = SpriterAnimationTimeline::getInstance(animationResource);
	this->isRepeating = true;
	this->currentEntityName = SpriterAnimationNode::DefaultAnimationEntityName;
	this->currentAnimation = SpriterAnimationNode::DefaultAnimationName;
	
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

void SpriterAnimationNode::advanceTimelineTime(float dt, float timelineMax)
{
	this->previousTimelineTime = this->timelineTime;
	this->timelineTime = MathUtils::wrappingNormalize(this->timelineTime + dt, 0.0f, timelineMax);
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
	// Check if part matches a bone name
	if (this->bones.find(this->currentEntityName) != this->bones.end()
		&& this->bones[this->currentEntityName].find(name) != this->bones[this->currentEntityName].end())
	{
		return this->bones[this->currentEntityName][name];
	}

	// Check if part matches a sprite name
	if (this->sprites.find(this->currentEntityName) != this->sprites.end()
		&& this->sprites[this->currentEntityName].find(name) != this->sprites[this->currentEntityName].end())
	{
		return this->sprites[this->currentEntityName][name];
	}

	return nullptr;
}

void SpriterAnimationNode::playAnimation(std::string animation)
{
	this->currentAnimation = animation;
	this->resetAnimation();
}

void SpriterAnimationNode::resetAnimation()
{
	this->previousTimelineTime = 0.0f;
	this->timelineTime = 0.0f;
}

void SpriterAnimationNode::setFlippedX(bool isFlippedX)
{
	// TODO
}

const std::string& SpriterAnimationNode::getCurrentEntityName()
{
	return this->currentEntityName;
}

const std::string& SpriterAnimationNode::getCurrentAnimation()
{
	return this->currentAnimation;
}

void SpriterAnimationNode::buildBones(const SpriterData& spriterData)
{
	for (auto entity : spriterData.entities)
	{
		for (auto objectInfo : entity.objectInfo)
		{
			if (objectInfo.type == "bone")
			{
				SpriterAnimationPart* part = SpriterAnimationPart::create();

				this->bones[entity.name][objectInfo.name] = part;
				this->animationPartContainer->addChild(part);

				// TODO: Get the ID for the bone. This will be tedious.
				// Perhaps this logic needs to be moved to a pre-processing and passed with parsed data.
				// This shit seems to be expensive and pre-computable.
				this->boneIdMap = this->boneIdMap;
			}
		}
	}
}
void SpriterAnimationNode::buildSprites(const SpriterData& spriterData, const std::string& animationResource)
{
	std::string containingFolder = StrUtils::replaceAll(animationResource, "\\", "/");
	containingFolder = FileUtils::getInstance()->fullPathForFilename(animationResource);
	containingFolder = containingFolder.substr(0, containingFolder.find_last_of("/\\")) + "/";

	std::map<unsigned long long, std::string> folderFileIdMap = std::map<unsigned long long, std::string>();
	
	// Build a mapping of folder/file ids to file names
	for (auto folder : spriterData.folders)
	{
		for (auto file : folder.files)
		{
			folderFileIdMap[unsigned long long(folder.id) << 32 | unsigned long long(file.id)] = file.name;
		}
	}
	
	for (auto entity : spriterData.entities)
	{
		for (auto animation : entity.animations)
		{
			for (auto timeline : animation.timelines)
			{
				for (auto key : timeline.keys)
				{
					if (key.objectType != SpriterObjectType::Object)
					{
						continue;
					}

					unsigned long long folderFileKey = unsigned long long(key.object.folderId) << 32 | unsigned long long(key.object.fileId);

					if (folderFileIdMap.find(folderFileKey) == folderFileIdMap.end()
						|| this->sprites[entity.name].find(timeline.name) != this->sprites[entity.name].end())
					{
						continue;
					}

					// Creation was deferred until now rather than during the folder/file id map building, since we needed a timeline id
					// As far as I can tell, timeline ids are the same for all references of an object.
					SpriterAnimationPart* part = SpriterAnimationPart::create();
					Sprite* sprite = Sprite::create(containingFolder + folderFileIdMap[folderFileKey]);

					part->addChild(sprite);

					this->animationPartContainer->addChild(part);

					this->sprites[entity.name][timeline.name] = part;
					this->spriteIdMap[timeline.id] = part;

					// Erase the key to ensure we only create the sprite once
					folderFileIdMap.erase(folderFileKey);
				}
			}
		}
	}
}
