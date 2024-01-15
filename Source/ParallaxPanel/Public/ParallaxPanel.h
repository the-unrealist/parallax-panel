// Copyright (c) 2024 citrus - https://unrealist.org
// Licensed under the MIT License.

#pragma once

#include "Components/PanelWidget.h"

#include "ParallaxPanel.generated.h"

/**
 * Allows widgets to be stacked on top of each other and translated based on the current offset of the panel and the
 * distance of each child widget.
 */
UCLASS(MinimalAPI)
class UParallaxPanel : public UPanelWidget
{
    GENERATED_BODY()

public:
    UParallaxPanel();

#if WITH_EDITOR
    virtual const FText GetPaletteCategory() override;
#endif

    /** Adds a child to this panel. */
    UFUNCTION(BlueprintCallable, Category="Widget")
    class UParallaxPanelSlot* AddChildToParallaxPanel(UWidget* Content);

    /** Sets the offset. This will translate all child widgets based on their distance. */
    UFUNCTION(BlueprintCallable, Category="Parallax Panel")
    void SetOffset(FVector2D InOffset);

    /** Gets the current parallax perspective. */
    FVector2D GetOffset() const;

protected:
    virtual UClass* GetSlotClass() const override;
    virtual void OnSlotAdded(UPanelSlot* InSlot) override;
    virtual void OnSlotRemoved(UPanelSlot* InSlot) override;

    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void ReleaseSlateResources(bool bReleaseChildren) override;
    virtual void SynchronizeProperties() override;

    /** The current offset. */
    UPROPERTY(EditAnywhere, Getter, Setter, BlueprintSetter=SetOffset, Category="Parallax Panel", meta=(Delta=1, LinearDeltaSensitivity=1))
    FVector2D Offset;

    TSharedPtr<SOverlay> ContainerOverlay;
};
