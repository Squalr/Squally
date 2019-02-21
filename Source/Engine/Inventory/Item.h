#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;

class Item : public SmartNode
{
public:
	LocalizedString* cloneName();
	std::string getIconResource();

protected:
	Item(LocalizedString* name, std::string iconResource);
	virtual ~Item();
	void onEnter() override;
	void initializeListeners() override;

	LocalizedString* name;
	std::string iconResource;

private:
	typedef SmartNode super;
};
