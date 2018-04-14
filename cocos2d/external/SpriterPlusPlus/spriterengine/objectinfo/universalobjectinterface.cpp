#include "universalobjectinterface.h"

#include "../global/settings.h"

namespace SpriterEngine
{

	UniversalObjectInterface::UniversalObjectInterface()
	{
	}

	UniversalObjectInterface::~UniversalObjectInterface()
	{
	}

	point UniversalObjectInterface::getPosition()
	{
		Settings::error("UniversalObjectInterface::getPosition - object does not contain this component - falling back on default value");
		return point();
	}

	real UniversalObjectInterface::getAngle()
	{
		Settings::error("UniversalObjectInterface::getAngle - object does not contain this component - falling back on default value");
		return 0;
	}

	point UniversalObjectInterface::getScale()
	{
		Settings::error("UniversalObjectInterface::getScale - object does not contain this component - falling back on default value");
		return point(1, 1);
	}

	point UniversalObjectInterface::getPivot()
	{
		Settings::error("UniversalObjectInterface::getPivot - object does not contain this component - falling back on default value");
		return point();
	}

	real UniversalObjectInterface::getAlpha()
	{
		Settings::error("UniversalObjectInterface::getAlpha - object does not contain this component - falling back on default value");
		return 1;
	}

	point UniversalObjectInterface::getSize()
	{
		Settings::error("UniversalObjectInterface::getSize - object does not contain this component - falling back on default value");
		return point();
	}


	ImageFile *UniversalObjectInterface::getImage()
	{
		Settings::error("UniversalObjectInterface::getImage - object does not contain this component - returning null pointer");
		return 0;
	}

	EntityInstanceData * UniversalObjectInterface::getEntity(int entityId)
	{
		Settings::error("UniversalObjectInterface::getEntity - object does not contain this component - returning null pointer");
		return 0;
	}

	real UniversalObjectInterface::getCurrentTime()
	{
		Settings::error("UniversalObjectInterface::getCurrentTime - object does not contain this component - falling back on default value");
		return 0;
	}

	real UniversalObjectInterface::getTimeRatio()
	{
		Settings::error("UniversalObjectInterface::getTimeRatio - object does not contain this component - falling back on default value");
		return 0;
	}

	void UniversalObjectInterface::reprocessCurrentTime()
	{
		Settings::error("UniversalObjectInterface::reprocessCurrentTime - object does not contain this component - no action taken");
	}

	ObjectInterfaceVector * UniversalObjectInterface::getZOrder()
	{
		Settings::error("UniversalObjectInterface::getZOrder - object does not contain this component - returning null pointer");
		return 0;
	}

	real UniversalObjectInterface::getRealValue()
	{
		Settings::error("UniversalObjectInterface::getRealValue - object does not contain this component - returning 0");
		return 0;
	}

	int UniversalObjectInterface::getIntValue()
	{
		Settings::error("UniversalObjectInterface::getIntValue - object does not contain this component - returning 0");
		return 0;
	}

	std::string UniversalObjectInterface::getStringValue()
	{
		Settings::error("UniversalObjectInterface::getStringValue - object does not contain this component - return empty string");
		return "";
	}

	int UniversalObjectInterface::getTriggerCount()
	{
		Settings::error("UniversalObjectInterface::getTriggerCount - object does not contain this component - falling back on default value");
		return 0;
	}

	real UniversalObjectInterface::getVolume()
	{
		Settings::error("UniversalObjectInterface::getVolume - object does not contain this component - falling back on default value");
		return 1;
	}

	real UniversalObjectInterface::getPanning()
	{
		Settings::error("UniversalObjectInterface::getPanning - object does not contain this component - falling back on default value");
		return 0;
	}

	VariableInstanceNameAndIdMap *UniversalObjectInterface::getVariables()
	{
		Settings::error("UniversalObjectInterface::getVariables - object does not contain this component - returning null pointer");
		return 0;
	}

	UniversalObjectInterface *UniversalObjectInterface::getTags() const
	{
		Settings::error("UniversalObjectInterface::getTags - object does not contain this component - returning null pointer");
		return 0;
	}

	bool UniversalObjectInterface::tagIsActive(const std::string &tagToCheck) const
	{
		Settings::error("UniversalObjectInterface::tagIsActive - object does not contain this component - falling back on default value");
		return false;
	}


	void UniversalObjectInterface::setPosition(const point &newPosition)
	{
		Settings::error("UniversalObjectInterface::setPosition - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setAngle(real newAngle)
	{
		Settings::error("UniversalObjectInterface::setAngle - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setScale(const point &newScale)
	{
		Settings::error("UniversalObjectInterface::setScale - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setPivot(const point &newPivot)
	{
		Settings::error("UniversalObjectInterface::setPivot - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setAlpha(real newAlpha)
	{
		Settings::error("UniversalObjectInterface::setAlpha - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setSpin(int newSpin)
	{
		Settings::error("UniversalObjectInterface::setSpin - object does not contain this component - no action taken");
	}


	void UniversalObjectInterface::setImage(ImageFile *newImageFile)
	{
		Settings::error("UniversalObjectInterface::setImage - object does not contain this component - no action taken");
	}


	void UniversalObjectInterface::setCurrentEntity(int newEntityId)
	{
		Settings::error("UniversalObjectInterface::setCurrentEntity - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setCurrentEntity(EntityInstanceData * newCurrentEntity)
	{
		Settings::error("UniversalObjectInterface::setCurrentEntity - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setCurrentAnimation(int newAnimationIndex)
	{
		Settings::error("UniversalObjectInterface::setCurrentAnimation - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setCurrentAnimation(AnimationInstance * newCurrentAnimation)
	{
		Settings::error("UniversalObjectInterface::setCurrentAnimation - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setTimeRatio(real newCurrentTimeRatio)
	{
		Settings::error("UniversalObjectInterface::setTimeRatio - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setRealValue(real newValue)
	{
		Settings::error("UniversalObjectInterface::setRealValue - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setIntValue(int newValue)
	{
		Settings::error("UniversalObjectInterface::setIntValue - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setStringValue(const std::string &newValue)
	{
		Settings::error("UniversalObjectInterface::setStringValue - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setStringValue(std::string *newValue)
	{
		Settings::error("UniversalObjectInterface::setStringValue - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setTriggerCount(int newTriggerCount)
	{
		Settings::error("UniversalObjectInterface::setTriggerCount - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setVolume(real newVolume)
	{
		Settings::error("UniversalObjectInterface::setVolume - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setPanning(real newPanning)
	{
		Settings::error("UniversalObjectInterface::setPanning - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setSound(SoundFile *newSoundFile)
	{
		Settings::error("UniversalObjectInterface::setSound - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setTagList(TagList *newTagList)
	{
		Settings::error("UniversalObjectInterface::setTagList - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		Settings::error("UniversalObjectInterface::setObjectToLinear - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance)
	{
		Settings::error("UniversalObjectInterface::setObjectToBlendedLinear - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::render()
	{
		Settings::error("UniversalObjectInterface::render - object does not contain this component - no action taken");
	}

	void UniversalObjectInterface::playTrigger()
	{
		Settings::error("UniversalObjectInterface::playTrigger - object does not contain this component - no action taken");
	}

}
