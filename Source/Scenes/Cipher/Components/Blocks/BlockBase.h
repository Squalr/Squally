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

	ClickableNode* block = nullptr;
	cocos2d::Sprite* icon = nullptr;
	BlockType blockType = BlockType::Normal;
	unsigned char receivedValue = 0;
	int receivedInputs = 0;
	
	unsigned char inputLeft = 0;
	unsigned char inputRight = 0;
	InputBolt* inputBoltLeft = nullptr;
	InputBolt* inputBoltRight = nullptr;
	OutputBolt* outputBoltLeft = nullptr;
	OutputBolt* outputBoltRight = nullptr;
	
	ConnectionType inputType = ConnectionType::None;
	ConnectionType outputType = ConnectionType::None;

private:
	typedef CipherComponentBase super;

	BlockBase* spawningBlock = nullptr;
	LocalizedLabel* label = nullptr;
	
	cocos2d::Vec2 spawnPosition;
	cocos2d::Vec2 originalPosition;
	cocos2d::Vec2 clickDelta;
};
