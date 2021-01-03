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
	this->bonesByName = std::map<std::string, std::map<std::string, SpriterAnimationBone*>>();
	this->bonesByHash = std::map<std::string, std::map<int, SpriterAnimationBone*>>();
	this->spritesByName = std::map<std::string, std::map<std::string, SpriterAnimationSprite*>>();
	this->spritesByHash = std::map<std::string, std::map<int, SpriterAnimationSprite*>>();
	this->timeline = SpriterAnimationTimeline::getInstance(animationResource);
	this->isRepeating = true;
	this->currentAnimation = SpriterAnimationNode::DefaultAnimationName;
	this->previousTimelineTime = 0.0f;
	this->timelineTime = 0.0f;
	this->entityBonesByName = nullptr;
	this->entityBonesByHash = nullptr;
	this->entitySpritesByName = nullptr;
	this->entitySpritesByHash = nullptr;
	
	const SpriterData& spriterData = SpriterAnimationParser::Parse(animationResource);

	this->timeline->registerAnimationNode(this);

	this->buildBones(spriterData);
	this->buildSprites(spriterData, animationResource);
	this->setCurrentEntity(SpriterAnimationNode::DefaultAnimationEntityName);
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

SpriterAnimationPart* SpriterAnimationNode::getPartByName(const std::string& name)
{
	// Check if part matches a bone name
	SpriterAnimationBone* bone = this->getBoneByName(name);

	if (bone != nullptr)
	{
		return bone;
	}

	// Check if part matches a sprite name
	return getSpriteByName(name);
}

SpriterAnimationBone* SpriterAnimationNode::getBoneByName(const std::string& name)
{
	if (this->entityBonesByName != nullptr && this->entityBonesByName->find(name) != this->entityBonesByName->end())
	{
		return (*this->entityBonesByName)[name];
	}

	return nullptr;
}

SpriterAnimationSprite* SpriterAnimationNode::getSpriteByName(const std::string& name)
{
	if (this->entitySpritesByName != nullptr && this->entitySpritesByName->find(name) != this->entitySpritesByName->end())
	{
		return (*this->entitySpritesByName)[name];
	}

	return nullptr;
}

SpriterAnimationPart* SpriterAnimationNode::getPartByHash(int id)
{
	// Check if part matches a bone id
	SpriterAnimationBone* bone = this->getBoneByHash(id);

	if (bone != nullptr)
	{
		return bone;
	}

	// Check if part matches a sprite id
	return getSpriteByHash(id);
}

SpriterAnimationBone* SpriterAnimationNode::getBoneByHash(int id)
{
	if (this->entityBonesByHash != nullptr && this->entityBonesByHash->find(id) != this->entityBonesByHash->end())
	{
		return (*this->entityBonesByHash)[id];
	}

	return nullptr;
}

SpriterAnimationSprite* SpriterAnimationNode::getSpriteByHash(int id)
{
	if (this->entitySpritesByHash != nullptr && this->entitySpritesByHash->find(id) != this->entitySpritesByHash->end())
	{
		return (*this->entitySpritesByHash)[id];
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
	this->setScaleX(isFlippedX ? -1.0f : 1.0f);
}

void SpriterAnimationNode::setCurrentEntity(const std::string& currentEntityName)
{
	this->currentEntityName = currentEntityName;
	this->entityBonesByName = nullptr;
	this->entityBonesByHash = nullptr;
	this->entitySpritesByName = nullptr;
	this->entitySpritesByHash = nullptr;
	
	if (this->bonesByName.contains(this->currentEntityName))
	{
		this->entityBonesByName = &this->bonesByName[this->currentEntityName];
	}
	
	if (this->bonesByHash.contains(this->currentEntityName))
	{
		this->entityBonesByHash = &this->bonesByHash[this->currentEntityName];
	}
	
	if (this->spritesByName.contains(this->currentEntityName))
	{
		this->entitySpritesByName = &this->spritesByName[this->currentEntityName];
	}
	
	if (this->spritesByHash.contains(this->currentEntityName))
	{
		this->entitySpritesByHash = &this->spritesByHash[this->currentEntityName];
	}
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
	if (!this->bonesByName.contains(this->currentEntityName))
	{
		this->bonesByName[this->currentEntityName] = std::map<std::string, SpriterAnimationBone*>();
	}

	return this->bonesByName[this->currentEntityName];
}

const std::map<std::string, SpriterAnimationSprite*>& SpriterAnimationNode::getCurrentSpriteMap()
{
	if (!this->spritesByName.contains(this->currentEntityName))
	{
		this->spritesByName[this->currentEntityName] = std::map<std::string, SpriterAnimationSprite*>();
	}

	return this->spritesByName[this->currentEntityName];
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
				std::hash<std::string> hasher = std::hash<std::string>();
				size_t hash = hasher(objectInfo.name);

				this->bonesByName[entity.name][objectInfo.name] = bone;
				this->bonesByHash[entity.name][int(hash)] = bone;
				
				this->addAnimationPartChild(bone);
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

					if (!folderFileIdMap.contains(folderFileKey) || this->spritesByName[entity.name].contains(timeline.name))
					{
						continue;
					}

					// Creation was deferred until now rather than during the folder/file id map building, since we needed a timeline id
					// As far as I can tell, timeline ids are the same for all references of an object.
					SpriterAnimationSprite* sprite = SpriterAnimationSprite::create(containingFolder + folderFileIdMap[folderFileKey], anchorMap[folderFileKey]);
					
					this->addAnimationPartChild(sprite);

					std::hash<std::string> hasher = std::hash<std::string>();
					size_t hash = hasher(timeline.name);

					this->spritesByName[entity.name][timeline.name] = sprite;
					this->spritesByHash[entity.name][int(hash)] = sprite;

					// Erase the key to ensure we only create the sprite once
					folderFileIdMap.erase(folderFileKey);
				}
			}
		}
	}
}
