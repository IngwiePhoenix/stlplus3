#include "persistent_ntree.hpp"
#include "persistent_map.hpp"
#include "persistent_string.hpp"
#include "persistent_shortcuts.hpp"
#include "file_system.hpp"
#include <string>
#include <map>

////////////////////////////////////////////////////////////////////////////////

#define NUMBER 1000
#define DATA "ntree_test.tmp"
#define MASTER "ntree_test.dump"

////////////////////////////////////////////////////////////////////////////////

typedef stlplus::ntree<std::string> string_tree;

////////////////////////////////////////////////////////////////////////////////

void dump_string_tree(stlplus::dump_context& context, const string_tree& data)
{
  stlplus::dump_ntree(context, data, stlplus::dump_string);
}

void restore_string_tree(stlplus::restore_context& context, string_tree& data)
{
  stlplus::restore_ntree(context, data, stlplus::restore_string);
}

// recursive part of the comparison
bool compare_r(const string_tree& left, const string_tree::const_iterator& left_i,
               const string_tree& right, const string_tree::const_iterator& right_i)
{
  bool result = true;
  // compare this node, then recursively compare the children
  if (*left_i != *right_i)
  {
    std::cerr << "left = \"" << *left_i << "\" is different from right = \"" << *right_i << "\"" << std::endl;
    result = false;
  }
  if (left.children(left_i) != right.children(right_i))
  {
    std::cerr << "left = \"" << *left_i << "\" has different number of children from right = \"" << *right_i << "\"" << std::endl;
    result = false;
  }
  else
  {
    for (unsigned i = 0; i < left.children(left_i); i++)
      result &= compare_r(left, left.child(left_i,i), right, right.child(right_i,i));
  }
  return result;
}

bool compare(const string_tree& left, const string_tree& right)
{
  // start the recursion
  if (left.empty() && right.empty())
    return true;
  if (left.empty())
  {
    std::cerr << "different size - left is empty right = " << right.size() << std::endl;
    return false;
  }
  if (right.empty())
  {
    std::cerr << "different size - right is empty left = " << left.size() << std::endl;
    return false;
  }
  return compare_r(left, left.root(), right, right.root());
}

void print_r(std::ostream& device, const string_tree& tree, const string_tree::const_iterator& i)
{
  device << *i << "=" << ((void*)&*i);
  if (tree.children(i) > 0)
  {
    device << "(";
    for (unsigned c = 0; c < tree.children(i); c++)
    {
      if (c != 0) device << ",";
      print_r(device,tree,tree.child(i,c));
    }
    device << ")";
  }
}

void print(std::ostream& device, const string_tree& tree)
{
  if (tree.empty())
    device << "<empty>" << std::endl;
  else
    print_r(device, tree, tree.root());
}

std::ostream& operator << (std::ostream& device, const string_tree& tree)
{
  print(device, tree);
  return device;
}

////////////////////////////////////////////////////////////////////////////////

void dump_string_tree_iterator(stlplus::dump_context& context, const string_tree::iterator& data)
{
  stlplus::dump_ntree_iterator(context,data);
}
void restore_string_tree_iterator(stlplus::restore_context& context, string_tree::iterator& data)
{
  stlplus::restore_ntree_iterator(context,data);
}

////////////////////////////////////////////////////////////////////////////////

typedef std::map<std::string,string_tree::iterator> tree_map;

void dump_tree_map(stlplus::dump_context& context, const tree_map& data)
{
  stlplus::dump_map(context, data, stlplus::dump_string, dump_string_tree_iterator);
}

void restore_tree_map(stlplus::restore_context& context, tree_map& data)
{
  stlplus::restore_map(context, data, stlplus::restore_string, restore_string_tree_iterator);
}

std::ostream& operator << (std::ostream& device, const tree_map& mappings)
{
  for (tree_map::const_iterator i = mappings.begin(); i != mappings.end(); i++)
  {
    if (i != mappings.begin()) device << ",";
    device << "(" << i->first << "=" << ((void*)&*(i->second)) << ")";
  }
  return device;
}

////////////////////////////////////////////////////////////////////////////////

class mapped_tree
{
public:
  string_tree m_tree;
  tree_map m_map;

  void add_mappings(void)
    {
      m_map.clear();
      for (string_tree::prefix_iterator i = m_tree.prefix_begin(); i != m_tree.prefix_end(); i++)
        m_map[*i] = i.simplify();
    }
  friend void dump_mapped_tree(stlplus::dump_context& context, const mapped_tree& data)
    {
      dump_string_tree(context,data.m_tree);
      dump_tree_map(context,data.m_map);
    }
  friend void restore_mapped_tree(stlplus::restore_context& context, mapped_tree& data)
    {
      restore_string_tree(context,data.m_tree);
      restore_tree_map(context,data.m_map);
    }
  friend std::ostream& operator << (std::ostream& device, const mapped_tree& data)
    {
      device << data.m_tree << std::endl;
      device << data.m_map << std::endl;
      return device;
    }
  friend bool compare(const mapped_tree& left, const mapped_tree& right)
    {
      // TODO - compare maps too
      return compare(left.m_tree,right.m_tree);
    }
};

////////////////////////////////////////////////////////////////////////////////

int main(unsigned argc, char* argv[])
{
  bool result = true;

  try
  {
    // build the sample data structure
    mapped_tree data;
    string_tree::iterator root = data.m_tree.insert("root");
    string_tree::iterator left = data.m_tree.append(root,"left");
    string_tree::iterator left_left = data.m_tree.append(left,"left_left");
    string_tree::iterator left_right = data.m_tree.append(left,"left_right");
    string_tree::iterator right = data.m_tree.append(root,"right");
    string_tree::iterator right_left = data.m_tree.append(right,"right_left");
    string_tree::iterator right_right = data.m_tree.append(right,"right_right");
    data.add_mappings();
    std::cerr << "tree = " << std::endl << data;
    // now dump to the file
    std::cerr << "dumping" << std::endl;
    stlplus::dump_to_file(data,DATA,dump_mapped_tree,0);

    // now restore the same file and compare
    std::cerr << "restoring" << std::endl;
    mapped_tree restored;
    restore_from_file(DATA,restored,restore_mapped_tree,0);
    std::cerr << "restored = " << std::endl << restored;
    result &= compare(data,restored);

    // compare with the master dump if present
    if (!stlplus::file_exists(MASTER))
    {
      std::cerr << "creating master" << std::endl;
      stlplus::file_copy(DATA,MASTER);
    }
    else
    {
      std::cerr << "restoring master" << std::endl;
      mapped_tree master;
      stlplus::restore_from_file(MASTER,master,restore_mapped_tree,0);
      result &= compare(data,master);
    }
  }
  catch(std::exception& except)
  {
    std::cerr << "caught standard exception " << except.what() << std::endl;
    result = false;
  }
  catch(...)
  {
    std::cerr << "caught unknown exception" << std::endl;
    result = false;
  }

  if (!result)
    std::cerr << "test failed" << std::endl;
  else
    std::cerr << "test passed" << std::endl;
  return result ? 0 : 1;
}
