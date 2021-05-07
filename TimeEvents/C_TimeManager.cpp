// Lin & Yin's Witchcraft 2020

#include "C_TimeManager.h"
#include "UI/Gameplay/CUI_Gameplay.h"
#include "UI/Gameplay/CUI_Calendar.h"
#include "UI/Gameplay/CUI_EventCard.h"
#include "Image.h"
#include "ScrollBox.h"
#include "PanelSlot.h"
#include "ScrollBoxSlot.h"
#include "WidgetSwitcher.h"
#include "ConstructorHelpers.h"

AC_TimeManager::AC_TimeManager()
{
	PrimaryActorTick.bCanEverTick = true;

	m_CurrentFDate = F_Date(1, 1, 1, 0);
	m_TodayDate = 1;
	m_TodayDay = E_CalendarDay::MONDAY;
	m_Month = 1;
	m_Season = E_CalendarSeason::SPRING;
	m_Year = 1;
	m_YMMDD = 10101;

// 	ConstructorHelpers::FClassFinder<UCUI_EventCard>eventClass(TEXT("/Game/UI/Calendar/CUI_EventCard_BP"));
// 	m_EventCardClass = eventClass.Class;  
}

void AC_TimeManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_TimeManager::InitTimeManager()
{
	if (m_CalendarUI)
	{
		m_CalendarUI->InitCalendarWidget(this);
		m_CalendarUI->SetDateTo(m_CurrentFDate);
	}

	AddEventCard(E_EventType::BREWING, FText::FromString("Red Potion"), 1);
	AddEventCard(E_EventType::BREWING, FText::FromString("Red Cheesecake"), 1);
	AddEventCard(E_EventType::QUEST, FText::FromString("Deliver: Red Potion"), 10);
	AddEventCard(E_EventType::BREWING, FText::FromString("Aqua Fortis"), 7);
	AddEventCard(E_EventType::QUEST, FText::FromString("Lirililia"), 3);
}

void AC_TimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsClockRunning)
	{
		RunDayCycle(DeltaTime);
	}

}

void AC_TimeManager::RunDayCycle(float deltaTime)
{
	m_4HourTickTimer += deltaTime;
	if (m_4HourTickTimer >= m_4HourTickRate)
	{
		m_4HourTickTimer = 0.f;

		int newTime = (int)m_TimeOfDay;
		newTime++;

		if (newTime > 5)
		{
			m_TimeOfDay = E_TimeOfDay::DAWN;
			GoNextDay();
		}
		else
		{
			m_TimeOfDay = E_TimeOfDay(newTime);
			GoNextTimeOfDay();
		}
	}
}




void AC_TimeManager::StartTheClock(bool isAutoRun)
{
	bIsClockRunning = true;
	bStopClock = false;
	bIsAutoRun = isAutoRun;
}

void AC_TimeManager::StopTheClock()
{
	bStopClock = true;
}

void AC_TimeManager::EndClockRun()
{
	bIsClockRunning = false;
	m_4HourTickTimer = 0.f;

	if (m_CalendarUI)
	{
		m_CalendarUI->ToggleButtonSwitcher(0);
	}
}


void AC_TimeManager::AddEventCard(E_EventType inEvent, FText inName, int inDays)
{
	if (m_EventCardClass && m_CalendarUI && m_CalendarUI->EventScrollBox)
	{
		UCUI_EventCard* tempCard = CreateWidget<UCUI_EventCard>(GetWorld(), m_EventCardClass);

		if (tempCard)
		{
			tempCard->InitEventCard(inEvent, inName, inDays);
			m_EventCardList.AddUnique(tempCard);

			RearrangeEventList();
		}
	}
}

void AC_TimeManager::RearrangeEventList()
{
	m_EventCardList.Sort([](const UCUI_EventCard& A, const UCUI_EventCard& B)
		{
			return A.m_RemainingDays < B.m_RemainingDays;
		});

	m_CalendarUI->EventScrollBox->ClearChildren();

	for (int i = 0; i < m_EventCardList.Num(); i++)
	{
		m_CalendarUI->EventScrollBox->AddChild(m_EventCardList[i]);
		if (!m_EventCardList[i]->bHasOpened)
		{
			m_EventCardList[i]->OpenEventCard();
		}
	}

	//m_CalendarWidget->EventScrollBox->ShiftChild(oldIndex, newIndex);
}

