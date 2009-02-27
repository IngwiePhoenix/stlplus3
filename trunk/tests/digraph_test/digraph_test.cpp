#include "digraph.hpp"
#include "persistent_contexts.hpp"
#include "persistent_digraph.hpp"
#include "persistent_vector.hpp"
#include "persistent_string.hpp"
#include "persistent_int.hpp"
#include "persistent_shortcuts.hpp"
#include "build.hpp"
#include <vector>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

typedef stlplus::digraph<std::string,int> string_int_graph;

////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& output, string_int_graph::iterator i)
{
  return output << ((long)((void*)&*i)) << "->" << *i;
}

std::ostream& operator<<(std::ostream& output, string_int_graph::arc_iterator i)
{
  return output << ((long)((void*)&*i)) << "->" << *i;
}

std::ostream& operator<<(std::ostream& output, string_int_graph::arc_vector arcs)
{
  for (unsigned i = 0; i < arcs.size(); i++)
  {
    if (i > 0) output << " : ";
    output << arcs[i];
  }
  return output;
}

std::ostream& operator<<(std::ostream& output, string_int_graph::path_vector paths)
{
  for (unsigned i = 0; i < paths.size(); i++)
  {
    if (i > 0) output << " - ";
    output << paths[i];
  }
  return output;
}

std::ostream& operator<<(std::ostream& output, string_int_graph::node_vector nodes)
{
  for (unsigned i = 0; i < nodes.size(); i++)
  {
    if (i > 0) output << " - ";
    output << nodes[i];
  }
  return output;
}

std::ostream& operator<<(std::ostream& output, string_int_graph& graph)
{
  output << "nodes:" << std::endl;
  for (string_int_graph::iterator n = graph.begin(); n != graph.end(); ++n)
    output << n << " inputs: " << graph.inputs(n) << " outputs: " << graph.outputs(n) << std::endl;
  output << "arcs:" << std::endl;
  for (string_int_graph::arc_iterator a = graph.arc_begin(); a != graph.arc_end(); ++a)
    output << a << " from " << graph.arc_from(a) << " to " << graph.arc_to(a) << std::endl;
  return output;
}

////////////////////////////////////////////////////////////////////////////////

bool select_less_than_4 (const string_int_graph& graph, string_int_graph::const_arc_iterator arc)
{
  return abs(*arc) < 4;
}

bool select_natural (const string_int_graph& graph, string_int_graph::const_arc_iterator arc)
{
  return *arc >= 0;
}

static void test (string_int_graph& graph)
{
  for (string_int_graph::iterator i = graph.begin(); i != graph.end(); i++)
  {
    for (string_int_graph::iterator j = graph.begin(); j != graph.end(); j++)
    {
      if (!graph.adjacent(i, j))
        std::cout << "  " << *i << " is NOT adjacent to " << *j << std::endl;
      else
        std::cout << "  " << *i << " is adjacent to " << *j << std::endl;
      if (!graph.path_exists(i, j))
        std::cout << "  " << *i << " does NOT have a path to " << *j << std::endl;
      else
      {
        std::cout << "  " << *i << " has a path to " << *j << std::endl;
        std::cout << "  " << "paths from " << *i << " to " << *j << " are: " << graph.all_paths(i, j) << std::endl;
        std::cout << "  " << "shortest path from " << *i << " to " << *j << " is: " << graph.shortest_path(i, j) << std::endl;
      }
    }
    std::cout << "  " << "shortest paths for " << *i << " less than " << 4 << " are: " 
         << graph.shortest_paths(i, select_less_than_4) << std::endl;
    std::cout << "  " << "reachable nodes from " << *i << " are: " << graph.reachable_nodes(i) << std::endl;
    std::cout << "  " << "nodes which can reach " << *i << " are: " << graph.reaching_nodes(i) << std::endl;
  }
  std::pair<string_int_graph::node_vector,string_int_graph::arc_vector> sort = graph.sort(select_natural);
  std::cout << "  " << "topographical sort: " << sort.first;
  if (!sort.second.empty())
  {
    std::cout << ", errors = " << sort.second;
  }
  std::cout << std::endl;
  std::cout << "  " << "DAG sort: " << graph.dag_sort(select_natural) << std::endl;
}

void dump_string_int_graph(stlplus::dump_context& context, const string_int_graph& graph)
{
  stlplus::dump_digraph(context, graph, stlplus::dump_string, stlplus::dump_int);
}

void restore_string_int_graph(stlplus::restore_context& context, string_int_graph& graph)
{
  stlplus::restore_digraph(context, graph, stlplus::restore_string, stlplus::restore_int);
}

////////////////////////////////////////////////////////////////////////////////

typedef std::vector<string_int_graph::iterator> node_vector;

void dump_string_int_graph_iterator(stlplus::dump_context& context, const string_int_graph::iterator& node)
{
  stlplus::dump_digraph_iterator(context, node);
}

void dump_node_vector(stlplus::dump_context& context, const node_vector& nodes)
{
  stlplus::dump_vector(context, nodes, dump_string_int_graph_iterator);
}

void restore_string_int_graph_iterator(stlplus::restore_context& context, string_int_graph::iterator& node)
{
  stlplus::restore_digraph_iterator(context, node);
}

void restore_node_vector(stlplus::restore_context& context, node_vector& nodes)
{
  stlplus::restore_vector(context, nodes, restore_string_int_graph_iterator);
}

