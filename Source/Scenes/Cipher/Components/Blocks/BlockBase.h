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
		Normal,
		Static,
	};

	void setSpawnPosition(cocos2d::Vec2 spawnPosition);
	void setInput(unsigned char input, int inputIndex);
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
	virtual ~BlockBase();

	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;
	virtual unsigned char compute() = 0;
	virtual float getBoltOffsetY();
	bool isInGameArea();

	ClickableNode* block;
	cocos2d::Sprite* icon;
	BlockType blockType;
	unsigned char receivedValue;
	int receivedInputs;
	
	unsigned char inputLeft;
	unsigned char inputRight;
	InputBolt* inputBoltLeft;
	InputBolt* inputBoltRight;
	OutputBolt* outputBoltLeft;
	OutputBolt* outputBoltRight;
	
	ConnectionType inputType;
	ConnectionType outputType;

private:
	typedef CipherComponentBase super;

	BlockBase* spawningBlock;
	LocalizedLabel* label;
	
	cocos2d::Vec2 spawnPosition;
	cocos2d::Vec2 originalPosition;
	cocos2d::Vec2 clickDelta;
};
