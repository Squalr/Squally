#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class InputBolt;
class Lightning;

class Connection : public SmartNode
{
public:
	static Connection* create();

	void execute(char value, std::function<void()> onExecuteComplete);
	void setInputBolt(InputBolt* target, bool trackBolt = true);
	void stretchToLocation(cocos2d::Vec2 location);
	InputBolt* getInputBolt();
	void runElectricityEffect(std::function<void()> onEffectComplete);

protected:
	Connection();
	virtual ~Connection();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	cocos2d::Sprite* connectionLine = nullptr;
	cocos2d::Sprite* connectionCap = nullptr;
	cocos2d::Vec2 currentStretchPosition;

	cocos2d::Sprite* connectionPulse = nullptr;
	Lightning* lightningEffectSource = nullptr;
	Lightning* lightningEffectDest = nullptr;

	bool trackBolt = false;
	InputBolt* inputBolt = nullptr;
};
