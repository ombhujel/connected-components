#include "functions.h"

int main(int argc, char** argv) {
    // Main function
    ifstream inFile; inFile.open(argv[1]);
    connectness = atoi (argv[2]);
    option = argv[3];
    ofstream RFpettyPrintFile; RFpettyPrintFile.open(argv[4]);
    ofstream labelFile; labelFile.open(argv[5]);
    ofstream propertyFile; propertyFile.open(argv[6]);
    ofstream deBugFile; deBugFile.open(argv[7]);
    while(inFile >> numRows >> numCols >> minVal >> maxVal){break;}
    zeroFramedAry = new int*[numRows+2];
    for(int i = 0; i < numCols+2 ; i++){
        zeroFramedAry[i]=new int[numCols+2];
    }
    EQAry = new int[(numRows*numCols)/4];
    newLabel = 0;
    zero2D(zeroFramedAry);
    loadImage(inFile, zeroFramedAry);
    
    if(option == "Y"|| option == "y"){
        conversion(zeroFramedAry);
    }
    if(connectness == 4){
        connected4(zeroFramedAry, newLabel, EQAry, RFpettyPrintFile, deBugFile);
    }
    if(connectness == 8){
        connected8(zeroFramedAry, newLabel, EQAry, RFpettyPrintFile, deBugFile);
    }
    labelFile << numRows << " " << numCols << " " << newMin << " " << newMax << endl;
    printImg(zeroFramedAry, labelFile);
    printCCProperty(propertyFile);
    CCproperty[trueNumCC+1].drawBoxes(zeroFramedAry, CCproperty, trueNumCC);
    RFpettyPrintFile << "The image Reformat after draw Boxes " << endl;
    imgReformat(zeroFramedAry, RFpettyPrintFile);
    RFpettyPrintFile << "The trueNumCC is " << trueNumCC << endl;

    inFile.close();
    RFpettyPrintFile.close();
    labelFile.close();
    propertyFile.close();
    deBugFile.close();
}
