#include "entityinstance.h"

#include "../global/settings.h"

#include "../objectref/objectrefinstance.h"
#include "../charactermap/charactermapinterface.h"
#include "../objectinfo/tagobjectinforeference.h"
#include "../objectinfo/triggerobjectinfo.h"

#include "../override/soundobjectinforeference.h"

#include "../model/spritermodel.h"

#include "entity.h"
#include "entityinstancedata.h"

namespace SpriterEngine
{
	EntityInstance::EntityInstance() :
		zOrder(0),
		position(0, 0),
		scale(1, 1),
		alpha(1),
		currentEntity(0),
		currentAnimation(0),
		characterMapInterface(0),
		playbackSpeedRatio(1),
		blendCurrentTime(0),
		blendTotalTime(0),
		blendedAnimation(0),
		isPlaying(true),
		justFinished(false)
	{
	}
	EntityInstance::EntityInstance(SpriterModel *model, Entity *entity, CharacterMapInterface *initialCharacterMapInterface, ObjectFactory *objectFactory) :
		zOrder(0),
		position(0, 0),
		scale(1, 1),
		alpha(1),
		currentEntity(0),
		currentAnimation(0),
		characterMapInterface(initialCharacterMapInterface),
		playbackSpeedRatio(1),
		blendCurrentTime(0),
		blendTotalTime(0),
		blendedAnimation(0),
		isPlaying(true),
		justFinished(false)
	{
		model->setupFileReferences(&files);
		currentEntity = (*entities.insert(std::make_pair(entity->getId(), new EntityInstanceData(model, this, entity, objectFactory))).first).second;
		setCurrentAnimation(0);
	}

	EntityInstance::~EntityInstance()
	{
		for (auto& it : files)
		{
			delete it;
		}

		for (auto& it : entities)
		{
			delete it.second;
		}
	}

	void EntityInstance::setTimeElapsed(real timeElapsed)
	{
		justFinished = false;
		if (currentAnimation)
		{
			if (isPlaying)
			{
				timeElapsed *= playbackSpeedRatio;
				real newTime = getCurrentTime() + timeElapsed;
				
				if (newTime >= currentAnimation->length())
				{
					justFinished = true;
					if (!currentAnimation->looping())
					{
						isPlaying = false;
						newTime = currentAnimation->length();
					}
				}

				if (blendedAnimation)
				{
					blendCurrentTime += timeElapsed;

					if (blendCurrentTime >= blendTotalTime)
					{
						blendCurrentTime = 0;
						blendTotalTime = 0;

						real currentT = getCurrentTime() / currentAnimation->length();
						newTime = (currentT * blendedAnimation->length()) + timeElapsed;

						currentAnimation = blendedAnimation;
						blendedAnimation = 0;

						currentAnimation->findAndProcessKeys(newTime, timeElapsed >= 0, &zOrder);
					}
					else
					{
						real blendRatio = blendCurrentTime / blendTotalTime;

						real currentT = getCurrentTime() / currentAnimation->length();

						real currentAnimationT = newTime / currentAnimation->length();
						real blendedAnimationT = ((currentT * blendedAnimation->length()) + timeElapsed) / blendedAnimation->length();

						currentT = linear(currentAnimationT, blendedAnimationT, blendRatio);

						blend(blendRatio, currentT);
					}
				}
				else
				{
					currentAnimation->findAndProcessKeys(newTime, timeElapsed >= 0, &zOrder);
				}
			}
			else
			{
				reprocessCurrentTime();
			}
		}
		else
		{
			Settings::error("EntityInstance::setTimeElapsed - current animation not set");
		}
	}

	void EntityInstance::startResumePlayback()
	{
		isPlaying = true;
		if (getCurrentTime() >= currentAnimation->length())
		{
			setCurrentTime(0);
		}
	}

	void EntityInstance::pausePlayback()
	{
		isPlaying = false;
	}

