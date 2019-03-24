#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class EqualsBlock : public ComparisonBlockBase
{
public:
	static EqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;
	bool compare(char inputA, char inputB) override;

private:
	typedef ComparisonBlockBase super;
	EqualsBlock(BlockType blockType);
	~EqualsBlock();
};
