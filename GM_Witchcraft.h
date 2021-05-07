#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Roster/C_Witch.h"
#include "GM_Witchcraft.generated.h"

class UCUI_Gameplay;
class UC_WitchcraftSave;

USTRUCT(Blueprintable)
struct F_GameplaySessionData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString playerName;
	UPROPERTY(EditAnywhere)
	TMap<FName, F_WitchStats> witchStatsMap;
	//TMap<E_Witch, F_WitchStats> witchStatsMap;
// 	UPROPERTY(EditAnywhere, meta = (Categories = "Witch"))
// 	TMap<FGameplayTag, F_WitchStats> witchTagMap;

	F_GameplaySessionData()
	{

	}
};


UCLASS()
class WITCHCRAFT_API AGM_Witchcraft : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_Witchcraft();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool m_UseDebugData = true;
	UPROPERTY(EditAnywhere, Category = "Debug")
	F_GameplaySessionData m_GameplaySessionData;
	UPROPERTY(VisibleAnywhere, Category = "Debug")
	FString m_SaveGameName;
	UPROPERTY(VisibleAnywhere, Category = "Debug")
	UC_WitchcraftSave* m_CurrentSaveGame;

	UPROPERTY(VisibleAnywhere, Category = "Managers")
	class AC_LevelScript* m_LevelScript = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Managers")
	class AC_TimeManager* m_TimeManager = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Managers")
	class AC_RosterManager* m_RosterManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Managers")
	class AC_RegionManager* m_RegionManager;

	UPROPERTY(VisibleAnywhere, Category = "Managers")
	class UWitchcraftGameInstance* m_GameInstance = nullptr;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCUI_Gameplay> m_GameplayUIClass = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UCUI_Gameplay* m_GameplayUI = nullptr;


	UCUI_Gameplay* GetGameplayUI();

	void SaveGame();
	void LoadGame(FString slotName);

	UFUNCTION()
	void OnSaveGameDone(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	UFUNCTION()
	void OnLoadGameDone(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

protected:
	void InitCurrentGameplaySession();
	void SearchGameplayTag();
};
