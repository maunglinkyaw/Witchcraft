// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "C_Location.generated.h"


USTRUCT(Blueprintable)
struct F_ActivityNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 level;

	F_ActivityNode()
	{
		level = 0;
	}
};

class AC_Region;

UCLASS()
class WITCHCRAFT_API AC_Location : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Location();

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* m_StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* m_LabelWidget;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	AC_Region* m_Region = nullptr;

	UFUNCTION(CallInEditor, Category = "Setup")
	void UpdateLocationDetails();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	FName m_Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	FText m_DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TSoftObjectPtr<UTexture2D> m_DisplayImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	FGameplayTagContainer m_GameplayTags;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TArray<F_ActivityNode> m_ActivityNodes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	int32 m_ActivitySlots = 2;

protected:
	virtual void BeginPlay() override;

	void RegisterToRegion();
	
	virtual void ShowLocationUI();
	
	bool SearchGameplayTag(FName inTag);

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnSelected(UPrimitiveComponent* component, FKey ButtonPressed);

};
