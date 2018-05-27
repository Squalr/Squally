#include "jsonspriterfileelementwrapper.h"

#include "jsonspriterfileattributewrapper.h"

namespace SpriterEngine
{
	JSONSpriterFileElementWrapper::JSONSpriterFileElementWrapper(JSONSpriterFileElementWrapper *parent,
																 std::string name, json array, int index) :
	m_array(array), m_index(index), m_name(name), m_parent(parent)
	{
	}

	std::string JSONSpriterFileElementWrapper::getName()
	{
		return m_name;
	}

	bool JSONSpriterFileElementWrapper::isValid()
	{
		// Check if the index is valid
		if(m_index >= m_array.size())
			return false;
		// Is the current object in the array an object?
		json object_value = m_array.at(m_index);
		if(! object_value.is_object()) {
			return false;
		}
		// Everything ok.
		return true;
;
	}

	void JSONSpriterFileElementWrapper::advanceToNextSiblingElement()
	{
		// First try in the array with the same name.
		m_index++;
		if(isValid()) {
			// Still valid so ok
			return;
		}

		// Then see for the next key of different name in the parent
		if(!m_parent) {
			return;
		}

		if(!m_parent->isValid())  {
			return;
		}

		// parent object
		json object = m_parent->m_array.at(m_parent->m_index);

		// search for the current object in the parent.
		json::iterator it;
		for (it = object.begin(); it != object.end(); ++it) {
			if(it.key() == m_name) {
				break;
			}
		}
		if(it == object.end()) {
			// Should not happen
			return;
		}
		// Advence to next element
		++it;
		if(it == object.end()) {
			// There is no next object
			return;
		}
		for (; it != object.end(); ++it) {
			if(!(it.value().is_object() || it.value().is_array())) {
				// It is a property (so no object or array)
				// Try next
				continue;
			}
			if(it.value().is_object()) {
				// It's an object so we mimic an array of objects with the same name
				json arr;
				arr.push_back(it.value());
				m_array = arr;
				m_index = 0;
				m_name = it.key();
			}
			else if(it.value().is_array()) {
				m_array = it.value();
				m_index = 0;
				m_name = it.key();
			}
			// Should not happen
			return;
		}
	}

	void JSONSpriterFileElementWrapper::advanceToNextSiblingElementOfSameName()
	{
		// The array has all elements with the same name so just advence the index.
		// Afterwards you can check ::isValid() to see if the next exists.
		++m_index;
	}

	// Is called from the attribute to set it to the next one found in this element.
	void JSONSpriterFileElementWrapper::advanceToNextAttribute(JSONSpriterFileAttributeWrapper *from_attribute)
	{
		// Checks
		if(!isValid()) {
			from_attribute->m_value = nullptr; // nullptr represends json null value
			from_attribute->m_name = "";
			return;
		}
		if(!from_attribute->isValid()) {
			from_attribute->m_value = nullptr;
			from_attribute->m_name = "";
			return;
		}

		// Current object
		json object = m_array.at(m_index);
		if(object.size() <= 0 ) {
			from_attribute->m_value = nullptr;
			from_attribute->m_name = "";
			return;
		}
		// Search current attribute
		json::iterator it;
		for (it = object.begin(); it != object.end(); ++it) {
			if(it.key() == from_attribute->m_name) {
				break;
			}
		}
		if(it == object.end()) {
			// Should not happen
			from_attribute->m_value = nullptr;
			from_attribute->m_name = "";
			return;
		}
		++it;
		if(it == object.end()) {
			// Last attribute so set to null
			from_attribute->m_value = nullptr;
			from_attribute->m_name = "";
			return;
		}
		for (; it != object.end(); ++it) {
			if(it.value().is_object() || it.value().is_array()) {
				// Is object or array so it's not a property but a child element.
				continue;
			}
			// Set to next found attribute.
			from_attribute->m_value = it.value();
			from_attribute->m_name = it.key();
			return;
		}
		// No next found.
		from_attribute->m_value = nullptr;
		from_attribute->m_name = "";
	}

