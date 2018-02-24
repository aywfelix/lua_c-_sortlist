#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <sys/types.h>
#include <errno.h>
#include <cstdio>
#include <list>
#include <algorithm>
#include <string>
#include <functional>  

using namespace std;
using  std::list;
using  std::string;


//define node 
class Node
{
public:
	Node(string& id, int tm);
	Node(const char* id,int tm);
	int get_tm();
	void set_tm(int tm);
	const string& get_id();
	virtual ~Node();
private:
	string m_id;
	int m_tm;
};

bool compare_tm(Node& node1, Node& node2);

class SortList
{
public:
	SortList();
	void AddNode(Node&);   //add new node to sortlist
	void AddNode(const char* id, int tm);
	list<Node> GetNodesByTm(int tm);     //get nodes from sortlist by node'tm before tm
	bool UpdateNodeTm(const string& id,int tm);
	Node GetNodeById(const string& id);
	void PrintNodes();

	void DelNodeByIds(list<string> ids);
	~SortList();
private:
	std::list<Node> m_sortlist;
};


#endif