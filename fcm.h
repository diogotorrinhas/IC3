#define FCM_H

#include<map>
#include<string>

using namespace std;

class fcm {
    private:
        int k; // order of the context model
        double alfa; // smoothing parameter

    public:
        /**
         * @brief variável para guardar distância calculada
         */
        double distance;

        /**
         * @brief variável para guardar a entropia do modelo previamente calculada
         */
        double modelEntropia;

        /**
         * @brief variável para guardar a entropia estimada de um dado texto
         */
        double estimatedEntropy;
        
        /**
         * @brief  variável para guardar o número de letras de um ficheiro a ser estimado
         */ 
        int nLetters;

        //Construtor
        fcm();
        /**
         * FCM class constructor
         * @param k order of the context model
         * @param alfa smoothing parameter
         */
        fcm(int k, double alfa);
        
        
        /**
         * FCM estimator
         * @brief For a given model (already initialized) and a new file, estimate the entropy and distance to the given file
         * @param model data structure that already must be initialized
         * @param ficheiro path to file
         */
        void estimateDistanceEntropy(map<string, map<char, int>> &model, char *ficheiro);
        
        /**
         * FCM model loader
         * @brief load a model from a given file name
         * @param model data structure that will represent the model and will be loaded with information
         * @param ficheiro source file
         */
         
         void estimateDistanceEntropyLocateLang(map<string, map<char, int>> &model, char *segment);
        
        /**
         * FCM model loader
         * @brief load a model from a given file name
         * @param model data structure that will represent the model and will be loaded with information
         * @param ficheiro source file
         */
         
        void saveModel(map<string, map<char, int>> &model, char *ficheiro);

        /**
         * FCM  model loader
         * @brief load existing model from a given file name
         * @param model data structure that will represent the model and will be loaded with information
         * @param ficheiro source file
         */
        void loadModel(map<string, map<char, int>> &model, char *ficheiro);
        
        /**
         * FCM Entropy calculator
         * @param model from where the entropy will be calculated
         */
        void calculateModelEntropy(map<string, map<char, int>> &model);
};

