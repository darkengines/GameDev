////////////////////////////////////////////////////
// File name: ObjectModelConverver.cpp
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "ObjectModelConverter.h"

////////////////////////////////////////////////////
// Body: ObjectModelConverter
////////////////////////////////////////////////////

ObjectModelConverter::ObjectModelConverter(): ModelConverter() {

}

ObjectModelConverter::ObjectModelConverter(ObjectModelConverter& other) {

}

int ObjectModelConverter::Convert(const char* input, const char* output) {
	ifstream istream;
	istream.open(input, ifstream::in);
	if (!istream.is_open()) {
		cout<<"Could not open "<<input<<endl;
		return -1;
	}
	int result = 0;
	Vertex* vertices;
	Normal* normals;
	UV* UVs;
	FaceIndicesSet* faceIndicesSets;
	vertices = 0;
	normals = 0;
	UVs = 0;
	faceIndicesSets = 0;
	unsigned int verticesCount, normalsCount, UVsCount, faceIndicesSetsCount, dataCount;
	result = Load(istream, &vertices, &verticesCount, &normals, &normalsCount, &UVs, &UVsCount, &faceIndicesSets, &faceIndicesSetsCount);
	if (result < 0) {
		cout<<"Could not load "<<input<< "content"<<endl;
		return -1;
	}
	istream.close();
	unsigned int *indices, indicesCount;
	indices = 0;
	result = Perform(&vertices, verticesCount, &normals, normalsCount, &UVs, UVsCount, &faceIndicesSets, faceIndicesSetsCount, &dataCount, &indices, &indicesCount);
	if (result < 0) {
		cout<<"Could not perform "<<input<< "data"<<endl;
		return -1;
	}
	ofstream ostream;
	ostream.open(output, ofstream::out | ifstream::binary);
	if (!ostream.is_open()) {
		cout<<"Could not open "<<output<<endl;
		return -1;
	}
	result = Save(ostream, vertices, normals,  UVs, dataCount, indices, indicesCount);
	if (result < 0) {
		cout<<"Could not save converted "<<input<< "data"<<endl;
		return -1;
	}
	ostream.close();
	free(vertices);
	free(normals);
	free(UVs);
	free(indices);
	free(faceIndicesSets);
	return 0;
}

int ObjectModelConverter::Load(ifstream& istream,
							   Vertex** vertices,
							   unsigned int* verticesCount,
							   Normal** normals,
							   unsigned int* normalsCount,
							   UV** UVs,
							   unsigned int* UVsCount,
							   FaceIndicesSet** faceIndicesSets,
							   unsigned int* faceIndicesSetsCount) {
	int result = 0;
	result = LoadCounts(istream, verticesCount, normalsCount, UVsCount, faceIndicesSetsCount);
	if (result < 0) {
		cout<<"Could not count model data"<<endl;
		return -1;
	}
	*vertices = (Vertex*)malloc(sizeof(Vertex)*(int)verticesCount);
	if (!vertices) {
		cout<<"Vertices malloc error"<<endl;
		return -1;
	}
	*normals = (Normal*)malloc(sizeof(Normal)*(int)normalsCount);
	if (!vertices) {
		cout<<"Normals malloc error"<<endl;
		return -1;
	}
	*UVs = (UV*)malloc(sizeof(UV)*(int)UVsCount);
	if (!vertices) {
		cout<<"UVs malloc error"<<endl;
		return -1;
	}
	*faceIndicesSets = (FaceIndicesSet*)malloc(sizeof(FaceIndicesSet)*(int)faceIndicesSetsCount);
	if (!faceIndicesSets) {
		cout<<"FaceIndicesSet malloc error"<<endl;
		return -1;
	}
	result = LoadData(istream, vertices, *verticesCount, normals, *normalsCount, UVs, *UVsCount, faceIndicesSets, *faceIndicesSetsCount);
	if (result < 0) {
		cout<<"Could not load model data"<<endl;
		return -1;
	}
	return 0;
}

