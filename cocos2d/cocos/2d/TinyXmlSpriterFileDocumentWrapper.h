#ifndef TINYXMLSPRITERFILEDOCUMENTWRAPPER_H
#define TINYXMLSPRITERFILEDOCUMENTWRAPPER_H

#include "2d/CCNode.h"
#include "tinyxml2.h"
#include "base/CCConsole.h"
#include "platform/CCFileUtils.h"
#include "TinyXmlSpriterFileElementWrapper.h"
#include "SpriterPlusPlus/spriterengine/override/spriterfiledocumentwrapper.h"

NS_CC_BEGIN

	class CC_DLL TinyXmlSpriterFileDocumentWrapper : public SpriterEngine::SpriterFileDocumentWrapper
	{
	public:
		TinyXmlSpriterFileDocumentWrapper();

		void loadFile(std::string fileName) override;

	private:
		SpriterEngine::SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
		SpriterEngine::SpriterFileElementWrapper *newElementWrapperFromFirstElement(const std::string & elementName) override;

		tinyxml2::XMLDocument doc;
	};

NS_CC_END

#endif // TINYXMLSPRITERFILEDOCUMENTWRAPPER_H