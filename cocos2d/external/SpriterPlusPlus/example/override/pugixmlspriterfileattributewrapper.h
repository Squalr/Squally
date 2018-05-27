#ifndef PUGIXMLSPRITERFILEATTRIBUTEWRAPPER_H
#define PUGIXMLSPRITERFILEATTRIBUTEWRAPPER_H

#include "../../pugixml/pugixml.hpp"

#include "../../spriterengine/override/spriterfileattributewrapper.h"

namespace SpriterEngine
{
    class PugiXmlSpriterFileAttributeWrapper : public SpriterFileAttributeWrapper
    {
        typedef pugi::xml_attribute AttributePtr_t;

    public:
        PugiXmlSpriterFileAttributeWrapper(AttributePtr_t initialAttribute);

        std::string getName() override;

        bool isValid() override;

        real getRealValue() override;
        int getIntValue() override;
        std::string getStringValue() override;

        void advanceToNextAttribute() override;

    private:
        AttributePtr_t attribute;
    };

}

#endif // PUGIXMLSPRITERFILEATTRIBUTEWRAPPER_H