int ObjectModelConverter::Save(ofstream& stream,
							   Vertex* vertices,
							   Normal* normals,
							   UV* UVs,
							   unsigned int dataCount,
							   unsigned int* indices,
							   unsigned int indicesCount) {

	if (!stream.is_open()) {
		cout<<"Target model file is not open"<<endl;
		return -1;
	}
	stream.write((char*)&dataCount, sizeof(dataCount));
	stream.write((char*)&indicesCount, sizeof(indicesCount));
	stream.write((char*)vertices, sizeof(Vertex)*dataCount);
	stream.write((char*)normals, sizeof(Normal)*dataCount);
	stream.write((char*)UVs, sizeof(UV)*dataCount);
	stream.write((char*)indices, sizeof(unsigned int)*indicesCount);

	return 0;
}

int ObjectModelConverter::Perform(Vertex** vertices,
								  const unsigned int verticesCount,
								  Normal** normals,
								  const unsigned int normalsCount,
								  UV** UVs,
								  const unsigned int UVsCount,
								  FaceIndicesSet** faceIndicesSets,
								  const unsigned int faceIndicesSetsCount,
								  unsigned int* dataCount,
								  unsigned int** indices,
								  unsigned int* indicesCount) {
	unsigned int i;
	unsigned int position;
	unsigned int j = 0;
	queue<IndexFix*> toFix = queue<IndexFix*>();
	IndexFix* fix;
	i = *dataCount = 0;
	while (i<faceIndicesSetsCount) {
		if (!FaceIndicesSetsContains(*faceIndicesSets, i, (*faceIndicesSets)[i], &position)) {
			(*dataCount)++;
		} else {
			fix = new IndexFix();
			fix->index = i;
			fix->position = position;
			toFix.push(fix);
		}
		i++;
	}

	Vertex* fixedVertices;
	Normal* fixedNormals;
	UV* fixedUVs;
	unsigned int* fixedIndices;
	fixedVertices = 0;
	fixedNormals = 0;
	fixedUVs = 0;
	fixedIndices = 0;

	fixedVertices = (Vertex*)malloc(sizeof(Vertex)*(*dataCount));
	if (!fixedVertices) {
		cout<<"fixedVertices malloc error"<<endl;
		return -1;
	}
	fixedNormals = (Normal*)malloc(sizeof(Normal)*(*dataCount));
	if (!fixedNormals) {
		cout<<"fixedNormals malloc error"<<endl;
		return -1;
	}
	fixedUVs = (UV*)malloc(sizeof(UV)*(*dataCount));
	if (!fixedUVs) {
		cout<<"fixedUVs malloc error"<<endl;
		return -1;
	}
	fixedIndices = (unsigned int*)malloc(sizeof(unsigned int)*faceIndicesSetsCount);
	if (!fixedIndices) {
		cout<<"fixedIndices malloc error"<<endl;
		return -1;
	}

	i = j = 0;
	while (i<faceIndicesSetsCount) {
		if (!toFix.empty()) {
			fix = toFix.front();
		}
		if (i != fix->index) {
			fixedIndices[i] = j;
			fixedVertices[j].x = (*vertices)[(*faceIndicesSets)[i].v].x;
			fixedVertices[j].y = (*vertices)[(*faceIndicesSets)[i].v].y;
			fixedVertices[j].z = (*vertices)[(*faceIndicesSets)[i].v].z;
			fixedNormals[j].x = (*normals)[(*faceIndicesSets)[i].n].x;
			fixedNormals[j].y = (*normals)[(*faceIndicesSets)[i].n].y;
			fixedNormals[j].z = (*normals)[(*faceIndicesSets)[i].n].z;
			fixedUVs[j].u = (*UVs)[(*faceIndicesSets)[i].uv].u;
			fixedUVs[j].v = (*UVs)[(*faceIndicesSets)[i].uv].v;
			j++;
		} else {
			fixedIndices[i] = fixedIndices[fix->position];
			toFix.pop();
			delete fix;
		}
		i++;
	}

	free(*vertices);
	free(*normals);
	free(*UVs);
	*vertices = fixedVertices;
	*normals = fixedNormals;
	*UVs = fixedUVs;
	*indices = fixedIndices;
	*indicesCount = faceIndicesSetsCount;
	return 0;
}

