// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "E_CommonEnums.h"
#include "Roster/C_Witch.h"
#include "Kismet/GameplayStatics.h"
#include "C_WitchcraftSave.generated.h"


UCLASS()
class WITCHCRAFT_API UC_WitchcraftSave : public USaveGame
{
	GENERATED_BODY()
public:
	UC_WitchcraftSave();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString m_PlayerName;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString m_SlotName;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 m_UserIndex;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TMap<FName, F_WitchStats> m_WitchStatsMap;

};
