#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<iostream>
#include<fstream>
#include<string>
#include <bits/stdc++.h>

using namespace std;

class property {
public: 
    int label;
    int numPixels;
    int minR;
    int minC;
    int maxR;
    int maxC;  
};

void zero2D(int **Ary);
void loadImage(ifstream &infile, int **Ary);
void conversion(int **Ary);
int connected8Pass1(int **Ary, int Label, int *EQAry);
void imgReformat(int **Ary, ofstream &File);
void printEQAry(int Label, ofstream &file);
void connected8Pass2(int **Ary, int *EQAry);
int manageEQAry(int *Ary, int label);
int connected4Pass1(int **Ary, int Label, int *EQAry);
void connected4Pass2(int **Ary, int *EQAry);
void connectPass3(int **Ary, int *EAry, property *CAry, int num, ofstream &File);
void connected4(int **Ary, int newLabel, int *EQAry, ofstream &File1, ofstream &File2);
void connected8(int **Ary, int newLabel, int *EQAry, ofstream &File1, ofstream &File2);
void printImg(int **Ary, ofstream &File);
void printCCProperty(ofstream &File);

#endif
