#ifndef PUGIXMLSPRITERFILEDOCUMENTWRAPPER_H
#define PUGIXMLSPRITERFILEDOCUMENTWRAPPER_H

#include "../../pugixml/pugixml.hpp"

#include "../../spriterengine/override/spriterfiledocumentwrapper.h"

namespace SpriterEngine
{
    class PugiXmlSpriterFileDocumentWrapper : public SpriterFileDocumentWrapper
    {
        typedef pugi::xml_document Document_t;

    public:
        PugiXmlSpriterFileDocumentWrapper();

        void loadFile(std::string fileName) override;

    private:
        SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
        SpriterFileElementWrapper *newElementWrapperFromFirstElement(const std::string & elementName) override;

        Document_t doc;
    };

}

#endif // PUGIXMLSPRITERFILEDOCUMENTWRAPPER_H
