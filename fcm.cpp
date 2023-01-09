#include "fcm.h"
#include<fstream>
#include<string>
#include<iostream>
#include<cmath>
#include <sstream>

using namespace std;

void readChar(ifstream &ifs, char *c);
        
fcm::fcm(){ }

//Para inicializar k-oder e alfa(smoothing parameter) no construtor
fcm::fcm(int k, double alfa){
    this->k = k;
    this->alfa = alfa; 
}

//Calcular Modelo e Guardar em ficheiro .txt
void fcm::saveModel(map<string, map<char, int>> &model, char *ficheiro){
    ifstream ifs(ficheiro, std::ios::in);
    if(!ifs.is_open()){
        throw runtime_error("Error: Can't open file...!");
    }

    string palavra;
    char aux;

    for (int i = 0; i < k; i++){  //dar append de chars até á ordem k (order of the context model)
        readChar(ifs, &aux);
        palavra.append(1, aux);  //dar append de 1 char
    }

    do{
        readChar(ifs, &aux);

        if (model.count(palavra) > 0){  // Verifica quantas keys = palavra existem no map
            model[palavra][aux]++;   //incrementa na key = palavra onde o proximo char é = aux
        }else{
            map<char, int> vazio;
            model[palavra] = vazio;     //como a key = palavra n existe, cria novo map (para guardar proximo caracter e aumentar a ocurrência dele)
            model[palavra][aux]++;      // key=palavra, prox char = aux, nº de ocurrência + 1
        }
        // update palavra
        palavra.erase(0,1); // remove primeiro char
        palavra.append(1, aux); //adiciona mais 1 char
    }while(!ifs.eof());

    // Nome do path/ficheiro para guardar o modelo
    size_t destino = string(ficheiro).find_last_of(".");
    string Ficheirodestino = string(ficheiro).substr(0, destino); 
    Ficheirodestino = "Model" + Ficheirodestino + ".txt";
    cout << Ficheirodestino << endl;

    ofstream myfile; //para gravar ficheiro destino com o modelo
    myfile.open (Ficheirodestino);
    myfile << k << "\t" << alfa << endl;
    for(auto p : model) {
        map<char, int> &ocurrencia = model[p.first];  // ver o proximo carácter da key(palavra) e nº de ocurrências do mesmo
        myfile << p.first;
        for(auto c : ocurrencia){
            myfile << '\t' << c.first << '\t' << c.second; // palavra -> próximo caracter -> nº de ocurrências
        }
        myfile << endl;
    }
    myfile.close();
}

void fcm::calculateModelEntropy(map<string, map<char, int>> &model){
       
    int totalEntradas = 0;
    int aux;
    map<string, int> totalOcurrenciaPalavra;
    for(auto p : model){
        map<char, int> &ocurrencia = model[p.first];
        aux = 0;
        for(auto p : ocurrencia){
            aux += p.second;
        }
        totalOcurrenciaPalavra[p.first] = aux;
        totalEntradas += aux;
    }

    int PalavraTotal;
    double probPalavra, prob, PalavraEntropia, H;

    for(auto p : model){
        map<char, int> &ocurrencia = model[p.first];

        PalavraTotal = totalOcurrenciaPalavra[p.first];
        probPalavra = (double)PalavraTotal / totalEntradas;

        PalavraEntropia = 0;
        for(auto p : ocurrencia){
            prob = (double) p.second / PalavraTotal;
            PalavraEntropia -= prob * log2(prob);

        }
        H += PalavraEntropia * probPalavra;
    }
    modelEntropia = H;
}

