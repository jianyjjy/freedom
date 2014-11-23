/*
 * PlaylistInterface.h
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#ifndef PLAYLISTINTERFACE_H_
#define PLAYLISTINTERFACE_H_

#include "common.h"
#include "m3u8/Playlist.h"

class VariantsInfo;

enum PLAYLIST_E
{
	MASTER,
	MEDIA,
	IFRAME
};


enum RENDITION_GROUP_E
{
	NONE,
	VIDEO,
	AUDIO,
	SUBTITLE,
};

#define PRINT(X) //X

class PlaylistInterface
{
protected:
	std::string path;
	std::string name;
	std::string url;

	Playlist playlist;
	unsigned int node_count;
	PLAYLIST_E playlist_type;
	RENDITION_GROUP_E group;
	unsigned int sessionId;

	void add_property(Tag &t, std::string & str)
	{
		PRINT(std::cout << "add_property: str: " << str << std::endl);
		size_t value_offset = str.find("=");
		std::string name;
		std::string value;
		if(value_offset != std::string::npos)
		{
			name = str.substr(0, value_offset);
			PRINT(std::cout << "add_property: name: " << name << std::endl);
			std::string value = str.substr(value_offset+1, str.size());
			PRINT(std::cout << "add_property: value: " << value << std::endl);
			t.add_property(name, value);
		}
		else
		{
			t.add_property(str);
		}
	}

    size_t validate_attributes_seprator(std::string & str)
    {
        //find double quotes position
        std::deque<std::pair<size_t,size_t>> quotes;
        size_t first = std::string::npos;
        char find = '\"';
        for(size_t i = 0; i < str.size(); i++)
        {
        	if(str[i] == find)
            {
                if(first == std::string::npos)
                    first = i;
                else
                {
                    quotes.push_back(std::pair<size_t,size_t>(first, i));
                    PRINT(std::cout << "double quotes are " << first << "..." << i << std::endl);
                    first = std::string::npos;
                }
            }
        }

        size_t attrib_offset = std::string::npos;
        find = ',';
        for(size_t i = 0; i < str.size(); i++)
        {
            if(str[i] == find)
            {
            	attrib_offset = i;
                for(unsigned int i = 0; i < quotes.size(); i++)
                    if(attrib_offset > quotes[i].first && attrib_offset < quotes[i].second)
                    	attrib_offset = std::string::npos;
                if(attrib_offset != std::string::npos) break;
            }
        }
        return attrib_offset;
    }


    void parse_property(Tag & t, std::string & str)
    {
    	size_t attrib_offset = std::string::npos;
    	if(str.find(",") != std::string::npos)
    		 attrib_offset = validate_attributes_seprator(str);
		if(attrib_offset == std::string::npos)
		{
			add_property(t, str);
		}
		else
		{
			std::string rem_str = str.substr(0,attrib_offset);
			add_property(t, rem_str);
			std::string attributes = str.substr(attrib_offset+1, str.size());
			PRINT(std::cout << "parse_property: attributes: " << attributes << std::endl);
			parse_property(t, attributes);
		}
	}


	Tag get_tag(std::string& str)
	{
		size_t tag_offset = str.find(":");
		if(tag_offset != std::string::npos)
		{
			std::string name = str.substr(0, tag_offset);
			PRINT(std::cout << "get_tag: name: " << name << std::endl);
			std::string attributes = str.substr(tag_offset+1, str.size()- tag_offset);
			PRINT(std::cout << "get_tag: attributes: " << attributes << std::endl);
			Tag new_tag(name);
			parse_property(new_tag, attributes);
			return new_tag;
		}
		else
		{
			PRINT(std::cout << "get_tag: str: " << str << std::endl);
			Tag new_tag(str);
			return new_tag;
		}
	}


public:
	PlaylistInterface (std::string filename)
	{
		node_count = 0;
		group = NONE;
		url = filename;
		size_t offset = url.find_last_of("/");
		if(offset != std::string::npos)
		{
			path = url.substr(0, offset+1);
			name = url.substr(offset+1, url.size() - offset);
		}
		else
			name = url;
	}

	virtual ~PlaylistInterface()
	{

	}

	virtual void add_header(std::deque<std::string> & strqueue)
	{
		//PRINT(std::cout << "add_header\n");
		Section header("header");
		for(unsigned int i = 0; i < strqueue.size(); i++)
		{
			Tag instance = get_tag(strqueue[i]);
			header.add_tag(instance);
		}
		playlist.add_section(header);
		PRINT(std::cout << "Header-----------------------------------------\n");
	}

	virtual void add_section(std::deque<std::string>& strqueue)
	{
		//PRINT(std::cout << "add_section\n");
		std::ostringstream oss;
		oss << "node-" << node_count++;
		Section node(oss.str());
		for(unsigned int i = 0; i < strqueue.size(); i++)
		{
			//PRINT(std::cout << strqueue[i] << std::endl);
			if(strqueue[i].find(".ts") != std::string::npos || (strqueue[i].find(".m3u8") != std::string::npos  && strqueue[i].find("URI") == std::string::npos))
			{
				size_t path_offset =  strqueue[i].find_last_of("/");
				if(path_offset != std::string::npos)
				{
					std::string path = strqueue[i].substr(0, path_offset+1);
					std::string name = strqueue[i].substr(path_offset+1, strqueue[i].size());
					PRINT(std::cout << "set path: " << path << std::endl);
					PRINT(std::cout << "set locator: " << name << std::endl);
					node.set_path(path);
					node.set_locator(name);
				}
				else
				{
					PRINT(std::cout << "set locator: " << strqueue[i] << std::endl);
					node.set_locator(strqueue[i]);
				}
			}
			else
			{
				Tag instance = get_tag(strqueue[i]);
				node.add_tag(instance);
			}
		}
		//PRINT(std::cout << "created a section\n");
		playlist.add_section(node);
		PRINT(std::cout << "Section-----------------------------------------\n");
	}

	virtual void add_footer(std::deque<std::string> & strqueue)
	{
		//PRINT(std::cout << "add_footer\n");
		Section footer("footer");
		for(unsigned int i = 0; i < strqueue.size(); i++)
		{
			Tag instance = get_tag(strqueue[i]);
			footer.add_tag(instance);
		}
		playlist.add_section(footer);
		PRINT(std::cout << "Footer-----------------------------------------\n");
	}

	virtual void remove_section(std::deque<std::string>& strqueue)
	{
		PRINT(std::cout << "remove_section\n");
	}

	virtual std::string marshall()
	{
		PRINT(std::cout << "marshall()\n");
		std::ostringstream oss;
		oss << url << std::endl;
		oss << playlist.marshall() << std::endl;
		return oss.str();
	}

	virtual unsigned int get_variants_count()
	{
		throw std::runtime_error("get_variants_count -- not implemented for this playlist");
	};

	virtual std::deque<VariantsInfo *> get_variants()
	{
		throw std::runtime_error("get_variants -- not implemented for this playlist");
	}
};

#undef PRINT

#endif /* PLAYLISTINTERFACE_H_ */
