#include <iostream>


//is_same
template <typename T, T val>
struct integral_constant {
    public:
        using value_type = T;
        static constexpr value_type value = val;
        using type = integral_constant;
        constexpr value_type operator()() const noexcept {
            return value;
        }
        constexpr operator value_type() const noexcept {
            return value;
        }
};

using false_type = integral_constant<bool, false>;
using true_type = integral_constant<bool, true>;

template <typename T, typename U>
struct is_same : public false_type{
};

template <typename T>
struct is_same<T, T> : public true_type {

};

// remove const
template <typename T>
struct remove_const {
    using type = T;
};

template <typename T>
struct remove_const<const T> {
    using type = T;
};

//remove volatile 
template <typename T>
struct remove_volatile {
    using type = T;
};

template <typename T>
struct remove_volatile<volatile T> {
    using type = T;
};

//remove cv
template <typename T>
struct remove_cv {
    using type = typename remove_const<typename remove_volatile<T>::type>::type;
};

//is_void<T>
// is_void<void>::value      // true
// is_void<int>::value       // false
template <typename T>
struct is_void : public false_type { };

template <>
struct is_void<void> : public true_type {

};

template <>
struct is_void<const void> : public true_type {

};

template <>
struct is_void<volatile void> : public true_type {

};

template <>
struct is_void<volatile const void> : public true_type {

};

//is_pointer
template <typename T>
struct is_pointer : public false_type {

};
template <typename T>
struct is_pointer<T*> : public true_type { 

};

template <typename T>
struct is_pointer<T* const> : public true_type { 

};

template <typename T>
struct is_pointer<T* volatile> : public true_type { 

};

template <typename T>
struct is_pointer<T* const volatile> : public true_type { 

};

//remove_reference
template <typename T>
struct remove_reference {
    using type = T;
};

template <typename T>
struct remove_reference<T&> {
    using type = T;
};


template <typename T>
struct remove_reference<T&&> {
    using type = T;
};

//add_reference

template <typename T>
struct add_reference {
    using type = typename remove_reference<T>::type&;
};


//is_reference
template <typename T>
struct is_reference : public false_type {

};

template <typename T>
struct is_reference<T&> : public true_type {

};

template <typename T>
struct is_reference<T&&> : public true_type {

};

//is_const
template <typename T>
struct is_const : public false_type {

};

template <typename T>
struct is_const<const T> : public true_type {

};

template <typename T>
struct is_const<const T*> : public true_type {

};

template <typename T>
struct is_const<const T&> : public true_type {

};





//after c++ 17
// template <typename T, typename U>
// using is_same_v = is_same<T, U>::value;

// template <typename T>
// using is_void_v = is_void<T>::value;

template <typename T>
using remove_const_t = typename remove_const<T>::type;

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
using add_reference_t = typename add_reference<T>::type;


int main() {
    static_assert(!is_same<int, char>::value);
    static_assert(is_void<void>::value);
    static_assert(is_same<remove_const_t<const int>, int>::value);
    static_assert(is_same<remove_volatile_t<volatile int>, int>::value);
    static_assert(is_same<remove_cv_t<const volatile int>, int>::value);
    static_assert(is_pointer<int* const>::value);
    static_assert(is_same<remove_reference_t<int&>, int>::value);
    static_assert(is_same<remove_reference_t<int&&>, int>::value);
    static_assert(is_same<int&, add_reference_t<int>>::value);
    static_assert(is_reference<const int&&>::value);
    static_assert(is_const<const int*>::value);
    std::cout << "test passed\n";
}