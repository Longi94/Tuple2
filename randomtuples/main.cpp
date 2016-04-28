#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    FILE* fp = fopen("input_int.dat", "wt");
	int db, n, from, to;

    srand(time(0));

	cout << "Number of tuples: ";
	cin >> n;
	cout << "Range: ";
	scanf("%d-%d", &from, &to);

	if (from > to)
	{
		int temp = to;
		to = from;
		from = temp;
	}

    for (int i = 0; i < n; i++)
    {
        switch (db = rand() % 4)
        {
            case 0:
                fprintf(fp, "%d:{}\n", db);
                break;
			case 1:
				fprintf(fp, "%d:{%d}\n", db, (rand() % (to - from)) + from);
				break;
			case 2:
				fprintf(fp, "%d:{%d,%d}\n", db, (rand() % (to - from)) + from, (rand() % (to - from)) + from);
				break;
			case 3:
				fprintf(fp, "%d:{%d,%d,%d}\n", db, (rand() % (to - from)) + from, (rand() % (to - from)) + from, (rand() % (to - from)) + from);
				break;
        }
    }
    return 0;
}
