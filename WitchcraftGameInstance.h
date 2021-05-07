// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WitchcraftGameInstance.generated.h"

class UC_SystemSave;

UCLASS()
class WITCHCRAFT_API UWitchcraftGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

UPROPERTY(EditDefaultsOnly)
FString m_SystemSaveName = "SystemSaveSlot";
UPROPERTY(VisibleAnywhere)
UC_SystemSave* m_TempSystemSave;
UPROPERTY(VisibleAnywhere)
FString m_SaveSlotToLoad = "TestGameSlot01";

void SaveSystemSave();
void LoadSystemSave();

UFUNCTION()
void OnSaveGameDone(const FString& SlotName, const int32 UserIndex, bool bSuccess);
UFUNCTION()
void OnLoadGameDone(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

UFUNCTION()
TArray<FString> GetAllSaveGameSlotNames();

};
