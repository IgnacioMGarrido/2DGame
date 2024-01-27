#include <engine/Logger.h>
#include <engine/App.h>
#include <engine/EntryPoint.h>

class App : public Core::App
{
public:
	App(std::string i_appName = "MyApp")
		: Core::App(i_appName)
	{

	}

	virtual void Update() override
	{
		LOG_TRACE("MyApp::Update()");
	}
};

Core::App* CreateApp()
{
	return new App();
}
