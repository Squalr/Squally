#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class EntityEqBehavior;
class LocalizedLabel;
class LocalizedString;
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

	EntityEqBehavior* eqBehavior;
	PlatformerEntity* target;
	cocos2d::Sprite* eqFrame;
	LocalizedLabel* eqLabel;
	ConstantString* eqValue;

	int cachedEq;
	int cachedIq;

	static const int EqCacheCipher;
};
