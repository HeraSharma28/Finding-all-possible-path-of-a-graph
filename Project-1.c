#include <stdio.h>

struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

int num_visa, a_index_c=0;
int index_list[1000], arr1[1000][50];

int addNode (struct Node * p, int nid, int count)
{
    int i =0, ncount = count;
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == nid) { break; }
    }
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

void addAdjacent (struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i =0, index;
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c+1;

            break;
        }
    }
}

int added (int * list, int lcount, int nid)
{
    int i =0;
    for (i=0;i<lcount;i++)
    {
        if (list[i] == nid) { return 1; }
    }
    return 0;
}


void findpath (struct Node * p, int count, int start, int end, int * list, int *clist, int lcount, int *visa)
{
    int index = 0, i=0, arr[1000], pathNode_c=0;


    //check if list contains the end node
    if (list[lcount-1] == end)
    {
        printf ("\n");
        int tcost = 0;
        for (i=0;i<lcount;i++)
        {
            printf ("%d ", list[i]);
            pathNode_c++;
            arr[i]=list[i];
            tcost += clist[i];
        }
        int compare_c=0;
        if(pathNode_c-1<=num_visa){
            for(int i=1; i<pathNode_c; i++){
                for(int j=0; j<num_visa; j++){
                    if(arr[i]==visa[j])
                        compare_c++;
                }
            }
        }
        if(compare_c==pathNode_c-1){
            int indx_c=0;
            for(int i=0; i<pathNode_c; i++){
                indx_c++;
                arr1[a_index_c][i]=arr[i];
            }
            index_list[a_index_c]=indx_c;
            a_index_c++;
        }
        return;
    }

    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == start) { index = i; break; }
    }

    for (i=0;i<p[index].adjcount;i++)
    {
        int a = added (list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath (p, count, p[index].adjs[i], end, list, clist, lcount, visa);
            lcount--;
        }
    }
}


int main() {
    // Write C code here
    //printf("Hello world");

    struct Node nodes[50];
    int nodecount = 0;
    int n1=0, n2=0, c = 0;


    while (1)
    {
        printf ("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c== -9) {break;}
        nodecount = addNode (&nodes[0], n1, nodecount);
        nodecount = addNode (&nodes[0], n2, nodecount);

        addAdjacent (&nodes[0], n1, n2, c, nodecount);
        addAdjacent (&nodes[0], n2, n1, c, nodecount);
    }

    int start, end;
    printf ("start, end ? ");
    scanf ("%d %d", &start, &end);
    int list[50], clist[50], lcount = 0;
    list[0] = start; clist[0] = 0; lcount = 1;

    printf("Number of Visa: ");
    scanf("%d", &num_visa);
    printf("Put Visa Node: ");
    int visa[num_visa];

    for(int i=0; i<num_visa; i++)
        scanf("%d", &visa[i]);

    findpath (nodes, nodecount, start, end, list, clist, lcount, visa);
    printf("\n\n");

    for(int k=0; k<a_index_c; k++){
        for(int l=0; l<index_list[k]; l++){
            printf("%d ",arr1[k][l]);
        }
        printf("\n");
    }

    return 0;
}
