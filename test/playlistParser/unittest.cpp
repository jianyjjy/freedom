/*
 * unittest.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: satram
 */

#include "pp_common.h"
#include "PlaylistFactory.h"

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


void test1(PlaylistInterface *playlist, char *argv[])
{
    if(playlist != NULL){
        std::string dom_output = playlist->marshall();
        std::string text_input = get_file_contents(argv[1]);
        if(text_input.compare(dom_output) != 0){
            std::cout << "-------File output--------\n";
            std::cout << text_input << std::endl;
            std::cout << "-------DOM output--------\n";
            std::cout << dom_output;
            std::cout << "---------------------------\n";
            std::cout << "FAIL \n";
        }else{
            std::cout << dom_output << std::endl;
            std::cout << "PASS \n";
        }
    }
}

void test2(PlaylistInterface *playlist, char *argv[])
{
	std::ofstream outfile;
	outfile.open("test_output.m3u8");
	if(outfile.is_open())
	{
		outfile << playlist->marshall();
		outfile.close();
	}
	std::ostringstream oss;
	oss << "diff " << argv[1] << " test_output.m3u8";
	system(oss.str().c_str());
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		std::cout << "Usage: ./playlistParserTool <name.m3u8>" << std::endl;
		return  -1;
	}
	PlaylistFactory * hls_pp = PlaylistFactory::get_instance();
	PlaylistInterface *playlist = hls_pp->getDOM(argv[1]);
    test1(playlist, argv);
    test2(playlist, argv);
    return 0;
}
