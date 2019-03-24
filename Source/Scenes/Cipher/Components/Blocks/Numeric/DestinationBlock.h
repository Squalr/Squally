#pragma once

#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ConstantString;
class LocalizedLabel;

class DestinationBlock : public BlockBase
{
public:
	static DestinationBlock* create(int cipherIndex);
	
protected:
	void execute(std::function<void()> onExecuteComplete) override;
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	DestinationBlock(int cipherIndex);
	~DestinationBlock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	float getBoltOffsetY() override;
	void loadDisplayValue();

	ConstantString* displayValue;
	LocalizedLabel* displayLabel;
	ConstantString* receivedDisplayValue;
	LocalizedLabel* receivedDisplayLabel;

	int cipherIndex;
	char charValue;
	CipherEvents::DisplayDataType displayDataType;

	cocos2d::Sprite* spriteAscii;
	cocos2d::Sprite* spriteBin;
	cocos2d::Sprite* spriteDec;
	cocos2d::Sprite* spriteHex;
};
