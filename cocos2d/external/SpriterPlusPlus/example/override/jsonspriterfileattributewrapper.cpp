#include "jsonspriterfileattributewrapper.h"
#include "jsonspriterfileelementwrapper.h"

namespace SpriterEngine
{
	JSONSpriterFileAttributeWrapper::JSONSpriterFileAttributeWrapper(JSONSpriterFileElementWrapper *parent_object, std::string name, json value):
		m_value(value), m_name(name), m_parent_object(parent_object)
	{

	}

	std::string JSONSpriterFileAttributeWrapper::getName()
	{
		return m_name;
	}

	bool JSONSpriterFileAttributeWrapper::isValid()
	{
		// The default is a null value, if this is set it's invalid
		return !m_value.is_null();
	}

	real JSONSpriterFileAttributeWrapper::getRealValue()
	{
		// implicit convert
		return m_value;
	}

	int JSONSpriterFileAttributeWrapper::getIntValue()
	{
		// Sometimes there are strings like "2" in the scon so try stoi first.
		if(m_value.is_string()) {
			// This will throw std::invalid_argument when not a number.
			std::string str = m_value;
			return std::stoi(str);
		}
		// implicit convert
		return m_value;
	}

	std::string JSONSpriterFileAttributeWrapper::getStringValue()
	{
		// implicit convert
		return m_value;
	}

	void JSONSpriterFileAttributeWrapper::advanceToNextAttribute()
	{
		m_parent_object->advanceToNextAttribute(this);
	}
}
