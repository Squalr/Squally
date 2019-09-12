#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class InputBolt;
class OutputBolt;
class ClickableNode;
class LocalizedLabel;
class LocalizedString;

class BlockBase : public CipherComponentBase
{
public:
	enum class BlockType
	{
		Toolbox,
		Normal,
		Static,
	};

	void pushInput(unsigned char input);
	virtual void execute(std::function<void()> onExecuteComplete);
	void removeConnections();
	ClickableNode* getBlock();

protected:
	enum class ConnectionType
	{
		None,
		Single,
		Double
	};

	BlockBase(BlockType blockType, ConnectionType inputType, ConnectionType outputType, ClickableNode* block, std::string iconResource, LocalizedString* label);
	~BlockBase();

	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;
	virtual unsigned char compute() = 0;
	virtual BlockBase* spawn() = 0;
	virtual float getBoltOffsetY();
	bool isInGameArea();

	ClickableNode* block;
	cocos2d::Sprite* icon;
	BlockType blockType;
	unsigned char receivedValue;

	std::vector<unsigned char> currentInputs;
	std::vector<InputBolt*> inputBolts;
	std::vector<OutputBolt*> outputBolts;

private:
	typedef CipherComponentBase super;

	BlockBase* spawningBlock;
	LocalizedLabel* label;
	
	ConnectionType inputType;
	ConnectionType outputType;
	cocos2d::Vec2 originalPosition;
	cocos2d::Vec2 clickDelta;
};
