#include "IntelliText.h"

IntelliText* IntelliText::create()
{
	IntelliText* instance = new IntelliText();

	instance->autorelease();

	return instance;
}

IntelliText* IntelliText::create(IntelliTextItem textItem)
{
	IntelliText* instance = IntelliText::create();

	instance->enqueueText(textItem);

	return instance;
}

void IntelliText::enqueueText(IntelliTextItem textItem)
{

}

IntelliText::IntelliText()
{
}

IntelliText::~IntelliText()
{
}
