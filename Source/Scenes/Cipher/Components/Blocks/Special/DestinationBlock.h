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

	int cipherIndex;
	unsigned char charValue;
	CipherEvents::DisplayDataType displayDataType;

	cocos2d::Sprite* spriteAscii;
	cocos2d::Sprite* spriteBin;
	cocos2d::Sprite* spriteDec;
	cocos2d::Sprite* spriteHex;
	cocos2d::Sprite* displayFrameAscii;
	cocos2d::Sprite* displayFrameBin;
	cocos2d::Sprite* displayFrameDec;
	cocos2d::Sprite* displayFrameHex;
	SmartAsciiLabel* displayLabel;
	SmartAsciiLabel* receivedDisplayLabel;
};
