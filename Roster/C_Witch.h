// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Witchcraft/E_CommonEnums.h"
#include "GameplayTagContainer.h"
#include "C_Witch.generated.h"

UENUM(Blueprintable)
enum class E_WitchAction : uint8
{
	NO_ACTION = 0			UMETA(DisplayName = "No Action"),
	RESTING					UMETA(DisplayName = "Resting"),
	BREWING					UMETA(DisplayName = "Brewing"),
	TRAVELING				UMETA(DisplayName = "Traveling"),
	SUPERVISING				UMETA(DisplayName = "Supervising"),
};

UENUM(Blueprintable)
enum class E_WitchSkill : uint8
{
	BREWING					UMETA(DisplayName = "Brewing"),
	ARCANOLOGY				UMETA(DisplayName = "Arcanology"),
	LORE					UMETA(DisplayName = "Lore"),
	DIPLOMACY				UMETA(DisplayName = "Diplomacy"),
	MANAGEMENT				UMETA(DisplayName = "Management"),
	COMBAT					UMETA(DisplayName = "Combat"),
	SURVIVAL				UMETA(DisplayName = "Survival"),
};


USTRUCT(Blueprintable)
struct F_WitchAction
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_WitchAction currentAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_MapRegion startLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_MapRegion targetLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 totalDays;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentDays;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName eventName;

	F_WitchAction()
	{

	}
};

USTRUCT(Blueprintable)
struct F_WitchSkill
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 rank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 growth;

	F_WitchSkill()
	{
		rank = 0;
		growth = 0;
	}

	F_WitchSkill(int32 inRank)
	{
		rank = inRank;
		growth = 0;
	}

	void AddGrowth(int32 inGrowth)
	{
		growth += inGrowth;
		
		if (CanRankUp() >= 0)
		{
			rank++;
			growth = CanRankUp();
		}
	}

	// if return is negative means NO.
	// if return is 0 or positive means YES.
	int32 CanRankUp()
	{
		int32 growthNeeded = 1000;

		switch (rank)
		{
		default:
			return -1;
			break;

		case 1:
			growthNeeded = 20;
			break;
		case 2:
			growthNeeded = 60;
			break;
		case 3:
			growthNeeded = 120;
			break;
		case 4:
			growthNeeded = 200;
			break;
		case 5:
			growthNeeded = 360;
			break;
		case 6:
			growthNeeded = 400;
			break;
		}

		return (growth - growthNeeded);
	}
};

// These data are meant to be the "changeable" stats. The one that will change as the game goes on. And is stored in the Save file.
USTRUCT(Blueprintable)
struct F_WitchStats
{
	GENERATED_USTRUCT_BODY()

	// Base Characteristics
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats")
	int32 alignment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats")
	TArray<int32> witchBonds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats|Skills")
		F_WitchSkill brewing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats|Skills")
		F_WitchSkill arcanology;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats|Skills")
		F_WitchSkill lore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats|Skills")
		F_WitchSkill diplomacy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats|Skills")
		F_WitchSkill management;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats|Skills")
		F_WitchSkill combat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats|Skills")
		F_WitchSkill survival;

	// Transient Characteristics (actions, locations, energy)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats")
		int32 moodLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats")
		E_MapRegion currentLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Witch Stats")
		F_WitchAction currentAction;

	F_WitchStats()
	{

	}
};


// These are meant to be the base data & static data.
// Base data = stats and so that the Witch starts with.
// Static data = data that will never change.
USTRUCT(Blueprintable)
struct F_WitchStaticData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName witchName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText displayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UTexture2D> smallPortrait = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UTexture2D> largePortrait = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText biography;

	F_WitchStaticData()
	{

	}
};


UCLASS()
class WITCHCRAFT_API AC_Witch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Witch();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	FGameplayTagContainer m_GameplayTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	UDataTable* m_WitchDataTable = nullptr;

	UPROPERTY(EditAnywhere, Category = "Character")
	F_WitchStaticData m_StaticData;
	UPROPERTY(EditAnywhere, Category = "Character")
	F_WitchStats m_WitchStats;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	bool m_HasInitStats = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetWitchStatsStruct(F_WitchStats statsStruct);
	void ToggleMapActivation(bool isActive);

	void AddStatsGrowth(E_WitchSkill skillStat, int32 inGrowth);

	F_WitchStaticData GetWitchStaticData();

};
