#ifndef JSONSPRITERFILEELEMENTWRAPPER_H
#define JSONSPRITERFILEELEMENTWRAPPER_H

#include "../../spriterengine/override/spriterfileelementwrapper.h"
#include "json.hpp"

using json = nlohmann::json;

namespace SpriterEngine
{
	class JSONSpriterFileAttributeWrapper;

	class JSONSpriterFileElementWrapper : public SpriterFileElementWrapper
	{
	public:
		JSONSpriterFileElementWrapper(JSONSpriterFileElementWrapper* parent=nullptr, std::string name = "", json array = json::array(), int index = 0);

		std::string getName() override;

		bool isValid() override;

		void advanceToNextSiblingElement() override;
		void advanceToNextSiblingElementOfSameName() override;

		void advanceToNextAttribute(JSONSpriterFileAttributeWrapper* from_attribute);

	private:
		SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute() override;
		SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute(const std::string & attributeName) override;

		SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
		SpriterFileElementWrapper *newElementWrapperFromFirstElement(const std::string & elementName) override;

		SpriterFileElementWrapper *newElementWrapperFromNextSiblingElement() override;

		SpriterFileElementWrapper *newElementClone() override;

		json m_array; // Array of elements with the same name
		int m_index; // Index of the current element
		std::string m_name;

		JSONSpriterFileElementWrapper *m_parent;
	};

}

#endif // JSONSPRITERFILEELEMENTWRAPPER_H
