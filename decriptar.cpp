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

//funcao que retorna se o caractere é letra ou nao
//(usado depois de transformar todas as maiusculas em minusculas)
bool ehLetra(const char &c){
	return ( c >= 97 && c <= 122 )? true : false;
}

//funcao que retorna se o caractere é numero ou nao
bool ehNumero(const char &c){
	return ( c >= 48 && c <= 57 )? true : false;
}

//funcao que inicia os vetores usados nas cifras
void iniciaVetoresCifra(){
	strcpy(matriz, PF);
	strcpy(chavevg, VG);

	//o vetor_playfair guarda onde a letra daquele indice está na matriz pf
	for (size_t i {0} ; i < 26 ; i++){
		int posicao {matriz[i] - 97};
		vetor_playfair[posicao] = i;
	}
	vetor_playfair[9] = vetor_playfair[8];	//copia o I no J

	//o vetor_vigenere guarda quantas posições a letra sera deslocada de acordo com a posicao na chave
	for (size_t i {0} ; i < 11 ; i++){
		int deslocamento {chavevg[i] - 97};
		vetor_vigenere[i] = deslocamento;
	}
}

//funcao que faz a decifra vigenere
std::string decifra2(const std::string &entrada){
	std::string saida {};
	int i_chave {0};

	for (size_t i {0} ; i < entrada.length() ; ){
		//nao decifra o que nao for letra
		while ( !(ehLetra(entrada[i])) ){
			saida += entrada[i];
			i++;
		}

		//desfaz o deslocamento de acordo com a posicao na chave
		int c {entrada[i] - vetor_vigenere[i_chave]};

		//caso a letra saia do campo de letras minusculas com a subtração
		if ( c < 97 ) saida += (char)(123 - 97 % c);
		else saida += c;

		i_chave = (i_chave + 1) % 11;
		i++;
	}

	return saida;
}

//funcao que faz a decifra play fair
std::string decifra1(const std::string &entrada){
    std::string saida {};

	for (size_t i {0} ; i < entrada.length() ; ){
		std::string aux {};

		char letra1 {entrada[i]};
		//nao decripta o que nao for letra
		while ( !(ehLetra(letra1)) && (i < entrada.length())){
			saida += letra1;
			i++;
			letra1 = entrada[i];
		}

		//cabou a string
		if (i >= entrada.length())
			continue;

		i++;

		char letra2 {entrada[i]};
		//guarda o que nao for letra entre duas letras em aux
		while ( !(ehLetra(letra2)) ){
			aux += letra2;
			i++;
			letra2 = entrada[i];
		}

		char saida1 {};
		char saida2 {};

		//pega quais linhas e colunas de cada letra
		int linha1	{vetor_playfair[letra1 - 97] / 5};
		int linha2	{vetor_playfair[letra2 - 97] / 5};
		int coluna1	{vetor_playfair[letra1 - 97] % 5};
		int coluna2	{vetor_playfair[letra2 - 97] % 5};

		//faz a decifra
		if ( linha1 == linha2 ){       
            coluna1--;
            if ( coluna1 == -1 ) coluna1 = 4;
            
            coluna2--;
            if ( coluna2 == -1 ) coluna2 = 4;

			saida1 = matriz[linha1*5 + (coluna1 % 5)];
			saida2 = matriz[linha2*5 + (coluna2 % 5)];
		}
		else if (coluna1 == coluna2){
			linha1--;
            if ( linha1 == -1 ) linha1 = 4;
            
            linha2--;
            if ( linha2 == -1 ) linha2 = 4;

			saida1 = matriz[((linha1) % 5)*5 + coluna1];
			saida2 = matriz[((linha2) % 5)*5 + coluna2];
		}
		else{
			saida1 = matriz[(linha1)*5 + coluna2];
			saida2 = matriz[(linha2)*5 + coluna1];
		}

		//coloca as letras com aux no meio
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

    //std::cout << "Texto claro:" << std::endl;
    std::cout << decifra1(decifra2(entrada)) << std::endl; 
}