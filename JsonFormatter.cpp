#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <Windows.h>

#include <jsonHelper.h>
#include <fstreamHelper.h>

using std::cin;
using std::cout;
using std::endl;

#define ESC_SLEEPING_TIME (100)
#define ERR_SLEEPING_TIME (750)

int main (int argc, char **argv) {
	std::ios::sync_with_stdio (false);

	if (argc > 1) {
		cout << argv[0] << " > " << argv[1];

		bool state = true;
		file_buffer file (argv[1]);
		if (!state) {
			cout << "\nAn Error Has Occured When Reading The File!\n" << endl;
			system ("pause");
		}

		doc doc;
		doc.Parse (file.getBuffer (), file.getSize ());
		if (doc.HasParseError ()) {
			cout << "\nAn Error Has Occured When Parsing The JSON!\n" << endl;
			system ("pause");
		}

		ofstream fout;
		if (!fstreamHelper::topen (fout, argv[1], ios_base::trunc | ios_base::out)) {
			cout << "\nAn Error Has Occured When Writing The File!\n" << endl;
			system ("pause");
		}

		fout << jsonHelper::stringify (doc);

		fout.clear ();
		fout.close ();

		Sleep (ESC_SLEEPING_TIME);

		return 0;
	}

	while (true) {
		cout << argv[0] << " > ";
		char path[_MAX_PATH];
		cin >> path;

		if (path[0] == 'e' && path[1] == 'x' && path[2] == 'i' && path[3] == 't') {
			cout << "Exiting..." << endl;
			Sleep (ESC_SLEEPING_TIME);
			break;
		}

		bool state = true;
		file_buffer file (path, state);
		if (!state) {
			cout << "\nAn Error Has Occured When Reading The File!\n" << endl;
			Sleep (ERR_SLEEPING_TIME);
			continue;
		}

		doc doc;
		doc.Parse (file.getBuffer (), file.getSize ());
		if (doc.HasParseError ()) {
			cout << "\nAn Error Has Occured When Parsing The JSON!\n" << endl;
			Sleep (ERR_SLEEPING_TIME);
			continue;
		}

		ofstream fout;
		if (!fstreamHelper::topen (fout, path, ios_base::trunc | ios_base::out)) {
			cout << "\nAn Error Has Occured When Writing The File!\n" << endl;
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
