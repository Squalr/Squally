#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class OutputBolt;

class Connection : public SmartNode
{
public:
	static Connection* create();

	void stretchToLocation(cocos2d::Vec2 location);

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
};
