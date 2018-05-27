#include "jsonspriterfiledocumentwrapper.h"
#include "jsonspriterfileelementwrapper.h"

#include "../../spriterengine/global/settings.h"

#include <string>
#include <fstream>
#include <streambuf>

namespace SpriterEngine
{
	JSONSpriterFileDocumentWrapper::JSONSpriterFileDocumentWrapper()
	{
	}

	void JSONSpriterFileDocumentWrapper::loadFile(std::string fileName)
	{
		// Load in string
		std::ifstream t(fileName);
		std::string json_str;

		// reserve space is faster with big files
		t.seekg(0, std::ios::end);
		json_str.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		json_str.assign((std::istreambuf_iterator<char>(t)),
					std::istreambuf_iterator<char>());

		// parse the json string
		m_json = json::parse(json_str);
	}

	SpriterFileElementWrapper * JSONSpriterFileDocumentWrapper::newElementWrapperFromFirstElement()
	{
		// The root of the document should be an object
		if(m_json.is_object() && !m_json.empty()) {
			// We keep track of the elements with the same name as an array like it's structured in the scon file.
			// So if we don't have an array, we create one with one element.
			json array;
			array.push_back(m_json);
			return new JSONSpriterFileElementWrapper(nullptr, "spriter_data", array, 0);
		}
		SpriterEngine::Settings::error("JSON document doesn't contain an object");
		return new JSONSpriterFileElementWrapper();

	}

	SpriterFileElementWrapper * JSONSpriterFileDocumentWrapper::newElementWrapperFromFirstElement(const std::string & elementName)
	{
		// The root has no name, but the scml has one (spriter_data), so we expect this here.
		assert(elementName.compare("spriter_data") == 0);
		return newElementWrapperFromFirstElement();
	}

}
