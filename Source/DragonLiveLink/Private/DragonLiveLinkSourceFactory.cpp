// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#include "DragonLiveLinkSourceFactory.h"
#include "DragonLiveLinkSource.h"
#include "SDragonLiveLinkSourceFactory.h"

#define LOCTEXT_NAMESPACE "DragonLiveLinkSourceFactory"

FText UDragonLiveLinkSourceFactory::GetSourceDisplayName() const
{
	return LOCTEXT("SourceDisplayName", "Dragon LiveLink");
}

FText UDragonLiveLinkSourceFactory::GetSourceTooltip() const
{
	return LOCTEXT("SourceTooltip", "Creates a connection to a Dragon UDP Stream");
}

TSharedPtr<SWidget> UDragonLiveLinkSourceFactory::BuildCreationPanel(FOnLiveLinkSourceCreated InOnLiveLinkSourceCreated) const
{
	return SNew(SDragonLiveLinkSourceFactory)
		.OnOkClicked(SDragonLiveLinkSourceFactory::FOnOkClicked::CreateUObject(this, &UDragonLiveLinkSourceFactory::OnOkClicked, InOnLiveLinkSourceCreated));
}

TSharedPtr<ILiveLinkSource> UDragonLiveLinkSourceFactory::CreateSource(const FString& InConnectionString) const
{
	FIPv4Endpoint DeviceEndPoint;
	if (!FIPv4Endpoint::Parse(InConnectionString, DeviceEndPoint))
	{
		return TSharedPtr<ILiveLinkSource>();
	}

	return MakeShared<FDragonLiveLinkSource>(DeviceEndPoint);
}

void UDragonLiveLinkSourceFactory::OnOkClicked(FIPv4Endpoint InEndpoint, FOnLiveLinkSourceCreated InOnLiveLinkSourceCreated) const
{
	InOnLiveLinkSourceCreated.ExecuteIfBound(MakeShared<FDragonLiveLinkSource>(InEndpoint), InEndpoint.ToString());
}

#undef LOCTEXT_NAMESPACE