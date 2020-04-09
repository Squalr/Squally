#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class GreaterThanBlock : public ComparisonBlockBase
{
public:
	static GreaterThanBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	GreaterThanBlock(BlockType blockType);
	virtual ~GreaterThanBlock();
	unsigned char compute() override;
	bool compare(unsigned char inputA, unsigned char inputB) override;

private:
	typedef ComparisonBlockBase super;
};
