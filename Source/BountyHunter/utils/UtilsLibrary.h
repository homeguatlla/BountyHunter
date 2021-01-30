#pragma once
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include <string>

#include "Engine/World.h"

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

	static TArray<FHitResult> TraceVisionBox(
		UWorld* world,
        const FVector& startLocation,
        const FVector& endLocation,
        const FVector& halfExtend,
        const FQuat& rotation,
        ECollisionChannel channel)
		{
			const auto shape = FCollisionShape::MakeBox(halfExtend);
			return TraceSweepMultyByChannel(world, startLocation, endLocation, rotation, channel, shape);
		}
	
		static TArray<FHitResult> TraceSweepMultyByChannel(
			UWorld* world,
			const FVector& startLocation,
			const FVector& endLocation,
			const FQuat& rotation,
			ECollisionChannel channel,
			const FCollisionShape& shape) 
		{
			TArray<FHitResult> outHits;
			
			auto result = world->SweepMultiByChannel(
				outHits,
				startLocation,
				endLocation,
				rotation,
				channel,
				shape);

			return outHits;
		}
};
}
