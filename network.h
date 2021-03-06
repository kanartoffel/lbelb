# include <stdlib.h>
# include <stdio.h>

#ifndef DEFAULT_WEIGHTS_FILE
#define DEFAULT_WEIGHTS_FILE "4630.txt"
// /4750, 95 outputs
#endif

#ifndef WEIGHTS_FILE
#define WEIGHTS_FILE "tmp_weights.txt"
#endif

#ifndef RESULTS_FILE
#define RESULTS_FILE "tmp_results.txt"
#endif

#ifndef DATABASE
#define DATABASE "testData.bin"
#endif

#ifndef OCR_RES
#define OCR_RES "document.txt"
#endif

#ifndef NETWORK_H_
#define NETWORK_H_

struct Neuron
{
    float  bias;
    int    nbInputs;
    float *weights;
    float  nabla_b;
    float  delta_nabla_b;
    float *nabla_w;
    float *delta_nabla_w;
    float  activation;
    float  z;
};

struct Layer
{
    int            nbNeurons;
    struct Neuron *neurons;
    float          sum_outputs;
};

struct Network
{
    int           nbLayers;
    int          *nbNeurons;
    struct Layer *layers;
};

struct TrainingData
{
    float *trainingInputs;
    int    res;
    int   *desiredOutput;
};

float sigmoid(float z);
float sigmoid_prime(float z);
float cost_derivative(float output_activation, int y);
float softmax(struct Network *n, int j);
double random_normal(void);
int highest(float result[], int size);
float* feedforward(struct Network *n,
                   int             iLayer,
                   float           inputsVect[]);
int test(struct Network *n, float inputsVect[]);
size_t evaluate(struct Network      *n,
                struct TrainingData  td[],
                size_t               size_td);
void backprop(struct Network *n,
              float           trainingInputs[],
              int             desiredOutput[]);
void update_mini_batch(struct Network      *n,
                       struct TrainingData *td,
                       struct TrainingData *td_end,
                       float                eta);
void SGD(struct Network      *n,
         struct TrainingData  td[],
         size_t               size_td,
         unsigned             epochs,
         unsigned             mini_batch_size,
         float                eta);
void SGD_eval(struct Network      *n,
              struct TrainingData  td[],
              size_t               size_td,
              unsigned             epochs,
              unsigned             mini_batch_size,
              float                eta);
void initNeuron(struct Neuron *_neuron, float _bias, int _nbInputs);
void initLayer(struct Layer *_layer, int _nbNeurons, int _nbInputs);
void initNetwork(struct Network *_network, int _nbLayers, int *_nbNeurons);
void array_print(int *begin, int *end);
void printNetwork(struct Network *n);
void openWeightsFile(struct Network *n, char fileName[]);
void writeWeightsFile(struct Network *n, char fileName[]);
void buildDataBase(FILE                *f,
                   struct TrainingData  td[],
                   size_t               size_td,
                   size_t               size_inputs,
                   size_t               size_outputs);
void readDataBase(FILE                 *f,
                  struct TrainingData  *td[],
                  size_t               *size_td,
                  size_t               *size_inputs,
                  size_t               *size_outputs);
void freeMemoryNetwork(struct Network *n);
void freeMemoryTD(struct TrainingData *td[], size_t size_td);
void randomInitScanf(struct Network *n);
void randomInit(struct Network *n, int input, int hidden, int output);
int* indexOutputToVector(int index, size_t len);
int isAcceptedByNeuralNetwork(float input[]);
int specialTreatment(float input[]);
int outputIntToChar(int outputInt);
void buildResultFile(struct Network *n,
                     int            *inputs[],
                     size_t          len,
                     char            fileName[]);
void buildResultFileTraining(struct Network      *n,
                             struct TrainingData  td[],
                             size_t               len,
                             char                 fileName[]);
int OCR(char *path, char *fileres);
int learning();
int recog(char *path);
int Xor();
#endif /* NETWORK_H_ */
