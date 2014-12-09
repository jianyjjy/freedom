//CompareFile.cpp

#include "CompareFile.h"
#include "CompareFile.h"
#include "CompareResultInterface.h"
#include "DeletedLine.h"
#include "AddedLine.h"
#include "ModifiedLine.h"

#include <fstream>
#include <vector>
#include <numeric>
using namespace std;

#include <iostream>
using namespace std;
#define LOG(str) //cout << "[LOG] " << str << endl;

struct CommonSubSeq
{
	int src_st;
	int dst_st;
	int len;
};

//Longest Common Sub-seqeuence algorithm
CommonSubSeq* CompareFile::longest_common_subseq(deque<string> data1, int start1, int end1, deque<string>data2, int start2, int end2)
{
	CommonSubSeq* pLCS = new CommonSubSeq();
	pLCS->src_st = start1;
	pLCS->dst_st = start2;
	pLCS->len = 0;

	vector< vector<int> > lcs(data1.size(), vector<int>(data2.size(), 0) );
	int lcs_len;
	for( auto src_itr = start1 ; src_itr < end1 ; src_itr++ )
	{
		for( auto dst_itr = start2 ; dst_itr < end2 ; dst_itr++ )
		{
			if( data1[src_itr] != data2[dst_itr] )
				continue;

			if( src_itr > start1 && dst_itr > start2 )
				lcs_len = lcs[src_itr][dst_itr] = lcs[src_itr-1][dst_itr-1] + 1;
			else
				lcs_len = lcs[src_itr][dst_itr] = 1;
			if( lcs_len > pLCS->len )
			{
				pLCS->src_st = src_itr-lcs_len+1;
				pLCS->dst_st = dst_itr-lcs_len+1;
				pLCS->len = lcs_len;
			}
		}
	}

	return pLCS;
}

void CompareFile::find_common_subseqs(deque<string> data1, int start1, int end1, deque<string> data2, int start2, int end2, deque<CommonSubSeq*>* pCommonSeqs)
{
	CommonSubSeq* common_subseq = longest_common_subseq(data1, start1, end1, data2, start2, end2);
	if( common_subseq->len == 0 )
		return;

	find_common_subseqs(data1, start1, common_subseq->src_st, data2, start2, common_subseq->dst_st, pCommonSeqs);
	pCommonSeqs->push_back(common_subseq);
	find_common_subseqs(data1, common_subseq->src_st + common_subseq->len, end1, data2, common_subseq->dst_st + common_subseq->len, end2, pCommonSeqs);

	return;
}

//Getting maximum contiguous matches between 2 strings
int CompareFile::get_match_count(string s1, string s2)
{
	//Addition of extra characters at end of 2nd string to match character count within 1st string
	//length(1st string) always less then length(2nd string) ... useful for inner_product()
	s2.append( s1.size()-1, ' ');

	string t1 = s1;
	int product;
	int max_product = 0;
	for(unsigned int i = 0 ; i < s1.length() ; i++ )
	{
		//inner_product to get count of matching characters between 1st string & appended 2nd string
		product = inner_product(t1.begin()+i, t1.end(), s2.begin(), 0, std::plus<int>(), std::equal_to<std::string::value_type>());
		if( product > max_product )
			max_product = product;
	}

	return max_product;
}

