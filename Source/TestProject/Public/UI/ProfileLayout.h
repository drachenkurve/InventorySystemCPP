﻿#pragma once

#include "CoreMinimal.h"
#include "SlotLayout.h"
#include "WindowLayout.h"
#include "ProfileLayout.generated.h"

UCLASS()
class TESTPROJECT_API UProfileLayout : public UWindowLayout
{
	GENERATED_BODY()
	
public:
	UProfileLayout();

	virtual void ToggleWindow() override;
	virtual void RefreshWindow() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UUniformGridPanel* EquipmentGridPanel;
	
protected:
	UPROPERTY()
	TArray<USlotLayout*>EquipmentSlotsArray;

private:
	virtual void NativeConstruct() override;
	virtual void CreateChildWidgets() override;
	virtual void InitializeSlots() override;
	virtual void OnButtonQuitClicked() override;
	
	UPROPERTY()
	uint8 NumberOfColumns;
	UPROPERTY()
	uint8 NumberOfRows;
};
