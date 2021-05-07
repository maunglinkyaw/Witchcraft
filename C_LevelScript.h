// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "C_LevelScript.generated.h"

/**
 * 
 */


UCLASS()
class WITCHCRAFT_API AC_LevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Managers")
	class AC_TimeManager* m_TimeManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Managers")
	class AC_RosterManager* m_RosterManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Managers")
	class AC_RegionManager* m_RegionManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Managers")
	class AC_ItemManager* m_ItemManager = nullptr;


};
