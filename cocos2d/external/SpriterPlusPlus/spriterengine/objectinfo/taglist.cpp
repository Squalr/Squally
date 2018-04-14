#include "taglist.h"

namespace SpriterEngine
{

	TagList::TagList()
	{
	}

	bool TagList::tagIsActive(std::string tag) const
	{
		for (auto& it : tags)
		{
			if (*it == tag)
			{
				return true;
			}
		}
		return false;
	}

	void TagList::pushBackTag(const std::string * tag)
	{
		tags.push_back(tag);
	}

}
