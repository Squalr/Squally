#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class GreaterThanBlock : public ComparisonBlockBase
{
public:
	static GreaterThanBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;
	BlockBase* spawn() override;
	bool compare(unsigned char inputA, unsigned char inputB) override;

private:
	typedef ComparisonBlockBase super;
	GreaterThanBlock(BlockType blockType);
	~GreaterThanBlock();
};
