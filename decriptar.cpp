// Autores:
// João Lucas Cordeiro - GRR20190427
// Tiago Serique - GRR20195138

#include <string>
#include <iostream>
#include <algorithm>
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

bool ehLetra(const char &letra){
	return ( letra >= 97 && letra <= 122 )? true : false;
}

bool ehNumero(const char &letra){
	return ( letra >= 48 && letra <= 57 )? true : false;
}

void iniciaVetoresCifra(){
	strcpy(matriz, PF);
	strcpy(chavevg, VG);

	for (size_t i {0} ; i < 26 ; i++){
		int posicao {matriz[i] - 97};
		vetor_playfair[posicao] = i;
	}
	vetor_playfair[9] = vetor_playfair[8];	//copia o I no J

	for (size_t i {0} ; i < 11 ; i++){
		int deslocamento {chavevg[i] - 97};
		vetor_vigenere[i] = deslocamento;
	}
}

std::string decifra2(const std::string &entrada){
	std::string saida {};
	int i_chave {0};

	for (size_t i {0} ; i < entrada.length() ; ){
		while ( !(ehLetra(entrada[i])) ){
			saida += entrada[i];
			i++;
		}

		int c {entrada[i] - vetor_vigenere[i_chave]};

		if ( c < 97 ) saida += (char)(123 - 97 % c);
		else saida += c;

		i_chave = (i_chave + 1) % 11;
		i++;
	}

	return saida;
}

std::string decifra1(const std::string &entrada){
    std::string saida {};

	for (size_t i {0} ; i < entrada.length() ; ){
		std::string aux {};

		char letra1 {entrada[i]};
		while ( !(ehLetra(letra1)) ){
			saida += letra1;
			i++;
			letra1 = entrada[i];
		}

		i++;

		char letra2 {entrada[i]};
		while ( !(ehLetra(letra2)) ){
			aux += letra2;
			i++;
			letra2 = entrada[i];
		}

		char saida1 {};
		char saida2 {};

		int linha1	{vetor_playfair[letra1 - 97] / 5};
		int linha2	{vetor_playfair[letra2 - 97] / 5};
		int coluna1	{vetor_playfair[letra1 - 97] % 5};
		int coluna2	{vetor_playfair[letra2 - 97] % 5};

		if ( linha1 == linha2 ){       
            coluna1 = coluna1 - 1;
            if ( coluna1 == -1 ) coluna1 = 4;
            
            coluna2 = coluna2 - 1;
            if ( coluna2 == -1 ) coluna2 = 4;

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
		saida += aux;
        saida += saida2;

		i++;
	}
    
	return saida;
}


int main (){
    std::string entrada;
    
	iniciaVetoresCifra();

    getline(std::cin, entrada);

    std::cout << "Texto claro:" << std::endl; 
    std::cout << decifra1(decifra2(entrada)) << std::endl; 
}