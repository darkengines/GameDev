////////////////////////////////////////////////////
// File name: ObjectModelConverver.h
////////////////////////////////////////////////////

#ifndef _OBJECTMODELCONVERTER_H_
#define _OBJECTMODELCONVERTER_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "ModelConverter.h"

////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////

typedef struct {
	unsigned int v, n, uv;
} FaceIndicesSet;

typedef struct {
	unsigned int position, index;
} IndexFix;

////////////////////////////////////////////////////
// Class name: ObjectModelConverver.h
////////////////////////////////////////////////////

class ObjectModelConverter: public ModelConverter {
private:
public:
	ObjectModelConverter();
	ObjectModelConverter(ObjectModelConverter&);
	int Convert(const char*, const char*);
private:
	int Perform(Vertex**, const unsigned int, Normal**, const unsigned int, UV**, const unsigned int, FaceIndicesSet**, const unsigned int, unsigned int*, unsigned int**, unsigned int*);
	int Load(ifstream&, Vertex**, unsigned int*, Normal**, unsigned int*, UV**, unsigned int*, FaceIndicesSet**, unsigned int*);
	int Save(ofstream&, Vertex*, Normal*, UV*, unsigned int, unsigned int*, const unsigned int);
	int LoadCounts(ifstream&, unsigned int*, unsigned int*, unsigned int*, unsigned int*);
	int LoadData(ifstream&, Vertex**, unsigned int, Normal**, unsigned int, UV**, unsigned int, FaceIndicesSet**, unsigned int);
	bool FaceIndicesSetsContains(FaceIndicesSet*, const unsigned int, FaceIndicesSet, unsigned int*);
};

#endif