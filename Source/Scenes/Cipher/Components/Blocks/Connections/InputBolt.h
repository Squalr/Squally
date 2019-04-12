#pragma once

#include "Scenes/Cipher/Components/Blocks/Connections/BoltBase.h"

namespace cocos2d
{
	class Sprite;
}

class BlockBase;
class ClickableNode;

class InputBolt : public BoltBase
{
public:
	static InputBolt* create(BlockBase* parentBlock);

	void execute(char value, std::function<void()> onExecuteComplete);
	void setConnection(Connection* connection) override;
	void hideHelp();
	void onConnectionUpdated() override;

private:
	typedef BoltBase super;
	InputBolt(BlockBase* parentBlock);
	~InputBolt();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	BlockBase* parentBlock;
	cocos2d::Sprite* bolt;
	cocos2d::Sprite* helperArrow;
};
