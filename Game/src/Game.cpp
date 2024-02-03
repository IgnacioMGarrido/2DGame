#include <engine/platform/Logger.h>

// TODO(Nacho): These Drawer thing has to go
#include <engine/render/Drawer.h>
#include <engine/EntryPoint.h>
#include "Game.h"


///////////////////////////////////////////////////////////////////////////

Game::Game(Core::App::AppContext i_context)
	: Core::App(i_context)
{
	//1 paddle, 1 ball, 68 Blocks
	m_blockEntities.reserve(72);

	// Paddle
	m_blockEntities.push_back({
			.speedX = 0.f,
			.speedY = 0.f,
			.isAlive = true,
			.rect = { .x = 576.f, .y = 600.f, .w = 128.f, .h = 32.f },
			.color = {.r = 43, .g = 0, .b = 255}});

	// Ball
	m_blockEntities.push_back({
			.speedX = .5f,
			.speedY = .5f,
			.isAlive = true,
			.rect = { .x = 632.f, .y = 580.f, .w = 16.f, .h = 16.f },
			.color = {.r = 0, .g = 255, .b = 0}});


	const float offsetX = 32.0f;
	const float offsetY = 16.0f;
	const float padding = 8.0f;
	int row = 0;
	int col = 0;
	const int blocksPerRow = 17;

	for(int index = 2; index < 200; index++)
	{

		m_blockEntities.push_back({
				.speedX = 0.00f,
				.speedY = 0.00f,
				.isAlive = true,
				.rect = {
					.x = offsetX + (padding + 64) * col,
					.y = offsetY + (padding + 16) * row,
					.w = 64.f,
					.h = 16.f
				},
				.color = {
					.r = (uint8_t)(rand() % 200),
					.g = (uint8_t)(rand() % 200),
					.b = (uint8_t)(rand() % 200)
				}
			});

		col++;
		if(col == blocksPerRow)
		{
			col = 0;
			row++;
		}
	}
}

///////////////////////////////////////////////////////////////////////////

void Game::Update(float i_fixedTick)
{

	Block& paddle = m_blockEntities.at(0);
	Block& ball = m_blockEntities.at(1);

	paddle.rect.x += paddle.speedX * i_fixedTick;

	ball.rect.x += ball.speedX * i_fixedTick;
	ball.rect.y += ball.speedY * i_fixedTick;

	if(BlockGetSide(ball, BLOCKSIDE_LEFT) < 0)
	{
		ball.rect.x = 0;
		ball.speedX = ball.speedX * -1;
	}
	if(BlockGetSide(ball, BLOCKSIDE_RIGHT) > 1280)
	{
		ball.rect.x = 1280 - ball.rect.w;
		ball.speedX = ball.speedX * -1;
	}
	if(BlockGetSide(ball, BLOCKSIDE_TOP) < 0)
	{
		ball.rect.y = 0;
		ball.speedY = ball.speedY * -1;
	}

	if(HasBallCollidedTo(ball, paddle))
	{
		ball.rect.y = BlockGetSide(paddle, BLOCKSIDE_TOP) - ball.rect.h;
		ball.speedY = ball.speedY * -1;
	}

	for(auto& block : m_blockEntities)
	{
		if(&block == &paddle || &block == &ball)
		{
			continue;
		}

		if(!block.isAlive)
		{
			continue;
		}

		if(HasBallCollidedTo(ball, block))
		{
			// kill block
			block.isAlive = false;
			ball.speedY = ball.speedY * -1;

		}
	}

	//LOG_TRACE("MyApp::Update() -> %.1f fps", i_fixedTick);
}

///////////////////////////////////////////////////////////////////////////

void Game::Render()
{

	for(const auto& block : m_blockEntities)
	{
		if(block.isAlive)
		{
			m_drawer->DrawFilledRect(block.rect, block.color);
		}
	}
}

///////////////////////////////////////////////////////////////////////////

