/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_bool.hpp"
#include "persistent_int.hpp"
#include "persistent_xref.hpp"
////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T, typename D>
  void stlplus::dump_ntree_r(dump_context& context,
                             const ntree<T>& tree, 
                             const TYPENAME ntree<T>::const_iterator& node,
                             D dump_fn)
    throw(persistent_dump_failed);

  template<typename T, typename R>
  void restore_ntree_r(restore_context& context,
                       ntree<T>& tree,
                       const TYPENAME ntree<T>::iterator& node,
                       R restore_fn)
    throw(persistent_restore_failed);

} // end namespace stlplus

////////////////////////////////////////////////////////////////////////////////

template<typename T, typename D>
void stlplus::dump_ntree_r(stlplus::dump_context& context,
                           const stlplus::ntree<T>& tree, 
                           const TYPENAME stlplus::ntree<T>::const_iterator& node,
                           D dump_fn)
  throw(stlplus::persistent_dump_failed)
{
  // the magic key of the ntree_node is dumped as well as the contents - this is used in iterator persistence
  std::pair<bool,unsigned> node_mapping = context.pointer_map(node.node());
  if (node_mapping.first) throw stlplus::persistent_dump_failed("ntree: already dumped this node");
  stlplus::dump_unsigned(context,node_mapping.second);
  // now dump the contents
  dump_fn(context,*node);
  // dump the number of children
  unsigned children = tree.children(node);
  stlplus::dump_unsigned(context,children);
  // recurse on the children
  for (unsigned i = 0; i < children; i++)
    stlplus::dump_ntree_r(context,tree,tree.child(node,i),dump_fn);
}

template<typename T, typename D>
void stlplus::dump_ntree(stlplus::dump_context& context,
                         const stlplus::ntree<T>& tree,
                         D dump_fn)
  throw(stlplus::persistent_dump_failed)
{
  // dump a magic key to the address of the tree for use in persistence of iterators
  // and register it as a dumped address
  std::pair<bool,unsigned> mapping = context.pointer_map(&tree);
  if (mapping.first) throw stlplus::persistent_dump_failed("ntree: already dumped this tree");
  stlplus::dump_unsigned(context,mapping.second);
  // now dump the tree contents
  stlplus::dump_bool(context, tree.empty());
  if (!tree.empty())
    stlplus::dump_ntree_r(context,tree,tree.root(),dump_fn);
}

////////////////////////////////////////////////////////////////////////////////

template<typename T, typename R>
void stlplus::restore_ntree_r(stlplus::restore_context& context,
                              stlplus::ntree<T>& tree,
                              const TYPENAME stlplus::ntree<T>::iterator& node,
                              R restore_fn)
  throw(stlplus::persistent_restore_failed)
{
  // restore the node magic key, check whether it has been used before and add it to the set of known addresses
  unsigned node_magic = 0;
  stlplus::restore_unsigned(context,node_magic);
  std::pair<bool,void*> node_mapping = context.pointer_map(node_magic);
  if (node_mapping.first) throw stlplus::persistent_restore_failed("ntree: restored this tree node already");
  context.pointer_add(node_magic,node.node());
  // now restore the node contents
  restore_fn(context,*node);
  // restore the number of children
  unsigned children = 0;
  stlplus::restore_unsigned(context,children);
  // recurse on each child
  for (unsigned i = 0; i < children; i++)
  {
    typename ntree<T>::iterator child = tree.insert(node,i,T());
    stlplus::restore_ntree_r(context,tree,child,restore_fn);
  }
}

template<typename T, typename R>
void stlplus::restore_ntree(stlplus::restore_context& context,
                            stlplus::ntree<T>& tree,
                            R restore_fn)
  throw(stlplus::persistent_restore_failed)
{
  tree.erase();
  // restore the tree's magic key and map it onto the tree's address
  // this is used in the persistence of iterators
  unsigned magic = 0;
  stlplus::restore_unsigned(context,magic);
  context.pointer_add(magic,&tree);
  // now restore the contents
  bool empty = true;
  stlplus::restore_bool(context, empty);
  if (!empty)
  {
    typename ntree<T>::iterator node = tree.insert(T());
    stlplus::restore_ntree_r(context,tree,node,restore_fn);
  }
}

////////////////////////////////////////////////////////////////////////////////

template<typename T, typename TRef, typename TPtr>
void stlplus::dump_ntree_iterator(stlplus::dump_context& context,
                                  const stlplus::ntree_iterator<T,TRef,TPtr>& data) 
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_xref(context,data.owner());
  stlplus::dump_xref(context,data.node());
}

template<typename T, typename TRef, typename TPtr>
void stlplus::restore_ntree_iterator(stlplus::restore_context& context,
                                     stlplus::ntree_iterator<T,TRef,TPtr>& data)
  throw(stlplus::persistent_restore_failed)
{
  const ntree<T>* owner = 0;
  ntree_node<T>* node = 0;
  restore_xref(context,owner);
  restore_xref(context,node);
  data = stlplus::ntree_iterator<T,TRef,TPtr>(owner,node);
}

////////////////////////////////////////////////////////////////////////////////

template<typename T, typename TRef, typename TPtr>
void stlplus::dump_ntree_prefix_iterator(stlplus::dump_context& context,
                                         const stlplus::ntree_prefix_iterator<T,TRef,TPtr>& data)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_ntree_iterator(context,data.iterator());
}

template<typename T, typename TRef, typename TPtr>
void stlplus::restore_ntree_prefix_iterator(stlplus::restore_context& context,
                                            stlplus::ntree_prefix_iterator<T,TRef,TPtr>& data)
  throw(stlplus::persistent_restore_failed)
{
  stlplus::ntree_iterator<T,TRef,TPtr> iterator;
  stlplus::restore_ntree_iterator(context,iterator);
  data = stlplus::ntree_prefix_iterator<T,TRef,TPtr>(iterator);
}

////////////////////////////////////////////////////////////////////////////////

template<typename T, typename TRef, typename TPtr>
void stlplus::dump_ntree_postfix_iterator(stlplus::dump_context& context,
                                          const stlplus::ntree_postfix_iterator<T,TRef,TPtr>& data)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_ntree_iterator(context,data.iterator());
}

template<typename T, typename TRef, typename TPtr>
void stlplus::restore_ntree_postfix_iterator(stlplus::restore_context& context,
                                             stlplus::ntree_postfix_iterator<T,TRef,TPtr>& data)
  throw(stlplus::persistent_restore_failed)
{
  stlplus::ntree_iterator<T,TRef,TPtr> iterator;
  stlplus::restore_ntree_iterator(context,iterator);
  data = stlplus::ntree_postfix_iterator<T,TRef,TPtr>(iterator);
}

////////////////////////////////////////////////////////////////////////////////
