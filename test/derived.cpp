#include <iostream>

struct Base {
  virtual void on_event() {}
  virtual ~Base() {}

  template <class Derived>
  void raise_event() {
    if constexpr (!std::is_same_v<decltype(&Derived::on_event),
                                  decltype(&Base::on_event)>) {
      std::cout << "overrided" << std::endl;
    } else {
      std::cout << "not overrided" << std::endl;
    }
  }
};

struct Concrete1 : Base {
  virtual void on_event() override {}
};

struct Concrete2 : Base {
  // no override
};

int main() {
  Concrete1 c1;
  Concrete2 c2;

  c1.raise_event<Concrete1>();  // prints overridden
  c2.raise_event<Concrete2>();  // prints not overridden

  return 0;
}