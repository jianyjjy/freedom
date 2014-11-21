/*
 * unittest.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: satram
 */

#include "CompareFile.h"


std::string get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  std::string contents;
  if (in)
  {
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
  }
   return(contents);
}


int main(int argc, char *argv[])
{
	CompareFile fc;
	if(argc < 3)
	{
		std::cout << "Usage: ./filecomparetool <file1name> <file2name>";
		return -1;
	}
	fc.set_first(argv[1]);
	fc.set_second(argv[2]);
	std::cout << fc.get_result() << std::endl;

	std::ostringstream oss;
	oss << "diff " << argv[1] << " "<< argv[2] << " > difftmp.txt";
	system(oss.str().c_str());

	std::cout << "----diff result ----\n";
	std::cout << get_file_contents("difftmp.txt");

	return 0;
}
