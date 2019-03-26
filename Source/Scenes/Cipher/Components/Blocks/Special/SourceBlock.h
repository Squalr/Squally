#pragma once

#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SmartAsciiLabel;

class SourceBlock : public BlockBase
{
public:
	static SourceBlock* create(int cipherIndex);
	
protected:
	unsigned char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	SourceBlock(int cipherIndex);
	~SourceBlock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadDisplayValue();

	SmartAsciiLabel* displayLabel;

	int cipherIndex;
	unsigned char charValue;
	CipherEvents::DisplayDataType displayDataType;

	cocos2d::Sprite* spriteAscii;
	cocos2d::Sprite* spriteBin;
	cocos2d::Sprite* spriteDec;
	cocos2d::Sprite* spriteHex;
};
