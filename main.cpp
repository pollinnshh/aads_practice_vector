#include <iostream>
#include <iomanip>
#include "vector-top-it.hpp"

using topit::Vector;

bool test1() {
  Vector< int > v;
  return v.isEmpty();
}

bool test2() {
  Vector< int > v;
  return v.getSize() == 0;
}

bool test3() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
  return v.getSize() == size;
}

bool test4() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 1);
  try {
    int& value = v.at(0);
    return value == 1;
  } catch (... ) {
    return false;
  }
}

bool test5() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
  try {
    v.at(size + 1);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}

bool test6() {
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 1);
  try {
    const int& value = v.at(0);
    return value == 1;
  } catch (... ) {
    return false;
  }
}

bool test7() {
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 0);
  try {
    v.at(size + 1);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}

bool test8() {
  Vector< int > v(2, 0);
  Vector< int > yav = v;
  return yav == v;
}

bool test9() {
  Vector< int > v;
  Vector< int > yav(2, 0);
  bool res = v != yav;
  v = yav;
  return res && v == yav;
}

bool test10() {
  Vector< int > v(2, 0);
  Vector< int > yav(3, 1);
  
  Vector< int > cpy_v(v);
  Vector< int > cpy_yav(yav);
  v.swap(yav);
  
  return cpy_v == yav && cpy_yav == v;
}

bool test11() {
  Vector< int > v(2, 0);
  Vector< int > cpy_v(v);
  
  Vector< int > yav = std::move(v);
  return yav == cpy_v;
}

bool test12() {
  Vector< int > v(2, 0);
  Vector< int > cpy(v);
  Vector< int > yav;
  
  yav = std::move(v);
  return yav == cpy;
}

bool test13() {
  Vector<int> v;
  v.pushBack(10);
  v.pushBack(30);
  v.insert(1, 20);
  return v.getSize() == 3 && v[0] == 10 && v[1] == 20 && v[2] == 30;
}

bool test14() {
  Vector<int> v;
  v.pushBack(1);
  v.pushBack(5);
  
  Vector<int> rhs;
  rhs.pushBack(2);
  rhs.pushBack(3);
  rhs.pushBack(4);
  
  v.insert(1, rhs, 0, 3);
  return v.getSize() == 5 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5;
}

bool test15() {
  Vector<int> v;
  for (int i = 1; i <= 5; ++i) v.pushBack(i);
  v.erase(2);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 4 && v[3] == 5;
}

bool test16() {
  Vector< int > v{1, 2};
  return (v.getSize() == 2) && (v.at(0) == 1) && (v.at(1) == 2);
}

bool test17() {
  Vector< int > v{};
  return v.isEmpty();
}

bool test18() {
  Vector<int> v;
  v.reserve(100);
  return v.getCapacity() == 100 && v.getSize() == 0;
}

bool test19() {
  Vector<int> v(10, 5);
  v.reserve(5);
  return v.getCapacity() == 10 && v.getSize() == 10;
}

bool test20() {
  Vector<int> v;
  v.reserve(100);
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.shrinkToFit();
  return v.getCapacity() == 3 && v.getSize() == 3;
}

bool test21() {
  Vector<int> v;
  v.reserve(100);
  v.shrinkToFit();
  return v.getCapacity() == 0 && v.getSize() == 0;
}

bool test22() {
  Vector<int> v;
  v.repeatPushBack(7, 5);
  if (v.getSize() != 5) return false;
  for (size_t i = 0; i < 5; ++i) {
    if (v[i] != 7) return false;
  }
  return true;
}

bool test23() {
  Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.repeatPushBack(9, 3);
  return v.getSize() == 5 && v[0] == 1 && v[1] == 2 && v[2] == 9 && v[3] == 9 && v[4] == 9;
}

bool test24() {
  Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.repeatInsert(1, 99, 3);
  return v.getSize() == 6 && v[0] == 1 && v[1] == 99 && v[2] == 99 && v[3] == 99 && v[4] == 2 && v[5] == 3;
}

bool test25() {
  Vector<int> v;
  v.pushBack(10);
  v.pushBack(20);
  v.repeatInsert(2, 30, 2);
  return v.getSize() == 4 && v[0] == 10 && v[1] == 20 && v[2] == 30 && v[3] == 30;
}

bool test26() {
  int arr[] = {1, 2, 3, 4, 5};
  Vector<int> v;
  v.rangedPushBack(arr, 3);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool test27() {
  Vector<int> src;
  src.pushBack(10);
  src.pushBack(20);
  src.pushBack(30);
  src.pushBack(40);
  
  Vector<int> dst;
  dst.rangedPushBack(src.begin() + 1, 2);
  return dst.getSize() == 2 && dst[0] == 20 && dst[1] == 30;
}

int main() {
  using test_t = bool(*)();
  using case_t = std::pair< test_t, const char* >;
  case_t tests[] = {
    { test1, "Default constructed vector is empty" },
    { test2, "Default constructed vector size is zero" },
    { test3, "Vector constructed with size has non-zero size" },
    { test4, "In range access does not generate exceptions" },
    { test5, "Out of range access generates std::out_of_range exception" },
    { test6, "In range access for const vector: same as non-const" },
    { test7, "Out of range access for const vector: same as non-const" },
    { test8, "Copy constructor"},
    { test9, "Copy assignment operator"},
    { test10, "Swap for two vectors"},
    { test11, "Move constructor"},
    { test12, "Move assignment operator"}
    { test13, "Insert in middle" },
    { test14, "Insert range from another vector" },
    { test15, "Erase from middle" },
    { test16, "Non-empty initializer list ctr" },
    { test17, "Empty initializer list ctr" }
    { test18, "Increases capacity" },
    { test19, "Does nothing if k <= capacity" },
    { test20, "Reduces capacity to size" },
    { test21, "shrinkToFit (on empty vector)" },
    { test22, "Adds k copies" },
    { test23, "After existing elements" },
    { test24, "Inserts k copies in middle" },
    { test25, "Inserts k copies at end" },
    { test26, "rangedPushBack - from array" },
    { test27, "rangedPushBack - from vector iterator" }
  };
  
  size_t count = sizeof(tests) / sizeof(case_t);
  
  std::cout << std::boolalpha;
  bool result = true;
  size_t successes = 0, fails = 0;
  for (size_t i = 0; i < count; ++i) {
    bool case_result = tests[i].first();
    successes += case_result;
    fails += !case_result;
    result = result && case_result;
    std::cout << case_result;
    std::cout << ": ";
    std::cout << tests[i].second << "\n";
  }
  std::cout << "SUMMARY\n";
  std::cout << result << ": TEST RESULTS\n";
  std::cout << fails << ": failed tests\n";
  std::cout << successes << ": passed tests\n";
}
