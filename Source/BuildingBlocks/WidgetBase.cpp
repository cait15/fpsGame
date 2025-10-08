// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBase.h"
#if WITH_EDITOR
const FText UWidgetBase::GetPaletteCategory()
{
	return NSLOCTEXT("UMG", "CustomPaletteCategory", "Caits's Custom Widgets");
}

#endif