	void EntityInstance::blend(real blendRatio, real timeRatio)
	{
		real newCurrentAnimationTime = timeRatio * currentAnimation->length();
		currentAnimation->findCurrentKeys(newCurrentAnimationTime, newCurrentAnimationTime > currentAnimation->currentTime());
		currentAnimation->processRefKeys(currentAnimation->currentTime());
		currentAnimation->processCurrentTimelineKeys(currentAnimation->currentTime());

		real newBlendedAnimationTime = timeRatio * blendedAnimation->length();
		blendedAnimation->findCurrentKeys(newBlendedAnimationTime, newBlendedAnimationTime > blendedAnimation->currentTime());
		blendedAnimation->blendRefKeys(blendedAnimation->currentTime(), blendRatio);
		blendedAnimation->blendCurrentTimelineKeys(blendedAnimation->currentTime(), blendRatio);

		if (blendRatio < 0.5)
		{
			currentAnimation->setZOrder(&zOrder);
			currentAnimation->processRefTransforms();
		}
		else
		{
			blendedAnimation->setZOrder(&zOrder);
			blendedAnimation->processRefTransforms();
		}
	}

	void EntityInstance::reprocessCurrentTime()
	{
		currentAnimation->processCurrentKeys(currentAnimation->currentTime(), &zOrder);
	}

	UniversalObjectInterface *EntityInstance::getObjectInstance(int objectId)
	{
		return currentEntity->getObjectInstance(objectId);
	}

	UniversalObjectInterface *EntityInstance::getObjectInstance(const std::string &objectName)
	{
		return currentEntity->getObjectInstance(objectName);
	}



	FileReference *EntityInstance::getFile(int fileId)
	{
		if (fileId < files.size())
		{
			return files.at(fileId);
		}
		else
		{
			Settings::error("EntityInstance::getFile - file id " + std::to_string(fileId) + " out of range");
			return 0;
		}
	}

	point EntityInstance::getPosition()
	{
		return position;
	}

	real EntityInstance::getAngle()
	{
		return angle.angle;
	}

	point EntityInstance::getScale()
	{
		return scale;
	}

	real EntityInstance::getAlpha()
	{
		return alpha;
	}

	real EntityInstance::getCurrentTime()
	{
		return currentAnimation->currentTime();
	}

	real EntityInstance::getTimeRatio()
	{
		return getCurrentTime() / currentAnimation->length();
	}

	std::string EntityInstance::currentEntityName()
	{
		if (currentEntity)
		{
			return currentEntity->getName();
		}
		return "";
	}

	std::string EntityInstance::currentAnimationName()
	{
		if (currentAnimation)
		{
			return currentAnimation->getName();
		}
		return "";
	}

	int EntityInstance::animationCount()
	{
		if (currentEntity)
		{
			return currentEntity->animationCount();
		}
		else
		{
			Settings::error("EntityInstance::animationCount() - no current entity");
			return 0;
		}
	}

	VariableInstanceNameAndIdMap *EntityInstance::getVariables()
	{
		return getVariables(THIS_ENTITY);
	}

	UniversalObjectInterface *EntityInstance::getVariable(int variableId)
	{
		return getVariable(THIS_ENTITY, variableId);
	}

	VariableInstanceNameAndIdMap *EntityInstance::getVariables(int objectId)
	{
		return currentEntity->getVariables(objectId);
	}

	UniversalObjectInterface *EntityInstance::getVariable(int objectId, int variableId)
	{
		return currentEntity->getVariable(objectId, variableId);
	}

	UniversalObjectInterface *EntityInstance::getVariable(const std::string &variableName)
	{
		return currentEntity->getVariable(variableName);
	}

	VariableInstanceNameAndIdMap *EntityInstance::getVariables(const std::string &objectName)
	{
		return currentEntity->getVariables(objectName);
	}

	UniversalObjectInterface *EntityInstance::getVariable(const std::string &objectName, const std::string &variableName)
	{
		return currentEntity->getVariable(objectName, variableName);
	}

	real EntityInstance::getRealValue(const std::string &variableName)
	{
		UniversalObjectInterface *variable = getVariable(variableName);
		if (variable)
		{
			return variable->getRealValue();
		}
		else
		{
			Settings::error("EntityInstance::getRealValue - variable instance with name " + variableName + " not found");
			return 0;
		}
	}

