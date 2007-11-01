/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "cli_parser.hpp"
#include "file_system.hpp"

////////////////////////////////////////////////////////////////////////////////

static std::string to_string(int number)
{
  // use sprintf in a very controlled way that cannot overrun
  char* buffer = new char[50];
  sprintf(buffer, "%i", number);
  std::string result = buffer;
  delete buffer;
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// cli_definition internals

const std::string& stlplus::cli_definition::name(void) const
{
  return m_name;
}

stlplus::cli_kind_t stlplus::cli_definition::kind(void) const
{ 
  return m_kind;
}

stlplus::cli_mode_t stlplus::cli_definition::mode(void) const
{
  return m_mode;
}

const std::string& stlplus::cli_definition::message(void) const
{
  return m_message;
}

const std::string& stlplus::cli_definition::default_value(void) const
{
  return m_default;
}

////////////////////////////////////////////////////////////////////////////////
// internal data structures

namespace stlplus 
{

  class cli_value
  {
  public:
    unsigned m_definition;
    std::string m_value;
    unsigned m_level;
    std::string m_source;

    cli_value(unsigned definition, const std::string& value, unsigned level, const std::string& source) :
      m_definition(definition), m_value(value), m_level(level), m_source(source) {}
  };

  class cli_parser_data
  {
  public:
    message_handler& m_errors;
    std::string m_executable;
    cli_parser::definitions m_definitions;
    std::vector<cli_value> m_values;
    unsigned m_level;
    bool m_valid;
    std::vector<std::string> m_ini_files;

    cli_parser_data(message_handler& errors);
    unsigned add_definition(const std::string& name, cli_parser::kind_t kind, cli_parser::mode_t mode, const std::string& message);
    unsigned find_definition(const std::string& name);
    void clear_definitions(void);

    void reset_level(void);
    void increase_level(void);
    void clear_level(unsigned definition, unsigned level);

    void set_valid(void);
    void set_invalid(void);
    bool valid(void) const;

    unsigned add_value(unsigned definition, const std::string& value, const std::string& source);
    unsigned add_switch(unsigned definition, bool value, const std::string& source);
    void erase_value(unsigned definition);

    void add_ini_file(const std::string& file);
    unsigned ini_file_size(void) const;
    const std::string& ini_file(unsigned) const;

  private:
    // make this class uncopyable
    cli_parser_data(const cli_parser_data&);
    cli_parser_data& operator = (const cli_parser_data&);
  };

} // end namespace stlplus

stlplus::cli_parser_data::cli_parser_data(message_handler& errors) : 
  m_errors(errors), m_level(1), m_valid(true)
{
}

unsigned stlplus::cli_parser_data::add_definition(const std::string& name, cli_parser::kind_t kind, cli_parser::mode_t mode, const std::string& message)
{
  m_definitions.push_back(cli_parser::definition(name, kind, mode, message));
  return m_definitions.size()-1;
}

unsigned stlplus::cli_parser_data::find_definition(const std::string& name)
{
  // this does substring matching on the definitions and returns the first
  // match - however, it requires at least one character in the substring so
  // that the "" convention for command line arguments doesn't match with
  // anything. It returns size() if it fails
  for (unsigned i = 0; i < m_definitions.size(); i++)
  {
    std::string candidate = m_definitions[i].m_name;
    if ((candidate.empty() && name.empty()) ||
        (!name.empty() && candidate.size() >= name.size() && candidate.substr(0,name.size()) == name))
      return i;
  }
  return m_definitions.size();
}

void stlplus::cli_parser_data::clear_definitions(void)
{
  m_definitions.clear();
  m_values.clear();
  reset_level();
  set_valid();
}

void stlplus::cli_parser_data::reset_level(void)
{
  // the starting level is 1 so that later functions can call clear_level with
  // a value of m_level-1 without causing underflow
  m_level = 1;
}

void stlplus::cli_parser_data::increase_level(void)
{
  m_level++;
}

void stlplus::cli_parser_data::clear_level(unsigned definition, unsigned level)
{
  // clears all values with this definition at the specified level or below
  for (std::vector<cli_value>::iterator i = m_values.begin(); i != m_values.end(); )
  {
    if (i->m_definition == definition && i->m_level <= level)
      i = m_values.erase(i);
    else
      i++;
  }
}

void stlplus::cli_parser_data::set_valid(void)
{
  m_valid = true;
}

void stlplus::cli_parser_data::set_invalid(void)
{
  m_valid = false;
}

bool stlplus::cli_parser_data::valid(void) const
{
  return m_valid;
}

unsigned stlplus::cli_parser_data::add_value(unsigned definition, const std::string& value, const std::string& source)
{
  // behaviour depends on mode:
  //  - single: erase all previous values
  //  - multiple: erase values at a lower level than current
  //  - cumulative: erase no previous values
  switch (m_definitions[definition].m_mode)
  {
  case cli_single_mode:
    clear_level(definition, m_level);
    break;
  case cli_multiple_mode:
    clear_level(definition, m_level-1);
    break;
  case cli_cumulative_mode:
    break;
  }
  m_values.push_back(cli_value(definition,value,m_level,source));
  return m_values.size()-1;
}

unsigned stlplus::cli_parser_data::add_switch(unsigned definition, bool value, const std::string& source)
{
  return add_value(definition, value ? "on" : "off", source);
}

void stlplus::cli_parser_data::erase_value(unsigned definition)
{
  // this simply erases all previous values
  clear_level(definition, m_level);
}

void stlplus::cli_parser_data::add_ini_file(const std::string& file)
{
  m_ini_files.push_back(file);
}

unsigned stlplus::cli_parser_data::ini_file_size(void) const
{
  return m_ini_files.size();
}

const std::string& stlplus::cli_parser_data::ini_file(unsigned i) const
{
  return m_ini_files[i];
}

////////////////////////////////////////////////////////////////////////////////

stlplus::cli_parser::cli_parser(message_handler& errors) throw() : 
  m_data(new stlplus::cli_parser_data(errors))
{
}

stlplus::cli_parser::cli_parser(stlplus::cli_parser::definitions_t definitions, message_handler& errors) throw(cli_mode_error) : 
  m_data(new stlplus::cli_parser_data(errors))
{
  add_definitions(definitions);
}

stlplus::cli_parser::cli_parser(stlplus::cli_parser::definitions_t definitions, const ini_manager& defaults, const std::string& ini_section, message_handler& errors)  throw(cli_mode_error) : 
  m_data(new stlplus::cli_parser_data(errors))
{
  add_definitions(definitions);
  set_defaults(defaults, ini_section);
}

stlplus::cli_parser::cli_parser(char* argv[], stlplus::cli_parser::definitions_t definitions, message_handler& errors)  throw(cli_mode_error,message_handler_id_error,message_handler_format_error) : 
  m_data(new stlplus::cli_parser_data(errors))
{
  add_definitions(definitions);
  parse(argv);
}

stlplus::cli_parser::cli_parser(char* argv[], stlplus::cli_parser::definitions_t definitions, const ini_manager& defaults, const std::string& ini_section, message_handler& errors)  throw(cli_mode_error,message_handler_id_error,message_handler_format_error) : 
  m_data(new stlplus::cli_parser_data(errors))
{
  add_definitions(definitions);
  set_defaults(defaults, ini_section);
  parse(argv);
}

stlplus::cli_parser::cli_parser(stlplus::cli_parser::definitions definitions, message_handler& errors) throw(cli_mode_error) : 
  m_data(new stlplus::cli_parser_data(errors))
{
  add_definitions(definitions);
}

stlplus::cli_parser::cli_parser(stlplus::cli_parser::definitions definitions, const ini_manager& defaults, const std::string& ini_section, message_handler& errors)  throw(cli_mode_error) : 
  m_data(new stlplus::cli_parser_data(errors))
{
  add_definitions(definitions);
  set_defaults(defaults, ini_section);
}

stlplus::cli_parser::cli_parser(char* argv[], stlplus::cli_parser::definitions definitions, message_handler& errors)  throw(cli_mode_error,message_handler_id_error,message_handler_format_error) : 
  m_data(new stlplus::cli_parser_data(errors))
{
  add_definitions(definitions);
  parse(argv);
}

stlplus::cli_parser::cli_parser(char* argv[], stlplus::cli_parser::definitions definitions, const ini_manager& defaults, const std::string& ini_section, message_handler& errors)  throw(cli_mode_error,message_handler_id_error,message_handler_format_error) : 
  m_data(new stlplus::cli_parser_data(errors))
{
  add_definitions(definitions);
  set_defaults(defaults, ini_section);
  parse(argv);
}

stlplus::cli_parser::~cli_parser(void) throw()
{
}

void stlplus::cli_parser::add_definitions(stlplus::cli_parser::definitions_t definitions) throw(cli_mode_error)
{
  m_data->clear_definitions();
  // the definitions array is terminated by a definition with a null name pointer
  for (unsigned i = 0; definitions[i].m_name; i++)
    add_definition(definitions[i]);
}

unsigned stlplus::cli_parser::add_definition(const stlplus::cli_parser::definition_t& definition) throw(cli_mode_error,cli_argument_error)
{
  if (!definition.m_name) throw cli_argument_error("Definition must have a valid name");
  // check for stupid combinations
  // at this stage the only really stupid one is to declare command line arguments to be switch mode
  if (definition.m_name[0] == '\0' && definition.m_kind == cli_switch_kind) 
  {
    m_data->set_invalid();
    throw cli_mode_error("CLI arguments cannot be switch kind");
  }
  // add the definition to the set of all definitions
  unsigned i = m_data->add_definition(definition.m_name, definition.m_kind, definition.m_mode, definition.m_message);
  // also add it to the list of values, but only if it has a default value
  if (definition.m_default) m_data->add_value(i, definition.m_default, "builtin default");
  return i;
}

void stlplus::cli_parser::add_definitions(stlplus::cli_parser::definitions definitions) throw(cli_mode_error)
{
  m_data->clear_definitions();
  for (unsigned i = 0; i < definitions.size(); i++)
    add_definition(definitions[i]);
}

unsigned stlplus::cli_parser::add_definition(const stlplus::cli_parser::definition& definition) throw(cli_mode_error)
{
  // check for stupid combinations
  // at this stage the only really stupid one is to declare command line arguments to be switch mode
  if (definition.m_name.empty() && definition.m_kind == cli_switch_kind) 
  {
    m_data->set_invalid();
    throw cli_mode_error("CLI arguments cannot be switch kind");
  }
  // add the definition to the set of all definitions
  unsigned i = m_data->add_definition(definition.m_name, definition.m_kind, definition.m_mode, definition.m_message);
  // also add it to the list of values, but only if it has a default value
  if (!definition.m_default.empty()) m_data->add_value(i, definition.m_default, "builtin default");
  return i;
}

void stlplus::cli_parser::set_defaults(const ini_manager& defaults, const std::string& ini_section) throw()
{
  m_data->increase_level();
  // for each definition that exists, test to see if there is a value for it in the ini file
  for (unsigned i = 0; i < m_data->m_definitions.size(); i++)
  {
    std::string name = m_data->m_definitions[i].m_name;
    if (defaults.variable_exists(ini_section, name))
    {
      std::string value = defaults.variable_value(ini_section, name);
      // an empty string is used to negate the value
      if (value.empty())
        m_data->erase_value(i);
      else
        m_data->add_value(i, value, filespec_to_relative_path(defaults.variable_filename(ini_section, name)));
    }
  }
  // add the set of ini files to the list for usage reports
  for (unsigned j = 0; j < defaults.size(); j++)
    m_data->add_ini_file(defaults.filename(j));
}

bool stlplus::cli_parser::parse(char* argv[]) throw(cli_argument_error,message_handler_id_error,message_handler_format_error)
{
  bool result = true;
  if (!argv) throw cli_argument_error("Argument vector cannot be null");
  m_data->increase_level();
  if (argv[0])
    m_data->m_executable = argv[0];
  for (unsigned i = 1; argv[i]; i++)
  {
    std::string name = argv[i];
    if (!name.empty() && name[0] == '-')
    {
      // we have a command line option
      unsigned found = m_data->find_definition(name.substr(1, name.size()-1));
      if (found < m_data->m_definitions.size())
      {
        // found it in its positive form
        switch (m_data->m_definitions[found].m_kind)
        {
        case cli_switch_kind:
          m_data->add_switch(found, true, "command line");
          break;
        case cli_value_kind:
          // get the next argument in argv as the value of this option
          // first check that there is a next value
          if (!argv[i+1])
            result &= m_data->m_errors.error("CLI_VALUE_MISSING", name);
          else
            m_data->add_value(found, argv[++i], "command line");
          break;
        }
      }
      else if (name.size() > 3 && name.substr(1,2) == "no")
      {
        found = m_data->find_definition(name.substr(3, name.size()-3));
        if (found < m_data->m_definitions.size())
        {
          // found it in its negated form
          switch (m_data->m_definitions[found].m_kind)
          {
          case cli_switch_kind:
            m_data->add_switch(found, false, "command line");
            break;
          case cli_value_kind:
            m_data->erase_value(found);
            break;
          }
        }
        else
        {
          // could not find this option in either its true or negated form
          result &= m_data->m_errors.error("CLI_UNRECOGNISED_OPTION", name);
        }
      }
      else
      {
        // could not find this option and it could not be negated
        result &= m_data->m_errors.error("CLI_UNRECOGNISED_OPTION", name);
      }
    }
    else
    {
      // we have a command-line value which is represented internally as an option with an empty string as its name
      // some very obscure commands do not have values - only options, so allow for that case too
      unsigned found = m_data->find_definition("");
      if (found < m_data->m_definitions.size())
        m_data->add_value(found, name, "command line");
      else
        result &= m_data->m_errors.error("CLI_NO_VALUES", name);
    }
  }
  if (!result) m_data->set_invalid();
  return result;
}

bool stlplus::cli_parser::valid(void) throw()
{
  return m_data->valid();
}

unsigned stlplus::cli_parser::size(void) const throw()
{
  return m_data->m_values.size();
}

std::string stlplus::cli_parser::name(unsigned i) const throw(stlplus::cli_index_error)
{
  if (i >= size()) throw stlplus::cli_index_error("Index " + ::to_string(i) + " out of range");
  return m_data->m_definitions[m_data->m_values[i].m_definition].m_name;
}

unsigned stlplus::cli_parser::id(unsigned i) const throw(stlplus::cli_index_error)
{
  if (i >= size()) throw stlplus::cli_index_error("Index " + ::to_string(i) + " out of range");
  return m_data->m_values[i].m_definition;
}

stlplus::cli_parser::kind_t stlplus::cli_parser::kind(unsigned i) const throw(stlplus::cli_index_error)
{
  if (i >= size()) throw stlplus::cli_index_error("Index " + ::to_string(i) + " out of range");
  return m_data->m_definitions[m_data->m_values[i].m_definition].m_kind;
}

bool stlplus::cli_parser::switch_kind(unsigned i) const throw(stlplus::cli_index_error)
{
  return kind(i) == cli_switch_kind;
}

bool stlplus::cli_parser::value_kind(unsigned i) const throw(stlplus::cli_index_error)
{
  return kind(i) == cli_value_kind;
}

stlplus::cli_parser::mode_t stlplus::cli_parser::mode(unsigned i) const throw(stlplus::cli_index_error)
{
  if (i >= size()) throw stlplus::cli_index_error("Index " + ::to_string(i) + " out of range");
  return m_data->m_definitions[m_data->m_values[i].m_definition].m_mode;
}

bool stlplus::cli_parser::single_mode(unsigned i) const throw(stlplus::cli_index_error)
{
  return mode(i) == cli_single_mode;
}

bool stlplus::cli_parser::multiple_mode(unsigned i) const throw(stlplus::cli_index_error)
{
  return mode(i) == cli_multiple_mode;
}

bool stlplus::cli_parser::cumulative_mode(unsigned i) const throw(stlplus::cli_index_error)
{
  return mode(i) == cli_cumulative_mode;
}

bool stlplus::cli_parser::switch_value(unsigned i) const throw(stlplus::cli_mode_error,stlplus::cli_index_error)
{
  if (i >= size()) throw stlplus::cli_index_error("Index " + ::to_string(i) + " out of range");
  if (kind(i) != cli_switch_kind) throw stlplus::cli_mode_error(name(i) + " is not a switch kind");
  std::string value = m_data->m_values[i].m_value;
  return value == "on" || value == "true" || value == "1";
}

std::string stlplus::cli_parser::string_value(unsigned i) const throw(stlplus::cli_mode_error,stlplus::cli_index_error)
{
  if (i >= size()) throw stlplus::cli_index_error("Index " + ::to_string(i) + " out of range");
  if (kind(i) != cli_value_kind) throw stlplus::cli_mode_error(name(i) + " is not a value kind");
  return m_data->m_values[i].m_value;
}

////////////////////////////////////////////////////////////////////////////////

void stlplus::cli_parser::usage(void) const throw(std::runtime_error)
{
  m_data->m_errors.information("CLI_USAGE_PROGRAM", m_data->m_executable);
  m_data->m_errors.information("CLI_USAGE_DEFINITIONS");
  for (unsigned d = 0; d < m_data->m_definitions.size(); d++)
  {
    m_data->m_errors.information(m_data->m_definitions[d].m_message);
  }
  if (size() != 0)
  {
    m_data->m_errors.information("CLI_USAGE_VALUES");
    for (unsigned v = 0; v < size(); v++)
    {
      std::string source = m_data->m_values[v].m_source;
      std::string key = name(v);
      if (key.empty())
      {
        // command-line values
        m_data->m_errors.information("CLI_USAGE_VALUE_RESULT", string_value(v), source);
      }
      else if (kind(v) == cli_switch_kind)
      {
        // a switch
        m_data->m_errors.information("CLI_USAGE_SWITCH_RESULT", (switch_value(v) ? name(v) : "no" + name(v)), source);
      }
      else
      {
        // other values
        std::vector<std::string> args;
        args.push_back(name(v));
        args.push_back(string_value(v));
        args.push_back(source);
        m_data->m_errors.information("CLI_USAGE_OPTION_RESULT", args);
      }
    }
  }
  if (m_data->ini_file_size() > 0)
  {
    m_data->m_errors.information("CLI_INI_HEADER");
    for (unsigned i = 0; i < m_data->ini_file_size(); i++)
    {
      if (file_exists(m_data->ini_file(i)))
        m_data->m_errors.information("CLI_INI_FILE_PRESENT", filespec_to_relative_path(m_data->ini_file(i)));
      else
        m_data->m_errors.information("CLI_INI_FILE_ABSENT", filespec_to_relative_path(m_data->ini_file(i)));
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
