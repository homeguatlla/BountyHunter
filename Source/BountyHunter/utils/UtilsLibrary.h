#pragma once
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include <glm/glm.hpp>
#include <string>

namespace utils
{
class UtilsLibrary
{
	public:
		//estod m�todos probablemente sean est�ticos en alguna libreria-
		template <class InterfaceTypeSource, class InterfaceTypeTarget = InterfaceTypeSource>
		static InterfaceTypeTarget* CreateHUDFromClass(int hudIndex, const FString& name, APlayerController* playerController, TSubclassOf<InterfaceTypeSource> hudClass, bool autoAddToViewport = true, int32 zOrder = 0)
		{
			InterfaceTypeTarget* widget = InstantiateHUD<InterfaceTypeSource, InterfaceTypeTarget>(
			hudIndex, 
			name, 
			playerController,
			hudClass, 
			autoAddToViewport, 
			zOrder);
			
			return widget;
		}

		template <class InterfaceTypeSource, class InterfaceTypeTarget>
		static InterfaceTypeTarget* InstantiateHUD(int hudIndex, const FString& name, APlayerController* playerController, TSubclassOf<UUserWidget> hudClass, bool autoAddToViewport, int32 zOrder)
		{
			//CreateWidget need different FName for each create otherwise it returns a pointer to the previously create with the same name.
				//refer to the link below
				//https://answers.unrealengine.com/questions/810228/strange-behaviour-of-uuserwidgetcreatewidgetinstan.html?sort=oldest

			FString hudName = hudClass->GetName() + "_" + FString::FromInt(hudIndex) + "_" + name;
			UUserWidget* widget = CreateWidget<UUserWidget>(playerController, hudClass, FName(*hudName));

			if (autoAddToViewport)
				widget->AddToViewport(zOrder == 0 ? hudIndex + 1 : zOrder);
			//widget->InitializeWidget();

			return Cast<InterfaceTypeTarget>(widget);
		}

		template<class T>
		static TArray<AActor*> GetAllActorsOfClass(UWorld* world, TSubclassOf<T> classToFind)
		{
			TArray<AActor*> foundActors;
			UGameplayStatics::GetAllActorsOfClass(world, classToFind, foundActors);
			
			return foundActors;
		}

		static FString ConvertToFString(const std::string& text)
		{
			return UTF8_TO_TCHAR(text.c_str());
		}

		static std::string ConvertToString(const FString& text)
		{
			return std::string(TCHAR_TO_UTF8(*text));
		}

		static FVector ConvertToFVector(const glm::vec3& v)
		{
			return FVector(v.x, v.y, v.z);
		}

		static glm::vec3 ConvertToVec3(const FVector& v)
		{
			return glm::vec3(v.X, v.Y, v.Z);
		}
	
		static TArray<FHitResult> TraceVisionSphere(
			UWorld* world,
	        const FVector& startLocation,
	        const FVector& endLocation,
	        const float radius,
	        const FQuat& rotation,
	        ECollisionChannel channel,
	        const FCollisionQueryParams& params)
		{
			const auto shape = FCollisionShape::MakeSphere(radius);
			return TraceSweepMultyByChannel(world, startLocation, endLocation, rotation, channel, shape, params);
		}
	
		static TArray<FHitResult> TraceSweepMultyByChannel(
			UWorld* world,
			const FVector& startLocation,
			const FVector& endLocation,
			const FQuat& rotation,
			ECollisionChannel channel,
			const FCollisionShape& shape,
			const FCollisionQueryParams& params) 
		{
			TArray<FHitResult> outHits;

			//auto result = world->SweepMultiByObjectType(outHits, startLocation, endLocation, rotation, CHANNELOUT_LEFTSURROUND, shape, params);
			auto result = world->SweepMultiByChannel(
				outHits,
				startLocation,
				endLocation,
				rotation,
				channel,
				shape,
				params);

			return outHits;
		}


	static FQuat LookAt(const FVector& sourcePoint, const FVector& destPoint)
		{
			FVector forwardVector = destPoint - sourcePoint;
			forwardVector.Normalize();

			float dot = FVector::DotProduct(FVector::ForwardVector, forwardVector);

			//two opposite vectors, angle = 180 we proceed with UpVector and angle 180
			if (FMath::IsNearlyZero(FGenericPlatformMath::Abs(dot - (-1.0f))))
			{
				return FQuat(FVector::UpVector.X, FVector::UpVector.Y, FVector::UpVector.Z, PI);
			}
			//two coincident vectors, angle = 0, we proceed with identity
			else if (FMath::IsNearlyZero(FGenericPlatformMath::Abs(dot - (1.0f))))
			{
				return FQuat::Identity;
			}
			else
			{
				float rotAngle = (float)FGenericPlatformMath::Acos(dot);
				FVector rotAxis = FVector::CrossProduct(FVector::ForwardVector, forwardVector);
				rotAxis.Normalize();
				return CreateQuatFromAxisAngle(rotAxis, rotAngle);
			}
		}

	static FQuat CreateQuatFromAxisAngle(const FVector& axis, float angle)
		{
			float halfAngle = angle * .5f;
			float s = (float)FGenericPlatformMath::Sin(halfAngle);
			FQuat q;
			q.X = axis.X * s;
			q.Y = axis.Y * s;
			q.Z = axis.Z * s;
			q.W = (float)FGenericPlatformMath::Cos(halfAngle);
			return q;
		}
};
}
