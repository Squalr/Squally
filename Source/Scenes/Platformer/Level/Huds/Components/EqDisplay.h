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

class EqDisplay : public SmartNode
{
public:
	static EqDisplay* create();

	void setStatsTarget(Squally* target);

private:
	typedef SmartNode super;
	EqDisplay();
	~EqDisplay();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	Squally* target;
	cocos2d::Sprite* eqFrame;
	LocalizedLabel* eqLabel;
	ConstantString* eqValue;

	int cachedEq;
	int cachedIq;

	static const int EqCacheCipher;
};
