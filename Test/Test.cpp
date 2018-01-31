#include <iostream>

#define N (1024)
int map[N][N] = { 0 };
/**
* test that whether point 1 and point 2 is connected without corner.
*/
bool ZeroCornerLink(int array[][N], int x1, int y1, int x2, int y2)
{
	// p1 and p2 can't connected without corner.
	if (x1 != x2 && y1 != y2)
		return false;

	int offsetX = (x2 > x1) ? 1 : ((x2 < x1 ? -1 : 0));
	int offsetY = (y2 > y1) ? 1 : ((y2 < y1 ? -1 : 0));

	for (int y = y1 + offsetY, x = x1 + offsetX; x != x2 || y != y2;
		x += offsetX, y += offsetY)
	{
		if (array[x][y] != 0)
			return false;
	}
	return true;
}

/**
* test that whether point 1 and point 2 is connected with only one corner.
*/
bool OneCornerLink(int arry[][N], int x1, int y1, int x2, int y2)
{
	// p1 and p2 can't connected without corner.
	if (x1 == x2 || y1 == y2)
		return false;

	int offsetX = (x2 > x1) ? 1 : ((x2 < x1 ? -1 : 0));
	int offsetY = (y2 > y1) ? 1 : ((y2 < y1 ? -1 : 0));

	// scan from X offset at first.
	bool direction = true;  // true to indicate to scan from X first.   
	for (int i = 0; i < 2; i++)
	{
		int x = x1, y = y1;
		direction = (i == 0) ? true : false;
		while (x != x2 || y != y2)
		{
			if (arry[x][y] != 0)
				break; // we have meet a block.
			if (direction && x == x2)
				direction = false; // change direction
			if (!direction && y == y2)
				direction = true;  // change direction

			if (direction)
				x += offsetX;
			else
				y += offsetY;
		}
		if (x == x2 && y == y2)
			return true; // it is connected.
	}
	return false;
}
int main(int argc, char **argv)
{
	int mapRows, mapCols, nQueries;
	while (scanf("%d%d", &mapRows, &mapCols) && mapRows)
	{
		for (int i = 1; i <= mapRows; i++)
		{
			for (int j = 1; j <= mapCols; j++)
				scanf("%d", &map[i][j]);
		}

		scanf("%d", &nQueries);
		while (nQueries--)
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

			if (map[x1][y1] != map[x2][y2] || map[x1][y1] == 0 || x1 == x2&&y1 == y2)
			{
				printf("NO\n");
				continue;
			}

			if (ZeroCornerLink(map, x1, y1, x2, y2))
			{
				printf("Yes\n");
				continue;
			}
			else // corner link.
			{
				bool bConnected = false;
				// scan from up-down
				for (int x = x1 + 1, y = y1; !bConnected && x <= mapRows; ++x)
				{
					if (map[x][y] != 0) // block this direction
						break;
					if (OneCornerLink(map, x, y, x2, y2))
						bConnected = true;
				}
					
				// scan from down-up
				for (int x = x1 - 1, y = y1; !bConnected && x > 0; --x)
				{
					if (map[x][y] != 0) // block this direction
						break;
					if (OneCornerLink(map, x, y, x2, y2))
						bConnected = true;
				}
					
				// scan from left-right
				for (int x = x1, y = y1 + 1; !bConnected && y <= mapCols; ++y)
				{
					if (map[x][y] != 0) // block this direction
						break;
					if (OneCornerLink(map, x, y, x2, y2))
						bConnected = true;
				}
					
				// scan from right-left
				for (int x = x1, y = y1 - 1; !bConnected && y > 0; --y)
				{
					if (map[x][y] != 0) // block this direction
						break;
					if (OneCornerLink(map, x, y, x2, y2))
						bConnected = true;
				}
				if (bConnected)
					printf("Yes\n");
				else
					printf("No\n");
			}		
		}
	}
    return 0;
}