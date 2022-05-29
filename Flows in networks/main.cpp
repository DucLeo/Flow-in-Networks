#include "TransportNetwork.h"

int main()
{
	TransportNetwork net = TransportNetwork();
	net.takeData("file.txt");
	cout << "Original data after processing data from file, list of arcs:\n";
	cout << "Format: [starting] [destination] [flow] [throughput]\n\n";
	EoList<Vertex*>* cur = net.listVertexes->head;
	while (cur != NULL) {
		EoList<Arc*>* tmp = cur->data->goNextBy->head;
		while (tmp != NULL) {
			cout << tmp->data->starting << " " << tmp->data->destination << " " << tmp->data->flow << " " << tmp->data->throughput << endl;
			tmp = tmp->next;
		}
		cur = cur->next;
	}

	net.FordFulkerson();

	cout << "\n\nList of edges after implementing Ford-Fulkerson's algorithm:\n";
	cout << "Format: [starting] [destination] [flow] [throughput]\n\n";
	cur = net.listVertexes->head;
	while (cur != NULL) {
		EoList<Arc*>* tmp = cur->data->goNextBy->head;
		while (tmp != NULL) {
			cout << tmp->data->starting << " " << tmp->data->destination << " " << tmp->data->flow << " " << tmp->data->throughput << endl;
			tmp = tmp->next;
		}
		cur = cur->next;
	}

	cout << "\n\nThe MAX flow: " << net.maxFlow() << endl;
	
}
