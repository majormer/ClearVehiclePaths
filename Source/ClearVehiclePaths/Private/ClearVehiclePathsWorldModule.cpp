#include "ClearVehiclePathsWorldModule.h"

#include "ClearVehiclePathsCommand.h"

UClearVehiclePathsWorldModule::UClearVehiclePathsWorldModule()
{
	bRootModule = true;
	mChatCommands.Add(AClearVehiclePathsCommand::StaticClass());
}
