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
	
	Arc(char v1, char v2, unsigned int tp) {
		this->starting = v1;
		this->destination = v2;
		this->throughput = tp;
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

	Vertex(char v) {
		this->symbol = v;
		this->goNextBy = new List<Arc*>();
	}
	Vertex() {
		this->symbol = 0;
		this->goNextBy = new List<Arc*>();
	}
};

class TransportNetwork {
private:
	Vertex* getVertex(char v) {
		Vertex* result = new Vertex();
		EoList<Vertex*>* cur = listVertexes->head;
		while (cur != NULL) {
			if (cur->data->symbol == v) result = cur->data;
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
		Vertex* cur = source;
		impossibleVertices->pushback(cur->symbol);
		while (cur != stock) {
			if (cur->goNextBy->head == NULL) {

				if (cur != source) {
					cur = getVertex(result->tail->data->starting);
					result->popback();
				}
				else break;
			}
			else {

				Vertex* oldCur = cur;
				EoList<Arc*>* tmp = cur->goNextBy->head;
				while (tmp != NULL) {
					if (tmp->data->flow == tmp->data->throughput || impossibleVertices->isContain(tmp->data->destination)) tmp = tmp->next;
					else {
						cur = getVertex(tmp->data->destination);
						result->pushback(tmp->data);
						impossibleVertices->pushback(tmp->data->destination);
						break;
					}
				}
				if (cur == oldCur) {
					if (cur != source) {
						cur = getVertex(result->tail->data->starting);
						result->popback();
					}
					else break;
				}
			}
		}
		return result;
	}

	void setFlowPath(List<Arc*>* transportPath) {
		EoList<Arc*>* cur = transportPath->head;
		unsigned int cmin = cur->data->throughput - cur->data->flow;
		while (cur != NULL) {
			if (cur->data->throughput - cur->data->flow < cmin) {
				cmin = cur->data->throughput - cur->data->flow;
			}
			cur = cur->next;
		}
		cur = transportPath->head;
		while (cur != NULL) {
			cur->data->flow += cmin;
			Vertex* tmpVertex = getVertex(cur->data->destination);
			bool check = false;
			EoList<Arc*>* tmpArc = tmpVertex->goNextBy->head;
			while (tmpArc != NULL) {
				if (tmpArc->data->destination == cur->data->starting) {
					tmpArc->data->throughput += cmin;
					check = true;
					break;
				}
				tmpArc = tmpArc->next;
			}
			if (check == false) {
				Arc* newArc = new Arc(cur->data->destination, cur->data->starting, cmin);
				tmpVertex->goNextBy->pushback(newArc);
			}
			cur = cur->next;
		}
	}

public:
	Vertex* source;
	Vertex* stock;
	List<Vertex*>* listVertexes;

	void insertArc(Arc* newArc) {
		EoList<Vertex*>* cur = listVertexes->head;
		bool check1 = false;
		bool check2 = false;
		while (cur != NULL) {
			if (check1 == false && cur->data->symbol == newArc->starting) {
				cur->data->goNextBy->pushback(newArc);
				check1 = true;
			}
			else if (check2 == false && cur->data->symbol == newArc->destination) {
				check2 = true;
			}
			else if (check1 == true && check2 == true) break;
			cur = cur->next;
		}
		if (check1 != true) {
			Vertex* newVertex = new Vertex(newArc->starting);
			newVertex->goNextBy->pushback(newArc);
			listVertexes->pushback(newVertex);
		};
		if (check2 != true) {
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
				char v1 = NULL;
				char v2 = NULL;
				string value = "";
				for (size_t i = 0; i < tmp.length(); i++) {
					if (v1 == NULL) {
						v1 = tmp[i];
					}
					else {
						if (tmp[i] != ' ') {
							if (v2 == NULL) {
								v2 = tmp[i];
							}
							else value += tmp[i];
						}
					}
				}
				Arc* newArc = new Arc(v1, v2, toInt(value));
				insertArc(newArc);
			}
			file.close();
		}

	}

	void FordFulkerson() {
		int i = 1;
		while (1) {
			List<Arc*>* transportPath = getTransportPath();
			if (!transportPath->isEmpty()) setFlowPath(transportPath);
			else break;
		}
	}

	unsigned int maxFlow() {
		unsigned int max = 0;
		EoList<Arc*>* cur = source->goNextBy->head;
		while (cur != NULL) {
			max += cur->data->flow;
			cur = cur->next;
		}
		return max;
	}
	
	TransportNetwork() {
		this->source = new Vertex('S');
		this->stock = new Vertex('T');
		this->listVertexes = new List<Vertex*>();
		this->listVertexes->pushback(source);
		this->listVertexes->pushback(stock);
	}
};
