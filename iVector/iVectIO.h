#ifndef IVECTIO_H
#define IVECTIO_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "document.h"
#include "FeatureSpace.h"
#include <vector>

const static int TRAINSET = 0;
const static int DEVSET = 1;
const static int EVLSET = 2;
const static int NISTSET = 3;
const static int TRAIN_AND_DEVSET = 4;

std::vector<Document> fetchDocumentsFromFileList(int speechSet, std::string fileListDir, std::string baseDir, int dim, bool limitFeature);
void fetchDocumentsFromFileList(std::vector<Document> & documents, std::string fullPath, std::string baseDir, int dim, int languageCol, int fileNameCol, int featureNameCol, int featureValueCol);
//vector<Document> fetchDocuments(int speechSet, string speechPath, int dim);
void writeDocuments(std::vector<Document> & documents, std::string fullPath);
FeatureSpace readSpace(std::string fullPath);
void writeSpace(FeatureSpace & space, std::string fullPath);

#endif
