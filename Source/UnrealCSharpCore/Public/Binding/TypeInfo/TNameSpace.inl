#pragma once

#include "FNameSpace.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Template/TTemplateTypeTraits.inl"

template <typename T, typename Enable = void>
struct TNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TAnd<
	                                        TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                        TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>::Value, T>
                  ::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(TRemovePointer<T>::Type::StaticClass())};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(TTemplateTypeTraits<T>::Type::StaticClass()),
				FCommonNameSpace::Instance.Get()[0]
			};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> :
	TNameSpace<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};
