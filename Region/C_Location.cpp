// Lin & Yin's Witchcraft 2020


#include "C_Location.h"
#include "C_Region.h"
#include "C_RegionManager.h"
#include "Witchcraft.h"
#include "C_WitchcraftStatics.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

#include "UI/Gameplay/CUI_WorldLabel.h"

AC_Location::AC_Location()
{
	PrimaryActorTick.bCanEverTick = false;
	
	m_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_StaticMesh"));
	SetRootComponent(m_StaticMesh);
	
	m_StaticMesh->OnClicked.AddUniqueDynamic(this, &AC_Location::OnSelected);

	m_LabelWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("m_LabelWidget"));
	m_LabelWidget->SetupAttachment(RootComponent);
	m_LabelWidget->RegisterComponent();
	m_LabelWidget->SetRelativeLocationAndRotation(FVector(-100.f, 0.f, 15.f), FRotator(90.f, 180.f, 0.f));

	m_LabelWidget->OnClicked.AddUniqueDynamic(this, &AC_Location::OnSelected);
}

void AC_Location::OnConstruction(const FTransform& Transform)
{
// 	UCUI_WorldLabel* tempLabel = Cast<UCUI_WorldLabel>(m_LabelWidget->GetUserWidgetObject());
// 
// 	UE_LOG(LogSystem, Display, TEXT("%s - OnConstruction - tempLabel: %s"), *GetName(), *GetNameSafe(tempLabel));
// 
// 	if (tempLabel)
// 	{
// 		if (!m_DisplayName.IsEmptyOrWhitespace())
// 			tempLabel->UpdateLabelName(m_DisplayName);
// 	}
}

void AC_Location::UpdateLocationDetails()
{
	UE_LOG(LogSystem, Display, TEXT("%s - UpdateLocationDetails"), *GetName());

// 	UCUI_WorldLabel* tempLabel = Cast<UCUI_WorldLabel>(m_LabelWidget->GetUserWidgetObject());
// 	UE_LOG(LogSystem, Display, TEXT("%s - UpdateLocationDetails - tempLabel: %s"), *GetName(), *GetNameSafe(tempLabel));

	if (UCUI_WorldLabel* tempLabel = Cast<UCUI_WorldLabel>(m_LabelWidget->GetUserWidgetObject()))
	{
		if (!m_DisplayName.IsEmptyOrWhitespace())
			tempLabel->UpdateLabelName(m_DisplayName);
	}
}

void AC_Location::BeginPlay()
{
	Super::BeginPlay();
	
	if (!m_Region)
		UE_LOG(LogSystem, Error, TEXT("%s - BeginPlay - NO REGION ASSIGNED"), *GetName());

	if (UCUI_WorldLabel* tempLabel = Cast<UCUI_WorldLabel>(m_LabelWidget->GetUserWidgetObject()))
	{
		if (!m_DisplayName.IsEmptyOrWhitespace())
			tempLabel->UpdateLabelName(m_DisplayName);
	}
}

void AC_Location::RegisterToRegion()
{
	if (m_Region)
	{
		m_Region->RegisterLocation(this);
	}
	else
	{
		UE_LOG(LogSystem, Error, TEXT("%s - RegisterToRegion - NO REGION ASSIGNED"), *GetName());
	}
}

void AC_Location::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Location::OnSelected(UPrimitiveComponent* component, FKey ButtonPressed)
{
	UE_LOG(LogSystem, Display, TEXT("%s - OnSelected - Target: %s"), *GetName(), *GetNameSafe(component));
	
	ShowLocationUI();

// 	if (m_LabelUI)
// 		m_LabelUI->TestFunction();
}

void AC_Location::ShowLocationUI()
{
	if (AC_RegionManager* regionManager = UC_WitchcraftStatics::GetRegionManager(GetWorld()))
	{
		regionManager->ShowLocationMenu(this);
	}
}


bool AC_Location::SearchGameplayTag(FName inTag)
{
	FGameplayTag tempTag = FGameplayTag::RequestGameplayTag(inTag);

	return m_GameplayTags.HasTag(tempTag);

	// 	for (const TPair<FGameplayTag, F_WitchStats>& pair : m_GameplaySessionData.witchTagMap)
	// 	{
	// 		// 		pair.Key;
	// 		// 		pair.Value;
	// 
	// 		FString tagString = pair.Key.ToString();
	// 		UE_LOG(LogSystem, Display, TEXT("%s - InitCurrentGameplaySession - gameplayTag: %s"), *GetName(), *tagString);
	// 
	// 		FGameplayTag tempTag = FGameplayTag::RequestGameplayTag(FName("Witch"));
	// 
	// 		if (pair.Key.MatchesTag(tempTag))
	// 		{
	// 			UE_LOG(LogSystem, Display, TEXT("%s - InitCurrentGameplaySession - Matches Tag: %s"), *GetName(), *tempTag.ToString());
	// 		}
	// 	}
}
