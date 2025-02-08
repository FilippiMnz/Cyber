#include <iostream>
#include <vector>
   3 using namespace std;
   4
   5 int main() {
   6     while (1) {
   7         int N;
   8         cin >> N;
   9         vector<int> grid_largada(N);
  10         vector<int> grid_chegada(N);
  11
  12         for (int i = 0; i < N; i++) {
  13             cin >> grid_largada[i];
  14         }
  15         for (int i = 0; i < N; i++) {
  16             cin >> grid_chegada[i];
  17         }
  18
  19         int alt = 0;
  20
  21         for (size_t i = 0; i < N; i++) {
  22             for (size_t j = i + 1; j < N; j++) {
  23                 int largada_pos_i = find(grid_largada.begin(), grid_largada.end(),                              grid_chegada[i]) - grid_largada.begin();
  24                 int largada_pos_j = find(grid_largada.begin(), grid_largada.end(),                              grid_chegada[j]) - grid_largada.begin();
  25                                                                                              26                 if (largada_pos_i > largada_pos_j) {                                         27                     alt++;                                                                   28                 }                                                                            29             }                                                                                30         }                                                                                    31                                                                                              32         cout << alt << endl;                                                                 33     }                                                                                        34 }                                                                                            35                                                                                            ~                                                                                               ~                                                                                               ~