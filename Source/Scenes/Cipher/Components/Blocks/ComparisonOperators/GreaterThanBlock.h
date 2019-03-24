#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class GreaterThanBlock : public BlockBase
{
public:
	static GreaterThanBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	GreaterThanBlock(BlockType blockType);
	~GreaterThanBlock();

	void onEnter() override;
	void initializePositions() override;
};