	SpriterFileAttributeWrapper * JSONSpriterFileElementWrapper::newAttributeWrapperFromFirstAttribute()
	{
		if(!isValid()) {
			return new JSONSpriterFileAttributeWrapper(this);
		}

		// Current object
		json object = m_array.at(m_index);

		// Has the object property's?
		if(object.size() <= 0 ) {
			return new JSONSpriterFileAttributeWrapper(this);
		}
		for (json::iterator it = object.begin(); it != object.end(); ++it) {
			if(it.value().is_object() || it.value().is_array()) {
				// Are child elements so search again.
				continue;
			}
			// Found first
			return new JSONSpriterFileAttributeWrapper(this, it.key(), it.value());
		}
		// No found
		return new JSONSpriterFileAttributeWrapper(this);
	}

	SpriterFileAttributeWrapper * JSONSpriterFileElementWrapper::newAttributeWrapperFromFirstAttribute(const std::string & attributeName)
	{
		if(!isValid()) {
			return new JSONSpriterFileAttributeWrapper(this, attributeName);
		}

		// Current object
		json object = m_array.at(m_index);

		// Has the object property's?
		if(object.size() <= 0 ) {
			return new JSONSpriterFileAttributeWrapper(this, attributeName);
		}

		// Search for the name
		json::iterator it = object.find(attributeName);
		if(it == object.end() || (it.value().is_array() || it.value().is_object())) {
			// Not found or it is a child element.
			return new JSONSpriterFileAttributeWrapper(this, attributeName);
		}
		// Found
		return new JSONSpriterFileAttributeWrapper(this, attributeName, it.value());
	}

	SpriterFileElementWrapper * JSONSpriterFileElementWrapper::newElementWrapperFromFirstElement()
	{
		if(!isValid()) {
			return new JSONSpriterFileElementWrapper(this);
		}

		// Current object
		json object = m_array.at(m_index);

		// Has the object property's?
		if(object.size() <= 0 ) {
			return new JSONSpriterFileElementWrapper(this);
		}
		for (json::iterator it = object.begin(); it != object.end(); ++it) {
			if(!(it.value().is_object() || it.value().is_array())) {
				// Its not a child element so continue
				continue;
			}
			if(it.value().is_object()) {
				// Push it to empty array
				json arr;
				arr.push_back(it.value());
				return new JSONSpriterFileElementWrapper(this, it.key(), arr, 0);
			}
			// It's an array
			return new JSONSpriterFileElementWrapper(this, it.key(), it.value(), 0);
		}
		// Not found
		return new JSONSpriterFileElementWrapper(this);
	}

	SpriterFileElementWrapper * JSONSpriterFileElementWrapper::newElementWrapperFromFirstElement(const std::string & elementName)
	{
		if(!isValid()) {
			return new JSONSpriterFileElementWrapper(this, elementName);
		}

		// Current object
		json object = m_array.at(m_index);

		// Has the object property's?
		if(object.size() <= 0 ) {
			return new JSONSpriterFileElementWrapper(this, elementName);
		}

		// Search for the name
		json::iterator it = object.find(elementName);
		if(it == object.end()) {
			// Not found
			return new JSONSpriterFileElementWrapper(this, elementName);
		}
		if(it.value().is_array()) {
			return new JSONSpriterFileElementWrapper(this, elementName, it.value());
		}
		if(it.value().is_object()) {
			// Push to empty array
			json arr;
			arr.push_back(it.value());
			return new JSONSpriterFileElementWrapper(this, elementName, arr);
		}
		// It's a property iso an child element, so not found
		return new JSONSpriterFileElementWrapper(this, elementName);
	}

	SpriterFileElementWrapper * JSONSpriterFileElementWrapper::newElementWrapperFromNextSiblingElement()
	{
		JSONSpriterFileElementWrapper *wrapper = new JSONSpriterFileElementWrapper(m_parent, m_name, m_array, m_index);
		wrapper->advanceToNextSiblingElement();
		return wrapper;
	}

	SpriterFileElementWrapper * JSONSpriterFileElementWrapper::newElementClone()
	{
		return new JSONSpriterFileElementWrapper(m_parent, m_name, m_array, m_index);
	}

}
