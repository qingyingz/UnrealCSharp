using System;
using Script.Reflection.Container;

namespace Script.Common
{
    public class TSet<T>
    {
        public TSet() => SetUtils.Set_Register(this);

        public TSet(Type InValue)
        {
        }

        ~TSet() => SetUtils.Set_UnRegister(this);

        public void Empty(Int32 InExpectedNumElements = 0) => SetUtils.Set_Empty(this, InExpectedNumElements);

        public Int32 Num() => SetUtils.Set_Num(this);

        public void Add(T InValue) => SetUtils.Set_Add(this, InValue);

        public Int32 Remove(T InValue) => SetUtils.Set_Remove(this, InValue);

        public Boolean Contains(T InValue) => SetUtils.Set_Contains(this, InValue);
<<<<<<< HEAD
<<<<<<< HEAD

        //public  TArray<uint8*> ToArray()=>SetUtils.Set_ToArray(this);
       
        public Int32 Find(T Value)=>SetUtils.Set_Find(this,Value);
            
        public Int32 GetMaxIndex()=>SetUtils.Set_GetMaxIndex(this);

        public T this[Int32 InIndex]
        {
            get => SetUtils.Set_Get(this, InIndex);

            set => SetUtils.Set_Set(this, InIndex, value);
        }

        public TArray<T> ToArray()
        {
            return SetUtils.Set_ToArray(this);
        }
      


=======
>>>>>>> parent of dbcfe41 (TSet 的GetSet 以及迭代器)
=======
>>>>>>> parent of dbcfe41 (TSet 的GetSet 以及迭代器)
    }
}