#include <string>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>


#define PF "deraonlhsivftgpcbuqmxzkwy"
// Tabela Play Fair
// DERAO
// NLHSI
// VFTGP
// CBUQM
// XZKWY
// DERAONLHSIVFTGPCBUQMXZKWY

#define VG "davincicode"
// DAVINCICODE

int vetor_playfair[26];
int vetor_vigenere[26];
char matriz[25+1]; 		// +1 por causa do '\0'
char chavevg[11+1]; 	// +1 por causa do '\0'

void inicia_vetores_cifra(){
	strcpy (matriz, PF);
	strcpy (chavevg, VG);

	for (int i = 0 ; i < 26 ; i++){
		int posicao = matriz[i] - 97;
		vetor_playfair[posicao] = i;
	}
	vetor_playfair[9] = vetor_playfair[8];	//copia o I no J

	for (int i = 0 ; i < 11 ; i++){
		int deslocamento = chavevg[i] - 97;
		vetor_vigenere[i] = deslocamento;
	}
}

char* decifra_vg (const char* entrada){
	int tamanho	= strlen (entrada);
	char* saida = (char *) malloc (tamanho*sizeof(char));
	int i_chave = 0;

	for (int i = 0 ; i < tamanho ; i++){
		saida[i] = entrada[i] - vetor_vigenere[i_chave];
		i_chave = (i_chave + 1) % 11;
	}

	return saida;
}

std::string decifra_pf (const char* entrada){
    int tamanho	= strlen (entrada);
    std::string saida;

	for (int i = 0 ; i < tamanho ; i += 2){
		char letra1 = entrada[i];
		char letra2 = entrada[i+1];
        char saida1;
		char saida2;

		int linha1	= vetor_playfair[letra1 - 97] / 5;
		int linha2	= vetor_playfair[letra2 - 97] / 5;
		int coluna1	= vetor_playfair[letra1 - 97] % 5;
		int coluna2	= vetor_playfair[letra2 - 97] % 5;

		if (linha1 == linha2){        
            coluna1 = (coluna1 - 1);
            if ( coluna1 == -1 ) 
                coluna1 = 4;
            
            coluna2 = (coluna2 - 1);
            if ( coluna2 == -1 ) 
                coluna2 = 4;

			saida1 = matriz[linha1*5 + (coluna1 % 5)];
			saida2 = matriz[linha2*5 + (coluna2 % 5)];
		}
		else if (coluna1 == coluna2){
			saida1 = matriz[((linha1-1) % 5)*5 + coluna1];
			saida2 = matriz[((linha2-1) % 5)*5 + coluna2];
		}
		else{
			saida1 = matriz[(linha1)*5 + coluna2];
			saida2 = matriz[(linha2)*5 + coluna1];
		}

        saida += saida1;
        saida += saida2;

        // Mostra os pares de letras sendo traduzidas
        // std::cout << char (saida1) << char (saida2) << std::endl;
	}
    
	return saida;
}


int main (){
    std::string entrada;
    
	inicia_vetores_cifra();

    getline(std::cin, entrada);

    std::cout << decifra_pf(entrada.c_str()) << std::endl; 
}