#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;

class Item : public SmartNode
{
public:
	LocalizedString* cloneName();

protected:
	Item(LocalizedString* name);
	virtual ~Item();
	void onEnter() override;
	void initializeListeners() override;

	LocalizedString* name;

private:
	typedef SmartNode super;
};
