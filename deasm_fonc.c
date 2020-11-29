#include "deasm.h"
#include <stdio.h>
#include <string.h>
unsigned getRegName(unsigned num,char* name){
    unsigned compteur = 0;
    unsigned indice =0;
    char reg[32*4]={"$0\0$at\0$v0\0$v1\0$a0\0$a1\0$a2\0$a3\0$t0\0$t1\0$t2\0$t3\0$t4\0$t5\0$t6\0$t7\0"\
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
    *numRs = (codeInst <<6) >>(5+5+5+6+6);
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

//utoha non signé
void utoha(unsigned nbr,char *chaine){
    int compteur ;
    *chaine = '0';
    chaine ++;
    *chaine = 'x';
    chaine++;
    for(compteur =0;compteur <8; ++compteur){
        if(forDigit(nbr>>28)!= '0'){
            *chaine =forDigit(nbr>>28);
            chaine ++;
        }
        nbr = nbr<<4;        
    }
    *chaine = '\0' ;
}


void toString(int nombre,char *res,int base){    
    char tab[16]="0123456789ABCDEF";
    if (nombre == 0){
        *res=tab[nombre];
        *(res+1)= '\0';
        return ;
    }
    int pos=0;
    int nb1;
    if(base ==16){
        *res = '0';
        *(res+1)='x';
        pos = 2;
    }
    
    if(nombre >0){
        nombre = -nombre;
    }else {
        *(res+pos) = '-';
        pos++;
    }
    nb1 =nombre;
    do{
        nb1 =nb1/base ;
        pos ++;

    }while(nb1!=0);
    *(res+pos)= '\0';

    do{
        pos--;
        *(res+pos)=tab[-(nombre%base)];
        nombre = nombre / base;
    }while (nombre!=nb1);
    
}   

void itoa(int val,char *chaine){
    unsigned nombre1=val;
    do{
        nombre1 =nombre1/10;
        chaine ++;
    }while(nombre1!=0) ;    
    *chaine=(char)0;    
    do{
        chaine --;
        *chaine =forDigit(val%10);
        val =val/10;
    }while(nombre1!=val) ;
   
}


void getImmS16(unsigned codeInst,int *imms,char* chaine){
    int code = codeInst;
    *imms =(code << 16)>>16;
    toString(*imms,chaine, 10);
    
}

void getImmS16Hexa(unsigned codeInst,int *imms,char* chaine){
    *imms =codeInst;
    if((*imms & 0x00008000) == 0){
        *imms = *imms & 0x0000FFFF;
        
    }else{
        *imms = *imms | 0xFFFF0000;
    }
    printf("%d\n",*imms);
    utoha(*imms,chaine);

}


void getImmNs16(unsigned codeInst,unsigned *immNs,char* chaine){
    unsigned code = (codeInst<<16)>>16;
    *immNs = code;
    toString(code,chaine,16);
    
}
void getImmNs26(unsigned codeInst,unsigned *immNs,char* chaine){
    unsigned code = ((codeInst<<6)>>6)<<2;
    *immNs = code;
    toString(code,chaine,16);
}

void getShamt(unsigned codeInst,unsigned *shamt,char *chaine){
    *shamt = ((codeInst<<(6+5+5+5))>> (6+5+5+5+6));
    itoa(*shamt,chaine);
}




void strCpy(char *src,char *dest){
    int taille = strlen(src);
    dest[taille]='\0';  

    int i = 0;
    while (i< taille){
        dest[i]= src[i];
        i++;
    }
}

void strAdd(char *src,char *dest){
    int taille_dest = strlen(dest);
    int taille_src = strlen(src);
    int taille_finale =taille_dest+taille_src;
    
    dest[taille_finale] = '\0';
    size_t i = taille_dest ;
    int j = 0;
    while (i< taille_finale){
        dest[i]= src[j];
        i++;
        j++;
    } 
}
unsigned getInstructionName(unsigned codeInst,unsigned *Co,int *Nf,char *name){
    *Co = codeInst >> (5+5+5+5+6);
    *Nf = (codeInst<<(5+5+5+5+6))>>(5+5+5+5+6);
    int compteur =0;
    int indice =0;
    char nomImm[64*8]= { "X\0X\0X\0jal \0beq \0bne \0blez \0bgtz \0"\
                    "addi \0addiu \0slti \0sltiu \0andi \0ori \0xori \0lui \0"\
                    "X\0X\0X\0X\0X\0X\0X\0X\0X\0X\0X\0X\0X\0X\0X\0X\0"\
                    "lb \0X\0X\0lw \0lbu \0X\0X\0X\0"\
                    "sb \0X\0X\0sw \0X\0X\0X\0X\0"\
                    "X\0X\0X\0X\0X\0X\0X\0X\0"\
                    "X\0X\0X\0X\0X\0X\0X\0X\0"};  

    char nom3reg[64*8]= {"sll \0X\0srl \0sra \0sllv \0X\0srlv \0srav \0"\
                    "jr \0X\0X\0X\0syscall\0X\0X\0X\0"\
                    "mfhi \0X\0mflo \0X\0X\0X\0X\0X\0"\
                    "mult \0multu \0div \0divu \0X\0X\0X\0X\0"\
                    "add \0addu \0sub \0subu \0and \0or \0xor \0nor \0"\
                    "X\0X\0slt \0sltu \0X\0X\0X\0X\0"\
                    "X\0X\0X\0X\0X\0X\0X\0X\0"\
                    "X\0X\0X\0X\0X\0X\0X\0X\0"};

    if (*Co == 0){
        while (compteur != *Nf ){
            if(nom3reg[indice]=='\0'){
                compteur++;
            }
        indice++;
        }
        strCpy(&nom3reg[indice],name);
    }else {
        while (compteur != *Co ){
            if(nomImm[indice]=='\0'){
                compteur++;
            }
            indice++;
        }
        *Nf = -1;
        strCpy(&nomImm[indice],name);
    }
    
    if(name[0]=='X'){
        char non []= {"#Instruction inconnue"};
        strCpy(non,name);
        return 1;
    }
    return 0;
}
unsigned decodeInstruction(unsigned codeInst,char *inst){
    inst[0]='\0';
    unsigned co;
    int nf;
    char name [1000];
    int im=0;
    unsigned imm=0;
    char virgule []= {","};
    char p1 []= {"("};
    char p2 []= {")"};    
    unsigned valide  =getInstructionName(codeInst,&co,&nf,name);
    strAdd(name,inst);
    if(co == 3){
        getImmNs26(codeInst,&imm,name);
        strAdd(name,inst);
    }
    if(co == 4 ||co ==5){
        getRs(codeInst,&im,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getRt(codeInst,&imm,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getImmS16(codeInst,&im,name);
        strAdd(name,inst);
    }
    if(co == 7|| co ==6){
        getRs(codeInst,&im,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getImmS16(codeInst,&im,name);
        strAdd(name,inst);
    }
    if(co ==8|| co == 10){
        getRt(codeInst,&imm,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getRs(codeInst,&im,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getImmS16(codeInst,&im,name);
        strAdd(name,inst);
    }
    if(co ==9|| co == 11){
        getRt(codeInst,&imm,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getRs(codeInst,&im,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getImmS16Hexa(codeInst,&im,name);
        strAdd(name,inst);
    }
    if(co == 12||co ==13||co==14){
        getRt(codeInst,&imm,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getRs(codeInst,&im,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getImmNs16(codeInst,&imm,name);
        strAdd(name,inst);
    }
    if(co ==15){
        getRt(codeInst,&imm,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getImmNs16(codeInst,&im,name);
        strAdd(name,inst);
    }
    if (co == 0x23||co == 0x20||co == 0x24||co == 0x2B||co == 0x28){
        getRt(codeInst,&imm,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getImmS16(codeInst,&im,name);
        strAdd(name,inst);
        strAdd(p1,inst);
        getRs(codeInst,&im,name);
        strAdd(name,inst);
        strAdd(p2,inst);

    }
    if(nf==0||nf==2||nf==3){
        getRd(codeInst,&imm,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getRt(codeInst,&imm,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getShamt(codeInst,&imm,name);
        strAdd(name,inst);
    }
    if(nf ==8){
        getRs(codeInst,&im,name);
        strAdd(name,inst);
    }
    if(nf==0x10||nf==0x12){
        getRd(codeInst,&imm,name);
        strAdd(name,inst);
    }
    if(nf>= 0x18 && nf<= 0x1B){
        getRs(codeInst,&im,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getRt(codeInst,&imm,name);
        strAdd(name,inst);
    }
    if((nf>= 0x20 && nf<= 0x27 )||nf==0x2A ||nf==0x2B){
        getRd(codeInst,&imm,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getRs(codeInst,&im,name);
        strAdd(name,inst);
        strAdd(virgule,inst);
        getRt(codeInst,&imm,name);
        strAdd(name,inst);

    }
    return valide;
}

void decodePgm(unsigned *pgm,unsigned taille,char *decode){
    decode[0]= '\0';
    char name [1000];
    char saut []={"\n"};
    for(int i = 0 ;i<taille;++i){
        decodeInstruction(pgm[i],name);
        strAdd(name,decode);
        strAdd(saut,decode);
    }
}
