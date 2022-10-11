#pragma once

#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SmartAsciiLabel;

class DestinationBlock : public BlockBase
{
public:
	static DestinationBlock* create(int cipherIndex);

	unsigned char getValue();
	bool isMatchedValues();
	
protected:
	DestinationBlock(int cipherIndex);
	virtual ~DestinationBlock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	float getBoltOffsetY() override;
	void onAnyStateChange(CipherState* cipherState) override;
	void execute(std::function<void()> onExecuteComplete) override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
	
	void loadDisplayValue();

	int cipherIndex = 0;
	unsigned char charValue = 0;
	CipherEvents::DisplayDataType displayDataType = CipherEvents::DisplayDataType::Ascii;

	cocos2d::Sprite* spriteAscii = nullptr;
	cocos2d::Sprite* spriteBin = nullptr;
	cocos2d::Sprite* spriteDec = nullptr;
	cocos2d::Sprite* spriteHex = nullptr;
	cocos2d::Sprite* displayFrameAscii = nullptr;
	cocos2d::Sprite* displayFrameBin = nullptr;
	cocos2d::Sprite* displayFrameDec = nullptr;
	cocos2d::Sprite* displayFrameHex = nullptr;
	SmartAsciiLabel* displayLabel = nullptr;
	SmartAsciiLabel* receivedDisplayLabel = nullptr;
};
