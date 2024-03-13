#include "ml_lib/linreg.h"

int main(){

// Dataset for the training part

    char filename[] = "artificial_data/housing_prices2.txt";
    DataSet my_dataset;
    my_dataset = loadDataset(filename);
    // printRandomSample(my_dataset);


    int grade = 1;
    LiniarModel my_linearModel;
    
    // initializeModel(grade, activation_function)
    // Activation functions are te following: ReLU, Sigmoid, Softmax, Linear,
    my_linearModel = initializeModel(grade, Linear);

    // Loss functions are the following : MSE, MAE, RMSE, binary_crossentropy, categorical_crossentropy,
    // train(&linearmodel, dataset, loss function, alpha, epochs)
    my_linearModel.train(&my_linearModel, my_dataset, MAE, 0.000001, 200);
    showValuesW(my_linearModel);


// Load the second dataset that will be used for testing

    // Preparing the dataset
    char filename2[] = "artificial_data/housing_prices.txt";
    DataSet test_dataset = loadDataset(filename2);

    // Predicting the values
    float *result = predict(my_linearModel, test_dataset);
    compare5Samples(test_dataset, result);


    // freeing the allocated memory
    free(result);
    destroyModel(my_linearModel);
    destoryDataSet(my_dataset);
    destoryDataSet(test_dataset);
    return 0;

}