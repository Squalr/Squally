#pragma once

#include "Scenes/Cipher/Components/Blocks/Connections/BoltBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;

class OutputBolt : public BoltBase
{
public:
	static OutputBolt* create();

	void execute(char value, std::function<void()> onExecuteComplete);
	void setConnection(Connection* connection) override;

private:
	typedef BoltBase super;
	OutputBolt();
	~OutputBolt();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Sprite* bolt;
	cocos2d::Sprite* helperArrow;
};
