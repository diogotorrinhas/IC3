/**
 * programa tem como entrada  2 argumentos, 1 ficheiro de texto para o qual se quer tirar o modelo e calcular a entropia do mesmo
 * e outro ficheiro de texto que é usado para calcular a distância e entropia estimada desse ficheiro de texto em relação ao modelo 
 * ---- PARA ALTERAR K E ALFA, linha 36
 * 
 * comando de compilação: g++ testefcm.cpp -o testefcm
 *                        ./testefcm PT.utf8 TextoSimplesTeste.txt        ---- Estes comandos é para criar modelo de uma determinado linguagem/texto (opção n) e
 *                                                                          calcular entropia do modelo e distância e entropia estimada em relação a um certo texto
 *                                                                          (por exemplo o da Carochinha, TextoSimplesTeste.txt passado como segundo argumento)
 *                  
 *                        ./testefcm ModelPT.txt TextoSimplesTeste.txt    ---- Se já tivermos um modelo feito (por ex. ModelPT.txt), usámos este comando de compilação 
 *                                                                          (opção y) para calcular a entropia do modelo e calcular distância e entropia estimada 
 *                                                                          em relação ao segundo argumento (ficheiro de texto) 
 */
#include "fcm.cpp"
#include<map>
#include<string>

void printModel(map<string, map<char, int>> model, int n);

int main(int argc, char** argv){
    //Command line arguments processing
    if(argc < 2){
        cout << "Error: Usage sintax is: ./testefcm.cpp <textfile> <textfile>" << endl;
        return 0; 
    }

    char l ='x';
    while(l != 'y' & l != 'n') {
        cout << "Load de um model existente? (y or n): ";
        cin >> l;
    }

    int k =0;
    double alfa = 0.00;
    while(k<=0 || k>=100) {
        cout << "Valor de K: ";
        cin >> k;
    }
    while(alfa<=0 || alfa>=100) {
        cout << "Valor de alfa: ";
        cin >> alfa;
    }

    fcm f(k, alfa);  //k = 5, alfa = 0.1
    map<string, map<char, int>> model;

    for(int i = 1; i < argc - 1; i++){
        cout << "trying to process: " << argv[i] << endl;
        if(l == 'n') {
            f.saveModel(model, argv[i]);
        }
        else {
            f.loadModel(model, argv[i]);
        }
        // cout << "done" << endl;

        f.calculateModelEntropy(model);
        cout << "entropia do modelo: " << f.modelEntropia << endl;
        
        // estimar entropia de um texto de entrada
        f.estimateDistanceEntropy(model, (char*)argv[2]);
        cout << "Distancia estimada: " << f.distance << endl;
        cout << "Entropia estimada: " << f.estimatedEntropy << endl;
    }

    // cout << "printing model:" << endl;
    // //imprime os primeiros 10 pares do modelo
    // printModel(model, 10);
}

// void printModel(map<string, map<char, int>> model, int n){
//     int i = 0;
//     for (auto it : model) {
//         cout << "{\"" << it.first << "\" :";
//         map<char, int> &internal_map = it.second;
//         for (auto it2: internal_map) {
//             cout << " {'" << it2.first << "' : " << it2.second << "}";
//         }
//         cout << "}" << endl;
//         if(i > n){
//             break;
//         }
//         i++;
//     }
// }