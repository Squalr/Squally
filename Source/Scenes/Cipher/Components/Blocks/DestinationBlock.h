#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ConstantString;
class LocalizedLabel;

class DestinationBlock : public BlockBase
{
public:
	static DestinationBlock* create(int cipherIndex);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	DestinationBlock(int cipherIndex);
	~DestinationBlock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadDisplayValue(std::string output);

	ConstantString* displayValue;
	LocalizedLabel* displayLabel;

	int cipherIndex;
};
