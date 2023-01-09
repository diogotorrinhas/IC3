#include "fcm.cpp"
#include <iostream>
//g++ locatelang.cpp -o locatelang

int main(int argc, char** argv)
{
    //Command line arguments processing
    if(argc < 2){
        cout << "Error: Usage sintax is: ./locatelang <model> <model> ... <textfile>" << endl;  
        return 0; 
    }

    ifstream ifs(argv[argc-1], std::ios::in);
    if(!ifs.is_open()){
        throw runtime_error("Error: Can't open file...!");
    }

    //Context order and alpha
    int k = -1;
    float a = 0;
    char c ='z';

    int segmentSize = 0;
    cout << "Choose the segment size within the file: ";
    cin >> segmentSize;
    if (segmentSize == 0){
        cout << "Error: Segment size needs to be greater than 0. Choose again: ";
        cin >> segmentSize;
    }

    while(c != 'y' & c != 'n') {
        cout << "Load from an existing model? (y/n): ";
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
    
    //Variables
    fcm f = fcm(k, a);
    int distMin;
    string modelLang;
    //map<char, string> mapResult;    //Mapa onde vai ser armazenado a linguagem para cada segmento
    int index = 0;
    string segment;
    char aux;
    char firstChar;
    int splitIntoSegmentsIndex = segmentSize;
    int lastSegmentIndex;

    do{
        readChar(ifs,&aux);
        if (index < splitIntoSegmentsIndex){
            segment.append(1,aux);

            if(index == splitIntoSegmentsIndex -1){
                firstChar = segment[0];
                ///cout << "segment:" << segment << "\n";

                for(int i = 1; i < argc - 1; i++){
                    map<string, map<char, int>> model;

                    if(c == 'y'){
                        f.loadModel(model, argv[i]);
                    }else{
                        f.saveModel(model, argv[i]);
                    }

                    f.estimateDistanceEntropyLocateLang(model, (char*)segment.c_str());
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
                }
                //mapResult.insert({firstChar,modelLang});
                cout << "firstChar: " << firstChar << " da posição inicial " << index - segmentSize +1 << " até a " << splitIntoSegmentsIndex - 1 << " tem a linguagem " << modelLang;
                cout << "\n";

                lastSegmentIndex = splitIntoSegmentsIndex;
                splitIntoSegmentsIndex = splitIntoSegmentsIndex + segmentSize; //Somar splitIntoSegmentsIndex + segmentSize para o próximo segmento
                segment.erase(segment.begin(), segment.end()); //limpar a variavel segment para esta ficar com o conteudo do proximo segment
                //segment = "\0";
                firstChar = '\0';   //clear no valor do char
            }
        }
        //cout << "splitIntoSegmentsIndex:" << splitIntoSegmentsIndex;
        //cout << "\n";
        //cout << "splitIntoSegmentsIndex:" << splitIntoSegmentsIndex;
        //cout << "\n";
        index++;
    }while(!ifs.eof());

    //Ficheiro terminou e o último segmento é menor q o segmentSize
    if (ifs.eof() != 0 and segment.size() < segmentSize){
        firstChar = segment[0];
            //cout << "segment:" << segment << "\n";

            for(int i = 1; i < argc - 1; i++){
                map<string, map<char, int>> model;

                if(c == 'y'){
                    f.loadModel(model, argv[i]);
                }else{
                    f.saveModel(model, argv[i]);
                }

                f.estimateDistanceEntropyLocateLang(model, (char*)segment.c_str());
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
            }
            //mapResult.insert({firstChar,modelLang});
            cout << "firstChar: " << firstChar << " da posição inicial " << lastSegmentIndex << " até a " << index << " tem a linguagem " << modelLang;
            cout << "\n";
            splitIntoSegmentsIndex = splitIntoSegmentsIndex + segmentSize; //Somar splitIntoSegmentsIndex + segmentSize para o próximo segmento
            segment.erase(segment.begin(), segment.end()); //limpar a variavel segment para esta ficar com o conteudo do proximo segment
            firstChar = '\0';   //clear no valor do char
    }

    // ofstream stream("Result_Locatelang.txt"); //Write the result to a text file
    // for(auto& i : mapResult) {
    //     //stream << "First char: " << i.first << " | " << "Linguagem: " << i.second <<'\n';
    // }
    // stream.close();
    
    return 0;
}