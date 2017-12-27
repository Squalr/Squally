#include "Hover.h"

Hover* Hover::create()
{
	Hover* hover = new Hover();

	hover->autorelease();

	return hover;
}

Hover::Hover()
{
}

Hover::~Hover()
{
}
