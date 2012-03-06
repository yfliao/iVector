#ifndef IVECTMATH_H
#define IVECTMATH_H
#include <math.h>
#include "Document.h"
#include "FeatureSpace.h"
#include <boost/numeric/ublas/vector.hpp>
#include <vector>

boost::numeric::ublas::vector<double> calcAllPhiDenominators(FeatureSpace & space, std::vector<Document> & documents);
double calcAvgEuclideanDistance(std::vector<Document> & documents);
double calcTotalLikelihood(std::vector<Document> & documents, FeatureSpace & space);
double calcTotalLikelihoodExcludeInf(std::vector<Document> & documents, FeatureSpace & space);

void updateiVectors(std::vector<Document> & documents, FeatureSpace & space);
void updateiVectorCheckLike(Document & document, FeatureSpace & space);
void updateiVector(Document & document, FeatureSpace & space);

void updatetRows(std::vector<Document> & documents, FeatureSpace & space);
void updatetRow(std::vector<Document> & documents, FeatureSpace & space, unsigned int row, boost::numeric::ublas::vector<double> & denominators);

#endif
