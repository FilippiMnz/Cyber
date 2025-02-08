#include <iostream>
#include <vector>
using namespace std;

int main(){
    while(true) {
        int N;
        if(!(cin >> N)) break;  
        if(N == 0) break;

        vector<int> grid_largada, grid_chegada;
        grid_largada.reserve(N);
        grid_chegada.reserve(N);

        
        for (int i = 0; i < N; i++){
            int id;
            cin >> id;
            grid_largada.push_back(id);
        }

        
        for (int i = 0; i < N; i++){
            int id;
            cin >> id;
            grid_chegada.push_back(id);
        }

        int alt = 0;  

        
        for (size_t i = 0; i < grid_largada.size(); i++){
            int competidor = grid_largada[i];
            size_t pos_chegada = 0;
            
            for (size_t a = 0; a < grid_chegada.size(); a++){
                if(grid_chegada[a] == competidor){
                    pos_chegada = a;
                    break;
                }
            }
            
            
            if(i > pos_chegada){
                alt += (i - pos_chegada);
            }
            
            else if(i == pos_chegada){
                int ultrapassagens = 0;
                
                for (size_t k = 0; k < i; k++){
                    int comp_ahead = grid_largada[k];
                    size_t pos_chegada_ahead = 0;
                   
                    for (size_t m = 0; m < grid_chegada.size(); m++){
                        if(grid_chegada[m] == comp_ahead){
                            pos_chegada_ahead = m;
                            break;
                        }
                    }
                    
                    if(pos_chegada_ahead > pos_chegada)
                        ultrapassagens++;
                }
                alt += ultrapassagens;
            }
            
        }

        cout << alt << endl;
    }
    return 0;
}
