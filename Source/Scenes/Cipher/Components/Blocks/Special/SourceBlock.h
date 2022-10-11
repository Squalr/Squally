#pragma once

#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SmartAsciiLabel;

class SourceBlock : public BlockBase
{
public:
	static SourceBlock* create(int cipherIndex);
	
protected:
	SourceBlock(int cipherIndex);
	virtual ~SourceBlock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
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
	SmartAsciiLabel* displayLabel = nullptr;
};
