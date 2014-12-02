/*
 * VariantsInfo.h
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */

#ifndef VARIANTSINFO_H_
#define VARIANTSINFO_H_

#include "m3u8/Section.h"


class VariantsInfo
{
	//pantos v14
	//EXT-X-MEDIA attributes
	std::string type;
	unsigned int group_id;
	std::string language;
	std::string assoc_language;
	std::string media_name;
	bool default_value;
	bool auto_select;
	bool forced;
	std::string instream_id;  //used for closed captions only CC1, CC2, CC3, CC4 or SERVICEn
	std::string characteristics;

	//EXT-X-STREAM-INF and EXT-X-I-FRAME-STREAM-INF
	long long media_bandwidth;
	long long media_avg_bandwidth;
	long long iframe_bandwidth;
	long long iframe_avg_bandwidth;
	unsigned int width;
	unsigned int height;
	std::string codecs;
	std::string media_URI;
	std::string iframe_URI;
	unsigned int audio_id; //AUDIO
	unsigned int video_id; //VIDEO
	unsigned int subtitles_id; //SUBTITLES
	unsigned int cc_id; //CLOSED-CAPTIONS

	//pantos v5
	unsigned int media_program_id;
	unsigned int iframe_program_id;

public:
	VariantsInfo(Section *section, std::string master_path);
	virtual ~VariantsInfo();

	std::string get_quoted_string(std::string src)
	{
		size_t quote1 = src.find_first_of("\"");
		size_t quote2 = src.find_last_of("\"");
		std::string dst = src.substr(quote1+1, quote2-quote1-1);
		return dst;
	}
	unsigned int get_group_id()
	{
		if(group_id != std::numeric_limits<unsigned int>::max())
			return group_id;
		else if(media_program_id != std::numeric_limits<unsigned int>::max())
			return media_program_id;
		else if(iframe_program_id != std::numeric_limits<unsigned int>::max())
			return iframe_program_id;
		else
			return 0;
	}

	std::string get_media_URI()
	{
		return media_URI;
	}

	std::string get_iframe_URI()
	{
		return iframe_URI;
	}

	std::string marshall()
	{
		std::ostringstream oss;
		oss << "ProgramID " << media_program_id << "\t";
		oss << "URI " << media_URI << "\t";
		oss << "IfrURI " << iframe_URI << "\t";
		oss << "BW " << media_bandwidth << "\t";
		oss << "IfrBW " << iframe_bandwidth << "\t";
		oss << "wd " << width << "\t";
		oss << "ht " << height << "\t";
		oss << std::endl;

		return oss.str();
	}
};

#endif /* VARIANTSINFO_H_ */
