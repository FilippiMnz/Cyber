#include <iostream>
#include <vector>
using namespace std;

int main() {
    while (1) {
        int N;
        cin >> N;
        vector<int> grid_largada;
        vector<int> grid_chegada;

        for (size_t i = 0; i < N; i++) {
            int id;
            cin >> id;
            grid_largada.push_back(id);
        }

        for (size_t i = 0; i < N; i++) {
            int id;
            cin >> id;
            grid_chegada.push_back(id);
        }

        int alt = 0;

        for (size_t i = 0; i < N; i++) {
            for (size_t a = 0; a < N; a++) {
                if (grid_largada[i] == grid_chegada[a]) {
                    if (i > a) {  
                        int diff = i - a;
                        alt += diff;
                    } else if (i == a) {  
                        int ultrapassagens = 0;
                        for (size_t k = 0; k < N; k++) {
                            if (k != i && grid_largada[k] < grid_largada[i] &&
                                grid_chegada[k] > grid_chegada[a]) {
                                ultrapassagens++;
                            }
                        }
                        alt += ultrapassagens;
                    }
                }
            }
        }

        cout << alt << endl;
    }
}
