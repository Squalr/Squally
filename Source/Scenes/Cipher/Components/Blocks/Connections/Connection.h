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
	~Connection();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	cocos2d::Sprite* connectionLine;
	cocos2d::Sprite* connectionCap;
	cocos2d::Vec2 currentStretchPosition;

	cocos2d::Sprite* connectionPulse;
	Lightning* lightningEffectSource;
	Lightning* lightningEffectDest;

	bool trackBolt;
	InputBolt* inputBolt;
};
