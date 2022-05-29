#include "pch.h"
#include "gtest/gtest.h"
#include "..\Flows in networks\TransportNetwork.h"

TEST(Test_EasyNet) {
	TransportNetwork net = TransportNetwork();
	net.insertArc(new Arc('S', 'O', 3));
	net.insertArc(new Arc('S', 'P', 3));
	net.insertArc(new Arc('O', 'Q', 3));
	net.insertArc(new Arc('O', 'P', 2));
	net.insertArc(new Arc('P', 'R', 2));
	net.insertArc(new Arc('Q', 'R', 4));
	net.insertArc(new Arc('Q', 'T', 2));
	net.insertArc(new Arc('R', 'T', 3));

	ASSERT_EQ(net.maxFlow(), 0);

	net.FordFulkerson();
	ASSERT_EQ(net.maxFlow(), 5);
}

TEST(Test_HardNet) {
	TransportNetwork net = TransportNetwork();
	net.insertArc(new Arc('S', 'O', 16));
	net.insertArc(new Arc('S', 'P', 13));
	net.insertArc(new Arc('O', 'P', 10));
	net.insertArc(new Arc('O', 'Q', 12));
	net.insertArc(new Arc('P', 'O', 4));
	net.insertArc(new Arc('P', 'R', 14));
	net.insertArc(new Arc('Q', 'P', 9));
	net.insertArc(new Arc('Q', 'T', 20));
	net.insertArc(new Arc('R', 'Q', 7));
	net.insertArc(new Arc('R', 'T', 4));

	ASSERT_EQ(net.maxFlow(), 0);

	net.FordFulkerson();
	ASSERT_EQ(net.maxFlow(), 23);
}

TEST(Test_MediumNet) {
	TransportNetwork net = TransportNetwork();
	net.insertArc(new Arc('S', 'B', 19));
	net.insertArc(new Arc('S', 'C', 14));
	net.insertArc(new Arc('S', 'D', 20));
	net.insertArc(new Arc('B', 'E', 4));
	net.insertArc(new Arc('B', 'F', 4));
	net.insertArc(new Arc('C', 'E', 3));
	net.insertArc(new Arc('C', 'G', 9));
	net.insertArc(new Arc('D', 'F', 8));
	net.insertArc(new Arc('D', 'G', 9));
	net.insertArc(new Arc('E', 'H', 9));
	net.insertArc(new Arc('E', 'I', 5));
	net.insertArc(new Arc('F', 'H', 10));
	net.insertArc(new Arc('F', 'J', 5));
	net.insertArc(new Arc('G', 'I', 9));
	net.insertArc(new Arc('G', 'J', 10));
	net.insertArc(new Arc('H', 'T', 15));
	net.insertArc(new Arc('I', 'T', 11));
	net.insertArc(new Arc('J', 'T', 8));

	ASSERT_EQ(net.maxFlow(), 0);

	net.FordFulkerson();
	ASSERT_EQ(net.maxFlow(), 34);
}