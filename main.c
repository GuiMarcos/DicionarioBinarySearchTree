#include "dicionario.h"

Dicionario *raiz=NULL;

int main() {
    setlocale(LC_ALL,"");										//Possibilita impressao de caracteres especiais

    Dicionario *temp;

    FILE *arq = fopen("BaseDicionario3.json","r");				//Abrindo o arquivo
    if (arq == NULL){ 											//Verifica se ocorreu erro
        printf("Erro ao abrir o arquivo\nVerifique os diretórios e nomes");
    }

    FILE *f;


    base_dic2(arq);												//Ler Base de Dados

    fclose(arq);												//Fecha o arquivo

    int ind;
    while(ind!=6){
        printf("\n---------------------\n|    1.Busca        |\n|    2.Inserção     |\n|    3.Leitura      |\n|  4.Regras e Infos |\n|   5.Exportar Dic  |\n|      6.Saída      |\n---------------------\n\n>>>>Escolha Sua Opção: ");
        scanf("%d",&ind);
        switch (ind) {
            case 1:
                chama_busca();
                break;
            case 2:
                preenche_dic(temp);
                break;
            case 3:
                ler_dicionario(raiz);
                printf("\n");
                break;
            case 4:
                regras_infos();
                break;
            case 5:
                f=fopen("Dicionario.txt","w");		//Cria o arquivo Dicionario.txt
                exportar_dicionario(raiz,f);		//Exporta os dados do Dicionario para esse arquivo
                fclose(f);							//Fecha o arquivo
                printf("\n!!!Concluido!!!\n");
                break;
            case 6:
                exit(0);
            default:
                printf("INVALIDO!!!");
                break;
        }
    }

    return 0;
}
