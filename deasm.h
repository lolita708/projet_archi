void strAdd(char *src,char *dest); // Ajouter src a la fin de  destination
void strCpy(char *scr,char*des); // Copie chaine source dans destination

unsigned getRegName(unsigned num,char* name); // Contiendra char regName[32][4] ={"$0","$at"....} ; retourne 0 si OK, 1 sinon
unsigned getRs(unsigned codeInst,unsigned *numRs, char* name); // Numero registre et chaine contenant nom symbolique
unsigned getRt(unsigned codeInst,unsigned *numRt, char* name); // retourne 1 si erreur 
unsigned getRd(unsigned codeInst,unsigned *numRd, char* name);

void utoha(unsigned nbr,char *chaine); // chaine represantant valeur hexa de nbr avec un minumum de caracteres
void itoa(int nbr,char *chaine); //chaine represantant valeur decimale signée de nbr 


void getImmS16(unsigned codeInst,int *imms,char *chaine); // valeur imediate signee 16->32  bits (en decimal) 
void getImmS16Hexa(unsigned codeInst,int *imms,char *chaine); // valeur imediate signee 16->32  bits (en hexa débutant par 0x) 

void getImmNs16(unsigned codeInst,unsigned *immNs,char *chaine); // valeur immediate non signee  16->32bits en hexa debutant par 0x


void getImmNs26(unsigned codeInst,unsigned *immNs,char *chaine); // valeur immediate non signee  26->32bits  avec decalage a gauche de 2 debutant par 0x
void getShamt(unsigned codeInst,unsigned *shamt,char *chaine); // valeur de shamt non signée en decimal 


unsigned getInstructionName(unsigned codeInst,unsigned *Co,int *Nf,char *name);
//contiendra  char nomImm[64][8]={"?","?","j","jal".... a completer }  Vous choisirez un code particulier pour les instructions non traitees
//et char nom3reg[64][8]={"sll",.... a completer}
//Retourne 1 si instruction non trouvee 0 sinon 

unsigned decodeInstruction(unsigned codeInst,char *inst);
// Voir test pour les formats demandes

void decodePgm(unsigned *pgm,unsigned taille,char *decode);
// decode les tailles instructions du programme  dans un tableau de caracteres séparé par des \n
