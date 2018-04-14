#ifndef SOUNDOBJECTINFO_H
#define SOUNDOBJECTINFO_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{

	class SoundObjectInfo : public UniversalObjectInterface
	{
	public:
		SoundObjectInfo();

		int getTriggerCount() override;

		real getVolume() override;
		real getPanning() override;

		void setTriggerCount(int newTriggerCount) override;

		void setVolume(real newVolume) override;
		void setPanning(real newPanning) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

	private:
		real volume;
		real panning;

		bool trigger;
	};

}

#endif // SOUNDOBJECTINFO_H
