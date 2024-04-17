#include <stdio.h>

#define MAX_ROOMS 100

void dfs_recursive(int passages[MAX_ROOMS][MAX_ROOMS], int visited[MAX_ROOMS], int roomsAmount, int currentRoom, int exitRoom, int *pathFound)
{
    if (*pathFound == 1 || visited[currentRoom])
    {
        return;
    }

    visited[currentRoom] = 1;

    if (currentRoom == exitRoom)
    {
        *pathFound = 1;
        return;
    }

    for (int i = 0; i < roomsAmount; i++)
    {
        if (passages[currentRoom][i])
        {
            dfs_recursive(passages, visited, roomsAmount, i, exitRoom, pathFound);
        }
    }
}

int main()
{
    int roomsAmount, passagesAmount;
    scanf("%d %d", &roomsAmount, &passagesAmount);

    int passages[MAX_ROOMS][MAX_ROOMS] = {0};
    int visited[MAX_ROOMS] = {0};

    for (int i = 0; i < passagesAmount; i++)
    {
        int originRoom, destinationRoom;
        scanf("%d %d", &originRoom, &destinationRoom);

        passages[originRoom][destinationRoom] = 1; // todas iniciam possuindo passagem
    }

    int exitRoom = roomsAmount - 1;
    int pathFound = 0;

    dfs_recursive(passages, visited, roomsAmount, 0, exitRoom, &pathFound);

    if (visited[exitRoom])
    {
        printf("EXISTE CAMINHO\n");
    }
    else
    {
        printf("NAO EXISTE CAMINHO\n");
    }

    int allRoomsHavePassage = 1;
    for (int i = 0; i < roomsAmount; i++)
    {
        if (!visited[i])
        {
            allRoomsHavePassage = 0;
            break;
        }
    }

    if (allRoomsHavePassage)
    {
        printf("EH POSSIVEL PASSAR POR TODAS AS SALAS\n");
    }
    else
    {
        printf("NAO EH POSSIVEL PASSAR POR TODAS AS SALAS\n");
    }

    return 0;
}
