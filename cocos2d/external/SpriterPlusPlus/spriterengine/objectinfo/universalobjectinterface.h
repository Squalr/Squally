#ifndef UNIVERSALOBJECTINTERFACE_H
#define UNIVERSALOBJECTINTERFACE_H

#include <string>
#include <vector>

#include "../global/global.h"

namespace SpriterEngine
{
	class UniversalObjectInterface;
	class ImageFile;
	class SoundFile;
	class EntityInstanceData;
	class AnimationInstance;
	class TagList;
	class VariableInstanceNameAndIdMap;
	class TagObjectInfoReference;
	class TimelineKey;
	class ObjectRefInstance;

	typedef std::vector<UniversalObjectInterface*> ObjectInterfaceVector;
	
	class UniversalObjectInterface
	{
	public:
		UniversalObjectInterface();
		virtual ~UniversalObjectInterface() = 0;

		virtual point getPosition();
		virtual real getAngle();
		virtual point getScale();
		virtual point getPivot();
		virtual real getAlpha();

		virtual point getSize();

		virtual ImageFile *getImage();

		virtual EntityInstanceData *getEntity(int entityId);
		virtual real getCurrentTime();
		virtual real getTimeRatio();

		virtual void reprocessCurrentTime();

		virtual ObjectInterfaceVector *getZOrder();

		virtual real getRealValue();
		virtual int getIntValue();
		virtual std::string getStringValue();

		virtual int getTriggerCount();

		virtual real getVolume();
		virtual real getPanning();

		virtual VariableInstanceNameAndIdMap *getVariables();
		virtual UniversalObjectInterface *getTags() const;

		virtual bool tagIsActive(const std::string &tagToCheck) const;

		virtual void setPosition(const point &newPosition);
		virtual void setAngle(real newAngle);
		virtual void setScale(const point &newScale);
		virtual void setPivot(const point &newPivot);
		virtual void setAlpha(real newAlpha);
		virtual void setSpin(int newSpin);

		virtual void setImage(ImageFile *newImageFile);

		virtual void setCurrentEntity(int newEntityIndex);
		virtual void setCurrentEntity(EntityInstanceData *newCurrentEntity);
		virtual void setCurrentAnimation(int newAnimationIndex);
		virtual void setCurrentAnimation(AnimationInstance *newCurrentAnimation);
		virtual void setTimeRatio(real newCurrentTimeRatio);

		virtual void setRealValue(real newValue);
		virtual void setIntValue(int newValue);
		virtual void setStringValue(const std::string &newValue);
		virtual void setStringValue(std::string *newValue);

		virtual void setTriggerCount(int newTriggerCount);

		virtual void setVolume(real newVolume);
		virtual void setPanning(real newPanning);

		virtual void setSound(SoundFile *newSoundFile);

		virtual void setTagList(TagList *newTagList);


		virtual void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject);
		virtual void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0);

		virtual void render();

		virtual void playTrigger();
	};

}

#endif // UNIVERSALOBJECTINTERFACE_H
