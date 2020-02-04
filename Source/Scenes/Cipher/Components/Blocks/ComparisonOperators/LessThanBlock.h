#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class LessThanBlock : public ComparisonBlockBase
{
public:
	static LessThanBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	LessThanBlock(BlockType blockType);
	virtual ~LessThanBlock();
	unsigned char compute() override;
	bool compare(unsigned char inputA, unsigned char inputB) override;

private:
	typedef ComparisonBlockBase super;
};
