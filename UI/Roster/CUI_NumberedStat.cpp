// Lin & Yin's Witchcraft 2020


#include "CUI_NumberedStat.h"

#include "TextBlock.h"

void UCUI_NumberedStat::SetStat(int32 inStat)
{
	StatNum->SetText(FText::FromString(FString::FromInt(inStat)));
}

void UCUI_NumberedStat::SetProgress(float newProgress)
{

}
