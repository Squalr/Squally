#include "pugixmlspriterfileattributewrapper.h"

namespace SpriterEngine
{
    PugiXmlSpriterFileAttributeWrapper::PugiXmlSpriterFileAttributeWrapper(AttributePtr_t initialAttribute):
        attribute(initialAttribute)
    {
    }

    std::string PugiXmlSpriterFileAttributeWrapper::getName()
    {
        return attribute.name();
    }

    bool PugiXmlSpriterFileAttributeWrapper::isValid()
    {
        return attribute;
    }

    real PugiXmlSpriterFileAttributeWrapper::getRealValue()
    {
        return attribute.as_double();
    }

    int PugiXmlSpriterFileAttributeWrapper::getIntValue()
    {
        return attribute.as_int();
    }

    std::string PugiXmlSpriterFileAttributeWrapper::getStringValue()
    {
        return attribute.as_string();
    }

    void PugiXmlSpriterFileAttributeWrapper::advanceToNextAttribute()
    {
        attribute = attribute.next_attribute();
    }
}
