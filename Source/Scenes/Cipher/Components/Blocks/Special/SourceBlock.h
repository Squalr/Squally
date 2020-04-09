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

	int cipherIndex;
	unsigned char charValue;
	CipherEvents::DisplayDataType displayDataType;

	cocos2d::Sprite* spriteAscii;
	cocos2d::Sprite* spriteBin;
	cocos2d::Sprite* spriteDec;
	cocos2d::Sprite* spriteHex;
	SmartAsciiLabel* displayLabel;
};