////////////////////////////////////////////////////////////////////////////////
 
typedef std::vector<string_int_graph::arc_iterator> arc_vector;

void dump_string_int_graph_arc_iterator(stlplus::dump_context& context, const string_int_graph::arc_iterator& arc)
{
  stlplus::dump_digraph_arc_iterator(context, arc);
}

void dump_arc_vector(stlplus::dump_context& context, const arc_vector& arcs)
{
  stlplus::dump_vector(context, arcs, dump_string_int_graph_arc_iterator);
}

void restore_string_int_graph_arc_iterator(stlplus::restore_context& context, string_int_graph::arc_iterator& arc)
{
  stlplus::restore_digraph_arc_iterator(context, arc);
}

void restore_arc_vector(stlplus::restore_context& context, arc_vector& arcs)
{
  stlplus::restore_vector(context, arcs, restore_string_int_graph_arc_iterator);
}

////////////////////////////////////////////////////////////////////////////////

class test_graph
{
public:
  string_int_graph m_graph;
  node_vector m_nodes;
  arc_vector m_arcs;

  string_int_graph::iterator insert(const std::string& node_data)
    {
      string_int_graph::iterator result = m_graph.insert(node_data);
      m_nodes.push_back(result);
      return result;
    }
  string_int_graph::arc_iterator arc_insert(string_int_graph::iterator from, string_int_graph::iterator to, int arc_data)
    {
      string_int_graph::arc_iterator result = m_graph.arc_insert(from,to,arc_data);
      m_arcs.push_back(result);
      return result;
    }

  void dump(stlplus::dump_context& context) const
    {
      dump_string_int_graph(context,m_graph);
      dump_node_vector(context,m_nodes);
      dump_arc_vector(context,m_arcs);
    }

  void restore(stlplus::restore_context& context)
    {
      restore_string_int_graph(context,m_graph);
      restore_node_vector(context,m_nodes);
      restore_arc_vector(context,m_arcs);
    }

  bool report (void)
    {
      bool result = true;
      std::cout << "== Graph ====================" << std::endl;
      std::cout << m_graph;
      std::cout << "== Nodes ====================" << std::endl;
      std::cout << m_nodes << std::endl;
      std::cout << "== Arcs =====================" << std::endl;
      std::cout << m_arcs << std::endl;
      std::cout << "== Tests ====================" << std::endl;
      for (unsigned n = 0; n < m_nodes.size(); n++)
      {
        if (m_nodes[n].owner() != &m_graph)
        {
          std::cout << "ERROR: node " << m_nodes[n] << " doesn't belong to graph" << std::endl;
          result = false;
        }
      }
      for (unsigned a = 0; a < m_arcs.size(); a++)
      {
        if (m_arcs[a].owner() != &m_graph)
        {
          std::cout << "ERROR: arc " << m_arcs[a] << " doesn't belong to graph" << std::endl;
          result = false;
        }
      }
      std::cout << "=============================" << std::endl;
      return result;
    }
};

////////////////////////////////////////////////////////////////////////////////

void dump_test_graph(stlplus::dump_context& context, const test_graph& graph)
{
  graph.dump(context);
}

void restore_test_graph(stlplus::restore_context& context, test_graph& graph)
{
  graph.restore(context);
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
  std::cerr << stlplus::build() << std::endl;

  bool result = true;

  try
  {
    test_graph graph;

    // Note: backward arcs are labelled with negative values
    string_int_graph::iterator node1 = graph.insert("node1");
    string_int_graph::iterator node2 = graph.insert("node2");
    string_int_graph::iterator node3 = graph.insert("node3");
    string_int_graph::iterator node4 = graph.insert("node4");
    string_int_graph::iterator node5 = graph.insert("node5");
    graph.arc_insert(node1, node2, 1);
    graph.arc_insert(node2, node4, 2);
    graph.arc_insert(node4, node3, 3);
    string_int_graph::arc_iterator arc4 = graph.arc_insert(node1, node3, 4);
    graph.arc_insert(node3, node5, 5);
    graph.arc_insert(node5, node4, -6);
    graph.arc_insert(node4, node4, -7);
    std::cout << "### initial graph:" << std::endl;
    result &= graph.report();
    test(graph.m_graph);

    std::cout << "dumping to file" << std::endl;
    stlplus::dump_to_file(graph, "test.tmp", dump_test_graph, 0);

//     graph.m_graph.arc_move(arc4, node3, node1);
//     std::cout << std::endl << "### after move:" << std::endl;
//     result &= graph.report();
//     test(graph.m_graph);

//     graph.m_graph.arc_flip(arc4);
//     std::cout << "after flip:" << std::endl;
//     result &= graph.report();
//     test(graph.m_graph);

    test_graph graph2;
    std::cout << "restoring from file" << std::endl;
    stlplus::restore_from_file("test.tmp", graph2, restore_test_graph, 0);
    std::cout << "after restore from file:" << std::endl;
    result &= graph2.report();
    test(graph2.m_graph);
  }
  catch(const std::exception& exception)
  {
    std::cout << "caught exception: " << exception.what() << std::endl;
    result = false;
  }
  catch(...)
  {
    std::cout << "caught unknown exception" << std::endl;
    result = false;
  }
  if (result)
    std::cout << "... test PASSED" << std::endl;
  else
    std::cout << "... test FAILED" << std::endl;
  return result ? 0 : 1;
}
