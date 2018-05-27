#ifndef PUGIXMLSPRITERFILEELEMENTWRAPPER_H
#define PUGIXMLSPRITERFILEELEMENTWRAPPER_H

#include "../../pugixml/pugixml.hpp"

#include "../../spriterengine/override/spriterfileelementwrapper.h"

namespace SpriterEngine
{
    class PugiXmlSpriterFileElementWrapper : public SpriterFileElementWrapper
    {
        typedef pugi::xml_node ElementPtr_t;
        typedef pugi::xml_attribute AttributePtr_t;

    public:
        PugiXmlSpriterFileElementWrapper(ElementPtr_t initialElement);

        std::string getName() override;

        bool isValid() override;

        void advanceToNextSiblingElement() override;
        void advanceToNextSiblingElementOfSameName() override;

    private:
        SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute() override;
        SpriterFileAttributeWrapper *newAttributeWrapperFromFirstAttribute(const std::string & attributeName) override;

        SpriterFileElementWrapper *newElementWrapperFromFirstElement() override;
        SpriterFileElementWrapper *newElementWrapperFromFirstElement(const std::string & elementName) override;

        SpriterFileElementWrapper *newElementWrapperFromNextSiblingElement() override;

        SpriterFileElementWrapper *newElementClone() override;

        AttributePtr_t findAttributeInElement(const std::string & name);

        ElementPtr_t element;
    };

}

#endif // PUGIXMLSPRITERFILEELEMENTWRAPPER_H
