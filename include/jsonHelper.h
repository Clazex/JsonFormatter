#pragma once
#ifndef _JSONHELPER
#define _JSONHELPER 1

#include <string>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson\rapidjson.h>
#include <rapidjson\document.h>
#include <rapidjson\prettywriter.h>

using std::string;
typedef rapidjson::Document doc;
typedef rapidjson::Document::AllocatorType docAlc;

class jsonHelper {
	public:
	static doc initDoc () {
		doc doc;
		doc.SetObject ();
		return doc;
	}

	static doc parse (string &json) {
		doc doc;
		doc.Parse (json);
		return doc;
	}

	static string stringify (doc &doc) {
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer (buffer);
		doc.Accept (writer);
		return buffer.GetString ();
	}
};

#endif

