#include "fcm.cpp"


int main(int argc, char** argv)
{
    //Command line arguments processing
    if(argc < 2){
        cout << "Error: Usage sintax is: ./findlang <textfile> <textfile>" << endl;
        return 0; 
    }

    int k = -1; //context order
    float a = 0;
    char c ='z'; //Option model to choose

    while(c != 'y' & c != 'n') {
        cout << "Carregar modelos existentes? (y/n): ";
        cin >> c;
    }

    if(c == 'n') {
        while(k <= 0){
            cout << "Insert context order (k): ";
            cin >> k;
        }
        while(a <= 0){
            cout << "Insert alpha (a): ";
            cin >> a;
        }
    }
    
    //Load models and processing
    fcm f = fcm(k, a);
    int distMin;
    string modelLang;
    for(int i = 1; i < argc - 1; i++){
        
        map<string, map<char, int>> model;
        
        cout << "processing " << argv[i] << endl;
        if(c == 'y') {
            f.loadModel(model, argv[i]);
        }
        else {
            f.saveModel(model, argv[i]);
        }

        f.estimateDistanceEntropy(model, argv[argc-1]);
        cout << "distancia estimada: " << f.distance << endl;

        if(i == 1) {
            modelLang = argv[i];
            distMin = f.distance;
        }
        else {
            if(distMin > f.distance) {
                modelLang = argv[i];
                distMin = f.distance;
            }
        }
        cout << "Modelo carregado!" << endl;
    }

    cout << "\nLinguagem do texto escrito: " << modelLang << endl;
    
    return 0;
}