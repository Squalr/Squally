#include "TinyXmlSpriterFileAttributeWrapper.h"

NS_CC_BEGIN

	TinyXmlSpriterFileAttributeWrapper::TinyXmlSpriterFileAttributeWrapper(const tinyxml2::XMLAttribute *initialAttribute):
		attribute(initialAttribute)
	{
	}

	std::string TinyXmlSpriterFileAttributeWrapper::getName()
	{
		return attribute->Name();
	}

	bool TinyXmlSpriterFileAttributeWrapper::isValid()
	{
		return attribute;
	}

	SpriterEngine::real TinyXmlSpriterFileAttributeWrapper::getRealValue()
	{
		return attribute->DoubleValue();
	}

	int TinyXmlSpriterFileAttributeWrapper::getIntValue()
	{
		return attribute->IntValue();
	}

	std::string TinyXmlSpriterFileAttributeWrapper::getStringValue()
	{
		return attribute->Value();
	}

	void TinyXmlSpriterFileAttributeWrapper::advanceToNextAttribute()
	{
		attribute = attribute->Next();
	}

NS_CC_END
