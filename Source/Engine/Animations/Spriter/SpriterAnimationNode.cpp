#include "SpriterAnimationNode.h"

#include <cmath>
#include <limits>

#include "2d/CCSprite.h"
#include "platform/CCFileUtils.h"

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

SpriterAnimationNode* SpriterAnimationNode::create(const std::string& animationResource, const std::string& entityName)
{
	SpriterAnimationNode* instance = new SpriterAnimationNode(animationResource, entityName);

	instance->autorelease();

	return instance;
}

SpriterAnimationNode::SpriterAnimationNode(const std::string& animationResource, const std::string& entityName)
{
	this->timeline = SpriterAnimationTimeline::getInstance(animationResource);
	this->currentAnimation = SpriterAnimationNode::DefaultAnimationName;
	
	const SpriterData& spriterData = SpriterAnimationParser::Parse(animationResource);

	for (const SpriterEntity& entity : spriterData.entities)
	{
		for (const SpriterAnimation& animation : entity.animations)
		{
			this->animationDataByName[entity.name][animation.name] = animation;
		}
	}

	this->timeline->registerAnimationNode(this);

	this->buildBones(spriterData);
	this->buildSprites(spriterData, animationResource);
	this->setCurrentEntity(entityName);
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
	this->animationCompletedThisFrame = false;

	if (this->playbackPaused || timelineMax <= 0.0f)
	{
		return;
	}

	const float nextTime = this->timelineTime + dt;

	if (this->isRepeating)
	{
		if (nextTime >= timelineMax)
		{
			this->animationCompletedThisFrame = true;
		}

		this->timelineTime = MathUtils::wrappingNormalize(nextTime, 0.0f, timelineMax);
		return;
	}

	if (nextTime >= timelineMax)
	{
		this->animationCompletedThisFrame = true;
		this->playbackPaused = true;
		this->timelineTime = std::nextafter(timelineMax, 0.0f);
		return;
	}

	this->timelineTime = nextTime;
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

std::string SpriterAnimationNode::getSpriteResource(int folderId, int fileId) const
{
	uint64_t folderFileKey = uint64_t(folderId) << 32 | uint64_t(fileId);
	const auto resourceIt = this->spriteResourcesByFolderFile.find(folderFileKey);

	return resourceIt == this->spriteResourcesByFolderFile.end() ? "" : resourceIt->second;
}

void SpriterAnimationNode::playAnimation(std::string animation)
{
	this->currentAnimation = animation;

	if (this->animationDataByName.find(this->currentEntityName) != this->animationDataByName.end()
		&& this->animationDataByName[this->currentEntityName].find(animation) != this->animationDataByName[this->currentEntityName].end())
	{
		this->isRepeating = this->animationDataByName[this->currentEntityName][animation].isLooping;
	}

	this->resetAnimation();
}

void SpriterAnimationNode::resetAnimation()
{
	this->previousTimelineTime = 0.0f;
	this->timelineTime = 0.0f;
	this->animationCompletedThisFrame = false;
	this->playbackPaused = false;

	if (this->timeline != nullptr)
	{
		this->timeline->applyCurrentAnimationState(this);
	}
}

void SpriterAnimationNode::setFlippedX(bool isFlippedX)
{
	if (this->flippedX == isFlippedX)
	{
		return;
	}

	this->flippedX = isFlippedX;
	this->refreshCurrentEntityAnimationState();
}

void SpriterAnimationNode::setFlippedY(bool isFlippedY)
{
	if (this->flippedY == isFlippedY)
	{
		return;
	}

	this->flippedY = isFlippedY;
	this->refreshCurrentEntityAnimationState();
}

bool SpriterAnimationNode::getFlippedX() const
{
	return this->flippedX;
}

bool SpriterAnimationNode::getFlippedY() const
{
	return this->flippedY;
}

void SpriterAnimationNode::setRepeating(bool isRepeating)
{
	this->isRepeating = isRepeating;
	this->playbackPaused = false;
}

bool SpriterAnimationNode::getRepeating() const
{
	return this->isRepeating;
}

void SpriterAnimationNode::setPlaybackPaused(bool isPlaybackPaused)
{
	this->playbackPaused = isPlaybackPaused;
}

bool SpriterAnimationNode::getPlaybackPaused() const
{
	return this->playbackPaused;
}

void SpriterAnimationNode::setAnimationCompleteCallback(const std::function<void()>& callback)
{
	this->animationCompleteCallback = callback;
}

void SpriterAnimationNode::dispatchAnimationComplete()
{
	if (!this->animationCompletedThisFrame)
	{
		return;
	}

	this->animationCompletedThisFrame = false;

	if (this->animationCompleteCallback != nullptr)
	{
		this->animationCompleteCallback();
	}
}

void SpriterAnimationNode::seekAnimationTimeRatio(float timeRatio)
{
	if (this->animationDataByName.find(this->currentEntityName) == this->animationDataByName.end()
		|| this->animationDataByName[this->currentEntityName].find(this->currentAnimation) == this->animationDataByName[this->currentEntityName].end())
	{
		return;
	}

	const float animationLength = this->animationDataByName[this->currentEntityName][this->currentAnimation].length / 1000.0f;

	if (animationLength <= 0.0f)
	{
		return;
	}

	this->previousTimelineTime = this->timelineTime;
	this->animationCompletedThisFrame = false;
	this->timelineTime = timeRatio >= 1.0f
		? std::nextafter(animationLength, 0.0f)
		: animationLength * MathUtils::clamp(timeRatio, 0.0f, 1.0f);

	if (this->timeline != nullptr)
	{
		this->timeline->applyCurrentAnimationState(this);
	}
}

void SpriterAnimationNode::setCurrentEntity(const std::string& currentEntityName)
{
	this->currentEntityName = currentEntityName;
	this->entityBonesByName = nullptr;
	this->entityBonesByHash = nullptr;
	this->entitySpritesByName = nullptr;
	this->entitySpritesByHash = nullptr;

	for (const auto& entityBones : this->bonesByName)
	{
		if (entityBones.first == this->currentEntityName)
		{
			continue;
		}

		for (const auto& boneEntry : entityBones.second)
		{
			if (boneEntry.second != nullptr)
			{
				boneEntry.second->setVisible(false);
			}
		}
	}

	for (const auto& entitySprites : this->spritesByName)
	{
		if (entitySprites.first == this->currentEntityName)
		{
			continue;
		}

		for (const auto& spriteEntry : entitySprites.second)
		{
			if (spriteEntry.second != nullptr)
			{
				spriteEntry.second->setVisible(false);
			}
		}
	}
	
	if (this->bonesByName.find(this->currentEntityName) != this->bonesByName.end())
	{
		this->entityBonesByName = &this->bonesByName[this->currentEntityName];
	}
	
	if (this->bonesByHash.find(this->currentEntityName) != this->bonesByHash.end())
	{
		this->entityBonesByHash = &this->bonesByHash[this->currentEntityName];
	}
	
	if (this->spritesByName.find(this->currentEntityName) != this->spritesByName.end())
	{
		this->entitySpritesByName = &this->spritesByName[this->currentEntityName];
	}
	
	if (this->spritesByHash.find(this->currentEntityName) != this->spritesByHash.end())
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

Vec2 SpriterAnimationNode::getCascadePosition() const
{
	return Vec2::ZERO;
}

Vec2 SpriterAnimationNode::getCascadeScale() const
{
	return Vec2(this->flippedX ? -1.0f : 1.0f, this->flippedY ? -1.0f : 1.0f);
}

float SpriterAnimationNode::getCascadeRotation() const
{
	return 0.0f;
}

float SpriterAnimationNode::getCascadeOpacityMultiplier() const
{
	return 1.0f;
}

const std::map<std::string, SpriterAnimationBone*>& SpriterAnimationNode::getCurrentBoneMap()
{
	if (this->bonesByName.find(this->currentEntityName) == this->bonesByName.end())
	{
		this->bonesByName[this->currentEntityName] = std::map<std::string, SpriterAnimationBone*>();
	}

	return this->bonesByName[this->currentEntityName];
}

const std::map<std::string, SpriterAnimationSprite*>& SpriterAnimationNode::getCurrentSpriteMap()
{
	if (this->spritesByName.find(this->currentEntityName) == this->spritesByName.end())
	{
		this->spritesByName[this->currentEntityName] = std::map<std::string, SpriterAnimationSprite*>();
	}

	return this->spritesByName[this->currentEntityName];
}

void SpriterAnimationNode::refreshCurrentEntityAnimationState()
{
	for (const auto& next : this->getCurrentBoneMap())
	{
		if (next.second != nullptr && next.second->canTimelineUpdate())
		{
			next.second->refreshAnimationState();
		}
	}

	for (const auto& next : this->getCurrentSpriteMap())
	{
		if (next.second != nullptr && next.second->canTimelineUpdate())
		{
			next.second->refreshAnimationState();
		}
	}
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
				bone->setVisible(false);
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
			this->spriteResourcesByFolderFile[folderFileKey] = containingFolder + file.name;
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

					if (folderFileIdMap.find(folderFileKey) == folderFileIdMap.end() || this->spritesByName[entity.name].find(timeline.name) != this->spritesByName[entity.name].end())
					{
						continue;
					}

					// Creation was deferred until now rather than during the folder/file id map building, since we needed a timeline id
					// As far as I can tell, timeline ids are the same for all references of an object.
					SpriterAnimationSprite* sprite = SpriterAnimationSprite::create(containingFolder + folderFileIdMap[folderFileKey], anchorMap[folderFileKey]);
					
					this->addAnimationPartChild(sprite);
					sprite->setVisible(false);

					std::hash<std::string> hasher = std::hash<std::string>();
					size_t hash = hasher(timeline.name);

					this->spritesByName[entity.name][timeline.name] = sprite;
					this->spritesByHash[entity.name][int(hash)] = sprite;
				}
			}
		}
	}
}
