// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryLayout.h"

#include "FWidgetsLayoutBP.h"
#include "UI/SlotLayout.h"
#include "MyHUD.h"
#include "MyPlayerController.h"
#include "Components/InventoryManagerComponent.h"
#include "Components/UniformGridPanel.h"
#include "Internationalization/StringTableRegistry.h"

UInventoryLayout::UInventoryLayout()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> ObjectFind(TEXT("/Game/UI/Textures/T_UI_Slot"));
	Background_Slot = ObjectFind.Object;
}

void UInventoryLayout::NativeConstruct()
{
	Super::NativeConstruct();

	FText Text = LOCTABLE(COMMON_WORDS, "INVENTORYKey");
	Super::SetTitleToWindow(Text);

	/* TODO: This info needs to be Inventory Manager Component */
	NumberOfRows = 7;
	NumberOfColumns = 4;
	/**/

	if (IsValid(PlayerController))
	{
		InitializeSlots();
	}
}

void UInventoryLayout::InitializeSlots()
{
	CreateChildWidgets();
	uint8 FirstIndex = (uint8)EEquipmentSlot::Count;
	SetIndexToChilds(FirstIndex);
}

void UInventoryLayout::CreateChildWidgets()
{
	FWidgetsLayoutBP* WidgetLayout = Cast<AMyHUD>(PlayerController->MyHUD)->GetWidgetBPClass("SlotLayout_WBP");
	if (WidgetLayout)
	{
		USlotLayout* W_InventorySlot = nullptr;
		
		for(int i = 0; i < NumberOfRows; i++)
		{
			for(int j = 0; j < NumberOfColumns; j++)
			{
				W_InventorySlot = CreateWidget<USlotLayout>(GetWorld(), WidgetLayout->Widget);
				InventoryGridPanel->AddChildToUniformGrid(W_InventorySlot, i, j);
			
				InventorySlotsArray.Add(W_InventorySlot);
			}
		}
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("WBP_SlotLayout cannot load class" ))
	}
}

void UInventoryLayout::SetIndexToChilds(uint8& IndexStart)
{
	const FSlotStructure SlotStructure = PlayerController->InventoryManagerComponent->GetEmptySlot(EEquipmentSlot::Undefined);
	
	for(int i = 0; i < InventorySlotsArray.Num(); i++)
	{
		InventorySlotsArray[i]->UpdateSlot(SlotStructure);
		InventorySlotsArray[i]->InventorySlotIndex = IndexStart;
		InventorySlotsArray[i]->NativeFromInventory = true;
		
		IndexStart++;
	}
}

void UInventoryLayout::ToggleWindow()
{
	Super::ToggleWindow();
}