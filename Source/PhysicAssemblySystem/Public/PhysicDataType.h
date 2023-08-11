#pragma once

#include "PhysicDataType.generated.h"


USTRUCT(BlueprintType)
struct FConnectPath
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPrimitiveComponent * TracedComponent = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPrimitiveComponent * SelfComponent = nullptr;
	
	float Dis = 0.f;
	
	FConnectPath(){}
	FConnectPath(UPrimitiveComponent * InTracedComponent,UPrimitiveComponent * InOwnerComponent)
	{
		TracedComponent = InTracedComponent;
		SelfComponent = InOwnerComponent;
		Dis = FVector::DistSquared(InTracedComponent->GetComponentLocation(),InOwnerComponent->GetComponentLocation());
	}
};
