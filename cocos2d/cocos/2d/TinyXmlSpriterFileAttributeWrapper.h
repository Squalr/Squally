#ifndef TINYXMLSPRITERFILEATTRIBUTEWRAPPER_H
#define TINYXMLSPRITERFILEATTRIBUTEWRAPPER_H

#include "2d/CCNode.h"
#include "tinyxml2.h"
#include "SpriterPlusPlus/spriterengine/override/spriterfileattributewrapper.h"

NS_CC_BEGIN

	class CC_DLL TinyXmlSpriterFileAttributeWrapper : public SpriterEngine::SpriterFileAttributeWrapper
	{
	public:
		TinyXmlSpriterFileAttributeWrapper(const tinyxml2::XMLAttribute *initialAttribute);

		std::string getName() override;

		bool isValid() override;

		SpriterEngine::real getRealValue() override;
		int getIntValue() override;
		std::string getStringValue() override;

		void advanceToNextAttribute() override;

	private:
		const tinyxml2::XMLAttribute *attribute;
	};

NS_CC_END

#endif // TINYXMLSPRITERFILEATTRIBUTEWRAPPER_H