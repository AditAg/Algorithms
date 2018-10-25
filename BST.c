#include<stdio.h>
#include<conio.h>

struct node{
    int key;
    struct node *left,*right;
};

struct stack{
    int top;
    int s[100];
};

struct node *minx(struct node *root){
    struct node *x=root;
    while(x->left->left!=NULL)
        x=x->left;
    return x;
}

struct node *newNode(int key){
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->key=key;
    temp->left=NULL;
    temp->right=NULL;
    return temp;

}

struct node *insert(struct node *root,int key)
{

    struct node *x=root,*y=root;
    if(root==NULL){
        root=newNode(key);
    }
    else{

    while(x!=NULL){
        if(key<=(x->key)){
            y=x;
             x=x->left;
        }
        else if (key>(x->key)){
          y=x;
          x=x->right;
        }

    }
    x=newNode(key);
    if(key>(y->key)) {
        y->right=x;
    }
    else{
        y->left=x;
    }
    }

    return root;


}

struct node *search(struct node *root,int key){
    struct node *x=root;
    struct node *y=NULL;
    while(x!=NULL){
        if(x->key==key){
          y=x;
          break;

        } else if (x->key < key) x=x->right;
        else x=x->left;
    }
    return y;

};

struct node *deletenode(struct node *root,int key){
    struct node *x=root,*y=NULL;

    while(x!=NULL){
        if(key>(x->key)){
            y=x;
            x=x->right;

        }
        else if(key<(x->key)){
            y=x;
            x=x->left;

        }
        else{
            break;
        }
    }
    if(x==NULL){
        printf("Key not found to delete");
        return root;
    }
    if((x->right==NULL) && (x->left==NULL)){

        if(y==NULL)                {    root=NULL;   }
        else if(y->right!=NULL && key==y->right->key){ y->right=NULL;  }
        else if(y->left!=NULL && key==y->left->key) {  y->left=NULL;  }
        free(x);
        return root;
    }
    else if(x->right==NULL){
        if(y==NULL) {root=root->left;}
        else if(y->right!=NULL && key==y->right->key){ y->right=x->left; }
        else if(y->left!=NULL && key==y->left->key){ y->left=x->left;}
        return root;
    }
    else if(x->left==NULL){
        if(y==NULL)  {root=root->right;}
        else if(y->right!=NULL && key==y->right->key ){ y->right=x->right;}
        else if(y->left!=NULL && key==y->left->key){y->left=x->right;}
        return root;
    }
    else{
        if(x->right->left!=NULL){
            struct node *minimum=minx(x->right);
            x->key=minimum->left->key;
            minimum->left=NULL;
            }
            else{
                x->key=x->right->key;
                x->right=x->right->right;
            }

    }
    return root;


}
struct node *pop(struct stack *st,struct node *root){
    int key=(*st).s[(*st).top];

    struct node *x=search(root,key);
    (*st).top--;
    return x;
};


void inorder(struct node *root){

    struct node *current=root;

    struct stack st;
    st.top=-1;
    while(1){
        if(current!=NULL){
            st.top++;
            st.s[st.top]=current->key;
            current=current->left;}
        else{
            if(st.top != -1){
                current=pop(&st,root);
                printf("%d\n",current->key);
                current=current->right;
                            }
            else{
                break;
            }
        }
    }

}

int main()
{
    struct node *root=NULL;
    int choice,key;
    do{
        printf("Enter your choice:\n1.Insert\n2.Delete\n3.Search\n4.Inorder Traversal\n5.Exit\n");
        scanf("%d",&choice);

        switch(choice){
            case 1:

                printf("Enter the element to add to the tree\n");
                scanf("%d",&key);
                root=insert(root,key);
                printf("Item inserted\n");

                break;
            case 2:
                printf("Enter element to be deleted from the tree\n");
                scanf("%d",&key);
                root=deletenode(root,key);

                break;
            case 3:
                printf("Enter element to search in tree\n");
                scanf("%d",&key);
                struct node *y=search(root,key);
                if(y!=NULL) printf("Found in the tree\n");
                else printf("Not Found\n");
                break;
            case 4:
                inorder(root);
                break;
            case 5:
                break;
            default:
                printf("Sorry the entered integer is not correct\n");
                break;



        }
    }while(choice <= 4 && choice >= 1);

    return 0;
}
