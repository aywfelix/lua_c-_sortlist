#include "sortlist.h"


int main(int argc, char const *argv[])
{
	SortList sortList;
	string s = "wew";
	Node nd1(s,12345);
	s = "seds";
	Node nd2(s,2344);
	s = "sdfga";
	Node nd3(s,53125);
	s = "sdg";
	Node nd4(s,7343);
	s = "dhfsfdfg";
	Node nd5(s,234);
	s = "ergesrfs";
	Node nd6(s,25525);
	s = "fergsda";
	Node nd7(s,74535);
	s = "seaare";
	Node nd8(s,273524);
	sortList.AddNode(nd1);
	sortList.AddNode(nd2);
	sortList.AddNode(nd3);
	sortList.AddNode(nd4);
	sortList.AddNode(nd5);
	sortList.AddNode(nd6);
	sortList.AddNode(nd7);
	sortList.AddNode(nd8);

	char * ss = "aaaabbbb";
	//Node nd9(ss,43213);
	sortList.AddNode(ss,43213);

   sortList.PrintNodes();
   cout << "=========================="<<endl;
	list<Node> mylist = sortList.GetNodesByTm(25525);
	list<Node>::iterator iter = mylist.begin();
	for (;iter != mylist.end(); iter++)
	{
		Node node = *iter;
		cout << node.get_id() << "    "<<node.get_tm() <<endl;
	}
	cout << "=========================="<<endl;
	//delete node
	list<string> ids;
	for(list<Node>::iterator iter=mylist.begin();iter!=mylist.end();iter++)
	{
		ids.push_back((*iter).get_id());
	}

	sortList.DelNodeByIds(ids);
	sortList.PrintNodes();
	return 0;
}