	int EntityInstance::getIntValue(const std::string &variableName)
	{
		UniversalObjectInterface *variable = getVariable(variableName);
		if (variable)
		{
			return variable->getIntValue();
		}
		else
		{
			Settings::error("EntityInstance::getIntValue - variable instance with name " + variableName + " not found");
			return 0;
		}
	}

	std::string EntityInstance::getStringValue(const std::string &variableName)
	{
		UniversalObjectInterface *variable = getVariable(variableName);
		if (variable)
		{
			return variable->getStringValue();
		}
		else
		{
			Settings::error("EntityInstance::getStringValue - variable instance with name " + variableName + " not found");
			return 0;
		}
	}

	real EntityInstance::getRealValue(const std::string &objectName, const std::string &variableName)
	{
		UniversalObjectInterface *variable = getVariable(objectName, variableName);
		if (variable)
		{
			return variable->getRealValue();
		}
		else
		{
			Settings::error("EntityInstance::getRealValue - object instance with name " + objectName + " or variable instance with name " + variableName + " not found");
			return 0;
		}
	}

	int EntityInstance::getIntValue(const std::string &objectName, const std::string &variableName)
	{
		UniversalObjectInterface *variable = getVariable(objectName, variableName);
		if (variable)
		{
			return variable->getIntValue();
		}
		else
		{
			Settings::error("EntityInstance::getIntValue - object instance with name " + objectName + " or variable instance with name " + variableName + " not found");
			return 0;
		}
	}

