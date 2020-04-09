#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class CurrencyInventory;
class LocalizedLabel;

class CurrencyDisplay : public SmartNode
{
public:
	static CurrencyDisplay* create();

	void setCurrencyInventory(CurrencyInventory* inventory);

protected:
	CurrencyDisplay();
	virtual ~CurrencyDisplay();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef SmartNode super;

	CurrencyInventory* inventory;
	cocos2d::Sprite* emblem;
	LocalizedLabel* label;
	ConstantString* value;

	int cachedCurrency;

	static const int CacheCipher;
};
