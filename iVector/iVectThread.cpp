#include "iVectThread.h"
#include <boost/numeric/ublas/vector.hpp>

using namespace std;
/*
Wrapper to do the iterative newton-raphson updates in parallell.
*/


boost::mutex counterMutex;
unsigned int takenFrom;

void updateiVectorRange(vector<Document> &documents, FeatureSpace &space) {
	while (takenFrom < documents.size()) {
		int next = -1;
		{
			//Scoped mutex lock
			boost::mutex::scoped_lock lock(counterMutex);
			if (takenFrom < documents.size()) {
				next = takenFrom++;
			}
		}
		if (next >= 0) {
			//updateiVector(documents[next], space);
			updateiVectorCheckLike(documents[next], space);
		}
	}
}

void updateiVectors(vector<Document> &documents, FeatureSpace &space, int numOfThreads) {
	takenFrom = 0;
	boost::thread_group threads;
	for (int i = 0; i < numOfThreads; i++) {
		boost::thread * thread = new boost::thread(updateiVectorRange, boost::ref(documents), boost::ref(space));
		threads.add_thread(thread);
	}
	threads.join_all();
}
void updatetRowRange(vector<Document> &documents, FeatureSpace &space, boost::numeric::ublas::vector<double> &denominators, vector<Document> & devDocs) {
	while (takenFrom < space.height) {
		int next = -1;
		{
			//Scoped mutex lock
			boost::mutex::scoped_lock lock(counterMutex);
			if (takenFrom < space.height) {
				next = takenFrom++;
			}
		}
		if (next >= 0) {
			updatetRow(documents, space, next, denominators);
			//updatetRowPart(documents, space, next, denominators);
			//updatetRowCheckLike(documents, space, next, denominators, devDocs);
		}
	}
}

void updatetRows(std::vector<Document> &documents, FeatureSpace & space, int numOfThreads, std::vector<Document> & devDocs) {	
	takenFrom = 0;
	boost::numeric::ublas::vector<double> denominators = calcAllPhiDenominators(space, documents);
	boost::thread_group threads;
	for (int i = 0; i < numOfThreads; i++) {
		boost::thread * thread = new boost::thread(updatetRowRange, boost::ref(documents), boost::ref(space), boost::ref(denominators), boost::ref(devDocs));
		threads.add_thread(thread);
	}
	threads.join_all();
}

void updatetRows(vector<Document> & documents, FeatureSpace & space, int numOfThreads) {
	updatetRows(documents, space, numOfThreads, documents);
}