#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class LessThanBlock : public ComparisonBlockBase
{
public:
	static LessThanBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;
	bool compare(char inputA, char inputB) override;

private:
	typedef ComparisonBlockBase super;
	LessThanBlock(BlockType blockType);
	~LessThanBlock();
};
