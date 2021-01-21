#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arb
{
    int data,height;
    struct arb* dr;
    struct arb* st;
}arb;

int max(int a,int b)
{
    return (a>b)? a : b;
}

int inaltime(arb* node )
{
    if(node==NULL)
        return 0;
    return node->height;
}

int balanta(arb* node)
{
    if(node==NULL)
        return 0;
    return (inaltime(node->st)-inaltime(node->dr));
}

arb* rotatiedr(arb* root)
{
   arb* son=root->st;
   arb* temp=son->dr;

   son->dr=root;
   root->st=temp;

   root->height=max(inaltime(root->st),inaltime(root->dr))+1;
   son->height=max(inaltime(son->st),inaltime(son->dr))+1;
   return son;
}

arb* rotatiest(arb* root)
{
   arb* son=root->dr;
   arb* temp=son->st;

   son->st=root;
   root->dr=temp;

   root->height=max(inaltime(root->st),inaltime(root->dr))+1;
   son->height=max(inaltime(son->st),inaltime(son->dr))+1;
   return son;
}

arb* push(arb* root,int val)
{
        if(root==NULL)
            {arb* leaf=(arb*)malloc(sizeof(arb));
             leaf->data=val;
             leaf->st=NULL;
             leaf->dr=NULL;
             leaf->height=1;
             return leaf;
           }
else{
        if(val<root->data)
           root->st=push(root->st,val);
else if(val>root->data)
           root->dr=push(root->dr,val);
else return root;
        }
        root->height=1+max(inaltime(root->st),inaltime(root->dr));
        int bal=balanta(root);

        if(bal> 1 && val<root->st->data)   ///Left left  ><
            return rotatiedr(root);
        if(bal< -1 && val>root->dr->data)  ///Right right <>
            return rotatiest(root);

        if(bal>1 && val>root->st->data)    ///Left right >>
        {
            root->st=rotatiest(root->st);
            return rotatiedr(root);
        }
        if(bal<-1 && val<root->dr->data)    ///Right Left <<
        {
            root->dr=rotatiedr(root->dr);
            return rotatiest(root);
        }
        return root;
}

void afisRSD(arb* root)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        afisRSD(root->st);
        afisRSD(root->dr);
    }
}

void afisSRD(arb* root)
{
    if(root!=NULL)
    {
        afisSRD(root->st);
        printf("%d ",root->data);
        afisSRD(root->dr);
    }
}

void afismax(arb* root)
{
    arb* temp=root;
   while(temp->dr!=NULL)
    temp=temp->dr;

   printf("%d ",temp->data);
}

bool cautare(arb* root,int val)
{
    if(root==NULL)
       printf(" Arborele este gol. ");
    else
    {
        arb* temp=root;
        while(temp)
            {
            if(temp->data==val)
                return true;
            if(val<temp->data)
                temp=temp->st;
            else
                temp=temp->dr;
           }
           return false;
   }
}

arb* minim(arb* root)
{
    arb* temp=root;
   while(temp->st!=NULL)
    temp=temp->st;

    return temp;
}

arb* stergere(arb* root,int val)
{
    if (root == NULL)
    {
        printf(" Nu exista acest element in arbore \n");
        return root;
    }
        if ( val < root->data )
          root->st = stergere(root->st, val);
else if ( val > root->data )
          root->dr = stergere(root->dr,val);
else
    {
        if( (root->st == NULL) || (root->dr == NULL) )
        {
            arb *temp = root->st ? root->st : root->dr;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
             *root = *temp;

            free(temp);
        }
        else
        {

        arb* temp = minim(root->dr);
        root->data= temp->data;
        root->dr= stergere(root->dr, temp->data);
        }
    }

    if (root == NULL)
      return root;


    root->height = 1 + max(inaltime(root->st),inaltime(root->dr));
    int bal = balanta(root);

    // Left Left Case
    if (bal > 1 && balanta(root->st) >= 0)
        return rotatiedr(root);

    // Left Right Case
    if (bal > 1 && balanta(root->st) < 0)
    {
        root->st =  rotatiest(root->st);
        return rotatiedr(root);
    }

    // Right Right Case
    if (bal < -1 && balanta(root->dr) <= 0)
        return rotatiest(root);

    // Right Left Case
    if (bal < -1 && balanta(root->dr) > 0)
    {
        root->dr = rotatiedr(root->dr);
        return rotatiest(root);
    }

    return root;
}

int main()
{
    arb* root=NULL;
    arb* node=NULL;
    int optiune,val;

    int i,n=7,a[7]={12,2,-10,25,50,20,-5};
    for(i=0;i<n;i++)
    {
        root=push(root,a[i]);
    }

    printf("Afis RSD : ");
    afisRSD(root);
    printf("\n");
    printf("Afis SRD : ");
    afisSRD(root);
    printf("\n");
    printf("Elementul maxim este : ");
    afismax(root);

    do
    {
        printf("\n\n");
        printf("Ce vrei sa faci?\n\n [1] Sa cauti un element.\n [2] Sa stergi un element.\n Raspuns : ");
        scanf("%d",&optiune);
        printf("\n");

        switch(optiune)
        {
    case 1:
      printf(" Ce element vrei sa cauti?\n Raspuns : ");
      scanf("%d",&val);
      cautare(root,val) ? printf(" Exista in AVL") : printf(" Nu exista in AVL");
      break;

    case 2:
      printf(" Ce element vrei sa stergi?\n Raspuns : ");
      scanf("%d",&val);
      root=stergere(root,val);
      printf(" Afis SRD : ");
      afisSRD(root);
      printf("\n");
      break;

    default:
        printf("Optiune invalida ");
        printf("\n");
        break;

        }
    }while(optiune >=1 && optiune <=2);


    return 0;
}

