#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "HashSet.h"


#define HASH_SIZE 100

size_t HashFunction(size_t _data) {

        return _data;
}

void Print(size_t _item) {

  printf("%lu,",_item);
}

int main(){

/****************************************
          VARIABLES DECLARATION
****************************************/
        int option;
        HashSet* hash=NULL;
        size_t capacity;
        float loadFactor;
        size_t data;
        int result;
        size_t maxCollisionsEver;
        float averageCollisions;


/****************************************/

        while(1) {

                printf("Please select the function you wish to use: \n");
                printf("\n");
                printf("1: Create Hash Set  \n");
                printf("2: Hash Destroy  \n");
                printf("3: Hash Insert  \n");
                printf("4: Hash Remove  \n");
                printf("5: Hash Find/Contains \n");
                printf("6: Hash Get Size \n");
                printf("7: Hash Get Statistics \n");
                printf("8: Hash For Each Function \n");

                printf("Any another number - stop \n");
                scanf("%d", &option);
				printf("\n");
				
                switch(option) {

                case 1:

                        printf("Please enter the capacity for the hash Set:");
                        scanf("%lu",&capacity);
                        printf("Please enter the load factor for the hash in precentages:");
                        scanf("%f",&loadFactor);

                        hash=HashSetCreate(capacity,loadFactor, HashFunction);
                        printf("******************* \n");
                        if(hash== NULL)
                        {

                                printf("Could not create hash Set \n");

                        } else {

                                printf("Hash created succesfully \n");
                        }

                        printf("******************* \n");

                        break;

                case 2:
                        printf("******************* \n");
                        if(hash == NULL)
                        {

                                printf("Hash not initialized \n");
                        }
                        HashSetDestroy(hash);

                        hash=NULL;

                        if(hash==NULL)
                        {
                                printf("Hash destroyed successfully \n");
                        }
                        printf("******************* \n");

                        break;

                case 3:
                        printf("Please enter the data you wish to insert:");
                        scanf("%lu",&data);

                        result=HashSetInsert(hash, data);
                        printf("******************* \n");

                        if(result==ERR_OVERFLOW)
                        {

                                printf("Cannot insert anymore data into the hash \n");
                        } else if(result == ERR_EXIST)
                        {

                                printf("Data already exists in the hash Set \n");

                        } else if(result == ERR_NOT_INITIALIZED)
                        {

                                printf("Hash not initialized \n");
                        } else {

                                printf("Data inserted successfully \n");
                        }
                        printf("******************* \n");
                        break;

                case 4:
                        printf("Please enter the data you wish to remove:");
                        scanf("%lu",&data);

                        result=HashSetRemove(hash, data);
                        printf("******************* \n");


                        if(result==ERR_NOT_INITIALIZED)
                        {

                                printf("Hash not initialized \n");
                        } else if(result == ERR_NOT_FOUND) {

                                printf("Could not find data to remove \n");
                        } else {

                                printf("%lu removed successfully \n",data);
                        }

                        printf("******************* \n");
                        break;

                case 5:

                        printf("Please enter the data you wish to find:");
                        scanf("%lu",&data);


                        result = HashSetContains(hash,data);
                        printf("******************* \n");


                        if(result == -2)
                        {

                                printf("Hash not initialized \n");
                        } else if (result == 1)
                        {
                                printf("Data found in the hash \n");
                        } else {

                                printf("Could not find data \n");
                        }
                        printf("******************* \n");

                        break;
                case 6:

                        printf("******************* \n");
                        result=(int)HashSetSize(hash);
                        if(result == 0)
                        {

                                printf("Hash not initialized \n");
                        } else {
                                printf("There are currently %lu value in the hash Set\n",HashSetSize(hash));

                        }
                        printf("******************* \n");

                        break;
                case 7:

                        result=HashSetStatistics(hash,&maxCollisionsEver, &averageCollisions);
                        printf("******************* \n");
                        if(result == ERR_NOT_INITIALIZED) {

                                printf("Hash not initialized \n");

                        } else {
                                printf("The max number of collisions is %lu \n",maxCollisionsEver);
                                printf("The average number of collisions %f \n",averageCollisions);
                        }
                        printf("******************* \n");


                        break;
                case 8:
                        HashSetForEach(hash, Print);

                        break;
                case 9:


                        break;

                }
        }

        return 0;
}
