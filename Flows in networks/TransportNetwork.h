#pragma once
#include <fstream>
#include <string>
#include "..\BRT\List.h"

class Arc {
public:
	char starting;
	char destination;
	unsigned int throughput;
	unsigned int flow;
	
	Arc(char v1, char v2, unsigned int throughput) {
		this->starting = v1;
		this->destination = v2;
		this->throughput = throughput;
		this->flow = 0;
	}
	
	Arc() {
		this->starting = NULL;
		this->destination = NULL;
		this->throughput = 0;
		this->flow = 0;
	}
};

class Vertex {
public:
	char symbol;
	List<Arc*>* goNextBy;

	Vertex(char nameVertex) {
		this->symbol = nameVertex;
		this->goNextBy = new List<Arc*>();
	}
	Vertex() {
		this->symbol = 0;
		this->goNextBy = new List<Arc*>();
	}
};

class TransportNetwork {
private:
	Vertex* getVertex(char nameVertex) {
		Vertex* result = new Vertex();
		EoList<Vertex*>* cur = listVertexes->head;
		while (cur != NULL) {
			if (cur->data->symbol == nameVertex) result = cur->data;
			cur = cur->next;
		}
		if (result->symbol == NULL) throw logic_error("Not this vertex in network!");
		else return result;
	}

	int toInt(string org) {
		if (org.length() == 0) throw logic_error("Error number!");
		else {
			if (org[0] == '0' && org.length() > 1) throw invalid_argument("Error number!");
			else {
				unsigned int number = 0;
				for (int i = 0; i < org.length(); i++) {
					switch (org[i])
					{
					case '0':
						number += (int)(0 * pow(10, org.length() - 1 - i));
						break;
					case '1':
						number += (int)(1 * pow(10, org.length() - 1 - i));
						break;
					case '2':
						number += (int)(2 * pow(10, org.length() - 1 - i));
						break;
					case '3':
						number += (int)(3 * pow(10, org.length() - 1 - i));
						break;
					case '4':
						number += (int)(4 * pow(10, org.length() - 1 - i));
						break;
					case '5':
						number += (int)(5 * pow(10, org.length() - 1 - i));
						break;
					case '6':
						number += (int)(6 * pow(10, org.length() - 1 - i));
						break;
					case '7':
						number += (int)(7 * pow(10, org.length() - 1 - i));
						break;
					case '8':
						number += (int)(8 * pow(10, org.length() - 1 - i));
						break;
					case '9':
						number += (int)(9 * pow(10, org.length() - 1 - i));
						break;
					default:
						throw invalid_argument("Error number!");
					}
				}
				return number;
			}
		}
	}

	List<Arc*>* getTransportPath() {
		List<char>* impossibleVertices = new List<char>;
		List<Arc*>* result = new List<Arc*>();
		Vertex* curVertex = source;
		impossibleVertices->pushback(curVertex->symbol);
		while (curVertex != stock) {
			if (curVertex->goNextBy->head == NULL) {

				if (curVertex != source) {
					curVertex = getVertex(result->tail->data->starting);
					result->popback();
				}
				else break;
			}
			else {
				Vertex* oldVertex = curVertex;
				EoList<Arc*>* tmpArc = curVertex->goNextBy->head;
				while (tmpArc != NULL) {
					if (tmpArc->data->flow == tmpArc->data->throughput || impossibleVertices->isContain(tmpArc->data->destination)) tmpArc = tmpArc->next;
					else {
						curVertex = getVertex(tmpArc->data->destination);
						result->pushback(tmpArc->data);
						impossibleVertices->pushback(tmpArc->data->destination);
						break;
					}
				}
				if (curVertex == oldVertex) {
					if (curVertex != source) {
						curVertex = getVertex(result->tail->data->starting);
						result->popback();
					}
					else break;
				}
			}
		}
		return result;
	}

	void setFlowPath(List<Arc*>* transportPath) {
		EoList<Arc*>* curArc = transportPath->head;
		unsigned int cmin = curArc->data->throughput - curArc->data->flow;
		while (curArc != NULL) {
			if (curArc->data->throughput - curArc->data->flow < cmin) {
				cmin = curArc->data->throughput - curArc->data->flow;
			}
			curArc = curArc->next;
		}
		curArc = transportPath->head;
		while (curArc != NULL) {
			curArc->data->flow += cmin;
			Vertex* tmpVertex = getVertex(curArc->data->destination);
			bool check = false;
			EoList<Arc*>* tmpArc = tmpVertex->goNextBy->head;
			while (tmpArc != NULL) {
				if (tmpArc->data->destination == curArc->data->starting) {
					tmpArc->data->throughput += cmin;
					check = true;
					break;
				}
				tmpArc = tmpArc->next;
			}
			if (check == false) {
				Arc* newArc = new Arc(curArc->data->destination, curArc->data->starting, cmin);
				tmpVertex->goNextBy->pushback(newArc);
			}
			curArc = curArc->next;
		}
	}

public:
	Vertex* source;
	Vertex* stock;
	List<Vertex*>* listVertexes;

	void insertArc(Arc* newArc) {
		EoList<Vertex*>* curVertex = listVertexes->head;
		bool checkStarting = false;
		bool checkDestination = false;
		while (curVertex != NULL) {
			if (checkStarting == false && curVertex->data->symbol == newArc->starting) {
				curVertex->data->goNextBy->pushback(newArc);
				checkStarting = true;
			}
			else if (checkDestination == false && curVertex->data->symbol == newArc->destination) {
				checkDestination = true;
			}
			else if (checkStarting == true && checkDestination == true) break;
			curVertex = curVertex->next;
		}
		if (checkStarting != true) {
			Vertex* newVertex = new Vertex(newArc->starting);
			newVertex->goNextBy->pushback(newArc);
			listVertexes->pushback(newVertex);
		};
		if (checkDestination != true) {
			Vertex* newVertex = new Vertex(newArc->destination);
			listVertexes->pushback(newVertex);
		}
	}

	void takeData(string fileName) {
		fstream file(fileName);
		if (!file.is_open()) throw invalid_argument("Could not open file!");
		else {
			string tmp;
			while (getline(file, tmp, '\n')) {
				char starting = NULL;
				char destination = NULL;
				string throughput = "";
				for (size_t i = 0; i < tmp.length(); i++) {
					if (starting == NULL) {
						starting = tmp[i];
					}
					else {
						if (tmp[i] != ' ') {
							if (destination == NULL) {
								destination = tmp[i];
							}
							else throughput += tmp[i];
						}
					}
				}
				Arc* newArc = new Arc(starting, destination, toInt(throughput));
				insertArc(newArc);
			}
			file.close();
		}

	}

	void FordFulkerson() {
		List<Arc*>* transportPath = getTransportPath();
		while (!transportPath->isEmpty()) {
			setFlowPath(transportPath);
			transportPath = getTransportPath();
		}
	}

	unsigned int maxFlow() {
		unsigned int maxFlow = 0;
		EoList<Arc*>* curArc = source->goNextBy->head;
		while (curArc != NULL) {
			maxFlow += curArc->data->flow;
			curArc = curArc->next;
		}
		return maxFlow;
	}
	
	TransportNetwork() {
		this->source = new Vertex('S');
		this->stock = new Vertex('T');
		this->listVertexes = new List<Vertex*>();
		this->listVertexes->pushback(source);
		this->listVertexes->pushback(stock);
	}
};
