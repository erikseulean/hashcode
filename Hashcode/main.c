#include <stdio.h>
#include <stdlib.h>

int rows, columns, nrDrones, nrTurns, droneCapacity, nrProducts, nrWarehouse;
int nrOrders;
int productWeight[10000];

typedef struct
{
    int x,y;
    int ProductCount[10000];
} WAREHOUSE;

typedef struct
{
    int x,y;
    int NrOfItems;
    int *ItemTypes;
} ORDER;

#define LOAD 1
#define DELIVER 2

typedef struct
{
    union
    {
        int warehouse;
        int customer;
    };

    int action; // 1 load, 2 deliver
    int numberOfProducts;
    int typeOfProduct;
} COMMAND;

//i indice drona, j indicele comenzii
COMMAND commands[1000][50];

WAREHOUSE ware[10000];
ORDER orders[10000];
int commandIndex[1000];

int main()
{
    int i = 0;
    int j = 0;
    int k = 0;
    int itemCount = 0;
    int auxcounter = 0;
    int droneIndex = 0;
    int item;
    int nrTotalCommands = 0;
    int nrProd = 0;
    FILE * pFile;
    FILE * pFile2;
    pFile = fopen ("d:\\projects\\hashcode\\Hashcode\\busy_day.in","rb");
    if (pFile == NULL)
    {
        fclose (pFile);
        return -1;
    }

    pFile2 = fopen ("out.out","w");
    if (pFile2 == NULL)
    {
        fclose (pFile2);
        return -1;
    }



    fscanf(pFile, "%d %d %d %d %d", &rows, &columns, &nrDrones, &nrTurns, &droneCapacity);
    printf("rows: %d", rows);
    fscanf(pFile, "%d", &nrProducts);
    printf("nrProducts: %d", nrProducts);

    for (i = 0; i < nrProducts; i++)
    {
        fscanf(pFile, "%d", &productWeight[i]);
    }

    fscanf(pFile, "%d", &nrWarehouse);

    for (i = 0; i < nrWarehouse; i++)
    {
       fscanf(pFile, "%d %d",  &ware[i].x, &ware[i].y);
       for (j = 0; j < nrProducts; j++)
       {
           fscanf(pFile, "%d", &ware[i].ProductCount[j]);
       }
    }

    fscanf(pFile, "%d", &nrOrders);
    printf("nrOrders: %d", nrOrders);

    for (i = 0; i < nrOrders; i++)
    {
        fscanf(pFile, "%d %d",  &orders[i].x, &orders[i].y);
        fscanf(pFile, "%d",  &orders[i].NrOfItems);
        orders[i].ItemTypes = malloc (orders[i].NrOfItems * sizeof(int));
        if (!orders[i].ItemTypes)
        {
            return -2;
        }
        for (j = 0; j < orders[i].NrOfItems; j++)
        {
            fscanf(pFile, "%d",  &orders[i].ItemTypes[j]);
        }
    }

    printf("\n%d", orders[i-1].ItemTypes[j - 2]);


    for (i = 0; i < nrOrders; i++)
    {
        for (j = 0; j < orders[i].NrOfItems; j++)
        {
            item = orders[i].ItemTypes[j];

            for (k = 0; k < nrWarehouse; k++)
            {
                if (ware[k].ProductCount[item] > 0)
                {
                    ware[k].ProductCount[item]--;
                    commands[droneIndex][commandIndex[droneIndex]].action = LOAD;
                    commands[droneIndex][commandIndex[droneIndex]].numberOfProducts = 1;
                    commands[droneIndex][commandIndex[droneIndex]].typeOfProduct = item;
                    commands[droneIndex][commandIndex[droneIndex]].warehouse = k;
                    commandIndex[droneIndex]++;
                    commands[droneIndex][commandIndex[droneIndex]].action = DELIVER;
                    commands[droneIndex][commandIndex[droneIndex]].numberOfProducts = 1;
                    commands[droneIndex][commandIndex[droneIndex]].typeOfProduct = item;
                    commands[droneIndex][commandIndex[droneIndex]].customer = i;
                    commandIndex[droneIndex]++;
                    droneIndex = (droneIndex + 1) % nrDrones;
                    nrTotalCommands++;
                    nrTotalCommands++;
                    break;
                }
            }
        }
    }

    fprintf(pFile2, "%d\n", nrTotalCommands);

    for (i = 0; i < nrDrones; i++)
    {
        for (j = 0; j < commandIndex[i]; j++)
        {
            printf("drone: %d action %d, nrProd %d, type: %d warehouse/customer %d\n",
            i,
            commands[i][j].action,
            commands[i][j].numberOfProducts,
            commands[i][j].typeOfProduct,
            commands[i][j].warehouse
            );
            fprintf(pFile2, "%d %c %d %d %d\n", i, commands[i][j].action == 1 ? 'L' : 'D', commands[i][j].warehouse, commands[i][j].typeOfProduct, commands[i][j].numberOfProducts);
        }
    }
    printf("%d\n", auxcounter);

    return 0;
}

