#ifndef TAGOBJECTINFOREFERENCE_H
#define TAGOBJECTINFOREFERENCE_H

#include <string>

#include "universalobjectinterface.h"

namespace SpriterEngine
{

	class TagList;
	class TagObjectInfoReference : public UniversalObjectInterface
	{
	public:
		TagObjectInfoReference();

		bool tagIsActive(const std::string &tagToCheck) const override;

		void setTagList(TagList *newTagList) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

	private:
		const TagList *tagList;
	};

}

#endif // TAGOBJECTINFOREFERENCE_H
