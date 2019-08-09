#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class EntityEqBehaviorBase;
class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;

class EqDisplay : public SmartNode
{
public:
	static EqDisplay* create();

	void setStatsTarget(PlatformerEntity* target);

private:
	typedef SmartNode super;
	EqDisplay();
	~EqDisplay();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	EntityEqBehaviorBase* eqBehavior;
	PlatformerEntity* target;
	cocos2d::Sprite* eqFrame;
	LocalizedLabel* eqLabel;
	ConstantString* eqValue;

	int cachedEq;
	int cachedIq;

	static const int EqCacheCipher;
};
