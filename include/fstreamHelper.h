#pragma once
#ifndef _FSTREAMHELPER
#define _FSTREAMHELPER 1

#include <fstream>
#include <iosfwd>

using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios_base;

class fstreamHelper {
	public:
	fstreamHelper () {}

	~fstreamHelper () {
		this->close ();
	}

	ifstream &rtrv_ifstm () {
		return fin;
	}

	ofstream &rtrv_ofstm () {
		return fout;
	}

	void clear () {
		fin.clear ();
		fout.clear ();
	}

	void close () {
		this->clear ();
		fin.close ();
		fout.close ();
	}

	void open (const char *_Filename, ios_base::openmode _ModeIn, ios_base::openmode _ModeOut) {
		this->clear ();
		fin.open (_Filename, _ModeIn);
		fout.open (_Filename, _ModeOut);
	}

	bool is_open () const {
		return fin.is_open () && fout.is_open ();
	}

	bool good () const {
		return fin.good () && fout.good ();
	}

	inline static bool topen (ifstream &stm, const char *_Filename, ios_base::openmode _Mode = ios_base::in) {
		stm.open (_Filename, _Mode);
		return stm.is_open ();
	}

	inline static bool topen (ofstream &stm, const char *_Filename, ios_base::openmode _Mode = ios_base::out) {
		stm.open (_Filename, _Mode);
		return stm.is_open ();
	}

	inline static bool topen (fstream &stm, const char *_Filename, ios_base::openmode _Mode = ios_base::in | ios_base::out) {
		stm.open (_Filename, _Mode);
		return stm.is_open ();
	}

	protected:
	ifstream fin;
	ofstream fout;
};

class file_buffer {
	public:
	file_buffer (const char *_Filename) {
		ifstream file (_Filename, ios_base::binary);
		if (!file.is_open ()) {
			this->~file_buffer ();
			return;
		}
		std::filebuf *ptrbuf = file.rdbuf ();
		size = ptrbuf->pubseekoff (0, std::ios::end, std::ios::in);
		if (size <= 0) {
			this->~file_buffer ();
			return;
		}
		ptrbuf->pubseekpos (0, std::ios::in);
		buffer = new char[size];
		ptrbuf->sgetn (buffer, size);
		file.clear ();
		file.close ();
	}

	file_buffer (const char *_Filename, bool &state) {
		ifstream file (_Filename, ios_base::binary);
		if (!file.is_open ()) {
			state = false;
			this->~file_buffer ();
			return;
		}
		std::filebuf *ptrbuf = file.rdbuf ();
		size = ptrbuf->pubseekoff (0, std::ios::end, std::ios::in);
		if (size <= 0) {
			state = false;
			this->~file_buffer ();
			return;
		}
		ptrbuf->pubseekpos (0, std::ios::in);
		buffer = new char[size];
		ptrbuf->sgetn (buffer, size);
		file.clear ();
		file.close ();
		state = true;
	}

	~file_buffer () {
		delete[] buffer;
	}

	char *&getBuffer () {
		return buffer;
	}

	int &getSize () {
		return size;
	}

	private:
	char *buffer;
	int size;
};

#endif

