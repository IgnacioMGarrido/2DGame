#include <engine/platform/Logger.h>
#include <engine/App.h>
#include <engine/render/Drawer.h>
#include <engine/EntryPoint.h>

class App : public Core::App
{
public:

	struct Rect
	{
		float xpos;
		float ypos;
		float width;
		float height;
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};
	Rect myRect
	{
		.xpos = 128,
		.ypos = 0,
		.width = 128,
		.height = 32,
		.r = 0,
		.g = 255,
		.b = 0
	};

	App(std::string i_appName = "BreakOut")
		: Core::App(i_appName)
	{
	}

	virtual void Update(float i_fixedTick) override
	{
		myRect.xpos += 0.01f * i_fixedTick;
		LOG_TRACE("MyApp::Update() -> %.1f fps", i_fixedTick);
	}

	virtual void Render() override
	{
		m_drawer->DrawFilledRect(myRect.xpos, myRect.ypos, myRect.width, myRect.height, myRect.r, myRect.g, myRect.b);
		LOG_TRACE("MyApp::Render");
	}
};

Core::App* CreateApp()
{
	return new App();
}
