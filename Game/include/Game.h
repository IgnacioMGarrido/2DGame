#pragma once
#include <engine/App.h>
#include <vector>

class Game : public Core::App
{
public:

	struct Block
	{
		float speedX;
		float speedY;
		bool isAlive;
		Core::Drawer::Rect rect;
		Core::Drawer::Color color;
	};

	enum BlockSide
	{
		BLOCKSIDE_TOP,
		BLOCKSIDE_RIGHT,
		BLOCKSIDE_BOTTOM,
		BLOCKSIDE_LEFT
	};

	Game(Core::App::AppContext i_context);

protected:
	virtual void Update(float i_fixedTick) override;
	virtual void Render() override;

private:
	float BlockGetSide(const Block& i_block, BlockSide i_side);
	bool HasBallCollidedTo(const Block& ball, const Block& block);

public:
	std::vector<Block> m_blockEntities;
	float m_paddleSpeed = .7f;

};
