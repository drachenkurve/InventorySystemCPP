﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/InteractiveText_Entry.h"
#include "MyPlayerController.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Internationalization/StringTableRegistry.h"
#include "Inventory/FItemStructure.h"
#include "MyGameInstance.h"

void UInteractiveText_Entry::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (IsValid(NameLabel))
	{
		NameLabel->SetText(FText::FromName("Default Text"));
		
		SelectedImage->SetOpacity(0.f);
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Not Valid")));
	}

	PC = Cast<AMyPlayerController>(GetOwningPlayer());
	if (!IsValid(PC))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Controller Not Valid")));
	}

	GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (!IsValid(GameInstance))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GameInstance Not Valid")));
	}
}

void UInteractiveText_Entry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SelectedImage->SetOpacity(0.f);
	NameLabel->SetText(FText::FromName("Default"));
	
	if (UInteractiveText_Entry* Entry = Cast<UInteractiveText_Entry>(ListItemObject))
	{
		if (IsValid(Entry) && IsValid(PC))
		{
			const UDataTable* DataTable = PC->GetItemDB();
			if (IsValid(DataTable))
			{
				FItemStructure* NewItemData = DataTable->FindRow<FItemStructure>(FName(Entry->ID), "", true);
				if (NewItemData)
				{
					IconImage->SetBrushFromTexture(NewItemData->Icon);
					
					FString ItemName = NewItemData->ID.ToString();
					FName InTableID = GameInstance->COMMON_WORDS;
					FText ItemNameText = FText::FromStringTable(InTableID, ItemName);

					NameLabel->SetText(ItemNameText);
				}
			}		
		}
	}
}

void UInteractiveText_Entry::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	const FLinearColor LinearColor = {1,1,1,1};
}

void UInteractiveText_Entry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
	
	FLinearColor LinearColor;
	
	if (bIsSelected)
	{
		LinearColor = {0.75,0.25,0,1};

		SelectedImage->SetOpacity(1.f);
	}else{
		LinearColor = {1,1,1,0};
		
		SelectedImage->SetOpacity(0.f);
	}
}

void UInteractiveText_Entry::InitializeName(const FName& Name)
{
	ID = Name;
}

FName UInteractiveText_Entry::GetIDName()
{
	return ID;
}