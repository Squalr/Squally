#include "TinyXmlSpriterFileElementWrapper.h"

NS_CC_BEGIN

	TinyXmlSpriterFileElementWrapper::TinyXmlSpriterFileElementWrapper(tinyxml2::XMLElement *initialElement):
		element(initialElement)
	{
	}

	std::string TinyXmlSpriterFileElementWrapper::getName()
	{
		return element->Value();
	}

	bool TinyXmlSpriterFileElementWrapper::isValid()
	{
		return element;
	}

	void TinyXmlSpriterFileElementWrapper::advanceToNextSiblingElement()
	{
		element = element->NextSiblingElement();
	}

	void TinyXmlSpriterFileElementWrapper::advanceToNextSiblingElementOfSameName()
	{
		element = element->NextSiblingElement(getName().c_str());
	}

	SpriterEngine::SpriterFileAttributeWrapper * TinyXmlSpriterFileElementWrapper::newAttributeWrapperFromFirstAttribute()
	{
		return new TinyXmlSpriterFileAttributeWrapper(element->FirstAttribute());
	}

	SpriterEngine::SpriterFileAttributeWrapper * TinyXmlSpriterFileElementWrapper::newAttributeWrapperFromFirstAttribute(const std::string & attributeName)
	{
		return new TinyXmlSpriterFileAttributeWrapper(findAttributeInElement(attributeName));
	}

	SpriterEngine::SpriterFileElementWrapper * TinyXmlSpriterFileElementWrapper::newElementWrapperFromFirstElement()
	{
		return new TinyXmlSpriterFileElementWrapper(element->FirstChildElement());
	}

	SpriterEngine::SpriterFileElementWrapper * TinyXmlSpriterFileElementWrapper::newElementWrapperFromFirstElement(const std::string & elementName)
	{
		return new TinyXmlSpriterFileElementWrapper(element->FirstChildElement(elementName.c_str()));
	}

	SpriterEngine::SpriterFileElementWrapper * TinyXmlSpriterFileElementWrapper::newElementWrapperFromNextSiblingElement()
	{
		return new TinyXmlSpriterFileElementWrapper(element->NextSiblingElement(getName().c_str()));
	}

	SpriterEngine::SpriterFileElementWrapper * TinyXmlSpriterFileElementWrapper::newElementClone()
	{
		return new TinyXmlSpriterFileElementWrapper(element);
	}

	const tinyxml2::XMLAttribute * TinyXmlSpriterFileElementWrapper::findAttributeInElement(const std::string & name)
	{
		const tinyxml2::XMLAttribute *attribute =  element->FirstAttribute();

		while (attribute)
		{
			if (attribute->Name() == name)
			{
				return attribute;
			}

			attribute = attribute->Next();
		}

		return 0;
	}

NS_CC_END
