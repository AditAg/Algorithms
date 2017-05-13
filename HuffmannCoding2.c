#include<stdio.h>
#include<stdlib.h>
#define MAX 200
#define max_min >
typedef struct node{
    int ch;
    int frequency;
    struct node *left;
    struct node *right;
}node;
node *create_node(int frequency,int character){
    node *temp=(node *)(malloc(sizeof(node)));
    temp->ch=character;
    temp->frequency=frequency;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
void swap(node **a,node **b){
    node *temp=*a;
    *a=*b;
    *b=temp;
}
void insert(node **A,node *t,int position){
    A[position]=t;
    int parent=(position-1)/2;
    int lastindex=position;
    while(parent>=0 && A[parent]->frequency max_min A[lastindex]->frequency){
        swap(&A[parent],&A[lastindex]);
        lastindex=parent;
        parent=(lastindex-1)/2;
    }
    return;
}
void percolate_down(node **A,int N){
    int i=0;
    int child1=2*i+1;
    if(child1>N)    return;
    int child2=2*i+2;
    if(child2>N){
        if(A[i]->frequency max_min A[child1]->frequency){
            swap(&A[i],&A[child1]);
        }
        return;
    }
    while(i<=N &&(A[i]->frequency max_min A[child1]->frequency || A[i]->frequency max_min A[child2]->frequency)){
        if(A[child1]->frequency max_min A[child2]->frequency){
            swap(&A[child2],&A[i]);
            i=child2;
        }
        else{
            swap(&A[child1],&A[i]);
            i=child1;
        }
        child1=2*i+1;
        if(child1>N)    return;
        child2=2*i+2;
        if(child2>N){
            if(A[i]->frequency max_min A[child1]->frequency){
                swap(&A[i],&A[child1]);
            }
            return;
        }
    }
    return;
}
node *deletetop(node **A,int position){
    node *z=A[0];
    if(position==0){
        return z;
    }
    swap(&A[0],&A[position]);
    position-=1;
    percolate_down(A,position);
    return z;
}
void Huffman_codes(node *root,int arr[],int top,int A[][100]){
    if(root->left){
        arr[top]=0;
        Huffman_codes(root->left,arr,top+1,A);
    }
    if(root->right){
        arr[top]=1;
        Huffman_codes(root->right,arr,top+1,A);
    }
    if (root->ch!=-1 && (root->left==NULL && root->right==NULL)){
        int i;
        for(i=0;i<top;i++){
            A[root->ch][i]=arr[i];
        }
        A[root->ch][i]=-1;
    }
}
void inorder(node *root){
    if(root==0)  return;
    inorder(root->left);
    printf("%d   %d\n",root->ch,root->frequency);
    inorder(root->right);
}
int main(){
    char filename[MAX],ch,z;
    printf("Enter the filename to be opened :\n");
    scanf("%s",&filename);
    FILE *fptr;
    fptr=fopen(filename,"r");
    if(fptr==NULL){
        printf("Cannot open file   Try Again\n");
        exit(0);
    }
    fseek(fptr,0L,SEEK_END);
    long long int size=ftell(fptr);
    fseek(fptr,0L,SEEK_SET);
    int characters[256],i;
    for(i=0;i<256;i++) characters[i]=0;
    ch=fgetc(fptr);
    while(ch!=EOF){
        z=(int)ch;
        //if(z>=65 && z<=90){ z-=65;}
        //else if(z>=97 && z<=122){z-=97;}
        //else{ch=fgetc(fptr);
         //   continue;}
        characters[z]+=1;
        ch=fgetc(fptr);
    }
    fclose(fptr);
    node **A=(node **)(malloc(sizeof(node*)*512));
    node *t;
    int length=-1,j;
    for(i=0;i<256;i++){
        if(characters[i]!=0){
            length+=1;
            t=create_node(characters[i],i);
            insert(A,t,length);
        }
        else{ continue; }
    }
    node *combinedelement;
    node *topelement,*topelement2;
    int l=length;
    for(i=0;i<l;i++){
        topelement=(deletetop(A,length));
        //printf("\n%d    %d",topelement.ch,topelement.frequency);
        length-=1;
        topelement2=(deletetop(A,length));
        combinedelement=create_node(topelement2->frequency+topelement->frequency,-1);
        combinedelement->left=topelement;// wrong because this is actually storing a single node variable that is topelement
        //and so every time the top two statements change values of the two nodes and hence everytime this gets updated and thus all the
        //earlier internal nodes also get changed
        combinedelement->right=topelement2;
        insert(A,combinedelement,length);
        /*for(j=0;j<=l;j++){
            if(A[j]->left!=NULL && A[j]->right!=NULL)
            printf("%d    %d    %d    %d\n",A[j]->ch,A[j]->frequency,A[j]->left->ch,A[j]->right->ch);
            else
                printf("Leaf: %d    %d\n",A[j]->ch,A[j]->frequency);
        }
        printf("\n");*/
    }
    node *ptr=deletetop(A,length);
    int arr[l+1],top=0;
    int codes[256][100];
    for(i=0;i<256;i++){
        codes[i][0]=-1;
    }
    printf("Inorder Traversal \n");
    //inorder(ptr);
    printf("\nHuffman Codes are: \n");
    Huffman_codes(ptr,arr,top,codes);
    int lengths[256];
    for(i=0;i<256;i++){
        j=0;
        if(codes[i][j]==-1)  {lengths[i]=0;continue;}
        printf("%c : ",(char)i);
        while(codes[i][j]!=-1){
            printf("%d",codes[i][j]);
            j+=1;
        }
        lengths[i]=j;
        printf("\n");
    }
    printf("Original file size : %lld bits\n",size*8);
    FILE * storefile=fopen("encodeddata.txt","wb");
    long long int size2=0;
    for(i=0;i<256;i++){
        size2+=characters[i]*lengths[i];
    }
    printf("New file size : %lld bits",size2);
    printf("\nEncoding Data .........");
    fptr=fopen(filename,"r");
    ch=fgetc(fptr);
    while(ch!=EOF){
        j=0;
        while(codes[(int)ch][j]!=-1){
            fprintf(storefile,"%d",codes[(int)ch][j]);
            j+=1;
        }
        ch=fgetc(fptr);
    }
    fclose(fptr);
    fclose(storefile);
    //Decoding the data
    storefile=fopen("decodedfile.txt","w");
    fptr=fopen("encodeddata.txt","r");
    ch=fgetc(fptr);
    printf("\nDecoding Data........\n");
    while(ch!=EOF){
        node *root=ptr;
        while(root->left!=NULL && root->right!=NULL){
            if(((int)ch)-48==0){
                root=root->left;
                ch=fgetc(fptr);
            }
            else if(((int)ch)-48==1){
                    root=root->right;
                    ch=fgetc(fptr);
            }
            else{
                printf("\nSorry the binary file is not correct....Try again");
                return 0;
            }
        }
        if(root->right==NULL && root->left==NULL){
            fprintf(storefile,"%c",(char)root->ch);
        }
        else{
            printf("\nSorry the given file couldn't be decoded since some the codes donot match");
            return 0;
        }
    }
    return 0;
}
