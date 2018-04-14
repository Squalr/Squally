#ifndef SPRITERFILEDOCUMENTWRAPPER_H
#define SPRITERFILEDOCUMENTWRAPPER_H

#include <string>
#include <vector>

namespace SpriterEngine
{
	class SpriterFileElementWrapper;
	
	typedef std::vector<SpriterFileElementWrapper*> ElementVector;

	class SpriterFileDocumentWrapper
	{
	public:
		SpriterFileDocumentWrapper();

		virtual ~SpriterFileDocumentWrapper();

		virtual void loadFile(std::string fileName) = 0;

		SpriterFileElementWrapper *getFirstChildElement();
		SpriterFileElementWrapper *getFirstChildElement(std::string elementName);

	private:
		virtual SpriterFileElementWrapper *newElementWrapperFromFirstElement() = 0;
		virtual SpriterFileElementWrapper *newElementWrapperFromFirstElement(const std::string & elementName) = 0;

		ElementVector childElements;

	};

}

#endif // SPRITERFILEDOCUMENTWRAPPER_H