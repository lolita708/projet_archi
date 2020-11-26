#include "deasm.h"
#include <stdio.h>
#include <string.h>
unsigned getRegName(unsigned num,char* name){
    // char *buffer [32][4]= {"$0","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5"
    // ,"$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

    unsigned compteur = 0;
    unsigned indice =0;
    char reg[32*4]={"$0\0 $at\0$v0\0$v1\0$a0\0$a1\0$a2\0$a3\0$t0\0$t1\0$t2\0$t3\0$t4\0$t5\0$t6\0$t7\0"\
                    "$s0\0$s1\0$s2\0$s3\0$s4\0$s5\0$s6\0$s7\0$t8\0$t9\0$k0\0$k1\0$gp\0$sp\0$fp\0$ra\0"};
    if (num <0 || num > 31){
        return 1;

    }
    while (compteur != num ){
        if(reg[indice]=='\0'){
            compteur++;

        }
        indice++;
    }

    strCpy(&reg[indice],name);
    return 0;

    
}

unsigned getRs(unsigned codeInst,unsigned *numRs, char* name){
    
    *numRs = (codeInst <<6 ) >>(5+5+5+6+6);
    return getRegName(*numRs,name);
   
}
unsigned getRt(unsigned codeInst,unsigned *numRt, char* name){

    *numRt = (codeInst <<(6+5) ) >>(5+5+6+6+5);
    return getRegName(*numRt,name);
   
}

unsigned getRd(unsigned codeInst,unsigned *numRd, char* name){
    *numRd = (codeInst <<(6+5+5) ) >>(5+5+6+6+5);
    return getRegName(*numRd,name);
}
   
char forDigit(unsigned nombre){  
 
 if(nombre>9){
    return (char)(nombre+'A'-10);
 }else {
    return (char)(nombre+'0');
 }
}

void utoha(unsigned nbr,char *chaine){
    int compteur ;
    *chaine = '0';
    chaine ++;
    *chaine = 'x';
    chaine++;
    for(compteur =0;compteur <8; ++compteur){
        *chaine =forDigit(nbr>>28);
        nbr = nbr<<4;
        chaine ++;
    }
    *chaine = '\0' ;
}

void itoa(int val,char *chaine){
    unsigned nombre1=val;
    //Tailledelachainedo
    do{
        nombre1 =nombre1/10;
        chaine ++;
    }while(nombre1!=0) ;
    //Placerlecaracteredefin
    *chaine=(char)0;
    //Placerlescaracteresdepuislafin
    
    do{
        chaine --;
        *chaine =forDigit(val%10);
        val =val/10;
    }while(nombre1!=val) ;
    // A écrire
}


void getImmS16(unsigned codeInst,int *imms,char* chaine){
    utoha(codeInst,chaine);
    
}

void getImmS16Hexa(unsigned codeInst,int *imms,char* chaine){
}


void getImmNs16(unsigned codeInst,unsigned *immNs,char* chaine){
}
void getImmNs26(unsigned codeInst,unsigned *immNs,char* chaine){
}

void getShamt(unsigned codeInst,unsigned *shamt,char *chaine){
}

unsigned getInstructionName(unsigned codeInst,unsigned *Co,int *Nf,char *name){
    return 0;
}


void strCpy(char *src,char *dest){
    size_t taille = strlen(src);
    dest[taille]='\0';  

  size_t i = 0;
  while (i< taille){
    dest[i]= src[i];
    i++;
  }
}

void strAdd(char *src,char *dest){
    size_t taille_dest = strlen(dest);
    size_t taille_src = strlen(src);
    size_t taille_finale =taille_dest+taille_src;
    
    dest [taille_dest]= ' ';
    dest[taille_finale] = '\0';
    size_t i = taille_dest ;
    int j = 0;
    while (i< taille_finale){
        dest[i]= src[j];
        i++;
        j++;
    } 
}

unsigned decodeInstruction(unsigned codeInst,char *inst){
    return 0;
}

void decodePgm(unsigned *pgm,unsigned taille,char *decode){
}
