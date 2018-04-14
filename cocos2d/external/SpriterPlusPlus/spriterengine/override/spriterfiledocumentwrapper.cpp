#include "spriterfiledocumentwrapper.h"

#include "spriterfileelementwrapper.h"

namespace SpriterEngine
{
	SpriterFileDocumentWrapper::SpriterFileDocumentWrapper()
	{
	}

	SpriterFileDocumentWrapper::~SpriterFileDocumentWrapper()
	{
		for (auto& it : childElements)
		{
			delete it;
		}
	}

	SpriterFileElementWrapper * SpriterFileDocumentWrapper::getFirstChildElement()
	{
		childElements.push_back(newElementWrapperFromFirstElement());
		return childElements.back();
	}

	SpriterFileElementWrapper * SpriterFileDocumentWrapper::getFirstChildElement(std::string elementName)
	{
		childElements.push_back(newElementWrapperFromFirstElement(elementName));
		return childElements.back();
	}
}