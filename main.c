#include "ml_lib/linreg.h"

int main(){

    char filename[] = "artificial_data/housing_prices.txt";
    DataSet my_dataset;
    my_dataset = loadDataset(filename);
    printRandomSample(my_dataset);


    int grade = 1;
    LiniarModel my_linearModel;
    my_linearModel = initializeModel(grade, Sigmoid);
    showValuesW(my_linearModel);
    
    float *result = predict(my_linearModel, my_dataset);

    printf("The results of the prediction are: \n");
    for(int i=0; i<3; ++i){
        printf("%f ", result[i]);
    }
    printf("\n");
    
    my_linearModel.train(&my_linearModel, my_dataset, MSE);
    
    
    
    destroyModel(my_linearModel);
    destoryDataSet(my_dataset);
    return 0;

}