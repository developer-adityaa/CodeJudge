#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string
readFile (string path)
{
  ifstream file (path);
  return string ((istreambuf_iterator<char> (file)),
                 istreambuf_iterator<char> ());
}

int
main ()
{
  int total = 2;
  int passed = 0;

  for (int i = 1; i <= total; i++)
    {
#ifdef __APPLE__
      string input = "tests/input" + to_string (i) + ".txt";
      string cmd = "./solution < " + input + " > temp.txt";
#elif _WIN32
      string input = ".\\tests\\input" + to_string (i) + ".txt";
      string cmd = "cmd /c \"solution.exe < " + input + " > temp.txt\"";

#endif
      string expected = "tests/output" + to_string (i) + ".txt";

      system (cmd.c_str ());

      string out = readFile ("temp.txt");
      string exp = readFile (expected);

      if (out.find (exp) != string::npos)
        {
          cout << "\033[32mTest " << i << " PASSED\033[0m\n";
          passed++;
        }
      else
        {
          cout << "\033[31mTest " << i << " FAILED\033[0m\n";
        }
    }
  cout << "\nPassed " << passed << "/" << total << " tests\n";
}