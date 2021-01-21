#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
unsigned int xorshift32(unsigned int state[static 1])
{
    unsigned int r=state[0];
    r=r^r<<13;
    r=r^r>>17;
    r=r^r<<5;
    state[0]=r;
    return r;
}
typedef struct
{
    char r,g,b;
} culori;
void *liniarizare(char *nume_fisier,char *nume_destinatie)
{
    unsigned int height,width,dim;
    unsigned char header[54],*xor;
    culori *rgb;
    unsigned int inaltime,lungime,marime;
    FILE *fin=fopen(nume_fisier,"rb");
    if(fin==NULL)
    {
        printf("fisierul nu exista");
        return 0;
    }
    *header=malloc(54*sizeof(unsigned char));
    for(int i =0; i<54; i++)
        fread(header+i,sizeof(char),1,fin);
    FILE *fout=fopen(nume_destinatie,"wb+");
    fseek(fin,2,SEEK_SET);
    fread(&dim,sizeof(unsigned int),1,fin);
    printf("dimensiunea imaginii in octeti: %u \n",dim);

    fseek(fin,18,SEEK_SET);
    fread(&width,sizeof(unsigned int),1,fin);
    fseek(fin,22,SEEK_SET);
    fread(&height,sizeof(unsigned int),1,fin);
    fseek(fin,54,SEEK_SET);
    marime=width*height;
    printf("dimensiunea imaginii in pixeli este: %u x %u = %u \n",width,height,marime);
    fseek(fin,0,SEEK_SET);
    unsigned char copie;
    while(fread(&copie,1,1,fin)==1);
    {
        fwrite(&copie,1,1,fout);
        fflush(fout);
    }
//fclose(fin);
    unsigned int padding;
    if(width%4!=0)
        padding=4-(3*width)%4;
    else
        padding=0;
    printf("padding=%d\n",padding);
    fseek(fout,54,SEEK_SET);
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            fread(&rgb[i*width+j].b,1,1,fin);
            fread(&rgb[i*width+j].g,1,1,fin);
            fread(&rgb[i*width+j].r,1,1,fin);
        }
        fseek(fout,padding,SEEK_CUR);
    }
    fread(&xor[0],sizeof (unsigned int),1,fin);
    for(int i=1; i<marime-1; i++)
        xor[i]=xorshift32(xor[i-1]);
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            fwrite(&rgb[i*width+j].b,1,1,fout);
            fwrite(&rgb[i*width+j].g,1,1,fout);
            fwrite(&rgb[i*width+j].r,1,1,fout);
        }
        fseek(fout,padding,SEEK_CUR);
    }
    fclose(fin);
    fclose(fout);
}
int main()
{
    char nume_imagine[]="peppers.bmp";
    char nume_destinatie[]="peppers_copie.bmp";
    liniarizare(nume_imagine,nume_destinatie);
    return 0;
}

