#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class GreaterThanBlock : public ComparisonBlockBase
{
public:
	static GreaterThanBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;
	bool compare(char inputA, char inputB) override;

private:
	typedef ComparisonBlockBase super;
	GreaterThanBlock(BlockType blockType);
	~GreaterThanBlock();
};
