// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_RegionManager.generated.h"

class AC_Region;
class AC_Location;

UCLASS()
class WITCHCRAFT_API AC_RegionManager : public AActor
{
	GENERATED_BODY()
public:	
	AC_RegionManager();

	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
	class AC_TimeManager* m_TimeManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
	class AC_RosterManager* m_RosterManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
	class AC_ItemManager* m_ItemManager = nullptr;
	
	UPROPERTY()
	class UCUI_RegionMenu* m_RegionMenu = nullptr;

	void InitRegionManager();

	void ShowLocationMenu(AC_Location* inLocation);

	void AddEventToCalendar();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
