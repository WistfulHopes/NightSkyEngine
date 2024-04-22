// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonPreLoadScreen.h"
#include "Misc/App.h"
#include "Modules/ModuleManager.h"
#include "PreLoadScreenManager.h"

#define LOCTEXT_NAMESPACE "FCommonLoadingScreenModule"

class FCommonStartupLoadingScreenModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	bool IsGameModule() const override;

private:
	void OnPreLoadScreenManagerCleanUp();

	TSharedPtr<FCommonPreLoadScreen> PreLoadingScreen;
};


void FCommonStartupLoadingScreenModule::StartupModule()
{
	// No need to load these assets on dedicated servers.
	// Still want to load them in commandlets so cook catches them
	if (!IsRunningDedicatedServer())
	{
		PreLoadingScreen = MakeShared<FCommonPreLoadScreen>();
		PreLoadingScreen->Init();

		if (!GIsEditor && FApp::CanEverRender() && FPreLoadScreenManager::Get())
		{
			FPreLoadScreenManager::Get()->RegisterPreLoadScreen(PreLoadingScreen);
			FPreLoadScreenManager::Get()->OnPreLoadScreenManagerCleanUp.AddRaw(this, &FCommonStartupLoadingScreenModule::OnPreLoadScreenManagerCleanUp);
		}
	}
}

void FCommonStartupLoadingScreenModule::OnPreLoadScreenManagerCleanUp()
{
	//Once the PreLoadScreenManager is cleaning up, we can get rid of all our resources too
	PreLoadingScreen.Reset();
	ShutdownModule();
}

void FCommonStartupLoadingScreenModule::ShutdownModule()
{

}

bool FCommonStartupLoadingScreenModule::IsGameModule() const
{
	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCommonStartupLoadingScreenModule, CommonStartupLoadingScreen)
