#include "fcm.cpp"
#include<map>
#include<string>


// g++ modelEntropy.cpp -o modelEntropy
// ./modelEntropy TextoSimplesTeste.txt

int main(int argc, char** argv){

    map<string, map<char, int>> model;
    //Command line arguments processing
    if(argc != 2){
        cout << "Error: Usage sintax is: ./modelEntropy <textfile>" << endl;
        return 0; 
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


    for(int i=k; i < k+1; i++){
        fcm f(i, alfa);
        cout << "Processing for order " << i << " ..." << endl;
        f.saveModel(model, argv[1]);
        f.calculateModelEntropy(model);
        cout << "Model Entropy: " << f.modelEntropia << endl;
        model.clear();
    }



}