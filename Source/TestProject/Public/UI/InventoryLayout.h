// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowLayout.h"
#include "InventoryLayout.generated.h"

class USlotLayout;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEMCPP_API UInventoryLayout : public UWindowLayout
{
	GENERATED_BODY()

public:
	UInventoryLayout();

	virtual void ToggleWindow() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UUniformGridPanel* InventoryGridPanel;
	
	UPROPERTY()
	UTexture2D* Background_Slot;
	
	UPROPERTY()
	TArray<USlotLayout*>InventorySlotsArray;
	
private:
	virtual void NativeConstruct() override;
	virtual void InitializeSlots() override;
	virtual void CreateChildWidgets() override;
	virtual void SetIndexToChilds(uint8& IndexStart) override;

	UPROPERTY()
	uint8 NumberOfColumns;
	UPROPERTY()
	uint8 NumberOfRows;
};