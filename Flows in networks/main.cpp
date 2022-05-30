#include "TransportNetwork.h"

int main()
{
	TransportNetwork net = TransportNetwork();
	net.takeData("file.txt");
	cout << "Original data after processing data from file, list of arcs:\n";
	cout << "Format: [starting] [destination] [flow] [throughput]\n\n";
	EoList<Vertex*>* curVertex = net.listVertexes->head;
	while (curVertex != NULL) {
		EoList<Arc*>* curArc = curVertex->data->goNextBy->head;
		while (curArc != NULL) {
			cout << curArc->data->starting << " " << curArc->data->destination << " " << curArc->data->flow << " " << curArc->data->throughput << endl;
			curArc = curArc->next;
		}
		curVertex = curVertex->next;
	}

	net.FordFulkerson();

	cout << "\n\nList of edges after implementing Ford-Fulkerson's algorithm:\n";
	cout << "Format: [starting] [destination] [flow] [throughput]\n\n";
	curVertex = net.listVertexes->head;
	while (curVertex != NULL) {
		EoList<Arc*>* curArc = curVertex->data->goNextBy->head;
		while (curArc != NULL) {
			cout << curArc->data->starting << " " << curArc->data->destination << " " << curArc->data->flow << " " << curArc->data->throughput << endl;
			curArc = curArc->next;
		}
		curVertex = curVertex->next;
	}

	cout << "\n\nThe MAX flow: " << net.maxFlow() << endl;
}
