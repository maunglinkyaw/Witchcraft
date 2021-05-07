#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "F_CommonStructs.h"
#include "C_TimeManager.generated.h"

class UCUI_EventCard;
class UCUI_Calendar;
class UCUI_Gameplay;

UCLASS()
class WITCHCRAFT_API AC_TimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_TimeManager();

	UPROPERTY(VisibleAnywhere, Category = "Date Time")
	F_Date m_CurrentDate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Current Time & Date")
	E_TimeOfDay m_TimeOfDay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Current Time & Date")
	int m_TodayDate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Current Time & Date")
	E_CalendarDay m_TodayDay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Current Time & Date")
	int m_Month;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Current Time & Date")
	E_CalendarSeason m_Season;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Current Time & Date")
	int m_Year;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Current Time & Date")
	int m_YMMDD;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Time & Date")
	F_Date m_CurrentFDate;

	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
	class AC_RosterManager* m_RosterManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
	class AC_ItemManager* m_ItemManager = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup|Managers")
	class AC_RegionManager* m_RegionManager = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Managers")
	float m_4HourTickRate = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
	float m_4HourTickTimer = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
	bool bIsClockRunning;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
	bool bIsAutoRun;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
	bool bStopClock;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UCUI_Gameplay* m_GameplayUI = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UCUI_Calendar* m_CalendarUI = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TArray<UCUI_EventCard*> m_EventCardList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UCUI_EventCard> m_EventCardClass = nullptr;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void RunDayCycle(float deltaTime);

	void InitTimeManager();

	void AddEventCard(E_EventType inEvent, FText inName, int inDays);
	void RearrangeEventList();
	void EventListGoNextDay();

	UFUNCTION(BlueprintCallable)
	void StartTheClock(bool isAutoRun);
	UFUNCTION(BlueprintCallable)
	void StopTheClock();

	void EndClockRun();


	void GoNextTimeOfDay();
	void GoNextDay();
	void GoNextSeason();
	void GoNextYear();

	bool DoWeHaveEvents();
	void RunTodayEvents();

	UFUNCTION()
	F_Date CreateDate(int inDay, int inMonth, int inYear);
	UFUNCTION()
	E_CalendarDay GetDayOfWeek(int day, int month, int year);
};
