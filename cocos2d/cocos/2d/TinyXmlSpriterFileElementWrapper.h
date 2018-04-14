#ifndef TINYXMLSPRITERFILEELEMENTWRAPPER_H
#define TINYXMLSPRITERFILEELEMENTWRAPPER_H

#include "2d/CCNode.h"
#include "TinyXmlSpriterFileAttributeWrapper.h"
#include "tinyxml2.h"
#include "SpriterPlusPlus/spriterengine/override/spriterfileelementwrapper.h"

NS_CC_BEGIN

	class CC_DLL TinyXmlSpriterFileElementWrapper : public SpriterEngine::SpriterFileElementWrapper
	{
	public:
		TinyXmlSpriterFileElementWrapper(tinyxml2::XMLElement *initialElement);

		std::string getName() override;

		bool isValid() override;

		void advanceToNextSiblingElement() override;
		void advanceToNextSiblingElementOfSameName() override;

	private:
		SpriterEngine::SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute() override;
		SpriterEngine::SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute(const std::string & attributeName) override;

		SpriterEngine::SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
		SpriterEngine::SpriterFileElementWrapper *newElementWrapperFromFirstElement(const std::string & elementName) override;

		SpriterEngine::SpriterFileElementWrapper *newElementWrapperFromNextSiblingElement() override;

		SpriterEngine::SpriterFileElementWrapper *newElementClone() override;

		const tinyxml2::XMLAttribute * findAttributeInElement(const std::string & name);

		tinyxml2::XMLElement *element;
	};

NS_CC_END

#endif // TINYXMLSPRITERFILEELEMENTWRAPPER_H