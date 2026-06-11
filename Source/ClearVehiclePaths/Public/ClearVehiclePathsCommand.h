#pragma once

#include "CoreMinimal.h"
#include "Command/ChatCommandInstance.h"
#include "ClearVehiclePathsCommand.generated.h"

class AFGVehiclePathSegment;

/**
 * /clearvehiclepaths [legacy|all|count]
 *
 * legacy (default) - dismantles only path segments converted from the pre-1.2 recorded
 *                    vehicle paths (mIsLegacyPath). Newly drawn 1.2 paths are untouched.
 * all              - dismantles every vehicle path segment and standalone path node.
 * count            - dry run, reports how many segments would be removed.
 *
 * Path nodes are cleaned up automatically by the game when their last segment is
 * removed; the vehicle subsystem rebuilds path networks and sanitizes vehicle route
 * tables on its own after the dismantle.
 */
UCLASS()
class CLEARVEHICLEPATHS_API AClearVehiclePathsCommand : public AChatCommandInstance
{
	GENERATED_BODY()
public:
	AClearVehiclePathsCommand();

	EExecutionStatus ExecuteCommand_Implementation(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label) override;

private:
	/** Reads the protected AFGVehiclePathSegment::mIsLegacyPath flag via reflection */
	static bool IsLegacyPathSegment(const AFGVehiclePathSegment* PathSegment);
};