float Game::BlockGetSide(const Block& i_block, BlockSide i_side)
{
	float value = 0.0f;
	switch(i_side)
	{
		case BLOCKSIDE_TOP:
			value = i_block.rect.y;
			break;
		case BLOCKSIDE_RIGHT:
			value = i_block.rect.x + i_block.rect.w;
			break;
		case BLOCKSIDE_BOTTOM:
			value = i_block.rect.y + i_block.rect.h;
			break;
		case BLOCKSIDE_LEFT:
			value = i_block.rect.x;
			break;
	}

	return value;
}

///////////////////////////////////////////////////////////////////////////

bool Game::HasBallCollidedTo(const Block& ball, const Block& block)
{
	bool bottomHitTop = BlockGetSide(ball, BLOCKSIDE_BOTTOM) > BlockGetSide(block, BLOCKSIDE_TOP)
		&& BlockGetSide(ball, BLOCKSIDE_BOTTOM) < BlockGetSide(block, BLOCKSIDE_BOTTOM);
	bool topHitBottom = BlockGetSide(ball, BLOCKSIDE_TOP) < BlockGetSide(block, BLOCKSIDE_BOTTOM)
		&& BlockGetSide(ball, BLOCKSIDE_TOP) > BlockGetSide(block, BLOCKSIDE_TOP);
	bool rightWithtnWidth = BlockGetSide(ball, BLOCKSIDE_RIGHT) > BlockGetSide(block, BLOCKSIDE_LEFT)
		&& BlockGetSide(ball, BLOCKSIDE_RIGHT) < BlockGetSide(block, BLOCKSIDE_RIGHT);
	bool leftWithinWidth = BlockGetSide(ball, BLOCKSIDE_LEFT) < BlockGetSide(block, BLOCKSIDE_RIGHT)
		&& BlockGetSide(ball, BLOCKSIDE_LEFT) > BlockGetSide(block, BLOCKSIDE_LEFT);

	return (bottomHitTop || topHitBottom) && (rightWithtnWidth || leftWithinWidth);
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// TODO(Nacho): Find a better method to pass these callbacks to the engine

///////////////////////////////////////////////////////////////////////////

void SpaceBarPressed(Core::App& myApp)
{
	LOG_TRACE("Game::SpaceBarPressed");
}

///////////////////////////////////////////////////////////////////////////

void RightArrowPressed(Core::App& myApp)
{
	Game* app = (Game*)(&myApp);
	if(app)
	{
		Game::Block& paddle = app->m_blockEntities.at(0);
		paddle.speedX = app->m_paddleSpeed;
	}

	LOG_TRACE("Game::RightArrowPressed");
}

///////////////////////////////////////////////////////////////////////////

void LeftArrowPressed(Core::App& myApp)
{
	Game* app = (Game*)(&myApp);
	if(app)
	{
		Game::Block& paddle = app->m_blockEntities.at(0);
		paddle.speedX = -app->m_paddleSpeed;
	}

	LOG_TRACE("App::LeftArrowPressed ");
}

///////////////////////////////////////////////////////////////////////////

void DirectionReleased(Core::App& myApp)
{
	Game* app = (Game*)(&myApp);
	if(app)
	{
		Game::Block& paddle = app->m_blockEntities.at(0);
		paddle.speedX = 0;
	}

	LOG_TRACE("App::LeftArrowPressed ");
}

///////////////////////////////////////////////////////////////////////////

Core::App* CreateApp()
{
	Core::App::AppContext context =
	{ 
			.appName = "BreakOut",
			.winDimX = 1280,
			.winDimY = 720,
			.inputFNs =
			{
				.fSpaceBarPressed = &SpaceBarPressed,
				.fRightArrowPressed = &RightArrowPressed,
				.fLeftArrowPressed = &LeftArrowPressed,
				.fLeftArrowReleased = &DirectionReleased,
				.fRightArrowReleased = &DirectionReleased
			}
	};
	return new Game(context);
}

///////////////////////////////////////////////////////////////////////////