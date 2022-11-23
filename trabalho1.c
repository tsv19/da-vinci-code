#include <stdlib.h>
#include <string.h>

#define PF	DERAO
		  	NLHSI
		  	VFTGP
		  	CBUQM
		  	XZKWY
#define VG DAVINCICODE

int vetor_playfair[26];
int vetor_vigenere[11];
char* matriz[25];
char* chavevg[11];

void inicia_vetores_cifra(){
	strcpy (matriz, PF);
	strcpy (chavevg, VG);

	for (int i = 0 ; i < 25 ; i++){
		int posicao = matriz[i] - 97;
		vetor_playfair[posicao] = i;
	}
	vetor_playfair[9] = vetor_playfair[8];	//copia o I no J

	for (int i = 0 ; i < 11 ; i++){
		int deslocamento = chavevg[i] - 97;
		vetor_playfair[i] = deslocamento;
	}
}

char* cifra_2 (char* entrada){
	int tamanho	= strlen (entrada);
	char* saida = malloc (tamanho*sizeof(char));
	int i_chave = 0;

	for (int i = 0 ; i < tamanho ; i++){
		saida[i] = entrada[i] + vetor_vigenere[i_chave];
		i_chave = (i_chave + 1) % 11;
	}

	return saida;
}

//LEMBRAR DE VERIFICAR O I JUNTO COM O J
char* cifra_1 (char* entrada){
	int tamanho	= strlen (entrada);
	char* saida = malloc (tamanho*sizeof(char));

	for (int i = 0 ; i < tamanho ; i += 2){
		char letra1 = entrada[i];
		char letra2 = entrada[i+1];

		int linha1	= vetor_playfair[letra1 - 97] / 5;
		int linha2	= vetor_playfair[letra2 - 97] / 5;
		int coluna1	= vetor_playfair[letra1 - 97] % 5;
		int coluna2	= vetor_playfair[letra2 - 97] % 5;

		if (linha1 == linha2){
			char saida1 = matriz[linha1*5 + ((coluna1+1) % 5)];
			char saida2 = matriz[linha2*5 + ((coluna2+1) % 5)];
		}
		else if (coluna1 == coluna2){
			char saida1 = matriz[((linha1+1) % 5)*5 + coluna1];
			char saida2 = matriz[((linha2+1) % 5)*5 + coluna2];
		}
		else{
			char saida1 = matriz[(linha1)*5 + coluna2];
			char saida2 = matriz[(linha2)*5 + coluna1];
		}

		saida[i  ] = saida1;
		saida[i+1] = saida2;
	}

	return saida;
}

//tirar daqui depois lul
char* decifra_vg (char* entrada){
	int tamanho	= strlen (entrada);
	char* saida = malloc (tamanho*sizeof(char));
	int i_chave = 0;

	for (int i = 0 ; i < tamanho ; i++){
		saida[i] = entrada[i] - vetor_vigenere[i_chave];
		i_chave = (i_chave + 1) % 11;
	}

	return saida;
}

char* decifra_pf (char* entrada){
	
}

int main (){
	inicia_vetores_cifra();
}