deque<CompareResultInterface*> CompareFile::compare(void)
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

	deque<CommonSubSeq*> common_subseqs;
	find_common_subseqs(data1, 0, data1.size(), data2, 0, data2.size(), &common_subseqs);

	CommonSubSeq* final_empty_subseq = new CommonSubSeq();
	final_empty_subseq->src_st = data1.size();
	final_empty_subseq->dst_st = data2.size();
	final_empty_subseq->len = 0;

	common_subseqs.push_back(final_empty_subseq);

	int src_itr = 0;
	int dst_itr = 0;
	for( CommonSubSeq* subseq : common_subseqs )
	{
		CompareResultInterface* compare_result = nullptr;

		if( src_itr != subseq->src_st && dst_itr != subseq->dst_st )
		{
//Modified block
			int modified_match;
			int max_modified_match = 0;
			int src_closest_match, dst_closest_match;
			LOG("Getting closest match in modified lines");
			for( auto src = src_itr ; src < subseq->src_st ; src++ )
			{
				for( auto dst = dst_itr ; dst < subseq->dst_st ; dst++ )
				{
					modified_match = get_match_count(data1[src], data2[dst]);
					if( max_modified_match < modified_match )
					{
						max_modified_match = modified_match;
						src_closest_match = src;
						dst_closest_match = dst;
					}
				}
			}

			LOG("Closest match found at");
			LOG(src_closest_match);
			LOG(dst_closest_match);

//At start of Modified block : Added or Deleted block
			compare_result = nullptr;
			if ( (src_closest_match - src_itr) < (dst_closest_match - dst_itr) )
			{
				LOG("Added lines before closest match");
				LOG(src_itr);
				LOG(dst_itr);

				compare_result = new AddedLine(src_itr, dst_itr);
				while ( (src_closest_match - src_itr) != (dst_closest_match - dst_itr) )
					compare_result->add_dst_str(data2[dst_itr++]);
			}
			else if ( (src_closest_match - src_itr) > (dst_closest_match - dst_itr) )
			{
				LOG("Deleted lines before closest match");
				LOG(src_itr);
				LOG(dst_itr);

				compare_result = new DeletedLine(src_itr, dst_itr);
				while ( (src_closest_match - src_itr) != (dst_closest_match - dst_itr) )
					compare_result->add_src_str(data1[src_itr++]);
			}
			else
				LOG("No added or deleted lines before closest match");

			if( compare_result )
				diff_result.push_back(compare_result);

//Actual modified block
			LOG("Modified Lines");
			LOG(src_itr);
			LOG(dst_itr);
			compare_result = new ModifiedLine(src_itr, dst_itr);
			while ( (subseq->src_st - src_itr) > 0 && (subseq->dst_st - dst_itr) > 0 )
			{
				compare_result->add_src_str(data1[src_itr++]);
				compare_result->add_dst_str(data2[dst_itr++]);
			}
			diff_result.push_back(compare_result);



//At end of Modified block : Added or Deleted block
			compare_result = nullptr;
			if ( (subseq->dst_st - dst_itr) > 0 )
			{
				LOG("Added lines after closest match");	
				LOG(src_itr);
				LOG(dst_itr);

				compare_result = new AddedLine(src_itr, dst_itr);
                        	while( dst_itr < subseq->dst_st )
                                	compare_result->add_dst_str(data2[dst_itr++]);
			}
			else if ( (subseq->src_st - src_itr) > 0 )
			{
				LOG("Deleted lines after closest match");
				LOG(src_itr);
				LOG(dst_itr);

				compare_result = new DeletedLine(src_itr, dst_itr);
				while( src_itr < subseq->src_st )
                                	compare_result->add_src_str(data1[src_itr++]);
			}
			else
			{
				LOG("Invalid state of code");
				LOG(src_itr);
				LOG(dst_itr);
			}
		}
		else if( src_itr == subseq->src_st && dst_itr != subseq->dst_st )
		{
//Added block in Destination
			compare_result = new AddedLine(src_itr, dst_itr);

			while( dst_itr < subseq->dst_st )
				compare_result->add_dst_str(data2[dst_itr++]);
			LOG("Added Lines");
		}
		else if( dst_itr == subseq->dst_st && src_itr != subseq->src_st )
		{
//Deleted block from Source
			compare_result = new DeletedLine(src_itr, dst_itr);

			while( src_itr < subseq->src_st )
				compare_result->add_src_str(data1[src_itr++]);
			LOG("Deleted Lines");
		}

		src_itr = subseq->src_st + subseq->len;
		dst_itr = subseq->dst_st + subseq->len;

		if( compare_result == nullptr )
			continue;

		//LOG(compare_result->marshall());
		diff_result.push_back(compare_result);
	}

	return diff_result;
}
