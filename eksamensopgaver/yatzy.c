#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
	Ones,
	Twos,
	Threes,
	Fours,
	Fives,
	Sixes,
	OnePair,
	TwoPair,
	ThreeOfAKind,
	FourOfAKind,
	SmallStraight,
	LargeStraight,
	FullHouse,
	Chance,
	Yatzy
} throwType;


const char *throwNames[]={
	"Ones",
	"Twos",
	"Threes",
	"Fours",
	"Fives",
	"Sixes",
	"One Pair",
	"Two Pair",
	"Three Of A Kind",
	"Four Of A Kind",
	"Small Straight",
	"Large Straight",
	"Full House",
	"Chance",
	"Yatzy"
};

int *playYatzy (int);
void printThrow(throwType throw, int *die, int result, int size);
void printYatzy(int[]);
int *throwDie(int);
int process (throwType type, int *die, int size);
int count (int n, int *die, int size);
int onePair (int *die, int size);
int twoPair (int *die, int size);
int threeOfAKind (int *die, int size);
int fourOfAKind (int *die, int size);
int smallStraight (int *die, int size);
int largeStraight (int *die, int size);
int fullHouse (int *die, int size);
int chance (int *die);
int compare(const void *a, const void *b);
int yatzy (int *die, int size);


int main (void){
	srand(time(NULL));

	int dieAmount = 0;
	printf("Amount of Dice : ");

	scanf(" %d", &dieAmount);
	printf("\nPrinting dice:\n");

	int *results = playYatzy(dieAmount);
	printYatzy(results);

	return 0;
}

int *playYatzy(int dieAmount){
	int *result = (int *)malloc(dieAmount * sizeof(int));
	int games = 15;
	for (int i = 0; i < 15; i++)
	{
		int *die = throwDie(dieAmount);
		result[i] = process(i, die, dieAmount);
		printThrow(i, die, result[i], dieAmount);
	}
	return result;
}

void printThrow(throwType throw, int *die, int result, int size){
	for (int i = 0; i < size; i++)
	{
		printf(" %d",die[i]);
	}
	printf(" -- %2d", result);
	printf(" : %s\n", throwNames[throw]);
}

void printYatzy(int result[]){
	int sum = 0;
	printf("\nScore Board:\n");
	for (int i = 0; i < 15; i++)
	{
		sum+= result[i];
		printf("%s : %2d\n", throwNames[i], result[i]);
		if (i == 5){
			int bonus = 0;
			if (sum >= 63)
			{
				bonus = 50;
			}
			sum += bonus;
			printf("Bonus : %2d\n\n", bonus);
		} else if (i == 14)
		{
			printf("Total : %3d\n", sum);
		}
	}
	
}

int *throwDie (int dieAmount){
	int *die = (int *)malloc(dieAmount * sizeof(int));
	for (int i = 0; i < dieAmount; i++)
	{
		die[i] = rand() % 6 + 1;
	}
	return die;
}

int process (throwType type, int *die, int size){
	int result = 0;

	switch (type)
	{
	case Ones:
		result = 1 * count(1, die, size);
		break;
	case Twos:
		result = 2 * count(2, die, size);
		break;
	case Threes:
		result = 3 * count(3, die, size);
		break;
	case Fours:
		result = 4 * count(4, die, size);
		break;
	case Fives:
		result = 5 * count(5, die, size);
		break;
	case Sixes:
		result = 6 * count(6, die, size);
		break;
	case OnePair:
		result = 2 * onePair(die, size);
		break;
	case TwoPair:
		result = twoPair(die, size);
		break;
	case ThreeOfAKind:
		result = 3 * threeOfAKind(die, size);
		break;
	case FourOfAKind:
		result = 4 * fourOfAKind(die, size);
		break;
	case SmallStraight:
		result = 15 * smallStraight(die, size);
		break;
	case LargeStraight:
		result = 20 * largeStraight(die, size);
		break;
	case FullHouse:
		result = fullHouse(die, size);
		break;
	case Chance:
		result = chance(die);
		break;
	case Yatzy:
		result = 5 * yatzy(die, size);
		break;
	default:
		break;
	}
	return result;
}

int count (int n, int *die, int size){
	int result = 0;
	for (int i = 0; i < size; i++)
	{
		if (die[i] == n)
		{
			result++;
			if (result == 5)
			{
				break;
			}
		}
	}
	return result;
}

int onePair (int *die, int size){
	for (int i = 6; i > 0; i--)
	{
		if(count(i, die, size) >= 2){
			return i;
		}
	}
	return 0;
}

int twoPair (int *die, int size){
	for (int i = 6; i > 0; i--)
	{
		int amount = count(i, die, size); 
		if(amount >= 4){
			return 4 * i;
			break;
		} else if (amount >= 2){
			for (int j = i - 1; j > 0; j--)
			{
				if(count(j,die, size) >= 2){
					return 2 * i + 2 * j;
				}
			}
		}
	}
	return 0;
}

int threeOfAKind (int *die, int size){
	int result = 0;
	for (int i = 6; i > 0; i--)
	{
		if(count(i, die, size) >= 3){
			result = i;
		}
	}
	return result;
}

int fourOfAKind (int *die, int size){
	for (int i = 6; i > 0; i--)
	{
		if(count(i, die, size) >= 4){
			return i;
		}
	}
	return 0;
}

int smallStraight (int *die, int size){
	return (count(1,die, size) > 0 &&
			count(2,die, size) > 0 &&
			count(3,die, size) > 0 &&
			count(4,die, size) > 0 &&
			count(5,die, size) > 0);
}

int largeStraight (int *die, int size){
	return (count(2,die, size) > 0 &&
			count(3,die, size) > 0 && 
			count(4,die, size) > 0 &&
			count(5,die, size) > 0 && 
			count(6,die, size) > 0);
}

int fullHouse (int *die, int size){
	int temp = threeOfAKind(die, size);
	if (temp != 0)
	{
		for (int i = 6; i > 0; i--)
		{
			if (i != temp && count(i, die, size) >= 2){
				return temp * 3 + i * 2;
			} else if (count(i, die, size) >= 5) {
				return 5 * i;
			}
		}	
	}
	return 0;
}

int chance (int *die){
	int size = sizeof(die) / sizeof(die[0]);
	qsort(die, size, sizeof(int), compare);
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		sum += die[i];
	}
	return sum;
}

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a); //Changed a and b to make it decending order
}

int yatzy (int *die, int size){
	for (int i = 6; i > 0; i--)
	{
		if (count(i, die, size) >= 5)
		{
			return i;
		}
	}
	return 0;
}