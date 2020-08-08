#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <thread>
using namespace std;
using namespace std::chrono;

constexpr char PI_1BILLION_DIGITS_FILE_PATH[] = "PI-1BILLION-DIGITS.txt";
constexpr char LAST_66_DIGITS[] = "947757350076080576622871044045130245603581915324606712030765715945";


int64_t indexOf(const std::vector<char>& pi_digits, const std::string& search)
{
	char start = search[0];
	for (uint64_t i = 0; i < pi_digits.size(); i++)
	{
		if (pi_digits[i] == start)
		{
			bool found = true;
			for (uint64_t j = 1; j < search.size(); j++)
			{
				if (pi_digits[i + j] != search[j])
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				return i;
			}
		}
	}
	return -1;
}


int main(void)
{
	ifstream ifs(PI_1BILLION_DIGITS_FILE_PATH, ios_base::in);
	vector<char> digits;

	if (ifs)
	{
		cout << "Reading 1 BILLION PI Digits into vector...\n";

		auto t1 = high_resolution_clock::now();

		//Very efficient way to read large file into vector
		ifs.seekg(0, std::ios_base::end);
		std::streampos length(ifs.tellg());
		ifs.seekg(0, std::ios_base::beg);
		digits.resize(static_cast<std::size_t>(length));
		ifs.read(&digits.front(), static_cast<std::size_t>(length));

		auto t2 = high_resolution_clock::now();


		ifs.close();

		cout << "Successfully Allocated Digits.\n"
			<< "Length: " << digits.size() << " (First '3', '.' are included)\n";

		cout << "Took " << duration_cast<seconds>(t2 - t1).count() << " seconds\n";

		cout << '\a'; //alert sound to inform whend done reading file.
	}
	else { cerr << "Cloud not open " << PI_1BILLION_DIGITS_FILE_PATH; return 1; }
	
	
	{
		//Search for digits
		std::string search;
		for(;;)
		{
			if (search.empty()) break;

			cout << "Enter digits to search for: \n";
			getline(cin, search);
			auto t1 = high_resolution_clock::now();
			int64_t index = indexOf(digits, search);
			if (index != -1)
			{
				cout << "Found match at index " << index << endl;
			}
			else
			{
				cout << "Did not found any match of \"" << search << "\"" << endl;
			}
			auto t2 = high_resolution_clock::now();
			cout << "Search Took " << duration_cast<seconds>(t2 - t1).count() << " seconds\n\n";
		} 
	}


	cout << "\nPress ENTER to exit.\n";
	cin.get();


	return 0;
}