void AC_TimeManager::EventListGoNextDay()
{
	if (m_CalendarUI && m_CalendarUI->EventScrollBox)
	{
		for (int i = m_EventCardList.Num() - 1; i > -1; i--)
		{
			m_EventCardList[i]->AddOneDay();

			if (m_EventCardList[i]->m_RemainingDays == 0)
			{
				m_EventCardList[i]->CloseEventCard();
				m_EventCardList.RemoveAt(i);
			}
		}
	}
}


void AC_TimeManager::GoNextTimeOfDay()
{
	// Do next time of day stuff
	if (m_CalendarUI)
	{
		m_CalendarUI->UpdateTimeOfDay(m_TimeOfDay);
	}
}

void AC_TimeManager::GoNextDay()
{
	bool isNewSeason = false;
	bool isNewYear = false;

	// Add one day to the Date
	m_TodayDate++;

	// Did we cross into a new month?
	if (m_TodayDate > 30)
	{
		m_TodayDate = 1;
		m_Month++;

		// Did we cross into a new season?
		if (m_Month % 3 == 1)
		{
			int seasonIndex = (int)m_Season;
			seasonIndex++;
			if (seasonIndex > 3)
			{
				seasonIndex = 0;
			}
			m_Season = E_CalendarSeason(seasonIndex);

			isNewSeason = true;
		}

		// Did we cross into a new year?
		if (m_Month > 12)
		{
			m_Year++;
			m_Month = 1;

			isNewYear = true;
		}
	}

	// Find the new Day.
	m_TodayDay = GetDayOfWeek(m_TodayDate, m_Month, m_Year);

	m_YMMDD = m_Year * 10000 + m_Month * 100 + m_TodayDate;

	m_CurrentFDate.date = m_TodayDate;
	m_CurrentFDate.day = m_TodayDay;
	m_CurrentFDate.month = m_Month;
	m_CurrentFDate.season = m_Season;
	m_CurrentFDate.year = m_Year;
	m_CurrentFDate.ymmdd = m_YMMDD;

	// Update the Calendar Widget for new day
	if (m_CalendarUI)
	{
		m_CalendarUI->GoNextDay(m_CurrentFDate);
	}

	// Now do we have any new year or season?
	if (isNewYear)
	{
		GoNextYear();
	}
	else if (isNewSeason)
	{
		GoNextSeason();
	}

	// add one day to the events list.
	EventListGoNextDay();

	// now check the EventsManager for any new events.

	// if yes, we stop the clock and run them.
	if (DoWeHaveEvents())
	{
		EndClockRun();
		RunTodayEvents();
	}
	// if no, we only stop if it's not set to autorun.
	else if (!bIsAutoRun || bStopClock)
	{
		EndClockRun();
	}
}



void AC_TimeManager::GoNextSeason()
{

}

void AC_TimeManager::GoNextYear()
{

}

bool AC_TimeManager::DoWeHaveEvents()
{

	return false;
}

void AC_TimeManager::RunTodayEvents()
{

}


F_Date AC_TimeManager::CreateDate(int inDay, int inMonth, int inYear)
{
	F_Date newDate = F_Date();
	newDate.date = inDay;
	newDate.month = inMonth;
	newDate.year = inYear;
	newDate.day = GetDayOfWeek(inDay, inMonth, inYear);
	newDate.ymmdd = (inYear * 10000) + (inMonth * 100) + inDay;

	return newDate;
}

E_CalendarDay AC_TimeManager::GetDayOfWeek(int day, int month, int year)
{
	int totalDays = day - 1; // First day of game will be Monday
	totalDays += (month - 1) * 30;
	totalDays += (year - 1) * 360;

	return E_CalendarDay(totalDays % 7);
}
