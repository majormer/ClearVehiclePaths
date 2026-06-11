#include "ClearVehiclePathsCommand.h"

#include "ClearVehiclePaths.h"
#include "Command/CommandSender.h"
#include "EngineUtils.h"
#include "FGDismantleInterface.h"
#include "WheeledVehicles/FGStandaloneVehiclePathNode.h"
#include "WheeledVehicles/FGVehiclePathSegment.h"

AClearVehiclePathsCommand::AClearVehiclePathsCommand()
{
	CommandName = TEXT("clearvehiclepaths");
	Aliases.Add(TEXT("cvp"));
	Usage = NSLOCTEXT("ClearVehiclePaths", "CommandUsage",
		"/clearvehiclepaths [legacy|all|count] - dismantle vehicle paths map-wide (default: legacy paths converted from pre-1.2 saves only)");
	MinNumberOfArguments = 0;
}

bool AClearVehiclePathsCommand::IsLegacyPathSegment(const AFGVehiclePathSegment* PathSegment)
{
	static const FBoolProperty* LegacyPathProperty =
		FindFProperty<FBoolProperty>(AFGVehiclePathSegment::StaticClass(), TEXT("mIsLegacyPath"));
	return LegacyPathProperty && LegacyPathProperty->GetPropertyValue_InContainer(PathSegment);
}

EExecutionStatus AClearVehiclePathsCommand::ExecuteCommand_Implementation(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
	UWorld* World = GetWorld();
	if (!World || !HasAuthority())
	{
		Sender->SendChatMessage(TEXT("This command can only run on the server/host."), FLinearColor::Red);
		return EExecutionStatus::UNCOMPLETED;
	}

	const FString Mode = Arguments.Num() > 0 ? Arguments[0].ToLower() : TEXT("legacy");
	if (Mode != TEXT("legacy") && Mode != TEXT("all") && Mode != TEXT("count"))
	{
		PrintCommandUsage(Sender);
		return EExecutionStatus::BAD_ARGUMENTS;
	}
	const bool bLegacyOnly = Mode != TEXT("all");

	// Collect first, dismantle after - dismantling mutates the actor list and node graph
	TArray<AFGVehiclePathSegment*> SegmentsToRemove;
	int32 TotalSegments = 0;
	for (TActorIterator<AFGVehiclePathSegment> It(World); It; ++It)
	{
		TotalSegments++;
		if (!bLegacyOnly || IsLegacyPathSegment(*It))
		{
			SegmentsToRemove.Add(*It);
		}
	}

	if (Mode == TEXT("count"))
	{
		Sender->SendChatMessage(FString::Printf(
			TEXT("Vehicle path segments: %d total, %d legacy (pre-1.2). '/%s legacy' or '/%s all' to dismantle."),
			TotalSegments, SegmentsToRemove.Num(), *Label, *Label));
		return EExecutionStatus::COMPLETED;
	}

	int32 RemovedSegments = 0;
	for (AFGVehiclePathSegment* Segment : SegmentsToRemove)
	{
		if (IsValid(Segment))
		{
			IFGDismantleInterface::Execute_Dismantle(Segment);
			RemovedSegments++;
		}
	}

	// Plain path nodes clean themselves up when their last segment goes away; standalone
	// (player-placed) nodes are persistent, so 'all' sweeps them explicitly afterwards.
	int32 RemovedNodes = 0;
	if (!bLegacyOnly)
	{
		TArray<AFGStandaloneVehiclePathNode*> NodesToRemove;
		for (TActorIterator<AFGStandaloneVehiclePathNode> It(World); It; ++It)
		{
			NodesToRemove.Add(*It);
		}
		for (AFGStandaloneVehiclePathNode* Node : NodesToRemove)
		{
			if (IsValid(Node))
			{
				IFGDismantleInterface::Execute_Dismantle(Node);
				RemovedNodes++;
			}
		}
	}

	UE_LOG(LogClearVehiclePaths, Display, TEXT("%s dismantled %d/%d vehicle path segments (mode=%s) and %d standalone nodes"),
		*Sender->GetSenderName(), RemovedSegments, TotalSegments, *Mode, RemovedNodes);
	Sender->SendChatMessage(FString::Printf(
		TEXT("Dismantled %d vehicle path segment(s)%s. Vehicles that used them will need new paths."),
		RemovedSegments,
		bLegacyOnly ? TEXT(" (legacy only)") : *FString::Printf(TEXT(" and %d standalone node(s)"), RemovedNodes)));
	return EExecutionStatus::COMPLETED;
}
