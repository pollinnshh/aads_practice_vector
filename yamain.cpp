#include <vector>
#include <initializer_list>

int main() {
  int a[10];
  int b[a];
  struct A { int a; }
  
  std::vector< int > a = {1, 2, 3, 4, 5};
  
  std::initializer_list< int > il{1, 2, 3, 4, 5};
}
