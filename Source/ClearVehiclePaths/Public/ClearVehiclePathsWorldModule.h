#pragma once

#include "CoreMinimal.h"
#include "Module/GameWorldModule.h"
#include "ClearVehiclePathsWorldModule.generated.h"

/** Native root game world module - registers the chat command on world load */
UCLASS()
class CLEARVEHICLEPATHS_API UClearVehiclePathsWorldModule : public UGameWorldModule
{
	GENERATED_BODY()
public:
	UClearVehiclePathsWorldModule();
};
