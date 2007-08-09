/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_int.hpp"
#include "persistent_xref.hpp"
////////////////////////////////////////////////////////////////////////////////

template<typename NT, typename AT, typename DN, typename DA>
void stlplus::dump_digraph(stlplus::dump_context& context, const stlplus::digraph<NT,AT>& data,
                           DN dump_node, DA dump_arc)
  throw(stlplus::persistent_dump_failed)
{
  // dump a magic key to the address of the graph for use in persistence of iterators
  // and register it as a dumped address
  std::pair<bool,unsigned> mapping = context.pointer_map(&data);
  if (mapping.first) throw persistent_dump_failed("digraph: already dumped this graph");
  stlplus::dump_unsigned(context,mapping.second);
  // dump the nodes
  stlplus::dump_unsigned(context,data.size());
  for (typename stlplus::digraph<NT,AT>::const_iterator node = data.begin(); node != data.end(); node++)
  {
    // nodes are keyed by the magic key to the node address
    // this key is then used in dumping the arc from/to pointers
    std::pair<bool,unsigned> node_mapping = context.pointer_map(node.get_node());
    if (node_mapping.first) throw persistent_dump_failed("digraph: already dumped this node");
    stlplus::dump_unsigned(context,node_mapping.second);
    // finally, dump the node contents
    dump_node(context,*node);
  }
  // dump the arcs
  stlplus::dump_unsigned(context,data.arc_size());
  for (typename stlplus::digraph<NT,AT>::const_arc_iterator arc = data.arc_begin(); arc != data.arc_end(); arc++)
  {
    // dump the magic key to the arc address
    // this is used by iterator persistence too
    std::pair<bool,unsigned> arc_mapping = context.pointer_map(arc.get_arc());
    if (arc_mapping.first) throw persistent_dump_failed("digraph: already dumped this arc");
    stlplus::dump_unsigned(context,arc_mapping.second);
    // now dump the from/to pointers as cross-references
    stlplus::dump_xref(context,data.arc_from(arc).get_node());
    stlplus::dump_xref(context,data.arc_to(arc).get_node());
    // now dump the arc's data
    dump_arc(context,*arc);
  }
}

////////////////////////////////////////////////////////////////////////////////

template<typename NT, typename AT, typename RN, typename RA>
void stlplus::restore_digraph(stlplus::restore_context& context, stlplus::digraph<NT,AT>& data,
                              RN restore_node, RA restore_arc)
  throw(stlplus::persistent_restore_failed)
{
  data.clear();
  // restore the graph's magic key and map it onto the graph's address
  // this is used in the persistence of iterators
  unsigned magic = 0;
  stlplus::restore_unsigned(context,magic);
  context.pointer_add(magic,&data);
  // restore the nodes
  unsigned nodes = 0;
  stlplus::restore_unsigned(context, nodes);
  for (unsigned n = 0; n < nodes; n++)
  {
    unsigned node_magic = 0;
    stlplus::restore_unsigned(context,node_magic);
    // create a new node and map the magic key onto the new address
    typename stlplus::digraph<NT,AT>::iterator node = data.insert(NT());
    context.pointer_add(node_magic,node.get_node());
    // now restore the user's data
    restore_node(context,*node);
  }
  // restore the arcs
  unsigned arcs = 0;
  stlplus::restore_unsigned(context, arcs);
  for (unsigned a = 0; a < arcs; a++)
  {
    unsigned arc_magic = 0;
    stlplus::restore_unsigned(context,arc_magic);
    // restore the from and to cross-references
    stlplus::digraph_node<NT,AT>* from = 0;
    stlplus::digraph_node<NT,AT>* to = 0;
    stlplus::restore_xref(context,from);
    stlplus::restore_xref(context,to);
    // create an arc with these from/to pointers
    typename stlplus::digraph<NT,AT>::arc_iterator arc = 
      data.arc_insert(TYPENAME digraph<NT,AT>::iterator(&data,from), 
                      TYPENAME digraph<NT,AT>::iterator(&data,to));
    context.pointer_add(arc_magic,arc.get_arc());
    // restore the user data
    restore_arc(context,*arc);
  }
}

////////////////////////////////////////////////////////////////////////////////

template<typename NT, typename AT, typename NRef, typename NPtr>
void stlplus::dump_digraph_iterator(stlplus::dump_context& context, 
                                    const stlplus::digraph_iterator<NT,AT,NRef,NPtr>& data)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_xref(context,data.get_owner());
  stlplus::dump_xref(context,data.get_node());
}

template<typename NT, typename AT, typename NRef, typename NPtr>
void stlplus::restore_digraph_iterator(stlplus::restore_context& context, 
                                       stlplus::digraph_iterator<NT,AT,NRef,NPtr>& data)
  throw(stlplus::persistent_restore_failed)
{
  stlplus::digraph<NT,AT>* owner = 0;
  stlplus::digraph_node<NT,AT>* node = 0;
  stlplus::restore_xref(context,owner);
  stlplus::restore_xref(context,node);
  data = stlplus::digraph_iterator<NT,AT,NRef,NPtr>(owner,node);
}

////////////////////////////////////////////////////////////////////////////////

template<typename NT, typename AT, typename NRef, typename NPtr>
void stlplus::dump_digraph_arc_iterator(stlplus::dump_context& context,
                                        const stlplus::digraph_arc_iterator<NT,AT,NRef,NPtr>& data)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_xref(context,data.get_owner());
  stlplus::dump_xref(context,data.get_arc());
}

template<typename NT, typename AT, typename NRef, typename NPtr>
void stlplus::restore_digraph_arc_iterator(stlplus::restore_context& context, 
                                           stlplus::digraph_arc_iterator<NT,AT,NRef,NPtr>& data)
  throw(stlplus::persistent_restore_failed)
{
  stlplus::digraph<NT,AT>* owner = 0;
  stlplus::digraph_arc<NT,AT>* arc = 0;
  stlplus::restore_xref(context,owner);
  stlplus::restore_xref(context,arc);
  data = stlplus::digraph_arc_iterator<NT,AT,NRef,NPtr>(owner,arc);
}

////////////////////////////////////////////////////////////////////////////////
