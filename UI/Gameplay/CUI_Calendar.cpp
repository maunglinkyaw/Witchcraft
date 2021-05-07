// Lin & Yin's Witchcraft 2020


#include "CUI_Calendar.h"
#include "Button.h"
#include "TextBlock.h"
#include "Image.h"
#include "WidgetSwitcher.h"
#include "HorizontalBox.h"
#include "TimeEvents/C_TimeManager.h"


void UCUI_Calendar::InitCalendarWidget(AC_TimeManager* timeManager)
{
	m_TimeManager = timeManager;
}

void UCUI_Calendar::StartTheClock(bool isAutoRun)
{
	if (m_TimeManager)
	{
		m_TimeManager->StartTheClock(isAutoRun);
	}

	StopButton->SetIsEnabled(true);
	StopButtonText->SetText(FText::FromString("Stop"));

	if (ButtonSwitcher)
	{
		ButtonSwitcher->SetActiveWidget(StopBox);
	}
}

void UCUI_Calendar::StopTheClock()
{
	if (m_TimeManager)
	{
		m_TimeManager->StopTheClock();
	}

	StopButton->SetIsEnabled(false);
	StopButtonText->SetText(FText::FromString("Stopping"));
}

void UCUI_Calendar::ToggleButtonSwitcher(int newIndex)
{
	if (ButtonSwitcher)
	{
		ButtonSwitcher->SetActiveWidgetIndex(newIndex);
	}
}



void UCUI_Calendar::GoNextDay(F_Date newDate)
{
	UpdateTimeOfDay(E_TimeOfDay::DAWN);
	SetDateTo(newDate);
}

void UCUI_Calendar::SetDateTo(F_Date newDate)
{
	FText inText;
	if (DateText)
	{
		inText = FText::AsNumber(newDate.date);
		DateText->SetText(inText);
	}
	if (MonthText)
	{
		inText = FText::AsNumber(newDate.month);
		MonthText->SetText(inText);
	}
	if (YearText)
	{
		inText = FText::AsNumber(newDate.year);
		YearText->SetText(inText);
	}

	if (DayText)
	{
		inText = FText::FromString(DayAsString(newDate.day));
		DayText->SetText(inText);
	}

	UpdateTimeOfDay(newDate.timeOfDay);
}

void UCUI_Calendar::UpdateTimeOfDay(E_TimeOfDay newTime)
{
	if (WheelImage)
	{
		switch (newTime)
		{
		case E_TimeOfDay::DAWN:
		{
			WheelImage->SetColorAndOpacity(FLinearColor::Gray);
		}
		break;

		case E_TimeOfDay::MORNING:
		{
			WheelImage->SetColorAndOpacity(FLinearColor::White);
		}
		break;

		case E_TimeOfDay::AFTERNOON:
		{
			WheelImage->SetColorAndOpacity(FLinearColor::Green);
		}
		break;

		case E_TimeOfDay::EVENING:
		{
			WheelImage->SetColorAndOpacity(FLinearColor::Red);
		}
		break;

		case E_TimeOfDay::NIGHT:
		{
			WheelImage->SetColorAndOpacity(FLinearColor::Blue);
		}
		break;

		case E_TimeOfDay::WITCHINGHOUR:
		{
			WheelImage->SetColorAndOpacity(FLinearColor::Black);
		}
		break;

		};
	}

}
