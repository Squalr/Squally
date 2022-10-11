#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class EntityEqBehavior;
class LocalizedLabel;
class PlatformerEntity;

class EqDisplay : public SmartNode
{
public:
	static EqDisplay* create();

	void setStatsTarget(PlatformerEntity* target);

protected:
	EqDisplay();
	virtual ~EqDisplay();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef SmartNode super;

	EntityEqBehavior* eqBehavior = nullptr;
	PlatformerEntity* target = nullptr;
	cocos2d::Sprite* eqFrame = nullptr;
	LocalizedLabel* eqLabel = nullptr;
	ConstantString* eqValue = nullptr;

	int cachedEq = 0;
	int cachedIq = 0;

	static const int EqCacheCipher;
};