int ObjectModelConverter::LoadCounts(ifstream& stream, unsigned int* verticesCount, unsigned int* normalsCount, unsigned int* UVsCount, unsigned int* facesIndicesSetsCount) {
	if (!stream.is_open()) {
		cout<<"Model stream is not open"<<endl;
		return -1;
	}
	stream.clear();
	stream.seekg(0);
	*verticesCount = *normalsCount = *UVsCount = *facesIndicesSetsCount = 0;
	char input;
	while (stream>>input) {
		if (input == 'v') {
			stream.get(input);
			if (input == ' ') {
				(*verticesCount)++;
			}
			if (input == 'n') {
				(*normalsCount)++;
			}
			if (input == 't') {
				(*UVsCount)++;
			}
		}
		if (input == 'f') {
			stream.get(input);
			if (input == ' ') {
				(*facesIndicesSetsCount)++;
			}
		}
	}
	(*facesIndicesSetsCount)*=3;
	return 0;
}

int ObjectModelConverter::LoadData(ifstream& stream,
							   Vertex** vertices,
							   const unsigned int verticesCount,
							   Normal** normals,
							   const unsigned int normalsCount,
							   UV** UVs,
							   const unsigned int UVsCount,
							   FaceIndicesSet** faceIndicesSets,
							   const unsigned int faceIndicesSetsCount) {
	if (!stream.is_open()) {
		cout<<"Model stream is not open"<<endl;
		return -1;
	}
	stream.clear();
	stream.seekg(0);
	char input, foo;
	unsigned int vertexIndex, normalIndex, UVIndex, faceIndicesSetIndex;
	vertexIndex = normalIndex = UVIndex = faceIndicesSetIndex = 0;
	while (stream>>input) {
		if (input == 'v') {
			stream.get(input);
			if (input == ' ') {
				stream>>(*vertices)[vertexIndex].x>>(*vertices)[vertexIndex].y>>(*vertices)[vertexIndex].z;
				(*vertices)[vertexIndex].z *= -1.0f;
				vertexIndex++;
			}
			if (input == 'n') {
				stream>>(*normals)[normalIndex].x>>(*normals)[normalIndex].y>>(*normals)[normalIndex].z;
				(*normals)[normalIndex].z *= -1.0f;
				normalIndex++;
			}
			if (input == 't') {
				stream>>(*UVs)[UVIndex].u>>(*UVs)[UVIndex].v;
				(*UVs)[UVIndex].v = 1.0f - (*UVs)[UVIndex].v;
				UVIndex++;
			}
		}
		if (input == 'f') {
			stream.get(input);
			if (input == ' ') {
				stream>>(*faceIndicesSets)[faceIndicesSetIndex+2].v>>foo>>(*faceIndicesSets)[faceIndicesSetIndex+2].uv>>foo>>(*faceIndicesSets)[faceIndicesSetIndex+2].n;
				(*faceIndicesSets)[faceIndicesSetIndex+2].v--;
				(*faceIndicesSets)[faceIndicesSetIndex+2].n--;
				(*faceIndicesSets)[faceIndicesSetIndex+2].uv--;
				stream>>(*faceIndicesSets)[faceIndicesSetIndex+1].v>>foo>>(*faceIndicesSets)[faceIndicesSetIndex+1].uv>>foo>>(*faceIndicesSets)[faceIndicesSetIndex+1].n;
				(*faceIndicesSets)[faceIndicesSetIndex+1].v--;
				(*faceIndicesSets)[faceIndicesSetIndex+1].n--;
				(*faceIndicesSets)[faceIndicesSetIndex+1].uv--;
				stream>>(*faceIndicesSets)[faceIndicesSetIndex].v>>foo>>(*faceIndicesSets)[faceIndicesSetIndex].uv>>foo>>(*faceIndicesSets)[faceIndicesSetIndex].n;
				(*faceIndicesSets)[faceIndicesSetIndex].v--;
				(*faceIndicesSets)[faceIndicesSetIndex].n--;
				(*faceIndicesSets)[faceIndicesSetIndex].uv--;
				faceIndicesSetIndex+=3;
			}
		}
	}
	return 0;
}

bool ObjectModelConverter::FaceIndicesSetsContains(FaceIndicesSet* faceIndicesSets, const unsigned int size, FaceIndicesSet faceIndicesSet, unsigned int* position) {

	unsigned int i;
	bool contains = false;
	i = 0;

	while (!contains && i<size) {
		contains = faceIndicesSets[i].v == faceIndicesSet.v
				&& faceIndicesSets[i].n == faceIndicesSet.n
				&& faceIndicesSets[i].uv == faceIndicesSet.uv;
		i++;
	}
	*position = i-1;
	return contains;
}