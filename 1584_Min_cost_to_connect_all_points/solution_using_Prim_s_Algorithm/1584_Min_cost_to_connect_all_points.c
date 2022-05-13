#include <stdio.h>
#include <stdlib.h>
/*** PriorityQueue Implementation ( /w minHeap)*/
// priorityqueue function protos
// pop() extracts min element
int *pop(int **heap);
// insert() adds an element to the array
void insert(int **heap, int weight, int vrtx);
// destroyheap() frees the memory used by the heap and destroys the heap;
// -------
// Auxiliary funcitons proto.
void swap(int **a, int **b);
int father(int i);
int leftchild(int i);
int rightchild(int i);
int key(int *arr);
void heapifyup(int **heap, int child);
void heapifydown(int **heap, int parent);

// ---
int manDist(int *p1, int *p2);
int minCostConnectPoints(int **points, int pointsSize, int *pointsColSize);

// priorityqueue functions
// Creates an empty min-heap of size '*size'
// idx 0 contains the actual size of the heap ( # of elements it currently contains)
// and the max size of the heap
int **makeheap(int *size)
{
    int **newheap = calloc(*(size) + 1, sizeof(int *)); // +1 because we do not use idx 0  for our data.
    int *sizes = calloc(2, sizeof(int));
    sizes[1] = (*size); // max size of the heap
    newheap[0] = sizes;
    return newheap;
}

int *pop(int **heap)
{
    int numofels = heap[0][0];
    int *extract = heap[1];
    swap(&(heap[1]), &(heap[numofels]));
    (heap[0][0])--;
    heapifydown(heap, 1);
    return extract;
}

void insert(int **heap, int weight, int vrtx)
{
    int *size = &(heap[0][0]);
    int *maxSize = &(heap[0][1]);
    int *new = calloc(2, sizeof(int));
    new[0] = weight;
    new[1] = vrtx;
    (*size)++;

    heap[*size] = new;
    heapifyup(heap, *size);
    return;
}

void destroyheap( int **heap){
    int size = heap[0][0];
    for( int i = 0; i < size; i ++){
        if( heap[i] != NULL ){
            free( heap[i]);
        }
    }
    free(heap);
}

// Aux. Functions
void printheap(int **heap)
{

    printf("Size:%d\nMaxSize:%d\n", heap[0][0], heap[0][1]);
    for (int i = 1; i <= heap[0][1]; i++)
    {
        if (heap[i] == NULL)
        {
            printf("[NULL] ");
        }
        else if (i > heap[0][0])
        {
            printf("[grbg](%d, %d) ", heap[i][0], heap[i][1]);
        }
        else
        {
            printf("[(%d, %d)] ", heap[i][0], heap[i][1]);
        }
    }
    printf("\n");
    return;
}

void heapifydown(int **heap, int parent)
{
    int lftchild = leftchild(parent);
    int rghtchild = rightchild(parent);
    if (lftchild <= heap[0][0])
    { // child <= number of elements --> child has at least 1 child
        int smallestchild;
        if (lftchild == heap[0][0])
        { // one child
            smallestchild = lftchild;
        }
        else
        {
            smallestchild = key(heap[lftchild]) < key(heap[rghtchild]) ? lftchild : rghtchild;
        }

        // smallestchild < parent? --> swap( smallestchild with parent)
        if (key(heap[smallestchild]) < key(heap[parent]))
        {
            swap(&(heap[smallestchild]), &(heap[parent]));
            heapifydown(heap, smallestchild);
        }
    }
    return;
}
void heapifyup(int **heap, int child)
{

    if (child > 1)
    {
        int parent = father(child);
        if (key(heap[child]) < key(heap[parent]))
        {
            swap(&(heap[child]), &(heap[parent]));
            heapifyup(heap, parent);
        }
    }
    return;
}

int key(int *arr)
{
    return arr[0];
}
int rightchild(int i)
{
    return i * 2 + 1;
}

int leftchild(int i)
{
    return i * 2;
}

int father(int i)
{
    return i / 2;
}
void swap(int **a, int **b)
{
    int *tmp = *a;
    *a = *b;
    *b = tmp;
}

// Leetcode 1584 functions
int minCostConnectPoints(int **points, int pointsSize, int *pointsColSize)
{
    int *visited = calloc(pointsSize, sizeof(int));
    int size_pq = ((pointsSize * (pointsSize + 1)) / 2)*2;
    int **pq = makeheap(&size_pq);
    insert(pq, 0, 0);

    int weight = 0;
    int num_vert_visited = -1; // when num of vertices visisted == ( num of vert visited) - 1 end loop
    while (num_vert_visited != (pointsSize - 1))
    {
        int *val = pop(pq);
        // add to weight distance

        //if vertex not visited --> add to MST;
        if( !(visited[val[1]]) ){
            // add vrtx to visited vertices
            visited[val[1]] = 1;
            num_vert_visited++;
            // "add it to the MST"
            weight += key(val);

        }
        
        // visit all neighbouring vertices of the visited vertex
        // and add them to the pq
        for (int i = 0; i < pointsSize; i++)
        {
            if (i != val[1] && !(visited[i]))
            {
                // insert in queue distance from current vertex --> neighbouring vertex
                int manhD = manDist(points[val[1]],  points[i]); 
                insert(pq, manhD, i);
            }
        }

        // freeunused array
        free( val );
    }
    destroyheap( pq );

    return weight;
}
int manDist(int *p1, int *p2)
{
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
}

int main(int argc, char *argv[])
{
    // points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
    //int p[][2] = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};
    int p [][2] = {{11,-6},{9,-19},{16,-13},{4,-9},{20,4},{20,7},{-9,18},{10,-15},{-15,3},{6,6}};

    int size = sizeof(p) / sizeof(p[0]);

    int **new_arr = calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        new_arr[i] = calloc(2, sizeof(int));
        new_arr[i][0] = p[i][0];
        new_arr[i][1] = p[i][1];
    }
    

    
    for( int i = 0; i < size; i++ ){
        int md = 0;
        printf("Edges close to edge: %d-->", i);
        for( int j = 0; j < size; j++){
            if( i != j){
                md = manDist( p[i],p[j] );
                printf( " w:%d (p:%d), ",md, j);
            }

        }
        printf("\n\n");
    }
    
    int colsize = 2;
    int weight = minCostConnectPoints(new_arr, size, &colsize);
    printf("Weight is: %d\n", weight);


}
