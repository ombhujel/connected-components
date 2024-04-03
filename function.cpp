#include "functions.h"

void zero2D(int **Ary) {
    for(int i = 0; i < numRows + 2; i++) {
        for(int j = 0; j < numCols + 2; j++) {
            Ary[i][j] = 0;
        }
    }
}

void loadImage(ifstream &infile, int **Ary) {
    string string_array[numRows + 1];
    int *translationarray = new int[numRows * numCols];
    string text;
    int j = 0;
    // First store line of file into array
    while(!infile.eof()) {
        getline(infile, text);
        string_array[j] = text;
        j++; 
        if(j == (numRows + 1)) {
            break;
        }  
    } 
    int k = 0; 
    // Convert string array into int array 1D
    for(int p = 1; p < numRows + 1; p++) {
        string s = string_array[p];
        stringstream ss(s);  
        string word;
        while (ss >> word) {
            translationarray[k] = stoi(word);   
            k++;
        }
    }
    // Finally convert to 2D
    int l = 0;
    for(int i = 1; i < numRows + 1; i++) {
        for(int j = 1; j < numCols + 1; j++) {
            int value = translationarray[l];
            Ary[i][j] = translationarray[l];
            l++;
        }
    }
}

void conversion(int **Ary) {
    for(int i = 1; i < numRows + 1; i++) {
        for(int j = 1; j < numCols + 1; j++) {
            if(Ary[i][j] == 0) {
                Ary[i][j] = 1;
            } else {
                Ary[i][j] = 0;
            }
        }
    }
}

int connected8Pass1(int **Ary, int Label, int *EQAry) {
    for(int i = 1; i < numRows + 1; i++) {
        for(int j = 1; j < numCols + 1; j++) {
            int a = Ary[i - 1][j - 1];
            int b = Ary[i - 1][j];
            int c = Ary[i - 1][j + 1];
            int d = Ary[i][j - 1];
            
            if(Ary[i][j] > 0) {
                if((a || b || c || d) != 0) {
                    int arr[] = { a, b, c, d };
                    int n = sizeof(arr) / sizeof(arr[0]);
                    sort(arr, arr + n);
                    int x = 0;
                    while(arr[x] == 0) {
                        x++;
                    }
                    int minimum = arr[x];
                    
                    Ary[i][j] = minimum;
                    if(a > minimum) {
                        EQAry[a] = minimum;
                    }
                    if(b > minimum) {
                        EQAry[b] = minimum;
                    }
                    if(c > minimum) {
                        EQAry[c] = minimum;
                    }
                    if(d > minimum) {
                        EQAry[d] = minimum;
                    }
                } else {
                    Label++;
                    Ary[i][j] = Label;
                    EQAry[Label] = Label;
                    continue;  
                } 
            }
        }
    }
    return Label;
}

void imgReformat(int **Ary, ofstream &File) {
    File << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
    string str = to_string(maxVal);
    int Width = str.length();
    int r = 1;
    while(r < numRows + 1) {
        int c = 1;
        while(c < numCols + 1) {
            File << Ary[r][c];
            str = to_string(Ary[r][c]);
            int WW = str.length();
            while(WW <= Width) {
                File << " ";
                WW++;
            }
            c++;
        }
        File << '\n';
        r++;
    }
}

void printEQAry(int Label, ofstream &file) {
    for(int i = 1; i < Label + 1; i++) {
        file << EQAry[i] << " " ;
    }
    file << endl;
}

void connected8Pass2(int **Ary, int *EQAry) {
    for(int i = numRows; i > 0; i--) {
        for(int j = numCols; j > 0; j--) {
            if(Ary[i][j] > 0) {
                int e = Ary[i][j + 1];
                int f = Ary[i + 1][j - 1];
                int g = Ary[i + 1][j];
                int h = Ary[i + 1][j + 1];
                if((e || f || g || h) != 0) {
                    int arr[] = { e, f, g, h };
                    int n = sizeof(arr) / sizeof(arr[0]);
                    sort(arr, arr + n);
                    int x = 0;
                    while(arr[x] == 0) {
                        x++;
                    }
                    int minimum = arr[x];
                    if(Ary[i][j] > minimum) {
                        EQAry[(Ary[i][j])] = minimum;
                        Ary[i][j] = minimum;
                        if(e > minimum) {
                            EQAry[e] = minimum;
                        }
                        if(f > minimum) {
                            EQAry[f] = minimum;
                        }
                        if(g > minimum) {
                            EQAry[g] = minimum;
                        }
                        if(h > minimum) {
                            EQAry[h] = minimum;
                        }
                    }
                }   
            }
        }
    } 
}

int manageEQAry(int *Ary, int label) {
    int readLabel = 0;
    int index = 1;
    while(index < label + 1) {
        if(index != Ary[index]) {
            Ary[index] = Ary[Ary[index]];
        } else {
            readLabel++;
            Ary[index] = readLabel;
        }
        index++;
    }
    int max = 0;
    for(int i = 1; i < label + 1; i++) {
        if(Ary[i] > max) {
            max = Ary[i];
        }
    }
    return max;
}

int connected4Pass1(int **Ary, int Label, int *EQAry) {
    for(int i = 1; i < numRows + 1; i++) {
        for(int j = 1; j < numCols + 1; j++) {
            int b = Ary[i - 1][j];
            int d = Ary[i][j - 1];
            if(Ary[i][j] > 0) {
                if((b || d) != 0) {     
                    int arr[] = { b, d };
                    int n =
