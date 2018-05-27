#ifndef TINYXMLSPRITERFILEATTRIBUTEWRAPPER_H
#define TINYXMLSPRITERFILEATTRIBUTEWRAPPER_H

#include "../../tinyxml2/tinyxml2.h"

#include "../../spriterengine/override/spriterfileattributewrapper.h"

namespace SpriterEngine
{
	class TinyXmlSpriterFileAttributeWrapper : public SpriterFileAttributeWrapper
	{
	public:
		TinyXmlSpriterFileAttributeWrapper(const tinyxml2::XMLAttribute *initialAttribute);

		std::string getName() override;

		bool isValid() override;

		real getRealValue() override;
		int getIntValue() override;
		std::string getStringValue() override;

		void advanceToNextAttribute() override;

	private:
		const tinyxml2::XMLAttribute *attribute;
	};

}

#endif // TINYXMLSPRITERFILEATTRIBUTEWRAPPER_H