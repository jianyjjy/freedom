/*
 * VariantsInfo.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: satram
 */
#include "common.h"
#include "m3u8/Tag.h"
#include "VariantsInfo.h"

VariantsInfo::VariantsInfo(Section *section, std::string master_path)
{
	//std::cout << "creating variant info for section " << section->get_name() <<std::endl;
	std::string media_tag("#EXT-X-MEDIA");
	std::string stream_tag("#EXT-X-STREAM-INF");
	std::string iframe_tag("#EXT-X-I-FRAME-STREAM-INF");

	group_id = std::numeric_limits<unsigned int>::max();
	media_program_id = std::numeric_limits<unsigned int>::max();
	iframe_program_id = std::numeric_limits<unsigned int>::max();


	for(unsigned int i = 0; i < section->tags.size(); i++)
	{
		if(media_tag == section->tags[i]->get_name())
		{
			for(unsigned int j = 0; j < section->tags[i]->properties.size(); j++)
			{
				Property *ppty = section->tags[i]->properties[j];
				std::string name = ppty->get_name()->asString();
				if(name.compare("TYPE") == 0)
					type = ppty->get_value()->asString();
				else if(name.compare("URI") == 0)
				{
					media_URI = get_quoted_string(ppty->get_value()->asString());
					if(media_URI.find("/") == std::string::npos)
						media_URI = master_path + media_URI;
				}
				else if(name.compare("GROUP-ID") == 0)
					group_id = ppty->get_value()->asUInt();
				else if(name.compare("LANGUAGE") == 0)
					language = ppty->get_value()->asString();
				else if(name.compare("ASSOC-LANGUAGE") == 0)
					assoc_language = ppty->get_value()->asString();
				else if(name.compare("NAME") == 0)
					media_name = ppty->get_value()->asString();
				else if(name.compare("DEFAULT") == 0)
					default_value = ppty->get_value()->asBool();
				else if(name.compare("AUTOSELECT") == 0)
					default_value = ppty->get_value()->asBool();
				else if(name.compare("FORCED") == 0)
					default_value = ppty->get_value()->asBool();
				else if(name.compare("INSTREAM-ID") == 0)
					instream_id = ppty->get_value()->asString();
				else if(name.compare("CHARACTERISTICS") == 0)
					characteristics = ppty->get_value()->asString();
			}
		}
		else if(stream_tag == section->tags[i]->get_name())
		{
			for(unsigned int j = 0; j < section->tags[i]->properties.size(); j++)
			{
				Property *ppty = section->tags[i]->properties[j];
				std::string name = ppty->get_name()->asString();
				if(name.compare("BANDWIDTH") == 0)
					media_bandwidth = ppty->get_value()->asLongLong();
				else if(name.compare("AVERAGE-BANDWIDTH") == 0)
					media_avg_bandwidth = ppty->get_value()->asLongLong();
				else if(name.compare("CODECS") == 0)
					codecs = ppty->get_value()->asString();
				else if(name.compare("RESOLUTION") == 0)
				{
					std::string resolution = ppty->get_value()->asString();
					size_t offset = resolution.find_first_of("x");
					std::string wd = resolution.substr(0, offset);
					std::string ht = resolution.substr(offset+1, resolution.size());
					width = std::stoul(wd);
					height = std::stoul(ht);
				}
				else if(name.compare("AUDIO") == 0)
					audio_id = ppty->get_value()->asUInt();
				else if(name.compare("VIDEO") == 0)
					video_id = ppty->get_value()->asUInt();
				else if(name.compare("SUBTITLES") == 0)
					subtitles_id = ppty->get_value()->asUInt();
				else if(name.compare("CLOSED-CAPTIONS") == 0)
					cc_id = ppty->get_value()->asUInt();
				else if(name.compare("PROGRAM-ID") == 0)
					media_program_id = ppty->get_value()->asUInt();
			}
			media_URI = section->get_URI();
			if(media_URI.find("/") == std::string::npos)
				media_URI = master_path + media_URI;
		}
		else if(iframe_tag == section->tags[i]->get_name())
		{
			for(unsigned int j = 0; j < section->tags[i]->properties.size(); j++)
			{
				Property *ppty = section->tags[i]->properties[j];
				std::string name = ppty->get_name()->asString();
				if(name.compare("BANDWIDTH") == 0)
					iframe_bandwidth = ppty->get_value()->asLongLong();
				else if(name.compare("AVERAGE-BANDWIDTH") == 0)
					iframe_avg_bandwidth = ppty->get_value()->asLongLong();
				else if(name.compare("URI") == 0)
				{
					iframe_URI = get_quoted_string(ppty->get_value()->asString());
					if(iframe_URI.find("/") == std::string::npos)
						iframe_URI = master_path + iframe_URI;
				}
				else if(name.compare("PROGRAM-ID") == 0)
					iframe_program_id = ppty->get_value()->asUInt();
			}
		}
	}
}

VariantsInfo::~VariantsInfo()
{

}
