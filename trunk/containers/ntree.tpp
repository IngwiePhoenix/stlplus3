/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include <vector>
#include <algorithm>

namespace stlplus 
{

////////////////////////////////////////////////////////////////////////////////
// ntree_node

template<typename T>
class ntree_node
{
public:
  T m_data;
  ntree_node<T>* m_parent;
  std::vector<ntree_node<T>*> m_children;
public:
  ntree_node(const T& d = T()) : m_data(d), m_parent(0)
    {
    }

  ~ntree_node(void)
    {
      m_parent = (ntree_node<T>*)1;
      for (typename std::vector<ntree_node<T>*>::iterator i = m_children.begin(); i != m_children.end(); i++)
        delete *i;
    }

};

template<typename T>
static ntree_node<T>* ntree_copy(ntree_node<T>* root)
{
  if (!root) return 0;
  ntree_node<T>* new_tree = new ntree_node<T>(root->m_data);
  for (typename std::vector<ntree_node<T>*>::iterator i = root->m_children.begin(); i != root->m_children.end(); i++)
  {
    ntree_node<T>* new_child = ntree_copy(*i);
    new_tree->m_children.push_back(new_child);
    new_child->m_parent = new_tree;
  }
  return new_tree;
}

template<typename T>
static unsigned ntree_size(ntree_node<T>* root)
{
  if (!root) return 0;
  unsigned result = 1;
  for (typename std::vector<ntree_node<T>*>::iterator i = root->m_children.begin(); i != root->m_children.end(); i++)
    result += ntree_size(*i);
  return result;
}

template<typename T>
static unsigned ntree_depth(ntree_node<T>* root)
{
  unsigned depth = 0;
  for (ntree_node<T>* i = root; i; i = i->m_parent)
    depth++;
  return depth;
}

////////////////////////////////////////////////////////////////////////////////
// ntree_iterator

template<typename T, typename TRef, typename TPtr>
ntree_iterator<T,TRef,TPtr>::ntree_iterator(void) :
  m_owner(0), m_node(0)
{
}

template<typename T, typename TRef, typename TPtr>
ntree_iterator<T,TRef,TPtr>::~ntree_iterator(void)
{
}

template<typename T, typename TRef, typename TPtr>
ntree_iterator<T,TRef,TPtr>::ntree_iterator(const ntree<T>* owner, ntree_node<T>* node) :
  m_owner(owner), m_node(node)
{
}

template<typename T, typename TRef, typename TPtr>
bool ntree_iterator<T,TRef,TPtr>::null (void) const
{
  return m_owner == 0;
}

template<typename T, typename TRef, typename TPtr>
bool ntree_iterator<T,TRef,TPtr>::end (void) const
{
  if (m_owner == 0) return false;
  return m_node == 0;
}

template<typename T, typename TRef, typename TPtr>
bool ntree_iterator<T,TRef,TPtr>::valid (void) const
{
  return !null() && !end();
}

template<typename T, typename TRef, typename TPtr>
typename ntree_iterator<T,TRef,TPtr>::const_iterator ntree_iterator<T,TRef,TPtr>::constify(void) const
{
  return TYPENAME ntree_iterator<T,TRef,TPtr>::const_iterator(m_owner,m_node);
}

template<typename T, typename TRef, typename TPtr>
typename ntree_iterator<T,TRef,TPtr>::iterator ntree_iterator<T,TRef,TPtr>::deconstify(void) const
{
  return TYPENAME ntree_iterator<T,TRef,TPtr>::iterator(m_owner,m_node);
}

template<typename T, typename TRef, typename TPtr>
void ntree_iterator<T,TRef,TPtr>::make_null(void)
{
  m_owner = 0;
  m_node = 0;
}

template<typename T, typename TRef, typename TPtr>
void ntree_iterator<T,TRef,TPtr>::make_end(void)
{
  m_node = 0;
}

template<typename T, typename TRef, typename TPtr>
bool ntree_iterator<T,TRef,TPtr>::operator == (const TYPENAME ntree_iterator<T,TRef,TPtr>::this_iterator& r) const
{
  return m_node == r.m_node;
}

template<typename T, typename TRef, typename TPtr>
bool ntree_iterator<T,TRef,TPtr>::operator != (const TYPENAME ntree_iterator<T,TRef,TPtr>::this_iterator& r) const
{
  return m_node != r.m_node;
}

template<typename T, typename TRef, typename TPtr>
typename ntree_iterator<T,TRef,TPtr>::reference ntree_iterator<T,TRef,TPtr>::operator*(void) const
  throw(null_dereference,end_dereference)
{
  check_valid();
  return m_node->m_data;
}

template<typename T, typename TRef, typename TPtr>
typename ntree_iterator<T,TRef,TPtr>::pointer ntree_iterator<T,TRef,TPtr>::operator->(void) const
  throw(null_dereference,end_dereference)
{
  check_valid();
  return &(m_node->m_data);
}

template<typename T, typename TRef, typename TPtr>
void ntree_iterator<T,TRef,TPtr>::check_owner(const ntree<T>* owner) const
  throw(wrong_object)
{
  if (owner != m_owner)
    throw wrong_object("ntree node iterator");
}

template<typename T, typename TRef, typename TPtr>
void ntree_iterator<T,TRef,TPtr>::check_non_null(void) const
  throw(null_dereference)
{
  if (null())
    throw null_dereference("ntree node iterator");
}

template<typename T, typename TRef, typename TPtr>
void ntree_iterator<T,TRef,TPtr>::check_non_end(void) const
  throw(end_dereference)
{
  if (end())
    throw end_dereference("ntree node iterator");
}

template<typename T, typename TRef, typename TPtr>
void ntree_iterator<T,TRef,TPtr>::check_valid(void) const
  throw(null_dereference,end_dereference)
{
  check_non_null();
  check_non_end();
}

template<typename T, typename TRef, typename TPtr>
void ntree_iterator<T,TRef,TPtr>::check(const ntree<T>* owner) const
  throw(wrong_object,null_dereference,end_dereference)
{
  check_valid();
  if (owner) check_owner(owner);
}

template<typename T, typename TRef, typename TPtr>
const ntree<T>* ntree_iterator<T,TRef,TPtr>::owner(void) const
{
  return m_owner;
}

template<typename T, typename TRef, typename TPtr>
ntree_node<T>* ntree_iterator<T,TRef,TPtr>::node(void) const
{
  return m_node;
}

////////////////////////////////////////////////////////////////////////////////
// ntree_prefix_iterator

template<typename T, typename TRef, typename TPtr>
ntree_prefix_iterator<T,TRef,TPtr>::ntree_prefix_iterator(void)
{
}

template<typename T, typename TRef, typename TPtr>
ntree_prefix_iterator<T,TRef,TPtr>::~ntree_prefix_iterator(void)
{
}

template<typename T, typename TRef, typename TPtr>
ntree_prefix_iterator<T,TRef,TPtr>::ntree_prefix_iterator(const ntree_iterator<T,TRef,TPtr>& i) :
  m_iterator(i)
{
  // this is initialised with the root node
  // which is also the first node in prefix traversal order
}

template<typename T, typename TRef, typename TPtr>
bool ntree_prefix_iterator<T,TRef,TPtr>::null(void) const
{
  return m_iterator.null();
}

template<typename T, typename TRef, typename TPtr>
bool ntree_prefix_iterator<T,TRef,TPtr>::end(void) const
{
  return m_iterator.end();
}

template<typename T, typename TRef, typename TPtr>
bool ntree_prefix_iterator<T,TRef,TPtr>::valid(void) const
{
  return m_iterator.valid();
}

template<typename T, typename TRef, typename TPtr>
typename ntree_prefix_iterator<T,TRef,TPtr>::const_iterator ntree_prefix_iterator<T,TRef,TPtr>::constify(void) const
{
  return TYPENAME ntree_prefix_iterator<T,TRef,TPtr>::const_iterator(m_iterator);
}

template<typename T, typename TRef, typename TPtr>
typename ntree_prefix_iterator<T,TRef,TPtr>::iterator ntree_prefix_iterator<T,TRef,TPtr>::deconstify(void) const
{
  return TYPENAME ntree_prefix_iterator<T,TRef,TPtr>::iterator(m_iterator);
}

template<typename T, typename TRef, typename TPtr>
ntree_iterator<T,TRef,TPtr> ntree_prefix_iterator<T,TRef,TPtr>::simplify(void) const
{
  return ntree_iterator<T,TRef,TPtr>(m_iterator.m_owner,m_iterator.m_node);
}

template<typename T, typename TRef, typename TPtr>
bool ntree_prefix_iterator<T,TRef,TPtr>::operator == (const TYPENAME ntree_prefix_iterator<T,TRef,TPtr>::this_iterator& r) const
{
  return m_iterator == r.m_iterator;
}

template<typename T, typename TRef, typename TPtr>
bool ntree_prefix_iterator<T,TRef,TPtr>::operator != (const TYPENAME ntree_prefix_iterator<T,TRef,TPtr>::this_iterator& r) const
{
  return m_iterator != r.m_iterator;
}

template<typename T, typename TRef, typename TPtr>
typename ntree_prefix_iterator<T,TRef,TPtr>::this_iterator& ntree_prefix_iterator<T,TRef,TPtr>::operator ++ (void)
  throw(null_dereference,end_dereference)
{
  // pre-increment operator
  // algorithm: if there are any children, visit child 0, otherwise, go to
  // parent and deduce which child the start node was of that parent - if
  // there are further children, go into the next one. Otherwise, go up the
  // tree and test again for further children. Return null if there are no
  // further nodes
  m_iterator.check_valid();
  if (!m_iterator.m_node->m_children.empty())
  {
    // simply take the first child of this node
    m_iterator.m_node = m_iterator.m_node->m_children[0];
    return *this;
  }
  // this loop walks up the parent pointers
  // either it will walk off the top and exit or a new node will be found and the loop will exit
  for (;;)
  {
    // go up a level
    ntree_node<T>* old_node = m_iterator.m_node;
    m_iterator.m_node = m_iterator.m_node->m_parent;
    // if we've walked off the top of the tree, then return null
    if (!m_iterator.m_node) return *this;
    // otherwise find which index the old node was relative to this node
    typename std::vector<ntree_node<T>*>::iterator found = 
      std::find(m_iterator.m_node->m_children.begin(), m_iterator.m_node->m_children.end(), old_node);
    // if this was found, then see if there is another and if so return that
    found++;
    if (found != m_iterator.m_node->m_children.end())
    {
      m_iterator.m_node = *found;
      return *this;
    }
  }
  return *this;
}

template<typename T, typename TRef, typename TPtr>
typename ntree_prefix_iterator<T,TRef,TPtr>::this_iterator ntree_prefix_iterator<T,TRef,TPtr>::operator ++ (int)
  throw(null_dereference,end_dereference)
{
  // post-increment is defined in terms of the pre-increment
  typename ntree_prefix_iterator<T,TRef,TPtr>::this_iterator result = *this;
  ++(*this);
  return result;
}

template<typename T, typename TRef, typename TPtr>
typename ntree_prefix_iterator<T,TRef,TPtr>::reference ntree_prefix_iterator<T,TRef,TPtr>::operator*(void) const
  throw(null_dereference,end_dereference)
{
  return m_iterator.operator*();
}

template<typename T, typename TRef, typename TPtr>
typename ntree_prefix_iterator<T,TRef,TPtr>::pointer ntree_prefix_iterator<T,TRef,TPtr>::operator->(void) const
  throw(null_dereference,end_dereference)
{
  return m_iterator.operator->();
}

template<typename T, typename TRef, typename TPtr>
ntree_iterator<T,TRef,TPtr>& ntree_prefix_iterator<T,TRef,TPtr>::get_iterator(void) const
{
  return m_iterator;
}

////////////////////////////////////////////////////////////////////////////////
// ntree_postfix_iterator

template<typename T, typename TRef, typename TPtr>
ntree_postfix_iterator<T,TRef,TPtr>::ntree_postfix_iterator(void)
{
}

template<typename T, typename TRef, typename TPtr>
ntree_postfix_iterator<T,TRef,TPtr>::~ntree_postfix_iterator(void)
{
}

template<typename T, typename TRef, typename TPtr>
ntree_postfix_iterator<T,TRef,TPtr>::ntree_postfix_iterator(const ntree_iterator<T,TRef,TPtr>& i) :
  m_iterator(i)
{
  // this is initialised with the root node
  // initially traverse to the first node to be visited
  if (m_iterator.m_node)
    while (!m_iterator.m_node->m_children.empty())
      m_iterator.m_node = m_iterator.m_node->m_children[0];
}

template<typename T, typename TRef, typename TPtr>
bool ntree_postfix_iterator<T,TRef,TPtr>::null(void) const
{
  return m_iterator.null();
}

template<typename T, typename TRef, typename TPtr>
bool ntree_postfix_iterator<T,TRef,TPtr>::end(void) const
{
  return m_iterator.end();
}

template<typename T, typename TRef, typename TPtr>
bool ntree_postfix_iterator<T,TRef,TPtr>::valid(void) const
{
  return m_iterator.valid();
}

template<typename T, typename TRef, typename TPtr>
typename ntree_postfix_iterator<T,TRef,TPtr>::const_iterator ntree_postfix_iterator<T,TRef,TPtr>::constify(void) const
{
  return TYPENAME ntree_postfix_iterator<T,TRef,TPtr>::const_iterator(m_iterator);
}

template<typename T, typename TRef, typename TPtr>
typename ntree_postfix_iterator<T,TRef,TPtr>::iterator ntree_postfix_iterator<T,TRef,TPtr>::deconstify(void) const
{
  return TYPENAME ntree_postfix_iterator<T,TRef,TPtr>::iterator(m_iterator);
}

template<typename T, typename TRef, typename TPtr>
ntree_iterator<T,TRef,TPtr> ntree_postfix_iterator<T,TRef,TPtr>::simplify(void) const
{
  return ntree_iterator<T,TRef,TPtr>(m_iterator.m_owner,m_iterator.m_node);
}

template<typename T, typename TRef, typename TPtr>
bool ntree_postfix_iterator<T,TRef,TPtr>::operator == (const TYPENAME ntree_postfix_iterator<T,TRef,TPtr>::this_iterator& r) const
{
  return m_iterator == r.m_iterator;
}

template<typename T, typename TRef, typename TPtr>
bool ntree_postfix_iterator<T,TRef,TPtr>::operator != (const TYPENAME ntree_postfix_iterator<T,TRef,TPtr>::this_iterator& r) const
{
  return m_iterator != r.m_iterator;
}

template<typename T, typename TRef, typename TPtr>
typename ntree_postfix_iterator<T,TRef,TPtr>::this_iterator& ntree_postfix_iterator<T,TRef,TPtr>::operator ++ (void)
  throw(null_dereference,end_dereference)
{
  // pre-increment operator
  // algorithm: this node has been visited, therefore all children must have
  // already been visited. So go to parent. Return null if the parent is null.
  // Otherwise deduce which child the start node was of that parent - if there
  // are further children, go into the next one and then walk down any
  // subsequent first-child pointers to the bottom. Otherwise, if there are no
  // children then the parent node is the next in the traversal.
  m_iterator.check_valid();
  if (!m_iterator.m_node) return *this;
  // go up a level
  ntree_node<T>* old_node = m_iterator.m_node;
  m_iterator.m_node = m_iterator.m_node->m_parent;
  // if we've walked off the top of the tree, then the result is null so there's nothing more to be done
  if (!m_iterator.m_node) return *this;
  // otherwise find which index the old node was relative to this node
  typename std::vector<ntree_node<T>*>::iterator found =
    std::find(m_iterator.m_node->m_children.begin(), m_iterator.m_node->m_children.end(), old_node);
  // if this was found, then see if there is another - if not then the current node is the next in the iteration
  found++;
  if (found == m_iterator.m_node->m_children.end()) return *this;
  // if so traverse to it
  m_iterator.m_node = *found;
  // now walk down the leftmost child pointers to the bottom of the new sub-tree
  while (!m_iterator.m_node->m_children.empty())
    m_iterator.m_node = m_iterator.m_node->m_children[0];
  return *this;
}

template<typename T, typename TRef, typename TPtr>
typename ntree_postfix_iterator<T,TRef,TPtr>::this_iterator ntree_postfix_iterator<T,TRef,TPtr>::operator ++ (int)
  throw(null_dereference,end_dereference)
{
  // post-increment is defined in terms of the pre-increment
  typename ntree_postfix_iterator<T,TRef,TPtr>::this_iterator result = *this;
  ++(*this);
  return result;
}

template<typename T, typename TRef, typename TPtr>
typename ntree_postfix_iterator<T,TRef,TPtr>::reference ntree_postfix_iterator<T,TRef,TPtr>::operator*(void) const
  throw(null_dereference,end_dereference)
{
  return m_iterator.operator*();
}

template<typename T, typename TRef, typename TPtr>
typename ntree_postfix_iterator<T,TRef,TPtr>::pointer ntree_postfix_iterator<T,TRef,TPtr>::operator->(void) const
  throw(null_dereference,end_dereference)
{
  return m_iterator.operator->();
}

template<typename T, typename TRef, typename TPtr>
ntree_iterator<T,TRef,TPtr>& ntree_postfix_iterator<T,TRef,TPtr>::get_iterator(void) const
{
  return m_iterator;
}

////////////////////////////////////////////////////////////////////////////////
// ntree

template<typename T>
ntree<T>::ntree(void) : m_root(0)
{
}

template<typename T>
ntree<T>::~ntree(void)
{
  if (m_root) delete m_root;
}

template<typename T>
ntree<T>::ntree(const ntree<T>& r) : m_root(0)
{
  *this = r;
}

template<typename T>
ntree<T>& ntree<T>::operator=(const ntree<T>& r)
{
  if (m_root) delete m_root;
  m_root = ntree_copy(r.m_root);
  return *this;
}

template<typename T>
bool ntree<T>::empty(void) const
{
  return m_root == 0;
}

template<typename T>
unsigned ntree<T>::size(void) const
{
  return ntree_size(m_root);
}

template<typename T>
unsigned ntree<T>::size(const TYPENAME ntree<T>::const_iterator& i) const
  throw(wrong_object,null_dereference,end_dereference)
{
  i.check(this);
  return ntree_size(i.m_node);
}

template<typename T>
unsigned ntree<T>::size(const TYPENAME ntree<T>::iterator& i)
  throw(wrong_object,null_dereference,end_dereference)
{
  i.check(this);
  return ntree_size(i.m_node);
}

template<typename T>
unsigned ntree<T>::depth(const TYPENAME ntree<T>::const_iterator& i) const
  throw(wrong_object,null_dereference,end_dereference)
{
  i.check(this);
  return ntree_depth(i.m_node);
}

template<typename T>
unsigned ntree<T>::depth(const TYPENAME ntree<T>::iterator& i)
  throw(wrong_object,null_dereference,end_dereference)
{
  i.check(this);
  return ntree_depth(i.m_node);
}

template<typename T>
typename ntree<T>::const_iterator ntree<T>::root(void) const
{
  return TYPENAME ntree<T>::const_iterator(this,m_root);
}

template<typename T>
typename ntree<T>::iterator ntree<T>::root(void)
{
  return TYPENAME ntree<T>::iterator(this,m_root);
}

template<typename T>
unsigned ntree<T>::children(const TYPENAME ntree<T>::const_iterator& i) const
  throw(wrong_object,null_dereference,end_dereference)
{
  i.check(this);
  return i.m_node->m_children.size();
}

template<typename T>
unsigned ntree<T>::children(const TYPENAME ntree<T>::iterator& i)
  throw(wrong_object,null_dereference,end_dereference)
{
  i.check(this);
  return i.m_node->m_children.size();
}

template<typename T>
typename ntree<T>::const_iterator ntree<T>::child(const TYPENAME ntree<T>::const_iterator& i, unsigned child) const
  throw(wrong_object,null_dereference,end_dereference,std::out_of_range)
{
  i.check(this);
  if (child >= children(i)) throw std::out_of_range("ntree");
  return TYPENAME ntree<T>::const_iterator(this,i.m_node->m_children[child]);
}

template<typename T>
typename ntree<T>::iterator ntree<T>::child(const TYPENAME ntree<T>::iterator& i, unsigned child)
  throw(wrong_object,null_dereference,end_dereference,std::out_of_range)
{
  i.check(this);
  if (child >= children(i)) throw std::out_of_range("ntree");
  return TYPENAME ntree<T>::iterator(this,i.m_node->m_children[child]);
}

template<typename T>
typename ntree<T>::const_iterator ntree<T>::parent(const TYPENAME ntree<T>::const_iterator& i) const
  throw(wrong_object,null_dereference,end_dereference)
{
  i.check(this);
  return TYPENAME ntree<T>::const_iterator(this,i.m_node->m_parent);
}

template<typename T>
typename ntree<T>::iterator ntree<T>::parent(const TYPENAME ntree<T>::iterator& i)
  throw(wrong_object,null_dereference,end_dereference)
{
  i.check(this);
  return TYPENAME ntree<T>::iterator(this,i.m_node->m_parent);
}

template<typename T>
typename ntree<T>::const_prefix_iterator ntree<T>::prefix_begin(void) const
{
  return TYPENAME ntree<T>::const_prefix_iterator(TYPENAME ntree<T>::const_iterator(this,m_root));
}

template<typename T>
typename ntree<T>::prefix_iterator ntree<T>::prefix_begin(void)
{
  return TYPENAME ntree<T>::prefix_iterator(TYPENAME ntree<T>::iterator(this,m_root));
}

template<typename T>
typename ntree<T>::const_prefix_iterator ntree<T>::prefix_end(void) const
{
  return TYPENAME ntree<T>::const_prefix_iterator(TYPENAME ntree<T>::const_iterator(this,0));
}

template<typename T>
typename ntree<T>::prefix_iterator ntree<T>::prefix_end(void)
{
  return TYPENAME ntree<T>::prefix_iterator(TYPENAME ntree<T>::iterator(this,0));
}

template<typename T>
typename ntree<T>::const_postfix_iterator ntree<T>::postfix_begin(void) const
{
  return TYPENAME ntree<T>::const_postfix_iterator(TYPENAME ntree<T>::const_iterator(this,m_root));
}

template<typename T>
typename ntree<T>::postfix_iterator ntree<T>::postfix_begin(void)
{
  return TYPENAME ntree<T>::postfix_iterator(TYPENAME ntree<T>::iterator(this,m_root));
}

template<typename T>
typename ntree<T>::const_postfix_iterator ntree<T>::postfix_end(void) const
{
  return TYPENAME ntree<T>::const_postfix_iterator(TYPENAME ntree<T>::const_iterator(this,0));
}

template<typename T>
typename ntree<T>::postfix_iterator ntree<T>::postfix_end(void)
{
  return TYPENAME ntree<T>::postfix_iterator(TYPENAME ntree<T>::iterator(this,0));
}

template<typename T>
typename ntree<T>::iterator ntree<T>::insert(const T& data)
{
  // insert a new node as the root
  if (m_root) delete m_root;
  m_root = new ntree_node<T>(data);
  return TYPENAME ntree<T>::iterator(this,m_root);
}

template<typename T>
typename ntree<T>::iterator ntree<T>::insert(const TYPENAME ntree<T>::iterator& i, unsigned offset, const T& data)
  throw(wrong_object,null_dereference,end_dereference,std::out_of_range)
{
  // insert a new node as a child of i
  i.check(this);
  if (offset > children(i)) throw std::out_of_range("ntree");
  ntree_node<T>* new_node = new ntree_node<T>(data);
  i.m_node->m_children.insert(i.m_node->m_children.begin()+offset,new_node);
  new_node->m_parent = i.m_node;
  return TYPENAME ntree<T>::iterator(this,new_node);
}

template<typename T>
typename ntree<T>::iterator ntree<T>::append(const TYPENAME ntree<T>::iterator& i, const T& data)
  throw(wrong_object,null_dereference,end_dereference)
{
  return insert(i, i.m_node->m_children.size(), data);
}

template<typename T>
typename ntree<T>::iterator ntree<T>::insert(const TYPENAME ntree<T>::iterator& i, unsigned offset, const ntree<T>& tree)
  throw(wrong_object,null_dereference,end_dereference,std::out_of_range)
{
  // insert a whole tree as a child of i
  i.check(this);
  if (offset > children(i)) throw std::out_of_range("ntree");
  ntree_node<T>* new_node = ntree_copy(tree.m_root);
  i.m_node->m_children.insert(i.m_node->m_children.begin()+offset,new_node);
  new_node->m_parent = i.m_node;
  return TYPENAME ntree<T>::iterator(this,new_node);
}

template<typename T>
typename ntree<T>::iterator ntree<T>::append(const TYPENAME ntree<T>::iterator& i, const ntree<T>& tree)
  throw(wrong_object,null_dereference,end_dereference)
{
  return insert(i, children(i), tree);
}

template<typename T>
typename ntree<T>::iterator ntree<T>::push(const TYPENAME ntree<T>::iterator& node, const T& data)
  throw(wrong_object,null_dereference,end_dereference)
{
  // insert a new node to replace the existing node in the tree
  // making the original node the child of the new node
  // i.e. (node) becomes (new)->(node)
  // afterwards, the iterator still points to the old node, now the child
  // returns the iterator to the new node
  node.check(this);
  ntree_node<T>* new_node = new ntree_node<T>(data);
  if (node.m_node == m_root)
  {
    // pushing the root node
    m_root = new_node;
    new_node->m_parent = 0;
  }
  else
  {
    // pushing a sub-node
    *(std::find(node.m_node->m_parent->m_children.begin(), node.m_node->m_parent->m_children.end(), node.m_node)) = new_node;
    new_node->m_parent = node.m_node->m_parent;
  }
  // link up the old node as the child of the new node
  new_node->m_children.insert(new_node->m_children.begin(),node.m_node);
  node.m_node->m_parent = new_node;
  return TYPENAME ntree<T>::iterator(this,new_node);
}

template<typename T>
void ntree<T>::pop(const TYPENAME ntree<T>::iterator& parent, unsigned offset)
  throw(wrong_object,null_dereference,end_dereference)
{
  // inverse of push
  // removes the specified child of the parent node, adding its children to the parent node at the same offset
  parent.check(this);
  ntree_node<T>* node = parent.m_node;
  if (offset >= node->m_children.size()) throw std::out_of_range("ntree");
  // move the grandchildren first
  ntree_node<T>* child = parent.m_node->m_children[offset];
  while (!child->m_children.empty())
  {
    // remove the last grandchild and insert into node just after the child to be removed
    ntree_node<T>* grandchild = child->m_children[child->m_children.size()-1];
    child->m_children.pop_back();
    node->m_children.insert(node->m_children.begin()+offset+1, grandchild);
    grandchild->m_parent = node;
  }
  // now remove the child
  node->m_children.erase(node->m_children.begin()+offset);
  delete child;
}

template<typename T>
void ntree<T>::erase(void)
{
  // erase the whole tree
  if (m_root) delete m_root;
  m_root = 0;
}

template<typename T>
void ntree<T>::erase(TYPENAME ntree<T>::iterator& i)
  throw(wrong_object,null_dereference,end_dereference)
{
  // erase this node and its subtree
  // do this by erasing this child of its parent
  // handle the case of erasing the root
  i.check(this);
  if (i.m_node == m_root)
  {
    delete m_root;
    m_root = 0;
  }
  else
  {
    i.m_node->m_parent->m_children.erase(std::find(i.m_node->m_parent->m_children.begin(),
                                                   i.m_node->m_parent->m_children.end(),
                                                   i.m_node));
    delete i.m_node;
  }
  i.make_null();
}

template<typename T>
void ntree<T>::erase(const TYPENAME ntree<T>::iterator& i, unsigned offset)
  throw(wrong_object,null_dereference,end_dereference,std::out_of_range)
{
  i.check(this);
  if (offset > children(i)) throw std::out_of_range("ntree");
  delete i.m_node->m_children[offset];
  i.m_node->m_children.erase(i.m_node->m_children.begin() + offset);
}

template<typename T>
ntree<T> ntree<T>::subtree(void)
{
  ntree<T> result;
  result.m_root = ntree_copy(m_root);
  return result;
}

template<typename T>
ntree<T> ntree<T>::subtree(const TYPENAME ntree<T>::iterator& i)
  throw(wrong_object,null_dereference,end_dereference)
{
  i.check(this);
  ntree<T> result;
  result.m_root = ntree_copy(i.m_node);
  return result;
}

template<typename T>
ntree<T> ntree<T>::subtree(const TYPENAME ntree<T>::iterator& i, unsigned offset)
  throw(wrong_object,null_dereference,end_dereference,std::out_of_range)
{
  // copy the child to form a new subtree
  i.check(this);
  if (offset > children(i)) throw std::out_of_range("ntree");
  ntree<T> result;
  result.m_root = ntree_copy(i.m_node->m_children[offset]);
  return result;
}

template<typename T>
ntree<T> ntree<T>::cut(void)
{
  ntree<T> result;
  result.m_root = m_root;
  m_root = 0;
  return result;
}

template<typename T>
ntree<T> ntree<T>::cut(TYPENAME ntree<T>::iterator& i)
  throw(wrong_object,null_dereference,end_dereference)
{
  i.check(this);
  ntree<T> result;
  if (i.m_node == m_root)
  {
    result.m_root = m_root;
    m_root = 0;
  }
  else
  {
    typename std::vector<ntree_node<T>*>::iterator found = 
      std::find(i.m_node->m_parent->m_children.begin(), i.m_node->m_parent->m_children.end(), i.m_node);
    result.m_root = *found;
    i.m_node->m_parent->m_children.erase(found);
  }
  i.make_null();
  if (result.m_root) result.m_root->m_parent = 0;
  return result;
}

template<typename T>
ntree<T> ntree<T>::cut(const TYPENAME ntree<T>::iterator& i, unsigned offset)
  throw(wrong_object,null_dereference,end_dereference,std::out_of_range)
{
  i.check(this);
  if (offset > children(i)) throw std::out_of_range("ntree");
  ntree<T> result;
  result.m_root = i.m_node->m_children[offset];
  i.m_node->m_children.erase(i.m_node->m_children.begin() + offset);
  if (result.m_root) result.m_root->m_parent = 0;
  return result;
}

////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

