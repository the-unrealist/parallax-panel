// Copyright (c) 2024 citrus - https://unrealist.org
// Licensed under the MIT License.

#include "ParallaxPanel.h"

#include "ParallaxPanelSlot.h"

UParallaxPanel::UParallaxPanel()
{
    bIsVariable = false;
    SetVisibilityInternal(ESlateVisibility::SelfHitTestInvisible);
}

#if WITH_EDITOR
const FText UParallaxPanel::GetPaletteCategory()
{
    return NSLOCTEXT("ParallaxPanel", "PaletteCategory", "Panel");
}
#endif

UParallaxPanelSlot *UParallaxPanel::AddChildToParallaxPanel(UWidget *Content)
{
    return Cast<UParallaxPanelSlot>(AddChild(Content));
}

void UParallaxPanel::SetOffset(FVector2D InOffset)
{
    Offset = InOffset;

    if (ContainerOverlay.IsValid())
    {
        for (UPanelSlot *PanelSlot : Slots)
        {
            if (UParallaxPanelSlot *ParallaxPanelSlot = Cast<UParallaxPanelSlot>(PanelSlot))
            {
                ParallaxPanelSlot->SetOffset(InOffset);
            }
        }
    }
}

FVector2D UParallaxPanel::GetOffset() const
{
    return Offset;
}

UClass *UParallaxPanel::GetSlotClass() const
{
    return UParallaxPanelSlot::StaticClass();
}

void UParallaxPanel::OnSlotAdded(UPanelSlot *InSlot)
{
    // Add the child to the live canvas if it already exists.
    if (ContainerOverlay.IsValid())
    {
        CastChecked<UParallaxPanelSlot>(InSlot)->BuildSlot(ContainerOverlay.ToSharedRef());
    }
}

void UParallaxPanel::OnSlotRemoved(UPanelSlot *InSlot)
{
    // Remove the widget from the live slot if it exists.
    if (ContainerOverlay.IsValid() && InSlot->Content)
    {
        TSharedPtr<SWidget> Widget = InSlot->Content->GetCachedWidget();
        if (Widget.IsValid())
        {
            ContainerOverlay->RemoveSlot(Widget.ToSharedRef());
        }
    }
}

TSharedRef<SWidget> UParallaxPanel::RebuildWidget()
{
    ContainerOverlay = SNew(SOverlay);

    for (UPanelSlot *PanelSlot : Slots)
    {
        if (UParallaxPanelSlot *ParallaxPanelSlot = Cast<UParallaxPanelSlot>(PanelSlot))
        {
            ParallaxPanelSlot->Parent = this;
            ParallaxPanelSlot->BuildSlot(ContainerOverlay.ToSharedRef());
        }
    }

    return ContainerOverlay.ToSharedRef();
}

void UParallaxPanel::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);
    ContainerOverlay.Reset();
}

void UParallaxPanel::SynchronizeProperties()
{
    Super::SynchronizeProperties();
    SetOffset(Offset);
}
