#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ModBlock : public BlockBase
{
public:
	static ModBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;

private:
	typedef BlockBase super;
	ModBlock(BlockType blockType);
	~ModBlock();

	void onEnter() override;
	void initializePositions() override;
};
