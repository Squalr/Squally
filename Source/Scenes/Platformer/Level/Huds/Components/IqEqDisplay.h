#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class LocalizedString;
class Squally;

class IqEqDisplay : public SmartNode
{
public:
	static IqEqDisplay* create();

	void setStatsTarget(Squally* target);

private:
	typedef SmartNode super;
	IqEqDisplay();
	virtual ~IqEqDisplay();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	Squally* target;
	cocos2d::Sprite* iqEqFrame;
	LocalizedLabel* iqEqLabel;
	LocalizedString* iqEqValue;
	ConstantString* eqValue;
	ConstantString* iqValue;

	int cachedEq;
	int cachedIq;

	static const int IqCacheCipher;
	static const int EqCacheCipher;
};
