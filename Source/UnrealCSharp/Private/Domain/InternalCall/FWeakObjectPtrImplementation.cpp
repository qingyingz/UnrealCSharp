﻿#include "Domain/InternalCall/FWeakObjectPtrImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterWeakObjectPtr
{
	FRegisterWeakObjectPtr()
	{
		FBindingClassBuilder(TEXT("WeakObjectPtr"), NAMESPACE_LIBRARY)
			.Function("Register",
			          static_cast<void*>(FWeakObjectPtrImplementation::WeakObjectPtr_RegisterImplementation))
			.Function("UnRegister",
			          static_cast<void*>(FWeakObjectPtrImplementation::WeakObjectPtr_UnRegisterImplementation))
			.Function("Get",
			          static_cast<void*>(FWeakObjectPtrImplementation::WeakObjectPtr_GetImplementation))
			.Register();
	}
};

static FRegisterWeakObjectPtr RegisterWeakObjectPtr;

void FWeakObjectPtrImplementation::WeakObjectPtr_RegisterImplementation(MonoObject* InMonoObject,
                                                                        const MonoObject* InObject)
{
	const auto FoundObject = FCSharpEnvironment::GetEnvironment()->GetObject(InObject);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TWeakObjectPtr<UObject>>(InMonoObject, FoundObject);
}

void FWeakObjectPtrImplementation::WeakObjectPtr_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TWeakObjectPtr<UObject>>(InMonoObject);
}

void FWeakObjectPtrImplementation::WeakObjectPtr_GetImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment()->GetMulti<TWeakObjectPtr<UObject>>(InMonoObject);

	auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Multi.Get());

	if (FoundMonoObject == nullptr)
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(Multi->GetClass()),
			FUnrealCSharpFunctionLibrary::GetFullClass(Multi->GetClass()));

		FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

		FCSharpEnvironment::GetEnvironment()->Bind(Multi->GetClass(), false);

		FCSharpEnvironment::GetEnvironment()->AddObjectReference(Multi.Get(), FoundMonoObject);
	}

	*OutValue = FoundMonoObject;
}