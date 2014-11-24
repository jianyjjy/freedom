//CompareFile.cpp

#include "CompareFile.h"
#include "CompareFile.h"
#include "CompareResultInterface.h"
#include "DeletedLine.h"
#include "AddedLine.h"
#include "ModifiedLine.h"

#include <fstream>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

#include <iostream>
using namespace std;
#define LOG(str) cout << "[LOG] " << str << endl;


deque<CompareResultInterface*> CompareFile::get_result(void)
{
	deque<CompareResultInterface*> diff_result;

	if( first_file == "" || second_file == "" )
	{
		//FILE NAME NOT SET
		throw( string("EITHER OF FILE NAME NOT SET") );
	}

	deque<string> data1;
	deque<string> data2;

	{
		ifstream ifs1(first_file);
		ifstream ifs2(second_file);

		if( !ifs1.is_open() || !ifs2.is_open() )
		{
			//INVALID FILE1 OR FILE2
			throw( string("EITHER OF FILE IS INVALID") );
		}

		LOG("READING FILES");
		string line_data;
		while( !ifs1.eof() )
		{
			std::getline(ifs1, line_data);
			data1.push_back(line_data);
		}
		while( !ifs2.eof() )
		{
			std::getline(ifs2, line_data);
			data2.push_back(line_data);
		}
		LOG("READING FILES FINISHED");
	}

	CompareResultInterface* compare_result = nullptr;

	auto itr1 = data1.begin();
	auto itr2 = data2.begin();

	while( itr1 != data1.end() && itr2 != data2.end() )
	{
		//READING CONTINOUS MATCHING DATA
		if( *itr1 == *itr2 )
		{
			//LOG(*itr1)
			itr1++;
			itr2++;
			continue;
		}

		//LOG("FOUND NON-MATCHING")

		auto f_itr1 = find_first_of(itr1, data1.end(), itr2, data2.end());	//FIRST MATCHING POSITION IN data1, FROM [itr2, data2.end())
		auto f_itr2 = find_first_of(itr2, data2.end(), itr1, data1.end());	//FIRST MATCHING POSITION IN data2, FROM [itr1, data1.end())

		//LOG(*itr1)
		//LOG(*itr2)
		//LOG(*f_itr1)
		//LOG(*f_itr2)

		if( f_itr1 == data1.end() )	//means f_itr2 == data2.end()
		{
			LOG("UNABLE TO FIND NEXT MATCH")
			break;
		}

		if( f_itr2 == itr2 )
		{
			compare_result = new DeletedLine(itr1-data1.begin(), itr2-data2.begin(), 0, string());
			while( *itr1 != *itr2 )
			{
				compare_result->add_line(*itr1);
				itr1++;
			}
		}
		else if( f_itr1 == itr1 )
		{
			compare_result = new AddedLine(itr1-data1.begin(), itr2-data2.begin(), 0, string());
			while( *itr2 != *itr1 )
			{
				compare_result->add_line(*itr2);
				itr2++;
			}
		}
		else	//(*f_itr1 == *f_itr2)
		{
			compare_result = new ModifiedLine(itr1-data1.begin(), itr2-data2.begin(), string(), string());
			while( itr1 < f_itr1 )
			{
				compare_result->add_line(*itr1, string());
				itr1++;
			}
			while( itr2 < f_itr2 )
			{
				compare_result->add_line(string(), *itr2);
				itr2++;
			}

		}

		//LOG(compare_result->marshall());
		diff_result.push_back(compare_result);
	}

	if( itr1 == data1.end() && itr2 == data2.end() )
		return diff_result;

	if( itr2 == data2.end() )
	{
		compare_result = new DeletedLine(itr1-data1.begin(), itr2-data2.begin(), data1.end()-itr1, string());
		while( itr1 != data1.end() )
		{
			compare_result->add_line(*itr1);
			itr1++;
		}
	}
	else if( itr1 == data1.end() )
	{
		compare_result = new AddedLine(itr1-data1.begin(), itr2-data2.begin(), data2.end()-itr2, string());
		while( itr2 != data2.end() )
		{
			compare_result->add_line(*itr2);
			itr2++;
		}
	}
	else
	{
		compare_result = new ModifiedLine(itr1-data1.begin(), itr2-data2.begin(), string(), string());
		while( itr1 != data1.end() )
		{
			compare_result->add_line(*itr1, string());
			itr1++;
		}
		while( itr2 != data2.end() )
		{
			compare_result->add_line(string(), *itr2);
			itr2++;
		}
	}

	diff_result.push_back(compare_result);


	return diff_result;
}
