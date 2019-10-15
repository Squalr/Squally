#pragma once

#include "Engine/SmartNode.h"

class Item;
class LocalizedLabel;

class FilterEntry : public SmartNode
{
public:
	virtual std::vector<Item*> filter(std::vector<Item*> itemList) = 0;

protected:
	FilterEntry();
	~FilterEntry();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;
};
