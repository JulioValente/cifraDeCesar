#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

void nl(int y){  //fun��o para novas linhas.
    for(int i=0;i<y;i++){
        printf("\n");
    }
}

void tabul (int t){ //fun��o para tabula��es.
	int i;

	for(i=0; i<t; i++){
		printf("\t");
	}
}

void cabecalho (){ //fun��o do cabe�alho.
	printf("*================================================================================================================*");
	printf("\n\t\t\t\tdecodificador");
	printf("\n*================================================================================================================*");
	printf("\n\n");

	printf(" ->");
	tabul(3);
	printf("decodifica uma mensagem recebida por um arquivo de mensagem");
	nl(2);

	printf(" ->");
	tabul(3);
	printf("n�o pode ser escrito com caracteres especiais");
	nl(3);
}

void rodaMensagem(char *mensagem, int tamanho, int numRotacoes){ //fun��o para deslocar os caracteres da mensagem.
    for(int i=0; i<tamanho;i++){
        mensagem[i] = ((mensagem[i]-'A')+numRotacoes)%26 + 'A';
    }
}

int verificaChar(char c){ //verifica se o caractere � vogal ou consoante. Retorna v para vogal e s para consoante.
    return (c=='A' || c=='E' || c=='I' || c=='O' || c=='U')?'v':'s';
}

int verificaMensagem(char *mensagem, int tamanho){ //Verifica a coer�ncia da mensagem. Retrona 1 se a mensagem � coerente e 0 caso contr�rio.
    char estruturaMensagem[11];

    /*armazena os primeiros caracteres da mensagem*/
    if(tamanho<10){
        for(int i=0;i<tamanho;i++){
            estruturaMensagem[i] = verificaChar(mensagem[i]);
        }
        estruturaMensagem[tamanho] = '\0';
    }else{
        for(int i=0;i<10;i++){

        }
        estruturaMensagem[10] = '\0';
    }
    /**/

    /*verifica a estrutura��o das primeiras letras da mensagem*/
    char *estruturacoes[] = {"sv", "svv", "svvv", "ssv", "ssvv", "ssvvv", "vs", "vss", "vsss"}; //poss�veis estrutura��es
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            char temp[10];
            strcpy(temp,estruturacoes[i]);
            strcat(temp, estruturacoes[j]);
            if(!strcmp(estruturaMensagem, temp)){
                return 1;
            }
        }
    }
    return 0;
    /**/
}

void decifraMensagem(char *mensagem, int tamanho){ //decifra a mensagem automaticamente.
    for(int i=1;i<26;i++){
        rodaMensagem(mensagem, tamanho, i);

        if(verificaMensagem(mensagem, tamanho)){
            break;
        }
    }
}

int main(){
    FILE *arquivo;
    char nomeArquivo[30];
    char mensagem[100];
    int mensagemTamanho=0;

    setlocale(LC_ALL, "");

    cabecalho();

    printf("Digite o nome do arquivo: ");
    nl(2);
    scanf("%s", nomeArquivo);

    strcat(nomeArquivo, "_dec.txt"); //adiciona o formato do arquivo.

    arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL){ //verifica se o arquivo foi aberto.
        nl(1);
        printf("N�o foi poss�vel abrir o arquivo.");
        nl(2);
        printf("Digite qualquer tecla para sair.");
        getch();
        return 1;
    }


    /*armazena a mensagem do arquivo*/

    char c;
    c = fgetc(arquivo);
    while(c!=EOF){
        if(c >= 'A' && c <= 'z'){
            mensagem[mensagemTamanho] = toupper(c);
            mensagemTamanho++;
        }
        c=fgetc(arquivo);
    }

    /**/

    if(fclose(arquivo) == EOF){ //verifica se o arquivo foi fechado.
        nl(2);
        printf("N�o foi poss�vel fechar o arquivo.");
        nl(2);
        printf("Digite qualquer tecla para sair.");
        getch();
        return 1;
    }

    decifraMensagem(mensagem, mensagemTamanho);

    nl(1);
    printf("%s", mensagem);


    //fim do programa.
    nl(2);
    printf("Digite qualquer tecla para sair.");
    getch();

	return 0;
}
