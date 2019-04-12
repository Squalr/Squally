#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class AddBlock : public BlockBase
{
public:
	static AddBlock* create(BlockType blockType = BlockType::Normal);

protected:
	unsigned char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	AddBlock(BlockType blockType);
	~AddBlock();

	void onEnter() override;
	void initializePositions() override;
};
