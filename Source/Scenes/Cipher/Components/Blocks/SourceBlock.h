#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ConstantString;
class LocalizedLabel;

class SourceBlock : public BlockBase
{
public:
	static SourceBlock* create(int cipherIndex);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	SourceBlock(int cipherIndex);
	~SourceBlock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadDisplayValue(std::string input);

	ConstantString* displayValue;
	LocalizedLabel* displayLabel;

	int cipherIndex;
};
