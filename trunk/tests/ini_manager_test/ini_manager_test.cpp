/*------------------------------------------------------------------------------

  Author:    Andy Rushton

  Test the ini_manager subsystem

------------------------------------------------------------------------------*/
#include "debug.hpp"
#include "build.hpp"
#include "ini_manager.hpp"
#include "file_system.hpp"
#include "print_vector.hpp"
#include "print_string.hpp"
#include "string_utilities.hpp"
////////////////////////////////////////////////////////////////////////////////

static const char* ini_filename = "test.ini";
static const char* ini_subdirs = "";

////////////////////////////////////////////////////////////////////////////////
// utility for printing a vector of strings, used a lot in this program

std::ostream& operator<<(std::ostream& device, const std::vector<std::string>& strings)
{
  stlplus::print_vector(device, strings, stlplus::print_string, ":");
  return device;
}

////////////////////////////////////////////////////////////////////////////////
// create a lookup path for message files - later used to perform path lookup for the actual files

std::vector<std::string> generate_all_paths(const std::vector<std::string>& main_paths,
                                            const std::vector<std::string>& subdirs)
{
  DEBUG_TRACE;
  std::vector<std::string> result;
  // simply generate all permutations
  // including with no subdir and in the subdirs
  for (unsigned i = 0; i < main_paths.size(); i++)
  {
    std::string path = main_paths[i];
    IF_DEBUG(std::cerr << "adding path: " << path << std::endl);
    result.push_back(path);
    for (unsigned j = 0; j < subdirs.size(); j++)
    {
      std::string subpath = stlplus::folder_down(path,subdirs[j]);
      IF_DEBUG(std::cerr << "adding subpath: " << subpath << std::endl);
      result.push_back(subpath);
    }
  }
  IF_DEBUG(std::cerr << "paths: " << result << std::endl);
  return result;
}

std::vector<std::string> generate_basic_path(const std::string& installation_folder)
{
  DEBUG_TRACE;
  std::vector<std::string> paths;
  paths.push_back(stlplus::folder_current());
  paths.push_back(stlplus::folder_home());
  paths.push_back(stlplus::folder_up(installation_folder));
  paths.push_back(installation_folder);
  IF_DEBUG(std::cerr << "basic path: " << paths << std::endl);
  return paths;
}

std::string generate_lookup_path(const std::vector<std::string>& path)
{
  DEBUG_TRACE;
  std::string result = stlplus::join(path, ":");
  IF_DEBUG(std::cerr << "lookup path: " << result << std::endl);
  return result;
}

std::vector<std::string> standard_paths(const std::string& installation_folder, const std::string& subdirs)
{
  DEBUG_TRACE;
  IF_DEBUG(std::cerr << "installation folder: " << installation_folder << std::endl);
  std::vector<std::string> basic_path = generate_basic_path(installation_folder);
  IF_DEBUG(std::cerr << "basic path: " << basic_path << std::endl);
  std::vector<std::string> subdir_split = stlplus::split(subdirs,":");
  IF_DEBUG(std::cerr << "subdirs: " << subdir_split << std::endl);
  return generate_all_paths(basic_path, subdir_split);
}

std::string standard_lookup_path(const std::string& installation_folder, const std::string& subdirs)
{
  DEBUG_TRACE;
  std::vector<std::string> paths = standard_paths(installation_folder, subdirs);
  IF_DEBUG(std::cerr << "paths: " << paths << std::endl);
  return generate_lookup_path(paths);
}

std::string lookup_message_file(const std::string& name, const std::string& path)
{
  DEBUG_TRACE;
  // TODO - handle multiple languages by mofifying the message file name with the locale
  std::string result = stlplus::lookup(name, path, ":");
  IF_DEBUG(std::cerr << "lookup: " << name << " in: " << path << " = " << result << std::endl);
  return result;
}

std::vector<std::string> standard_ini_files(const std::string& name, 
                                            const std::string& installation_folder,
                                            const std::string& subfolders)
{
  DEBUG_TRACE;
  std::vector<std::string> path = standard_paths(installation_folder, subfolders);
  IF_DEBUG(std::cerr << "standard paths: " << path << std::endl);
  std::vector<std::string> result;
  for (unsigned i = 0; i < path.size(); i++)
  {
    std::string filespec = stlplus::create_filespec(path[i],name);
    IF_DEBUG(std::cerr << "adding filespec: " << filespec << std::endl);
    result.push_back(filespec);
  }
  IF_DEBUG(std::cerr << "standard ini files: " << result << std::endl);
  return result;
}

////////////////////////////////////////////////////////////////////////////////

bool test_ini_manager(stlplus::ini_manager& manager, const std::string& name)
{
  bool success = true;
  std::cerr << "======== Testing " << name << std::endl;
  for (unsigned i = 0; i < manager.size(); i++)
  {
    std::cerr << "ini file: " << manager.filename(i);
    std::cerr << (manager.writable(i) ? " writable" : " not writable");
    std::cerr << (manager.empty(i) ? " empty" : " not empty");
    std::cerr << std::endl;
  }

  if (manager.variable_exists("section","test"))
  {
    std::cerr << "variable \"test\" found in section \"section\" = " 
              << manager.variable_value("section","test") << std::endl;
    std::cerr << "filename = " << manager.variable_filename("section","test") 
              << ", line = " << manager.variable_linenumber("section","test") << std::endl;
  }
  else
  {
    std::cerr << "variable \"test\" not found in section \"section\"" << std::endl;
    success = false;
  }
  return success;
}

////////////////////////////////////////////////////////////////////////////////

int main (int argc, char* argv[])
{
  DEBUG_TRACE;
  std::cerr << stlplus::build() << std::endl;

  try
  {
    unsigned errors = 0;

    std::string install = stlplus::install_path(argv[0]);
    std::cerr << "install = " << install << std::endl;

    // set up an Ini file manager
    stlplus::ini_manager ini_files(standard_ini_files(ini_filename, install, ini_subdirs));
    std::cerr << "ini_files = " << ini_files << std::endl;
    if (!test_ini_manager(ini_files, "original"))
      errors++;

    stlplus::ini_manager ini_files2 = ini_files;
    if (!test_ini_manager(ini_files2, "alias"))
      errors++;

    return errors;
  }
  catch(std::exception& exception)
  {
    std::cerr << "exception: failed with " << exception.what() << std::endl;
    return -1;
  }
  return -2;
}

////////////////////////////////////////////////////////////////////////////////
