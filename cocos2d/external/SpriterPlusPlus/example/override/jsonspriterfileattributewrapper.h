#ifndef JSONSPRITERFILEATTRIBUTEWRAPPER_H
#define JSONSPRITERFILEATTRIBUTEWRAPPER_H

#include "../../spriterengine/override/spriterfileattributewrapper.h"
#include "json.hpp"

using json = nlohmann::json;

namespace SpriterEngine
{
	class JSONSpriterFileElementWrapper;

	class JSONSpriterFileAttributeWrapper : public SpriterFileAttributeWrapper
	{
	public:
		JSONSpriterFileAttributeWrapper(JSONSpriterFileElementWrapper* parent_object, std::string name = "", json value = nullptr);

		std::string getName() override;

		bool isValid() override;

		real getRealValue() override;
		int getIntValue() override;
		std::string getStringValue() override;

		void advanceToNextAttribute() override;

	private:
		json m_value;
		std::string m_name;
		JSONSpriterFileElementWrapper* m_parent_object;

		friend class JSONSpriterFileElementWrapper;
	};

}

#endif // JSONSPRITERFILEATTRIBUTEWRAPPER_H
