// Copyright Epic Games, Inc. All Rights Reserved.

#include "DewulfIgnaceZombieRuntimeModule.h"

#define LOCTEXT_NAMESPACE "FDewulfIgnaceZombieRuntimeModule"

void FDewulfIgnaceZombieRuntimeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory;
	// the exact timing is specified in the .uplugin file per-module
}

void FDewulfIgnaceZombieRuntimeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.
	// For modules that support dynamic reloading, we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDewulfIgnaceZombieRuntimeModule, DewulfIgnaceZombieRuntime)
