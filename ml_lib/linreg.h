#ifndef LINREG_H
#define LINREG_H

enum ActivationFunction{
    ReLU,
    Sigmoid,
    Softmax,
    Linear,
    NUM_ACTIVATION
};

const char *ActivationFunctionName[NUM_ACTIVATION] = {
    "relu",
    "sigmoid",
    "softmax",
    "linear"
};


enum LossFunction {
    MSE,
    MAE,
    RMSE,
    binary_crossentropy,
    categorical_crossentropy,
    NUM_LOSS
};

const char *LossFunctionNAME[NUM_LOSS] = {
    "mse",
    "mae",
    "rmse",
    "binary crossentropy",
    "categorical crossentropy"
};


typedef struct LiniarModel LiniarModel;
typedef struct DataSet DataSet;


struct LiniarModel{
    float *weights;
    int grade;
    float bias;
    enum ActivationFunction activation;
    enum LossFunction loss;
    void (*train)(LiniarModel *model, const DataSet dataset, enum LossFunction loss);
};

struct DataSet{
    float **X;
    int dimension;
};

LiniarModel initializeModel(int grade, enum ActivationFunction activation);
void showValuesW(const LiniarModel model);
void train(LiniarModel *model, const DataSet dataset, enum LossFunction loss);
float computeMSE(const float *predicted, const DataSet dataset);
float computeMAE(const float *predicted, const DataSet dataset);
float computeLoss(enum LossFunction losstype, const float *predicted, const DataSet dataset);
float *predict(const LiniarModel model, const DataSet dataset);
void destroyModel(const LiniarModel model);


DataSet loadDataset(char *filename);
void printData(const DataSet dataset);
void printRandomSample(const DataSet dataset);
void destoryDataSet(DataSet dataset);

#endif
