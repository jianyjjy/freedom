//CompareFile.cpp

#include "CompareFile.h"
#include "CompareFile.h"
#include "CompareResultInterface.h"
#include "DeletedLine.h"
#include "AddedLine.h"
#include "ModifiedLine.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <cmath>
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

CommonSubSeq* CompareFile::longest_common_subseq(deque<string> data1, int start1, int end1, deque<string>data2, int start2, int end2)
{
	CommonSubSeq* pLCS = new CommonSubSeq();
	pLCS->src_st = start1;
	pLCS->dst_st = start2;
	pLCS->len = 0;

	vector< vector<int> > lcs(data1.size(), vector<int>(data2.size(), 0) );
	int lcs_len;
	for( auto itr1 = start1 ; itr1 < end1 ; itr1++ )
	{
		for( auto itr2 = start2 ; itr2 < end2 ; itr2++ )
		{
			if( data1[itr1] != data2[itr2] )
				continue;

			if( itr1 > start1 && itr2 > start2 )
				lcs_len = lcs[itr1][itr2] = lcs[itr1-1][itr2-1] + 1;
			else
				lcs_len = lcs[itr1][itr2] = 1;
			if( lcs_len > pLCS->len )
			{
				pLCS->src_st = itr1-lcs_len+1;
				pLCS->dst_st = itr2-lcs_len+1;
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

	int itr1 = 0;
	int itr2 = 0;
	for( CommonSubSeq* subseq : common_subseqs )
	{
		CompareResultInterface* compare_result = nullptr;

		if( itr1 != subseq->src_st && itr2 != subseq->dst_st )
		{
			compare_result = new ModifiedLine(itr1, itr2);

			while( itr1 < subseq->src_st )
				compare_result->add_src_str(data1[itr1++]);
			while( itr2 < subseq->dst_st )
				compare_result->add_dst_str(data2[itr2++]);
			LOG("Modified Lines");
		}
		else if( itr1 == subseq->src_st && itr2 != subseq->dst_st )
		{
			compare_result = new AddedLine(itr1, itr2);

			while( itr2 < subseq->dst_st )
				compare_result->add_dst_str(data2[itr2++]);
			LOG("Added Lines");
		}
		else if( itr2 == subseq->dst_st && itr1 != subseq->src_st )
		{
			compare_result = new DeletedLine(itr1, itr2);

			while( itr1 < subseq->src_st )
				compare_result->add_src_str(data1[itr1++]);
			LOG("Deleted Lines");
		}

		itr1 = subseq->src_st + subseq->len;
		itr2 = subseq->dst_st + subseq->len;

		if( compare_result == nullptr )
			continue;

		//LOG(compare_result->marshall());
		diff_result.push_back(compare_result);
	}

	return diff_result;
}
