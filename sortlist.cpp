#include "sortlist.h"


Node::Node(string& id, int tm):m_id(id),m_tm(tm)
{
}

Node::Node(const char* id,int tm):m_id(id),m_tm(tm)
{
}

int Node::get_tm()
{
	return m_tm;
}

void Node::set_tm(int tm)
{
	this->m_tm = tm;
}

const string& Node::get_id()
{
	return m_id;
}

Node::~Node()
{}

bool compare_tm(Node& node1, Node& node2)
{
	return node1.get_tm() < node2.get_tm();
}

SortList::SortList()
{}

SortList::~SortList()
{}

void SortList::AddNode(Node& node)
{
	m_sortlist.push_back(node);
	m_sortlist.sort(compare_tm);
}

void SortList::AddNode(const char* id, int tm)
{
	Node node(id, tm);
	m_sortlist.push_back(node);
	m_sortlist.sort(compare_tm);	
}

list<Node> SortList::GetNodesByTm(int tm)
{
	list<Node> li;
	if (m_sortlist.empty())
		return li;
	list<Node>::iterator iter = m_sortlist.begin();
	for (;iter != m_sortlist.end();iter++)
	{
		int node_tm = (*iter).get_tm();
		if (node_tm <= tm)
		{
			li.push_back(*iter);			
		}
	}  
	return li;
}

bool SortList::UpdateNodeTm(const string& id, int tm)
{
	list<Node>::iterator iter = m_sortlist.begin();
	for (;iter!=m_sortlist.begin();iter++)
	{
		if ((*iter).get_id().compare(id))
		{
			(*iter).set_tm(tm);
			break;
		} 

	}
	m_sortlist.sort(compare_tm);
}

Node SortList::GetNodeById(const string& id)
{
	list<Node>::iterator iter = m_sortlist.begin();
	for (;iter!=m_sortlist.begin();iter++)
	{
		if ((*iter).get_id().compare(id)==0)
		{
			return *iter;
		} 

	}	
}

void SortList::PrintNodes()
{
	list<Node>::iterator iter = m_sortlist.begin();
	for (;iter!= m_sortlist.end();iter++)
	{
		cout << (*iter).get_id() << "   "<<(*iter).get_tm() <<endl;
	}
}

void SortList::DelNodeByIds(list<string> ids)
{
	list<string>::iterator iter = ids.begin();
	for(;iter != ids.end();iter++)
	{
		string id = *iter;
		for (list<Node>::iterator li_iter=m_sortlist.begin();li_iter != m_sortlist.end();)
		{
			if((*li_iter).get_id().compare(id)==0)
			{
				m_sortlist.erase(li_iter++);
			}else{ li_iter++;}
		}
	}
}
