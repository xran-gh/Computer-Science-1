// Ran Xu
// 9/7/2018
// COP3502C MW 6:00
// Shipping

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// library

typedef struct ship {

	int Id, NumContent;
	char **Content;

}ship;
// structure

int main(void);
int removeShip(ship **Ships, int NumShip);
ship **addShip(ship **Ships, int *NumShipPtr, int *ShipCapacityPtr, int *Id_countPtr);
void searchId(ship **Ships, int Count);
void searchContent(ship **Ships, int Count);
void freeShip(ship **Ships, int Count);
// declaration

int main(void) {
	
	int Input, NumShip = 0, ShipCapacity = 0, Id_count = 1;
	int *NumShipPtr, *ShipCapacityPtr, *Id_countPtr;
	ship **Ships;

	NumShipPtr = NULL;
	ShipCapacityPtr = NULL;
	Id_countPtr = NULL;
	Ships = NULL;
	NumShipPtr = &NumShip;
	ShipCapacityPtr = &ShipCapacity;
	Id_countPtr = &Id_count;
	scanf("%d", &Input);

	while (Input != -1) {

		if (Input == 0) {

			NumShip = removeShip(Ships, NumShip);

		}// if

		else if (Input == 1) {

			Ships = addShip(Ships, NumShipPtr, ShipCapacityPtr, Id_countPtr);

		}// else if

		else if (Input == 2) {

			searchId(Ships,NumShip);

		}// else if

		else if (Input == 3) {

			searchContent(Ships, NumShip);

		}// else if

		scanf("%d", &Input);

	}// while

	freeShip(Ships, NumShip);
	NumShipPtr = NULL;
	ShipCapacityPtr = NULL;
	Id_countPtr = NULL;

	return EXIT_SUCCESS;

}// main()

int removeShip(ship **Ships, int NumShip) {

	int RemoveId;

	scanf("%d", &RemoveId);
	
	if (RemoveId == Ships[NumShip-1]->Id) {

		for (int i = 0; i < Ships[NumShip-1]->NumContent; i++) {

			free(Ships[NumShip - 1]->Content[i]);
			Ships[NumShip - 1]->Content[i] = NULL;

		}// for

		free(Ships[NumShip - 1]->Content);
		Ships[NumShip - 1]->Content = NULL;
		free(Ships[NumShip - 1]);
		Ships[NumShip - 1] = NULL;

	}// if

	else {

		int Id_position = 0;

		for (int i = 0; i < Ships[NumShip - 2]; i++) {

			if (RemoveId == Ships[i]->Id) {

				Id_position = i;
				
				break;

			}// if

		}// for

		ship * Temp;

		Temp = Ships[Id_position];
		Ships[Id_position] = Ships[NumShip - 1];
		Ships[NumShip - 1] = Temp;

		for (int i = 0; i < Ships[NumShip - 1]->NumContent; i++) {

			free(Ships[NumShip - 1]->Content[i]);
			Ships[NumShip - 1]->Content[i] = NULL;

		}// for

		free(Ships[NumShip - 1]->Content);
		Ships[NumShip - 1]->Content = NULL;
		free(Ships[NumShip - 1]);
		Ships[NumShip - 1] = NULL;
		Temp = NULL;

	}// else

	return NumShip - 1;

}// removeShip()

ship **addShip(ship **Ships, int *NumShipPtr, int *ShipCapacityPtr, int *Id_countPtr) {

	if (*NumShipPtr == *ShipCapacityPtr) {

		ship ** NewArray = (ship **)calloc(*ShipCapacityPtr * 2 + 1, sizeof(ship *));

		for (int i = 0; i < *NumShipPtr; i++) {

			NewArray[i] = Ships[i];

		}// for

		free(Ships);
		Ships = NewArray;
		NewArray = NULL;
		*ShipCapacityPtr = *ShipCapacityPtr * 2 + 1;

	}// if

	int ContainersNum, SpaceNum;
	ship *ShipPtr;

	Ships[*NumShipPtr] = (ship *)calloc(1, sizeof(ship));
	ShipPtr = Ships[*NumShipPtr];
	ShipPtr->Id = *Id_countPtr;
	scanf("%d", &ContainersNum);
	ShipPtr->NumContent = ContainersNum;
	ShipPtr->Content = (char **)calloc(ContainersNum, sizeof(char *));

	for (int i = 0; i < ContainersNum; i++) {

		scanf("%d", &SpaceNum);
		ShipPtr->Content[i] = (char *)calloc(SpaceNum + 1, sizeof(char));
		scanf("%s", ShipPtr->Content[i]);

	}// for

	ShipPtr = NULL;
	*NumShipPtr = *NumShipPtr + 1;
	*Id_countPtr = *Id_countPtr + 1;

	return Ships;

}// addShip()

void searchId(ship **Ships, int Count) {

	int Position;

	scanf("%d", &Position);

	if ((Position > Count) || (Position <= 0)) {

		printf("-1\n");

	}// if

	else {

		printf("%d\n", Ships[Position-1]->Id);

	}// else

}// searchId()

void searchContent(ship **Ships, int Count) {

	int Position, ContainerNum;

	scanf("%d %d", &Position, &ContainerNum);

	if ((Position > Count) || (Position <= 0)) {

		printf("-1\n");

	}// if

	else {

		if ((ContainerNum > Ships[Position-1]->NumContent) || (ContainerNum <= 0)) {

			printf("-1\n");

		}// if

		else {

			printf("%s\n", Ships[Position-1]->Content[ContainerNum-1]);

		}// else

	}// else

}// searchContent()

void freeShip(ship **Ships, int Count) {

	for (int i = 0; i < Count; i++) {

		for (int j = 0; j < Ships[i]->NumContent; j++) {

			free(Ships[i]->Content[j]);
			Ships[i]->Content[j] = NULL;

		}// for

		free(Ships[i]->Content);
		Ships[i]->Content = NULL;
		free(Ships[i]);
		Ships[i] = NULL;

	}// for

	free(Ships);
	Ships = NULL;

}// freeShip()