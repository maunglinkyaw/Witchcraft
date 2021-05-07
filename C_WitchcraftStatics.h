// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "E_CommonEnums.h"
#include "C_WitchcraftStatics.generated.h"

class AC_PlayerController;
class AC_RegionManager;
class AC_RosterManager;
class AC_TimeManager;

UCLASS()
class WITCHCRAFT_API UC_WitchcraftStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Names")
	static FName GetWitchName(E_Witch witchEnum);

	UFUNCTION(BlueprintCallable, Category = "System Tools")
	static AC_PlayerController* GetPlayerController(UWorld* inWorld);
	UFUNCTION(BlueprintCallable, Category = "System Tools")
	static AC_RegionManager* GetRegionManager(UWorld* inWorld);
	UFUNCTION(BlueprintCallable, Category = "System Tools")
	static AC_RosterManager* GetRosterManager(UWorld* inWorld);
	UFUNCTION(BlueprintCallable, Category = "System Tools")
	static AC_TimeManager* GetTimeManager(UWorld* inWorld);
	UFUNCTION(BlueprintCallable, Category = "System Tools")
	static AC_ItemManager* GetItemManager(UWorld* inWorld);

};
