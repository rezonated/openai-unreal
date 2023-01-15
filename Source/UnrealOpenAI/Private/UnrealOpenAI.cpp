// Created, maintained by Vanan A. - rezonated @ github.com

#include "UnrealOpenAI.h"

#include "Developer/Settings/Public/ISettingsModule.h"
#include "Config/UnrealOpenAIConfig.h"

#define LOCTEXT_NAMESPACE "FUnrealOpenAIModule"

void FUnrealOpenAIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Open AI - Unreal",
			LOCTEXT("RuntimeSettingsName", "Open AI - Unreal"),
			LOCTEXT("RuntimeSettingsDescription", "Configure the Open AI - Unreal plugin"),
			GetMutableDefault<UUnrealOpenAIConfig>()
		);
	}
}

void FUnrealOpenAIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Open AI - Unreal");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnrealOpenAIModule, UnrealOpenAI)

DEFINE_LOG_CATEGORY(LogTypeOpenAI);