#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class OrBlock : public BlockBase
{
public:
	static OrBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	OrBlock(BlockType blockType);
	~OrBlock();

	void onEnter() override;
	void initializePositions() override;
};
