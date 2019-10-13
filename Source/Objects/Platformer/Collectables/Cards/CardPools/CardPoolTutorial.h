#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTutorial : public MinMaxPool
{
public:
	static CardPoolTutorial* create();

protected:
	CardPoolTutorial();
	~CardPoolTutorial();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MinMaxPool super;
};
