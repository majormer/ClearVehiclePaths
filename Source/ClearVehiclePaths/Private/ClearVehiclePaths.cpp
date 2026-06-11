#include "ClearVehiclePaths.h"

IMPLEMENT_MODULE(FClearVehiclePathsModule, ClearVehiclePaths)

DEFINE_LOG_CATEGORY(LogClearVehiclePaths);

void FClearVehiclePathsModule::StartupModule()
{
	UE_LOG(LogClearVehiclePaths, Display, TEXT("ClearVehiclePaths module starting up"));
}

void FClearVehiclePathsModule::ShutdownModule()
{
}