void fcm::estimateDistanceEntropy(map<string, map<char, int>> &model, char *ficheiro){
    ifstream ifs(ficheiro, std::ios::in);
    if(!ifs.is_open()){
        throw runtime_error("Error: Can't open file...!");
    }

    string palavra;
    char aux;
    for (int i = 0; i < k; i++){
        readChar(ifs, &aux);
        palavra.append(1, aux);
    }

    int nocurrencias, totalOcurrencias;
    double sumH = 0;
    int count = 0;

    do{
        readChar(ifs, &aux);
        count++;

        totalOcurrencias = 0;
        // se modelo contem palavra
        if(model.count(palavra) > 0){
            map<char, int> &occur = model[palavra];
            // se palavra tem o char que procuramos
            if(occur.count(aux) > 0){  
                nocurrencias = occur[aux];
            }else{ 
                nocurrencias = 0;
            }
            for(auto i : occur){
                // contar o número total de entradas para a palavra
                totalOcurrencias += i.second;
            }
        }else{ 
            nocurrencias = 0;
            totalOcurrencias = 0;
        }

        sumH += -log2((nocurrencias + alfa) / (totalOcurrencias + (alfa * 27)));  // 27 = tamanho do alfabeto

        // update da palavra
        palavra.erase(0,1); // remove primeiro caracter
        palavra.append(1, aux);
    }while(!ifs.eof());

    // guarda distancia estimada
    distance = sumH;

    // guarda entropia estimada
    estimatedEntropy = sumH / count;

    // Atualiza número de caracteres no ficheiro
    nLetters = count;
}

void fcm::estimateDistanceEntropyLocateLang(map<string, map<char, int>> &model, char *segment){
    string palavra;
    int i = 0;
    for (i = 0; i < k; i++){
        //readChar(segment, &aux); //Ler o segmento
        palavra.append(1, segment[i]);
    }

    int nocurrencias, totalOcurrencias;
    double sumH = 0;
    int count = 0;
    do{
        //readChar(segment, &aux); //Ler o segmento
        i++;
        count++;

        totalOcurrencias = 0;
        // se modelo contem palavra
        if(model.count(palavra) > 0){
            map<char, int> &occur = model[palavra];
            // se palavra tem o char que procuramos
            if(occur.count(segment[i]) > 0){
                nocurrencias = occur[segment[i]];
            }else{ 
                nocurrencias = 0;
            }
            for(auto i : occur){
                // contar o número total de entradas para a palavra
                totalOcurrencias += i.second;
            }
        }else{ 
            nocurrencias = 0;
            totalOcurrencias = 0;
        }

        sumH += -log2((nocurrencias + alfa) / (totalOcurrencias + (alfa * 27)));  // 27 = tamanho do alfabeto

        // update da palavra
        palavra.erase(0,1); // remove primeiro caracter
        palavra.append(1, segment[i]);
    }while(segment[i]!='\0'); 

    // guarda distancia estimada
    distance = sumH;

    // guarda entropia estimada
    estimatedEntropy = sumH / count;

    // Atualiza número de caracteres no ficheiro
    //nLetters = count;
}


void fcm::loadModel(map<string, map<char, int>> &model, char *ficheiro){

    ifstream file(ficheiro);
    string line;
    int i = -2;
    string a;
    char b;
    int c;

    while (getline(file, line)){
        istringstream lin(line);
        while(i < 0) {
            getline(lin, line, '\t');
            if(i== -2) {
                k = stoi(line);
            }
            else {
                alfa = stod(line);
            }
            i++;
        }

        if(i >= 0) {
            while(getline(lin, line, '\t')) {
                if(i == 0){
                    a = line;
                    i++;
                }
                else if(i == 1){
                    b = line[0];
                    i++;
                }
                else {
                    c = stoi(line);
                    model[a][b] = c;
                    if(getline(lin, line, '\t')) {
                        b = line[0];
                        i = 2;
                    }
                    else {
                        i = 0;
                    }
                }
            }
        }
    }
}

void readChar(ifstream &ifs, char *c){
    char s;
    do{
        ifs.get(s);
        if(!(s == '\t'| s == '\n')) {
            *c = s;
        }
    }while((*c == '\t'|*c == '\n') && !ifs.eof());
}