#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class XorBlock : public BlockBase
{
public:
	static XorBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;

private:
	typedef BlockBase super;
	XorBlock(BlockType blockType);
	~XorBlock();

	void onEnter() override;
	void initializePositions() override;
};
