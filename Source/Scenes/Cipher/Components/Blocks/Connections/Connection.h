#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class InputBolt;

class Connection : public SmartNode
{
public:
	static Connection* create();

	void setInputBolt(InputBolt* target, bool trackBolt = true);
	void stretchToLocation(cocos2d::Vec2 location);
	InputBolt* getInputBolt();

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

	bool trackBolt;
	InputBolt* inputBolt;
};
