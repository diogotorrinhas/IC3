//g++ lang.cpp -o lang
//Primeiro paramêtro é um ficheiro de texto ou um modelo já criado de um dado ficheiro de texto
//Caso o primeiro parametro seja um ficheiro de texto, vai ser criado um modelo para ele mesmo e dps faz-se a comparação com o segundo ficheiro de texto de entrada


#include "fcm.cpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2){
        cout << "Error: Sintax is: ./lang <textfile> <textfile>" << endl;
        return 0; 
    }

    float alpha = 0;
    int k = -1; //context order
    char c = 'z';   //Option model to choose

    while(c != 'n' && c != 'y'){
        cout << "Load from an existing model? (y/n):";
        cin >> c;
    }

    if(c == 'n') {
        while(alpha <= 0){
            cout << "Insert alpha: ";
            cin >> alpha;
        }
        while(k <= 0){
            cout << "Insert (k): ";
            cin >> k;
        }
    }
    
    
    map<string, map<char, int>> model;

    //Load model and processing it
    fcm f = fcm(k, alpha);

    cout << "Begin processing..." << endl;
    if(c == 'y') {
        f.loadModel(model, argv[1]);
    }
    else {
        f.saveModel(model, argv[1]);
    }
    cout << "Processing Model ended sucessfully!" << endl;

    //Number of bits required to compress second file
    f.estimateDistanceEntropy(model, argv[2]);
    cout << "Estimated number of bits to compress file: " << f.distance<< endl;
    cout << "Estimated number of bits per character: " << f.distance/f.nLetters << endl; 

    return 0;
}