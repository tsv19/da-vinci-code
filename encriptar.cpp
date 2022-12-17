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

bool ehLetra(char letra){
	if ( letra >= 97 && letra <= 122 ){
		return true;
	}
	return false;
}

bool ehNumero(char letra){
	if ( letra >= 48 && letra <= 57 ){
		return true;
	}
	return false;
}

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

char* cifra_2 (const char* entrada){
	int tamanho	= strlen (entrada);
	char* saida = (char *) malloc (tamanho*sizeof(char));
	int i_chave = 0;

	for (int i = 0 ; i < tamanho ; i++){
		saida[i] = entrada[i] + vetor_vigenere[i_chave];
		i_chave = (i_chave + 1) % 11;
	}

	return saida;
}

//LEMBRAR DE VERIFICAR O I JUNTO COM O J
std::string cifra_1 (const char* entrada){
	std::string saida {};

	for (size_t i = 0 ; i < strlen(entrada) ;){
		std::string aux {};

		char letra1 = entrada[i];
		while ( !(ehLetra(letra1)) && !(ehNumero(letra1)) ){
			saida += letra1;
			i++;
			letra1 = entrada[i];
		}

		while ( ehNumero(letra1) ){
			saida += letra1;
			i++;
			letra1 = entrada[i];
		}

		i++;

		char letra2 = entrada[i];
		while ( !(ehLetra(letra2)) && !(ehNumero(letra2)) ){
			aux += letra2;
			i++;
			letra2 = entrada[i];
		}

		while ( ehNumero(letra2) ){
			aux += letra2;
			i++;
			letra2 = entrada[i];
		}

		// checa os pares de letras 
		// printf("%c %c\n", letra1, letra2);

		char saida1;
		char saida2;

		int linha1	= vetor_playfair[letra1 - 97] / 5;
		int linha2	= vetor_playfair[letra2 - 97] / 5;
		int coluna1	= vetor_playfair[letra1 - 97] % 5;
		int coluna2	= vetor_playfair[letra2 - 97] % 5;

		if ( linha1 == linha2 ){
			saida1 = matriz[linha1*5 + ((coluna1+1) % 5)];
			saida2 = matriz[linha2*5 + ((coluna2+1) % 5)];
		}
		else if ( coluna1 == coluna2 ){
			saida1 = matriz[((linha1+1) % 5)*5 + coluna1];
			saida2 = matriz[((linha2+1) % 5)*5 + coluna2];
		}
		else{
			saida1 = matriz[(linha1)*5 + coluna2];
			saida2 = matriz[(linha2)*5 + coluna1];
		}

		saida += saida1;
		saida += aux;
		saida += saida2;

		i++;
		// Mostra os pares de letras sendo encriptadas
		// std::cout << char (saida1) << char (saida2) << std::endl;
	}

	return saida;
}

void trata_entrada(std::string &entrada_tratada){
	std::string entrada {};
	
	// pega linha inteira de uma vez e coloca na string de entrada
	getline(std::cin, entrada);
	
	// remove os espacos vazios da string, se houverem
	entrada.erase(remove(entrada.begin(), entrada.end(), ' '), entrada.end());

	for (size_t i = 0 ; i < entrada.size() ;){
		char letra1 = tolower(entrada[i]);

		while ( !(ehLetra(letra1)) && !(ehNumero(letra1)) ){
			i++;
			letra1 = entrada[i];
		}

		char letra2 = tolower(entrada[i+1]);

		while ( !(ehLetra(letra2)) && !(ehNumero(letra2)) && letra2 != '\0' ){
			i++;
			letra2 = entrada[i+1];
		}

		if ( ehNumero(letra1) ){
			while ( ehNumero(letra1) ){
				entrada_tratada += letra1;
				i++;
				letra1 = tolower(entrada[i]);
			}
			continue;
		}

		entrada_tratada += letra1;
		i++;

		while ( ehNumero(letra2) ){
			entrada_tratada += letra2;
			i++;
			letra2 = tolower(entrada[i]);
		}

		if ( letra1 == letra2 || letra2 == '\0' )
			entrada_tratada += 'x';
		else
			entrada_tratada += letra2;
		
		i++;
	}

	// Entrada tratada com os x's nos lugares certos
	std::cout << entrada_tratada << std::endl;
}


int main (){
	std::string entrada {};

	inicia_vetores_cifra();
	trata_entrada(entrada);
	std::cout << "Saida criptografada com playfair:" << std::endl;
	std::cout << cifra_1(entrada.c_str()) << std::endl;
}