	std::string EntityInstance::getStringValue(const std::string &objectName, const std::string &variableName)
	{
		UniversalObjectInterface *variable = getVariable(objectName, variableName);
		if (variable)
		{
			return variable->getStringValue();
		}
		else
		{
			Settings::error("EntityInstance::getStringValue - object instance with name " + objectName + " or variable instance with name " + variableName + " not found");
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstance::getTags() const
	{
		return currentEntity->getTags();
	}

	UniversalObjectInterface *EntityInstance::getTags(int objectId) const
	{
		return currentEntity->getTags(objectId);
	}

	bool EntityInstance::tagIsActive(int objectId, const std::string &tagToCheck) const
	{
		return currentEntity->tagIsActive(objectId, tagToCheck);
	}

	bool EntityInstance::tagIsActive(const std::string &tagToCheck) const
	{
		return currentEntity->tagIsActive("", tagToCheck);
	}

	UniversalObjectInterface *EntityInstance::getTags(const std::string &objectName) const
	{
		return currentEntity->getTags(objectName);
	}

	bool EntityInstance::tagIsActive(const std::string &objectName, const std::string &tagToCheck) const
	{
		return currentEntity->tagIsActive(objectName, tagToCheck);
	}

	UniversalObjectInterface *EntityInstance::getTriggerObject(int triggerId)
	{
		return currentEntity->getTriggerObject(triggerId);
	}

	UniversalObjectInterface *EntityInstance::getTriggerObject(const std::string &triggerName)
	{
		return currentEntity->getTriggerObject(triggerName);
	}

	UniversalObjectInterface *EntityInstance::getSoundObject(int soundId)
	{
		return currentEntity->getSoundObject(soundId);
	}

	UniversalObjectInterface *EntityInstance::getSoundObject(const std::string &soundName)
	{
		return currentEntity->getSoundObject(soundName);
	}

	void EntityInstance::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void EntityInstance::setAngle(real newAngle)
	{
		angle.angle = newAngle;
		if (currentEntity)
		{
			currentEntity->updateTransformProcessor();
		}
	}

	void EntityInstance::setScale(const point &newScale)
	{
		scale = newScale;
	}

	void EntityInstance::setAlpha(real newAlpha)
	{
		alpha = newAlpha;
	}

	void EntityInstance::setSpin(int newSpin)
	{
		angle.spinDirection = newSpin;
	}


	void EntityInstance::setCurrentEntity(int newEntityId)
	{
		auto it = entities.find(newEntityId);
		if (it != entities.end())
		{
			currentEntity = (*it).second;
			currentEntity->updateTransformProcessor();
		}
		else
		{
			Settings::error("EntityInstance::setCurrentEntity - entity with id " + std::to_string(newEntityId) + " not found");
		}
	}

	void EntityInstance::setCurrentEntity(EntityInstanceData * newCurrentEntity)
	{
		currentEntity = newCurrentEntity;
		if (currentEntity)
		{
			currentEntity->updateTransformProcessor();
		}
	}

	void EntityInstance::setCurrentEntity(const std::string & newEntityName, const std::string & newAnimationName, SpriterModel * modelForAutoAppend)
	{
		for (auto& it : entities)
		{
			if (it.second->getName() == newEntityName)
			{
				setCurrentEntity(it.second);
				if (!newAnimationName.empty())
				{
					setCurrentAnimation(newAnimationName);
				}
				else
				{
					setCurrentAnimation(0);
				}
				return;
			}
		}
		if (modelForAutoAppend)
		{
			appendEntity(modelForAutoAppend, newEntityName);
			setCurrentEntity(newEntityName, newAnimationName);
		}
	}

	void EntityInstance::setCurrentAnimation(int newAnimationIndex)
	{
		currentEntity->setCurrentAnimation(newAnimationIndex, &currentAnimation);
		isPlaying = true;
	}

	void EntityInstance::setCurrentAnimation(const std::string & animationName)
	{
		currentEntity->setCurrentAnimation(animationName, &currentAnimation);
		blendedAnimation = 0;
		blendCurrentTime = 0;
		blendTotalTime = 0;
		isPlaying = true;
	}

	void EntityInstance::setCurrentAnimation(const std::string & animationName, real blendTime)
	{
		blendedAnimation = currentEntity->getAnimation(animationName);
		blendCurrentTime = 0;
		blendTotalTime = blendTime;
		isPlaying = true;
	}

	void EntityInstance::setCurrentAnimation(AnimationInstance * newCurrentAnimation)
	{
		currentAnimation = newCurrentAnimation;
		isPlaying = true;
	}

	void EntityInstance::setCurrentTime(real newCurrentTime)
	{
		justFinished = false;
		if (currentAnimation)
		{
			currentAnimation->findAndProcessKeys(newCurrentTime, newCurrentTime > getCurrentTime(), &zOrder);
		}
		else
		{
			Settings::error("EntityInstance::setCurrentTime - current animation not set");
		}
	}

	void EntityInstance::setTimeRatio(real newCurrentTimeRatio)
	{
		justFinished = false;
		currentAnimation->findCurrentKeys(newCurrentTimeRatio * currentAnimation->length(), newCurrentTimeRatio >= inverseLinear(0, currentAnimation->length(), getCurrentTime()));
	}

	void EntityInstance::setPlaybackSpeedRatio(real newPlaybackSpeedRatio)
	{
		playbackSpeedRatio = newPlaybackSpeedRatio;
	}

	int EntityInstance::currentMainlineKeyIndex()
	{
		if (currentAnimation)
		{
			return currentAnimation->currentMainlineKeyIndex();
		}
		else
		{
			Settings::error("EntityInstance::currentMainlineKeyIndex - current animation not set");
			return 0;
		}
	}

	bool EntityInstance::animationJustFinished(bool orLooped)
	{
		if(currentAnimation)
		{
			if (orLooped || !currentAnimation->looping())
			{
				return justFinished;
			}
		}
		else
		{
			Settings::error("EntityInstance::animationJustFinished - current animation not set");
		}
		return false;
	}

	bool EntityInstance::animationJustLooped()
	{
		if (currentAnimation)
		{
			if (currentAnimation->looping())
			{
				return justFinished;
			}
		}
		else
		{
			Settings::error("EntityInstance::animationJustFinished - current animation not set");
		}
		return false;
	}

	void EntityInstance::setCurrentTimeToNextKeyFrame()
	{
		justFinished = false;
		if (currentAnimation)
		{
			currentAnimation->setCurrentTimeToNextKeyFrame(&zOrder);
		}
		else
		{
			Settings::error("EntityInstance::setCurrentTimeToNextKeyFrame - current animation not set");
		}
	}

	void EntityInstance::setCurrentTimeToPreviousKeyFrame()
	{
		justFinished = false;
		if (currentAnimation)
		{
			currentAnimation->setCurrentTimeToPreviousKeyFrame(&zOrder);
		}
		else
		{
			Settings::error("EntityInstance::setCurrentTimeToPreviousKeyFrame - current animation not set");
		}
	}

	void EntityInstance::setCurrentTimeToKeyAtIndex(int newKeyIndex)
	{
		justFinished = false;
		if (currentAnimation)
		{
			currentAnimation->setCurrentTimeToKeyAtIndex(newKeyIndex, &zOrder);
		}
		else
		{
			Settings::error("EntityInstance::setCurrentTimeToKeyAtIndex - current animation not set");
		}
	}

	UniversalObjectInterface *EntityInstance::objectIfExistsOnCurrentFrame(const std::string & objectName)
	{
		if (zOrder)
		{
			UniversalObjectInterface *object = getObjectInstance(objectName);
			if (object)
			{
				for (auto& it : *zOrder)
				{
					if (it == object)
					{
						return object;
					}
				}
			}
		}
		return 0;
	}

	void EntityInstance::applyCharacterMap(const std::string &mapName)
	{
		characterMapInterface->applyCharacterMap(mapName, &files);
		appliedCharacterMaps.push_back(mapName);
	}

	void EntityInstance::removeCharacterMap(const std::string &mapName)
	{
		characterMapInterface->removeAllCharacterMaps(&files);
		appliedCharacterMaps.remove(mapName);
		for (auto& it : appliedCharacterMaps)
		{
			characterMapInterface->applyCharacterMap(it, &files);
		}
	}

	void EntityInstance::removeAllCharacterMaps()
	{
		characterMapInterface->removeAllCharacterMaps(&files);
		appliedCharacterMaps.clear();
	}

	void EntityInstance::render()
	{
		if (zOrder)
		{
			for (auto& it : *zOrder)
			{
				it->render();
			}
		}
	}

	void EntityInstance::playAllTriggers()
	{
		playSoundTriggers();
		playEventTriggers();
	}

	void EntityInstance::playSoundTriggers()
	{
		currentEntity->playSoundTriggers();
	}

	void EntityInstance::playEventTriggers()
	{
		currentEntity->playEventTriggers();
	}

	ObjectInterfaceVector * EntityInstance::getZOrder()
	{
		return zOrder;
	}

	void EntityInstance::appendEntity(SpriterModel * model, Entity * entity, ObjectFactory * objectFactory)
	{
		model->setupFileReferences(&files);
		EntityInstanceData *newEntityData = (*entities.insert(std::make_pair(entity->getId(), new EntityInstanceData(model, this, entity, objectFactory))).first).second;
	}

	void EntityInstance::appendEntity(SpriterModel * model, std::string entityName)
	{
		model->appendEntityToInstanceByName(this, entityName);
	}

	EntityInstanceData * EntityInstance::getEntity(int entityId)
	{
		auto it = entities.find(entityId);
		if (it != entities.end())
		{
			return (*it).second;
		}
		else
		{
			Settings::error("EntityInstance::getEntity - entity instance data with id " + std::to_string(entityId) + " not found");
			return 0;
		}
	}

	void EntityInstance::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance)
	{
		real tempAngle = angle.angle;
		point tempPosition = position;
		point tempScale = scale;
		real tempAlpha = alpha;
		real tempTimeRatio = getCurrentTime() / currentAnimation->length();
		EntityInstanceData *tempCurrentEntity = currentEntity;
		AnimationInstance *tempCurrentAnimation = currentAnimation;

		blendedRefInstance->preProcess();

		aObject->setObjectToLinear(bObject, t, this);

		setAngle(shortestAngleLinear(tempAngle, angle.angle, blendRatio));
		setPosition(linear(tempPosition, position, blendRatio));
		setScale(linear(tempScale, scale, blendRatio));
		setAlpha(linear(tempAlpha, alpha, blendRatio));

		blendedRefInstance->processTransform();

		real timeRatio = linear(tempTimeRatio, getCurrentTime() / currentAnimation->length(), blendRatio);

		if (currentEntity == tempCurrentEntity)
		{
			blendedAnimation = currentAnimation;
			currentAnimation = tempCurrentAnimation;

			blend(blendRatio, timeRatio);;
		}

		blendedAnimation = 0;
	}
}
