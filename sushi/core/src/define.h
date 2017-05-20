#pragma once

#if defined(__cplusplus)

#define SU_DEF_BEG extern "C" {

#define SU_DEF_END }

#else

#define SU_DEF_BEG

#define SU_DEF_END

#endif

#define SU_DEF_PROP(Type, Name)                 protected:\
                                                Type                Name;\
                                                public:\
                                                const Type&         get_##Name              () const;\
                                                void                set_##Name              (const Type& value);


#define SU_SYN_PROP(ParentType, Type, Name)     const Type&         ParentType::get_##Name  () const { return Name; } \
                                                void                ParentType::set_##Name  (const Type& value) { Name = value; }


#define SU_DEF_PROP_RO(Type, Name)              static_assert(std::is_pointer<Type>::value == false, "Type needs to be a non-pointer value.");\
                                                protected:\
                                                Type                Name;\
                                                public:\
                                                const Type&         get_##Name              () const;

#define SU_SYN_PROP_RO(ParentType, Type, Name)  static_assert(std::is_pointer<Type>::value == false, "Type needs to be a non-pointer value.");\
                                                const Type&         ParentType::get_##Name  () const { return Name; }

#define SU_DEF_FUNC(...)

#define SU_DEF_OBJ(...)
