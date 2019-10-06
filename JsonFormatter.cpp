#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <Windows.h>

#include <jsonHelper.h>
#include <fstreamHelper.h>

using std::cin;

#define ERR_SLEEPING_TIME (750)

int main (int argc, char **argv) {
	if (argc > 1) {
		bool state = true;
		file_buffer file (argv[1]);
		if (!state) {
			printf ("\nAn Error Has Occured When Reading The File!\n\n");
			system ("pause");
		}

		doc doc;
		doc.Parse (file.getBuffer (), file.getSize ());
		file.~file_buffer ();
		if (doc.HasParseError ()) {
			printf ("\nAn Error Has Occured When Parsing The JSON!\n\n");
			system ("pause");
		}

		ofstream fout;
		if (!fstreamHelper::topen (fout, argv[1], ios_base::trunc | ios_base::out)) {
			printf ("\nAn Error Has Occured When Writing The File!\n\n");
			system ("pause");
		}

		fout << jsonHelper::stringify (doc);

		fout.clear ();
		fout.close ();
		return 0;
	}

	while (true) {
		printf ("%s > ", argv[0]);
		char path[_MAX_PATH];
		cin >> path;

		if (path[1] != ':') {
			printf ("Exiting...\n", argv[0]);
			break;
		}

		bool state = true;
		file_buffer file (path, state);
		if (!state) {
			printf ("\nAn Error Has Occured When Reading The File!\n\n");
			Sleep (ERR_SLEEPING_TIME);
			continue;
		}

		doc doc;
		doc.Parse (file.getBuffer (), file.getSize ());
		if (doc.HasParseError ()) {
			printf ("\nAn Error Has Occured When Parsing The JSON!\n\n");
			Sleep (ERR_SLEEPING_TIME);
			continue;
		}

		ofstream fout;
		if (!fstreamHelper::topen (fout, path, ios_base::trunc | ios_base::out)) {
			printf ("\nAn Error Has Occured When Writing The File!\n\n");
			Sleep (ERR_SLEEPING_TIME);
			continue;
		}


		fout << jsonHelper::stringify (doc);

		fout.clear ();
		fout.close ();

		printf ("Successfully Formatted\n\n");
	}

	return 0;
}
