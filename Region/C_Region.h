// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Region.generated.h"

class AC_RegionManager;
class AC_Location;

UCLASS()
class WITCHCRAFT_API AC_Region : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Region();

	UPROPERTY(EditInstanceOnly, Category = "Region")
	TArray<AC_Location*> m_Locations;
	UPROPERTY(EditInstanceOnly, Category = "Region")
	AC_RegionManager* m_RegionManager = nullptr;

	void RegisterLocation(AC_Location* inLocation);

	UFUNCTION(CallInEditor, Category = "Setup")
	void UpdateRegionDetails();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
