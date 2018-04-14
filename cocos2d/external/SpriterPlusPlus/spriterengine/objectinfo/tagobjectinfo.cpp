#include "tagobjectinfo.h"

namespace SpriterEngine
{

	TagObjectInfo::TagObjectInfo()
	{
	}

	void TagObjectInfo::setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setTagList(&tagList);
	}

	void TagObjectInfo::pushBackTag(const std::string * tag)
	{
		tagList.pushBackTag(tag);
	}

}
