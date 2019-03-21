#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class InputBolt;
class OutputBolt;

class Connection : public SmartNode
{
public:
	static Connection* create(InputBolt* source, OutputBolt* dest);

protected:
	Connection(InputBolt* source, OutputBolt* dest);
	~Connection();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	cocos2d::Sprite* connectionLine;
	cocos2d::Sprite* connectionCap;
	InputBolt* source;
	OutputBolt* dest;
};
