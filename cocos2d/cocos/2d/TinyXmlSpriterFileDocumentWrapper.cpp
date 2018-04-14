#include "TinyXmlSpriterFileDocumentWrapper.h"

NS_CC_BEGIN

	TinyXmlSpriterFileDocumentWrapper::TinyXmlSpriterFileDocumentWrapper()
	{
	}

	void TinyXmlSpriterFileDocumentWrapper::loadFile(std::string fileName)
	{
		cocos2d::Data data = cocos2d::FileUtils::getInstance()->getDataFromFile(fileName);
		if (!data.isNull())
		{
			int rc = doc.Parse((const char*)data.getBytes(), data.getSize());
			if (rc != 0) {
				cocos2d::log("TinyXML failed to Parse: %s,%d\n",fileName.c_str(),rc);
			}
		} else {
			cocos2d::log("TinyXMLSpriterFileDocumentWrapper failed to read data from file: %s", fileName.c_str());
		}
	}

	SpriterEngine::SpriterFileElementWrapper * TinyXmlSpriterFileDocumentWrapper::newElementWrapperFromFirstElement()
	{
		return new TinyXmlSpriterFileElementWrapper(doc.FirstChildElement());
	}

	SpriterEngine::SpriterFileElementWrapper * TinyXmlSpriterFileDocumentWrapper::newElementWrapperFromFirstElement(const std::string & elementName)
	{
		return new TinyXmlSpriterFileElementWrapper(doc.FirstChildElement(elementName.c_str()));
	}

NS_CC_END
