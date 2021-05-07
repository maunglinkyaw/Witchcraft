// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "E_CommonEnums.h"
#include "C_RosterManager.generated.h"

class AC_Witch;

UCLASS()
class WITCHCRAFT_API AC_RosterManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_RosterManager();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TMap<FName, TSubclassOf<AC_Witch>> m_WitchClassMap;
	
	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
		class AC_TimeManager* m_TimeManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
		class AC_ItemManager* m_ItemManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
		class AC_RegionManager* m_RegionManager = nullptr;

	// Map of ALL witches possible in the game.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roster")
	TMap<FName, AC_Witch*> m_AllWitchMap;
	// Map of the witches currently in player's roster.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roster")
	TMap<FName, AC_Witch*> m_WitchRoster;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roster")
	TArray<AC_Witch*> m_WitchesArray;
	
	UPROPERTY()
	class UCUI_RosterMenu* m_RosterMenu = nullptr;

	void InitRosterManager();

	void AddWitchToRoster(FName witchName);

	AC_Witch* GetWitchByName(FName witchName);

	TArray<AC_Witch*> GetWitchesArray();

	void ShowWitchDetails(FName witchName);

protected:
	virtual void BeginPlay() override;
	

	void SpawnAllWitches();
	AC_Witch* SpawnWitch(FName witchName);

public:	
	virtual void Tick(float DeltaTime) override;


};
