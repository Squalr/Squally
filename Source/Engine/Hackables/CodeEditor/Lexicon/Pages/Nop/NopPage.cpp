#include "NopPage.h"

using namespace cocos2d;

NopPage* NopPage::create()
{
	NopPage* instance = new NopPage();

	instance->autorelease();

	return instance;
}

NopPage::NopPage()
{
}

NopPage::~NopPage()
{
}