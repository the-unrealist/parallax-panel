// Copyright (c) 2024 citrus - https://unrealist.org
// Licensed under the MIT License.

#pragma once

#include "Components/OverlaySlot.h"

#include "ParallaxPanelSlot.generated.h"

/**
 * Slot for UParallaxPanel. The distance property controls how much this slot translates in comparison to other slots
 * based on the offset of the parent UParallaxPanel.
 */
UCLASS(MinimalAPI)
class UParallaxPanelSlot : public UOverlaySlot
{
    friend class UParallaxPanel;

    GENERATED_BODY()

public:
    /** Sets the distance of this slot in Slate units. */
    UFUNCTION(BlueprintCallable, Category = "Layout|Parallax Panel Slot")
    void SetDistance(float InDistance);

    /** Gets the distance of this slot in Slate units. */
    UFUNCTION(BlueprintPure, Category = "Layout|Parallax Panel Slot")
    float GetDistance() const;

protected:
    /** Sets the offset of this slot adjusted for distance. */
    void SetOffset(FVector2D InOffset);

    virtual void BuildSlot(TSharedRef<SOverlay> InOverlay) override;
    virtual void SynchronizeProperties() override;

    /**
     * Controls how much this slot translates compared to other slots. A higher value indicates that this slot should
     * appear further away and will have smaller translations when the offset of a UParallaxPanel changes.
     */
    UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter = GetDistance, BlueprintSetter = SetDistance, Category = "Layout|Parallax Panel Slot", meta = (DesignerRebuild, UIMin = 0, ClampMin = 0, Delta = 1, LinearDeltaSensitivity = 1))
    float Distance;
};
