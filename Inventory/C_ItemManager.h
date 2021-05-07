// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "C_ItemManager.generated.h"

USTRUCT(Blueprintable)
struct F_Inventory
{
	GENERATED_USTRUCT_BODY()


};

USTRUCT(Blueprintable)
struct F_ItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	F_ItemData()
		: itemValue(0)
	{}

	/** Base value of the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int32 itemValue;

	/** Icon to use for Item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	TSoftObjectPtr<UTexture> itemIcon;

};



UCLASS()
class WITCHCRAFT_API AC_ItemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_ItemManager();

	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
	class AC_TimeManager* m_TimeManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
	class AC_RosterManager* m_RosterManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
	class AC_RegionManager* m_RegionManager = nullptr;


protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;


};
