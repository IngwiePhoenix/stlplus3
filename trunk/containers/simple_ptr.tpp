////////////////////////////////////////////////////////////////////////////////

//   Author:    Daniel Milton
//   Copyright: (c) Daniel Milton           2002-2009

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////
  // simple_ptr_base class
  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////
  // constructors, assignments and destructors

  // create a null pointer
  template <typename T, typename C>
  simple_ptr_base<T,C>::simple_ptr_base(void) :
    m_pointer(0),
    m_count(new unsigned(1))
  {
  }

  // create a pointer containing a *copy* of the object pointer
  template <typename T, typename C>
  simple_ptr_base<T,C>::simple_ptr_base(const T& data) throw(illegal_copy) :
    m_pointer(C()(data)),
    m_count(new unsigned(1))
  {
  }

  // create a pointer containing a dynamically created object
  // Note: the object must be allocated *by the user* with new
  // constructor form - must be called in the form simple_ptr<type> x(new type(args))
  template <typename T, typename C>
  simple_ptr_base<T,C>::simple_ptr_base(T* data) :
    m_pointer(data),
    m_count(new unsigned(1))
  {
  }

  // copy constructor implements counted referencing - no copy is made
  template <typename T, typename C>
  simple_ptr_base<T,C>::simple_ptr_base(const simple_ptr_base<T,C>& r) :
    m_pointer(r.m_pointer),
    m_count(r.m_count)
  {
    increment();
  }

  // assignment operator - required, else the output of GCC suffers segmentation faults
  template <typename T, typename C>
  simple_ptr_base<T,C>& simple_ptr_base<T,C>::operator=(const simple_ptr_base<T,C>& r)
  {
    alias(r);
    return *this;
  }

  // destructor decrements the reference count and delete only when the last reference is destroyed
  template <typename T, typename C>
  simple_ptr_base<T,C>::~simple_ptr_base(void)
  {
    if(decrement()) 
    {
      delete m_pointer;
      delete m_count;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // logical tests to see if there is anything contained in the pointer since it can be null

  template <typename T, typename C>
  bool simple_ptr_base<T,C>::null(void) const
  {
    return m_pointer==0;
  }

  template <typename T, typename C>
  bool simple_ptr_base<T,C>::present(void) const
  {
    return m_pointer!=0;
  }

  template <typename T, typename C>
  bool simple_ptr_base<T,C>::operator!(void) const
  {
    return m_pointer==0;
  }

  template <typename T, typename C>
  simple_ptr_base<T,C>::operator bool(void) const
  {
    return m_pointer!=0;
  }

  //////////////////////////////////////////////////////////////////////////////
  // dereference operators and functions

  template <typename T, typename C>
  T& simple_ptr_base<T,C>::operator*(void) throw(null_dereference)
  {
    if (!m_pointer) throw null_dereference("null pointer dereferenced in simple_ptr::operator*");
    return *m_pointer;
  }

  template <typename T, typename C>
  const T& simple_ptr_base<T,C>::operator*(void) const throw(null_dereference)
  {
    if (!m_pointer) throw null_dereference("null pointer dereferenced in simple_ptr::operator*");
    return *m_pointer;
  }

  template <typename T, typename C>
  T* simple_ptr_base<T,C>::operator->(void) throw(null_dereference)
  {
    if (!m_pointer) throw null_dereference("null pointer dereferenced in simple_ptr::operator->");
    return m_pointer;
  }

  template <typename T, typename C>
  const T* simple_ptr_base<T,C>::operator->(void) const throw(null_dereference)
  {
    if (!m_pointer) throw null_dereference("null pointer dereferenced in simple_ptr::operator->");
    return m_pointer;
  }

  //////////////////////////////////////////////////////////////////////////////
  // explicit function forms of the above assignment dereference operators

  template <typename T, typename C>
  void simple_ptr_base<T,C>::set_value(const T& data) throw(illegal_copy)
  {
    set(C()(data));
  }

  template <typename T, typename C>
  T& simple_ptr_base<T,C>::value(void) throw(null_dereference)
  {
    if (!m_pointer) throw null_dereference("null pointer dereferenced in simple_ptr::value");
    return *m_pointer;
  }

  template <typename T, typename C>
  const T& simple_ptr_base<T,C>::value(void) const throw(null_dereference)
  {
    if (!m_pointer) throw null_dereference("null pointer dereferenced in simple_ptr::value");
    return *m_pointer;
  }

  template <typename T, typename C>
  void simple_ptr_base<T,C>::set(T* data)
  {
    unsigned& count = *m_count;
    if (count<=1)
      delete m_pointer;
    else
    {
      --count;
      m_count = new unsigned(1);
    }
    m_pointer = data;
  }

  template <typename T, typename C>
  T* simple_ptr_base<T,C>::pointer(void)
  {
    return m_pointer;
  }

  template <typename T, typename C>
  const T* simple_ptr_base<T,C>::pointer(void) const
  {
    return m_pointer;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // functions to manage counted referencing

  template <typename T, typename C>
  void simple_ptr_base<T,C>::increment(void)
  {
    ++(*m_count);
  }

  template <typename T, typename C>
  bool simple_ptr_base<T,C>::decrement(void)
  {
    unsigned& count = *m_count;
    --count;
    return count == 0;
  }

  // make this an alias of the passed object
  template <typename T, typename C>
  void simple_ptr_base<T,C>::alias(const simple_ptr_base<T,C>& r)
  {
    // make it alias-copy safe - this means that I don't try to do the
    // assignment if r is either the same object or an alias of it
    if (m_pointer==r.m_pointer) return;
    if(decrement()) {
      delete m_pointer;
      delete m_count;
    }
    m_pointer = r.m_pointer;
    m_count = r.m_count;
    increment();
  }

  template <typename T, typename C>
  bool simple_ptr_base<T,C>::aliases(const simple_ptr_base<T,C>& r) const
  {
    return m_count == r.m_count;
  }

  template <typename T, typename C>
  unsigned simple_ptr_base<T,C>::alias_count(void) const
  {
    return *m_count;
  }

  template <typename T, typename C>
  void simple_ptr_base<T,C>::clear(void)
  {
    set(0);
  }

  template <typename T, typename C>
  void simple_ptr_base<T,C>::clear_unique(void)
  {
    set(0);	// no difference between clear and clear_unique with the simple_ptr
  }

  template <typename T, typename C>
  void simple_ptr_base<T,C>::make_unique(void) throw(illegal_copy)
  {
    unsigned& count = *m_count;
    if (count <= 1) return;
    --count;
    if (m_pointer) m_pointer = C()(*m_pointer);
    m_count = new unsigned(1);
  }

  template <typename T, typename C>
  void simple_ptr_base<T,C>::copy(const simple_ptr_base<T,C>& data) throw(illegal_copy)
  {
    alias(data);
    make_unique();
  }

  // dynamic cast of underlying pointer to a derived/parent
  template <typename T, typename C>
  template <typename T2>
  simple_ptr_base<T2,C> simple_ptr_base<T,C>::dyn_cast(void) const
  {
    simple_ptr_base<T2,C> rtn;
    rtn.m_pointer = dynamic_cast<T2*>(m_pointer);
    if (rtn.m_pointer) {
      delete rtn.m_count;
      rtn.m_count = m_count;
      rtn.increment();
    }
    return rtn;
  }

  // static cast of underlying pointer to a derived/parent
  template <typename T, typename C>
  template <typename T2>
  simple_ptr_base<T2,C> simple_ptr_base<T,C>::stat_cast(void) const
  {
    simple_ptr_base<T2,C> rtn;
    rtn.m_pointer = static_cast<T2*>(m_pointer);
    if (rtn.m_pointer) {
      delete rtn.m_count;
      rtn.m_count = m_count;
      rtn.increment();
    }
    return rtn;
  }

  // cast of underlying pointer to a base - while keeping the same ref-counted object
  template <typename T, typename C>
  template <typename T2>
  simple_ptr_base<T2,C> simple_ptr_base<T,C>::cast(void) const
  {
    simple_ptr_base<T2,C> rtn;
    rtn.m_pointer = (T2*)m_pointer;
    if (rtn.m_pointer) {
      delete rtn.m_count;
      rtn.m_count = m_count;
      rtn.increment();
    }
    return rtn;
  }

  // internal function for distinguishing unique simple_ptr objects
  // used for example in persistence routines

  template <typename T, typename C>
  unsigned* simple_ptr_base<T,C>::_count(void) const
  {
    return m_count;
  }

  template <typename T, typename C>
  T* simple_ptr_base<T,C>::_pointer(void) const
  {
    return m_pointer;
  }

  template <typename T, typename C>
  void simple_ptr_base<T,C>::_make_alias(T* pointer, unsigned* count)
  {
    // make it alias-copy safe - this means that I don't try to do the
    // assignment if r is either the same object or an alias of it
    if (m_count != count)
    {
      if(decrement())
      {
        delete m_pointer;
        delete m_count;
      }
      m_pointer = pointer;
      m_count = count;
      increment();
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

