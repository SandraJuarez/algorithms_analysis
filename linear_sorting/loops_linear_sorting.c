#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// #### COUNTING SORT #####
// 
void counting_sort(int *array, int k_max,int lenght,int *sorted_array) {
    int *count = malloc((k_max+1) * sizeof(int));

    // we fill our vector with null elements
    for (int i = 0; i < k_max+1; i++) {
        count[i] = 0;
    }

    // Searching in the whole input array we count repeated elements and save into count[]
    for (int j=0; j<lenght ; j++) {
        count[array[j]]=count[array[j]]+1;
    }

    //we compute the cummulative sum of our count array
    for (int i =1; i<k_max+1; i++) {
        count[i]=count[i]+count[i-1];
    }

    for (int j=lenght-1; j>=0; j--) {
        //we have have to substract 1 because having a 1 in array count means that this is our first element
        count[array[j]]=count[array[j]]-1;
        sorted_array[count[array[j]]-1]=array[j];   
    }

    }

// ## RADIX SORT (queue version)
void enqueue(int *array,int lenght,int digitos,int *array_temp,int **queue){
        for (int j=0; j<10 ;j++){   //we search  in the digits from 0 to 0
            int r=0;
            for (int i =0; i<lenght;i++){   //in array_temp we'll have the digit corresponding to the units, tens, etc
                if (array_temp[i]==j){
                    queue[j][r]=array[i]; // and we'll store in the the corresponding row of queue
                    r++;
                }
            }
        }
    }

void dequeue(int lenght,int **queue,int *array){
    int indice_sorted_array=0;
    for (int j=0; j<10 ;j++){

        int i=0;
        // we iterate until we find the null element in queue
        while (queue[j][i]!=0){
                //we save the element into a new sorted array
                array[indice_sorted_array]=queue[j][i];
                indice_sorted_array++;
           
            i++;
        }
        }

    }
    
void radix_sort(int *array,int k_max,int lenght,int *sorted_array){
    //we count the digits of our biggest element
    int digitos=0;
    while(k_max!=0){
        k_max=k_max/10;
        digitos++;
    }

    for (int m=0;m<digitos;m++){

        int *array_temp=malloc(sizeof(int)*lenght);
        // with this we extract the units digit, the tens, etc. Sounds weird but making a few examples we can see it is correct
        for (int j=0; j<lenght ;j++){
            array_temp[j]=(array[j] % (int)pow(10, m + 1) -array[j] % (int)pow(10, m))/((int)pow(10, m));
            //array_temp[j]=array[j] % (int)pow(10, m + 1);
            printf("%d ",array_temp[j]);
        }
        printf("\n");

        //create queue matrix with size (10,length)
        int **queue=malloc(sizeof(int*)*10);
        for (int j=0; j<10 ;j++){
            queue[j]=malloc(sizeof(int)*lenght);
        }
        //fill with null elements
        for (int j=0; j<10 ;j++){
            for (int i=0; i<lenght ;i++){
                queue[j][i]=0;
            }
        }

        enqueue(array,lenght,digitos,array_temp,queue);
        dequeue(lenght,queue,array);
        }

    for (int i=0;i<lenght;i++){
        sorted_array[i]=array[i];
    }
    }


// ## BUCKKET SORT ###

//We define our hash function
int hash(int x){
    return x/3;
}

// We define a method to sort our buckets
void insertion_sort(int **array,int lenght,int indice_bucket){

    for(int i=1;i<lenght;i++){
        int key=array[indice_bucket][i];
        int j=i-1;
        while(j>=0 && array[indice_bucket][j]>key){
            array[indice_bucket][j+1]=array[indice_bucket][j];
            j=j-1;
        }
        array[indice_bucket][j+1]=key;
        }
    }

// And we insert the sorted buckets into the array A
void sortedB_to_sortedA(int **sortedB,int *sortedA,int lenght){
    int indice_sortedA=0;
    for (int i=0;i<lenght;i++){
        int lenght_each_bucket=0;
        while(sortedB[i][lenght_each_bucket]!=-1){
            lenght_each_bucket++;
        }
        insertion_sort(sortedB,lenght_each_bucket,i);

        
        
        
        for (int j=0;j<lenght_each_bucket;j++){
            sortedA[indice_sortedA]=sortedB[i][j];
            indice_sortedA++;
        }
        
    }
}

// And we call all our functions
void bucket_sort(int *array,int k_max,int lenght,int *sorted_array){
    
    //create buckets
    int k=0;
    int num_buckets=k_max/3+1;
    // we create an array of the number of buckets in the rows
    int **buckets=malloc(sizeof(int*)*num_buckets);
    // we now create lenght columns for each row
    for (int i=0;i<num_buckets;i++){
        buckets[i]=malloc(sizeof(int)*lenght);
    }

    //And we fill our array with -1 
    for (int j=0; j<num_buckets ;j++){
        for (int i=0; i<lenght ;i++){
            buckets[j][i]=-1;
        }
    }

    //We allocate our numbers in their corresponding bucket
    for (int i=0;i<lenght;i++){
        k=hash(array[i]); //this will allocate array[i] in bucket[k]
        int indice_bucket=0;
        int stop_seach=0;       //when the space is empty in the k bucket we write and this will stop the while
        while (stop_seach==0)   //we'll be in the while loop until we succesfully write our array[i]
        {   // if our bucket is empty we can write our array[i] in it
            if (buckets[k][indice_bucket]==-1){
                buckets[k][indice_bucket]=array[i];
                stop_seach=1; //since we already wrote our array[i] we can conclude the while
            }
            else{ //but if we find that the bucket isn't empty we'll go to the next index in the same bucket
                indice_bucket++; //if this else occurs we are still in the while
            } 
            
        }
    }
    
    sortedB_to_sortedA(buckets,sorted_array,num_buckets);
}







int main() {
    int array[] = {8124, 2, 18, 70, 8123, 9, 15, 300, 1, 12};
    int length = sizeof(array) / sizeof(array[0]);  // Obtener la longitud del array

    int * sorted_array = malloc(sizeof(int) * length);
    
    bucket_sort(array,8124,length,sorted_array);
    

    return 0;
    
}


    






    


