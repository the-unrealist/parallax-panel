// Copyright (c) 2024 citrus - https://unrealist.org
// Licensed under the MIT License.

#include "ParallaxPanelSlot.h"

#include "Components/Widget.h"
#include "ParallaxPanel.h"

void UParallaxPanelSlot::SetDistance(float InDistance)
{
    Distance = InDistance < 0.f ? 0.f : Distance;
}

float UParallaxPanelSlot::GetDistance() const
{
    return Distance;
}

void UParallaxPanelSlot::SetOffset(FVector2D InOffset)
{
    if (Slot)
    {
        TSharedRef<SWidget> ContentContainer = Slot->GetWidget();

        float ParallaxFactor = 1 / (1 + Distance / 100);
        ContentContainer->SetRenderTransform(InOffset * ParallaxFactor);
    }
}

void UParallaxPanelSlot::BuildSlot(TSharedRef<SOverlay> InOverlay)
{
    // Wrap the child widget in a container so that parallax transformation is applied without overriding the child's
    // existing render transform properties.
    TSharedRef<SOverlay> ContentContainer =
        SNew(SOverlay) + SOverlay::Slot()
                             [Content == nullptr ? SNullWidget::NullWidget : Content->TakeWidget()];

    InOverlay->AddSlot()
        .Expose(Slot)
        .Padding(GetPadding())
        .HAlign(GetHorizontalAlignment())
        .VAlign(GetVerticalAlignment())
            [ContentContainer];
}

void UParallaxPanelSlot::SynchronizeProperties()
{
    Super::SynchronizeProperties();
    SetDistance(Distance);
}
