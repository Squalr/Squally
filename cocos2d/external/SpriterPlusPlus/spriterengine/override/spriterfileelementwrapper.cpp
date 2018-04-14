#include "spriterfileelementwrapper.h"

#include "spriterfileattributewrapper.h"

namespace SpriterEngine
{
	SpriterFileElementWrapper::SpriterFileElementWrapper()
	{
	}

	SpriterFileElementWrapper::~SpriterFileElementWrapper()
	{
		for (auto& it : childAttributes)
		{
			delete it;
		}

		for (auto& it : childElements)
		{
			delete it;
		}
	}

	SpriterFileAttributeWrapper * SpriterFileElementWrapper::getFirstAttribute()
	{
		childAttributes.push_back(newAttributeWrapperFromFirstAttribute());
		return childAttributes.back();
	}

	SpriterFileAttributeWrapper * SpriterFileElementWrapper::getFirstAttribute(const std::string & attributeName)
	{
		childAttributes.push_back(newAttributeWrapperFromFirstAttribute(attributeName));
		return childAttributes.back();
	}

	SpriterFileElementWrapper * SpriterFileElementWrapper::getFirstChildElement()
	{
		childElements.push_back(newElementWrapperFromFirstElement());
		return childElements.back();
	}

	SpriterFileElementWrapper * SpriterFileElementWrapper::getFirstChildElement(const std::string & elementName)
	{
		childElements.push_back(newElementWrapperFromFirstElement(elementName));
		return childElements.back();
	}
	SpriterFileElementWrapper * SpriterFileElementWrapper::getNextSiblingElement()
	{
		childElements.push_back(newElementWrapperFromNextSiblingElement());
		return childElements.back();
	}

	SpriterFileElementWrapper * SpriterFileElementWrapper::getCloneElement()
	{
		childElements.push_back(newElementClone());
		return childElements.back();
	}
}