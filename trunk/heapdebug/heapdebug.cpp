/*------------------------------------------------------------------------------

  Author: Andy Rushton (c) 2007

  ------------------------------------------------------------------------------*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define STLPLUS_HEAPDEBUG_USE_MACRO_NEW
#include "heapdebug.hpp"
#include <cstdlib>
#include <cstdio>

// easier to do this - resolves differences in namespaces between gcc and Visual Studio 6
using namespace std;

#ifndef NDEBUG

////////////////////////////////////////////////////////////////////////////////
// globals used to control the memory debug code

static unsigned heapdebug_allocations = 0;
static unsigned heapdebug_deallocations = 0;
static unsigned heapdebug_errorcount = 0;
static size_t heaphash_bins = 10239;
#define allocated_mask 0xaaaaaaaa
#define deallocated_mask 0xdadadada
static bool heapdebug_verbose = false;

////////////////////////////////////////////////////////////////////////////////
// types and macros used in calculating offsets
// memory is allocated in whole words, where a word is assumed to be an unsigned int

typedef unsigned word;
#define word_size(bytes) ((bytes+sizeof(word)-1)/sizeof(word))
#define total_word_size(bytes) (word_size(bytes)+1)
#define byte_size(words) (words*sizeof(word))
#define suffix_field(pointer,words) (((word*)pointer)+words)

////////////////////////////////////////////////////////////////////////////////
// hash table used to store a record of every block allocated
// a data entry is made on allocation and preserved even after deallocation
// however, when memory is allocated again, it is then removed from the hash
// the hash table is an array of bins, each one containing an unsorted list of hash entries

// the data type forming the linked list
struct heaphash_data
{
  word* memory;
  size_t size;
  const char* file;
  int line;
  bool allocated;
  bool array;
  heaphash_data* next;
};

// the pointer to the array of bins - initialised in the init function
static heaphash_data** heaphash = 0;

// hashing function simply uses remainder to give hash value - this only works well if number of bins is odd
static unsigned heaphash_hash(word* address)
{
  return ((unsigned)address) % heaphash_bins;
}

// lookup a memory block in the hash table
static heaphash_data* heaphash_find(word* address)
{
  // find the bin and walk down the list in that bin
  for (heaphash_data* i = heaphash[heaphash_hash(address)]; i; i = i->next)
  {
    if (i->memory == address)
      return i;
  }
  return 0;
}

// find and remove the data stored on a particular block
static void heaphash_remove(word* address)
{
  heaphash_data* prev = 0;
  for (heaphash_data* i = heaphash[heaphash_hash(address)]; i; i = i->next)
  {
    if (i->memory == address)
    {
      if (prev)
        prev->next = i->next;
      else
        heaphash[heaphash_hash(address)] = i->next;
      free(i);
      break;
    }
    prev = i;
  }
}

////////////////////////////////////////////////////////////////////////////////
// initialisation function called once on first call of any allocation/deallocation function

static void heapdebug_init(void)
{
  fprintf(stderr, "****************************************\n"); 
  fprintf(stderr, "*** heapdebug: (c) Andy Rushton\n"); 
  fprintf(stderr, "****************************************\n"); 
  fflush(stderr);
  atexit(stlplus::heapdebug_report);
  heapdebug_verbose = getenv("HEAPDEBUG") != 0;
  heaphash = (heaphash_data**)malloc(sizeof(heaphash_data*)*heaphash_bins);
  for (size_t i = 0; i < heaphash_bins; i++)
    heaphash[i] = 0;
}

////////////////////////////////////////////////////////////////////////////////
// allocate a block of memory and add a record of it to the hash table

static void* heaphash_allocate(size_t size, bool array, const char* file = 0, int line = 0)
{
  // initialise the whole system on first call
  if (!heaphash) heapdebug_init();
  // allocate the block of memory requested by the user
  word* memory = (word*)malloc(byte_size(total_word_size(size)));
  if (!memory)
  {
    //  error handling if it failed
    fprintf(stderr, "*** heapdebug: ERROR failed to allocate %uB", size);
    if (file) fprintf(stderr, " at %s line %d", file, line);
    fprintf(stderr, "\n");
    fflush(stderr);
    ++heapdebug_errorcount;
    return 0;
  }
  // remove any previous use of this memory from the hash
  heaphash_remove(memory);
  // allocate the record of this memory block
  heaphash_data* new_item = (heaphash_data*)malloc(sizeof(heaphash_data));
  if (!new_item)
  {
    //  error handling if it failed
    free(memory);
    fprintf(stderr, "*** heapdebug: ERROR failed to allocate internal data for %uB", size);
    if (file) fprintf(stderr, " at %s line %d", file, line);
    fprintf(stderr, "\n");
    fflush(stderr);
    ++heapdebug_errorcount;
    return 0;
  }
  if (heapdebug_verbose)
  {
    fprintf(stderr, "*** heapdebug:  allocated : %p, %uB", memory, size);
    if (array) fprintf(stderr, " array");
    if (file) fprintf(stderr, " at %s line %d", file, line);
    fprintf(stderr, "\n");
    fflush(stderr);
  }
  // now fill in the record with details of this allocation
  ++heapdebug_allocations;
  *suffix_field(memory,word_size(size)) = allocated_mask;
  new_item->memory = memory;
  new_item->size = size;
  new_item->file = file;
  new_item->line = line;
  new_item->allocated = true;
  new_item->array = array;
  // hook the record into the hash table
  new_item->next = heaphash[heaphash_hash(memory)];
  heaphash[heaphash_hash(memory)] = new_item;
  return memory;
}

////////////////////////////////////////////////////////////////////////////////
// localised new function implements the main memory-allocation algorithm
// required of the new operator but with no exceptions - this is used within
// the actual new operators

static void* heapdebug_new(size_t size, bool array, const char* file = 0, int line = 0)
{
  // try at first to allocate some memory
  void* memory = heaphash_allocate(size, array, file, line);
  if (memory) return memory;
  // now try releasing memory by calling the new handler
  // unfortunately the standard library does not give an easy way to get the
  // current handler, but set_new_handler returns the old value so get the
  // handler and then put the handler back again
  new_handler handler = set_new_handler(0);
  set_new_handler(handler);
  if (handler) handler();
  // now try again to get some memory
  memory = heaphash_allocate(size, array, file, line);
  return memory;
}

////////////////////////////////////////////////////////////////////////////////

static void heaphash_deallocate(word* address, bool array)
{
  // initialise the whole system on first call
  if (!heaphash) heapdebug_init();
  // test for deallocating a null pointer
  if (!address)
  {
    fprintf(stderr, "*** heapdebug: ERROR deallocating a null pointer\n");
    fflush(stderr);
    ++heapdebug_errorcount;
    return;
  }
  // lookup the block in the hash table
  heaphash_data* found = heaphash_find(address);
  // now diagnose what happened
  if (!found)
  {
    // if not in the hash table, then this memory was not allocated by new
    // report the error and deallocate anyway
    fprintf(stderr, "*** heapdebug: ERROR deallocating a block not allocated by heapdebug: %p\n", address);
    fflush(stderr);
    ++heapdebug_errorcount;
    free(address);
  }
  else if (!found->allocated)
  {
    // the memory was allocated by new but has already been deleted
    // report the error but do not deallocate
    fprintf(stderr, "*** heapdebug: ERROR deallocating a block already deallocated: %p, %uB", address, found->size);
    if (found->file) fprintf(stderr, " allocated at %s line %d", found->file, found->line);
    fprintf(stderr, "\n");
    fflush(stderr);
    ++heapdebug_errorcount;
  }
  else
  {
    // a block allocated by new is being deallocated correctly
    // check whether the right delete operator has been used
    if (found->array != array)
    {
      // deallocated using wrong delete operator
      fprintf(stderr, "*** heapdebug: ERROR deallocating with %s: %p, %uB",
              (array ? "array delete[]" : "non-array delete"), address, found->size);
      if (found->array) fprintf(stderr, " array");
      if (found->file) fprintf(stderr, " allocated at %s line %d", found->file, found->line);
      fprintf(stderr, "\n");
      fflush(stderr);
      ++heapdebug_errorcount;
    }
    // record the fact that it has been deallocated and then deallocate it
    found->allocated = false;
    // test for buffer overrun by testing the bit-pattern in the extra suffix word
    if (*suffix_field(address,word_size(found->size)) != allocated_mask)
    {
      fprintf(stderr, "*** heapdebug: ERROR memory overrun detected on: %pm %uB", address, found->size);
      if (found->array) fprintf(stderr, " array");
      if (found->file) fprintf(stderr, " allocated at %s line %d", found->file, found->line);
      fprintf(stderr, "\n");
      fflush(stderr);
      ++heapdebug_errorcount;
    }
    // overwrite the contents with a distinctive bit-pattern to detect access of deallocated memory
    for (word* i = address; i <= suffix_field(address,word_size(found->size)); i++)
      *i = deallocated_mask;
    // report only in verbose mode
    if (heapdebug_verbose)
    {
      fprintf(stderr, "*** heapdebug: deallocated: %p, %uB", address, found->size);
      if (found->array) fprintf(stderr, " array");
      if (found->file) fprintf(stderr, " allocated at %s line %d", found->file, found->line);
      fprintf(stderr, "\n");
      fflush(stderr);
    }
    // now deallocate the memory
    ++heapdebug_deallocations;
    free(address);
  }
}

////////////////////////////////////////////////////////////////////////////////
// report on any memory currently in use
// can be called anywhere but automatically called on exit

void stlplus::heapdebug_report(void)
{
  fprintf(stderr, "****************************************\n"); 
  fprintf(stderr, "*** heapdebug: SUMMARY: blocks allocated: %u, outstanding: %u, errors: %u\n", 
          heapdebug_allocations, heapdebug_allocations - heapdebug_deallocations, heapdebug_errorcount);
  for (size_t i = 0; i < heaphash_bins; i++)
  {
    for (heaphash_data* j = heaphash[i]; j; j = j->next)
    {
      if (j->allocated)
      {
        fprintf(stderr, "*** heapdebug: block not deallocated: %p %uB", j->memory, j->size);
        if (j->file) fprintf(stderr, " allocated at %s line %d", j->file, j->line);
        fprintf(stderr, "\n");
      }
    }
  }
  fprintf(stderr, "****************************************\n"); 
  fflush(stderr);
}

////////////////////////////////////////////////////////////////////////////////

unsigned stlplus::heapdebug_errors(void)
{
  return heapdebug_errorcount;
}

////////////////////////////////////////////////////////////////////////////////

unsigned stlplus::heapdebug_outstanding(void)
{
  return heapdebug_allocations - heapdebug_deallocations;
}

////////////////////////////////////////////////////////////////////////////////
// exported new/delete operators

#ifndef HEAPDEBUG_BROKEN_NOTHROW

// nothrow version of new returns null on error
// use in concert with the place function to get file/line information
void* operator new (size_t size, const nothrow_t& nothrow) throw()
{
  void* result = heapdebug_new(size, false);
  return result;
}

// array form of nothrow new
// use in concert with the place function to get file/line information
void* operator new[] (size_t size, const nothrow_t& nothrow) throw()
{
  void* result = heapdebug_new(size, true);
  return result;
}

#endif

// conventional new throws exception on error
// use in concert with the place function to get file/line information
void* operator new (size_t size) throw(bad_alloc)
{
  void* result = heapdebug_new(size, false);
  if (!result) throw bad_alloc();
  return result;
}

// array form of conventional new
// use in concert with the place function to get file/line information
void* operator new[] (size_t size) throw(bad_alloc)
{
  void* result = heapdebug_new(size, true);
  if (!result) throw bad_alloc();
  return result;
}

////////////////////////////////////////////////////////////////////////////////

#ifndef HEAPDEBUG_BROKEN_NOTHROW

// nothrow version of delete
// use in concert with the place function to get file/line information
void operator delete (void* memory, const nothrow_t&) throw()
{
  heaphash_deallocate((word*)memory, false);
}

// array form of nothrow delete
// use in concert with the place function to get file/line information
void operator delete[] (void* memory, const nothrow_t&) throw()
{
  heaphash_deallocate((word*)memory, true);
}

#endif

// conventional version of delete
// use in concert with the place function to get file/line information
void operator delete (void* memory) throw()
{
  heaphash_deallocate((word*)memory, false);
}

// array form of conventional delete
// use in concert with the place function to get file/line information
void operator delete[] (void* memory) throw()
{
  heaphash_deallocate((word*)memory, true);
}

////////////////////////////////////////////////////////////////////////////////
// placement new/delete for source tracing 

void* operator new (size_t size, const char* file, int line) throw(bad_alloc)
{
  void* result = heapdebug_new(size, false, file, line);
  if (!result) throw bad_alloc();
  return result;
}

void* operator new[] (size_t size, const char* file, int line) throw(bad_alloc)
{
  void* result = heapdebug_new(size, true, file, line);
  if (!result) throw bad_alloc();
  return result;
}

#ifndef HEAPDEBUG_NO_PLACEMENT_DELETE

void operator delete (void*, const char*, int) throw()
{
}

void operator delete[] (void*, const char*, int) throw()
{
}

#endif

#else

////////////////////////////////////////////////////////////////////////////////
// non-debug versions

void stlplus::heapdebug_report(void)
{
}

unsigned stlplus::heapdebug_errors(void)
{
  return 0;
}

unsigned stlplus::heapdebug_outstanding(void)
{
  return 0;
}

#endif
