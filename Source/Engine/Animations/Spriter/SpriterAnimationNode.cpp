#include "SpriterAnimationNode.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimeline.h"
#include "Engine/Animations/Spriter/SpriterAnimationBone.h"
#include "Engine/Animations/Spriter/SpriterAnimationParser.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/Animations/Spriter/SpriterAnimationSprite.h"
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
	this->bones = std::map<std::string, std::map<std::string, SpriterAnimationBone*>>();
	this->boneIdMap = std::map<int, SpriterAnimationBone*>();
	this->sprites = std::map<std::string, std::map<std::string, SpriterAnimationSprite*>>();
	this->spriteIdMap = std::map<int, SpriterAnimationSprite*>();
	this->animationPartContainer = Node::create();
	this->timeline = SpriterAnimationTimeline::getInstance(animationResource);
	this->isRepeating = true;
	this->currentEntityName = SpriterAnimationNode::DefaultAnimationEntityName;
	this->currentAnimation = SpriterAnimationNode::DefaultAnimationName;
	this->previousTimelineTime = 0.0f;
	this->timelineTime = 0.0f;
	
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
	SpriterAnimationBone* bone = this->getBoneById(name);

	if (bone != nullptr)
	{
		return bone;
	}

	// Check if part matches a sprite name
	return getSpriteById(name);
}

SpriterAnimationBone* SpriterAnimationNode::getBoneById(const std::string& name)
{
	if (this->bones.find(this->currentEntityName) != this->bones.end()
		&& this->bones[this->currentEntityName].find(name) != this->bones[this->currentEntityName].end())
	{
		return this->bones[this->currentEntityName][name];
	}

	return nullptr;
}

SpriterAnimationSprite* SpriterAnimationNode::getSpriteById(const std::string& name)
{
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

const std::map<std::string, SpriterAnimationBone*>& SpriterAnimationNode::getCurrentBoneMap()
{
	if (this->bones.find(this->currentEntityName) == this->bones.end())
	{
		this->bones[this->currentEntityName] = std::map<std::string, SpriterAnimationBone*>();
	}

	return this->bones[this->currentEntityName];
}

const std::map<std::string, SpriterAnimationSprite*>& SpriterAnimationNode::getCurrentSpriteMap()
{
	if (this->sprites.find(this->currentEntityName) == this->sprites.end())
	{
		this->sprites[this->currentEntityName] = std::map<std::string, SpriterAnimationSprite*>();
	}

	return this->sprites[this->currentEntityName];
}

void SpriterAnimationNode::buildBones(const SpriterData& spriterData)
{
	for (auto entity : spriterData.entities)
	{
		for (auto objectInfo : entity.objectInfo)
		{
			if (objectInfo.type == "bone")
			{
				SpriterAnimationBone* bone = SpriterAnimationBone::create(objectInfo.size);

				this->bones[entity.name][objectInfo.name] = bone;
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

	std::map<uint64_t, std::string> folderFileIdMap = std::map<uint64_t, std::string>();
	std::map<uint64_t, Vec2> anchorMap = std::map<uint64_t, Vec2>();
	
	// Build a mapping of folder/file ids to file names
	for (auto folder : spriterData.folders)
	{
		for (auto file : folder.files)
		{
			uint64_t folderFileKey = uint64_t(folder.id) << 32 | uint64_t(file.id);

			folderFileIdMap[folderFileKey] = file.name;
			anchorMap[folderFileKey] = file.anchor;
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

					uint64_t folderFileKey = uint64_t(key.object.folderId) << 32 | uint64_t(key.object.fileId);

					if (folderFileIdMap.find(folderFileKey) == folderFileIdMap.end()
						|| this->sprites[entity.name].find(timeline.name) != this->sprites[entity.name].end())
					{
						continue;
					}

					// Creation was deferred until now rather than during the folder/file id map building, since we needed a timeline id
					// As far as I can tell, timeline ids are the same for all references of an object.
					SpriterAnimationSprite* part = SpriterAnimationSprite::create(containingFolder + folderFileIdMap[folderFileKey], anchorMap[folderFileKey]);
					
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
