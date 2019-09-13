#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class MulBlock : public BlockBase
{
public:
	static MulBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;

private:
	typedef BlockBase super;
	MulBlock(BlockType blockType);
	~MulBlock();

	void onEnter() override;
	void initializePositions() override;
};
