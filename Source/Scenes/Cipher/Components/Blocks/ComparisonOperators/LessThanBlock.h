#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class LessThanBlock : public BlockBase
{
public:
	static LessThanBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	LessThanBlock(BlockType blockType);
	~LessThanBlock();

	void onEnter() override;
	void initializePositions() override;
};
