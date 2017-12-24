#include "RadioButtonGroup.h"

RadioButtonGroup* RadioButtonGroup::create()
{
	RadioButtonGroup* radioButtonGroup = new RadioButtonGroup();

	radioButtonGroup->autorelease();

	return radioButtonGroup;
}

RadioButtonGroup::RadioButtonGroup()
{
}

RadioButtonGroup::~RadioButtonGroup()
{
}
