//
// Created by suun on 11/4/19.
//

#include <functional>
#include <cstdio>

template<typename T>
struct remove_class {};
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...)> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) const> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) volatile> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) const volatile> { using type = R(A...); };

template<typename T>
struct get_signature_impl {
  using type = typename remove_class<
      decltype(&std::remove_reference<T>::type::operator())>::type;
};
template<typename R, typename... A>
struct get_signature_impl<R(A...)> { using type = R(A...); };
template<typename R, typename... A>
struct get_signature_impl<R(&)(A...)> { using type = R(A...); };
template<typename R, typename... A>
struct get_signature_impl<R(*)(A...)> { using type = R(A...); };
template<typename T> using get_signature = typename get_signature_impl<T>::type;

template<class Base, class Derived>
bool type_switch_helper(Base *base, std::function<void(Derived *)> function) {
  if (auto entity = dynamic_cast<Derived *>(base)) {
    function(entity);
    return true;
  }
  return false;
}

template<class Base, class FirstFunction, class ...OtherFunction>
void type_switch(Base *base, FirstFunction &&function,
                 OtherFunction &&...otherFunction) {
  using Signature = get_signature<FirstFunction>;

  if (type_switch_helper(base, (std::function<Signature>) function)) {
    return;
  }
  type_switch(base, otherFunction...);
}

template<class Base>
void type_switch(Base *base) {}

class Animal {
 public:
  virtual void go() = 0;
};

class Cat : public Animal {
 public:
  void go() override {};
};

class Dog : public Animal {
 public:
  void go() override {};
};

void testTypeSwitch();
