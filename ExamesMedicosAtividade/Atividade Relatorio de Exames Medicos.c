#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Struct
struct Paciente 
{
    char Nome[50];
    int taxaXolesterol;
    int taxaBroteinas;
    int taxaToroteinas;
    int hipoXolesterol;
    int hiperXolesterol;
    int hipoBroteina;
    int hiperBroteina;
    int hipoToroteinas;
    int hiperToroteinas;
};

struct Paciente **vetor = NULL;


// Função de busca em vetor desordenado
int buscaDesordenada(struct Paciente *vetor, int numero)
{
    char nomeBuscado[50];
    bool encontrado = false; // Indica se o paciente foi encontrado ou não

    printf("Digite o nome do paciente que deseja buscar: ");
    scanf("%s", nomeBuscado);

    // Percorre o vetor de pacientes procurando pelo nome desejado
    for (int i = 0; i < numero; i++)
    {
        // Se o nome for encontrado, imprime os dados do paciente e atualiza a flag encontrado para true
        if (strcmp(vetor[i].Nome, nomeBuscado) == 0)
        {
            printf("\nDados do paciente buscado:\n");
            printf("Nome: %s\n", vetor[i].Nome);
            printf("TaxaX: %d\n", vetor[i].taxaXolesterol);
            printf("TaxaB: %d\n", vetor[i].taxaBroteinas);
            printf("TaxaT: %d\n", vetor[i].taxaToroteinas);
            encontrado = true;
            break;
        }
    }

    // Se "encontrado" ainda for false, significa que o paciente não foi encontrado
    if (!encontrado)
    {
        printf("Paciente não encontrado.\n");
        return 0;
    }

    return 1;
}

// Função para receber dados e imprimir de forma ordenada
void Ordenar(struct Paciente *vetor, int numero)
{
    // Ordena o vetor de pacientes em ordem alfabética pelo campo "Nome"
    for (int i = 0; i < numero-1; i++) {
        for (int j = i+1; j < numero; j++) {
            if (strcmp(vetor[i].Nome, vetor[j].Nome) > 0) {
                struct Paciente temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }

}

// Função para verificar as condições dos inputs do usuário
int verificarInputs(int taxaXolesterol, int taxaBroteinas, int taxaToroteinas)
{
    // Verifica se a taxaXolesterol está entre 0 e 100
    if (taxaXolesterol < 0 || taxaXolesterol > 100) {
        printf("Erro: a taxa de colesterol deve estar entre 0 e 100.\n");
        return -1;
    }

    // Verifica se a taxaProteinas está entre -10 e 10
    if (taxaBroteinas < -10 || taxaBroteinas > 10) {
        printf("Erro: a taxa de proteínas deve estar entre -10 e 10.\n");
        return -1;
    }

    // Verifica se a taxaToroteinas está entre 5000 e 10000
    if (taxaToroteinas < 5000 || taxaToroteinas > 10000) {
        printf("Erro: a taxa de toroteínas deve estar entre 5000 e 10000.\n");
        return -1;
    }

    // Se todas as condições foram atendidas, retorna 0
    return 0;
}

// Função para inicializar programa
struct Paciente* inicializarPrograma(int* numeroPacientes) {
    printf("Digite o numero de pacientes: ");
    scanf("%d", numeroPacientes);


    //O código abaixo apresenta bugs a serem resolvidos em próximas versões sobre alocação dinâmica de memória e, consequentemente, inicialização do programa.
    // Aloca memória para o vetor de ponteiros para struct Paciente
    struct Paciente** vetor = (struct Paciente**) malloc((*numeroPacientes) * sizeof(struct Paciente*));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria");
        return NULL;
    }

    // Loop para preencher os dados dos pacientes
    for (int i = 0; i < (*numeroPacientes); i++) {
        printf("Paciente %d\n", i + 1);

        // Aloca memória para a struct Paciente atual
        struct Paciente* p = (struct Paciente*) malloc(sizeof(struct Paciente));
        if (p == NULL) {
            printf("Erro ao alocar memoria");
            return NULL;
        }

        // Pede o nome do paciente
        printf("Digite o nome do paciente: ");
        scanf("%s", p->Nome);

        // Pede a taxa de colesterol do paciente
        printf("Digite a taxa de colesterol do paciente: ");
        scanf("%d", &p->taxaXolesterol);

        // Pede a taxa de proteínas do paciente
        printf("Digite a taxa de proteinas do paciente: ");
        scanf("%d", &p->taxaBroteinas);

        // Pede a taxa de toroteínas do paciente
        printf("Digite a taxa de toroteinas do paciente: ");
        scanf("%d", &p->taxaToroteinas);

        // Verifica se as taxas estão dentro dos limites aceitáveis
        if (verificarInputs(p->taxaXolesterol, p->taxaBroteinas, p->taxaToroteinas) == -1) {
            printf("Erro ao verificar inputs");
            return NULL;
        }

        // Adiciona o paciente no vetor
        vetor[i] = p;
    }

    return *vetor;
}

void imprimirTodosPacientes(struct Paciente *vetor, int numero)
{
    printf("\nDados dos pacientes:\n");
    for (int i = 0; i < numero; i++)
    {
        printf("Paciente %d:\n", i+1);
        printf("Nome: %s\n", vetor[i].Nome);
        printf("TaxaX: %d\n", vetor[i].taxaXolesterol);
        printf("TaxaB: %d\n", vetor[i].taxaBroteinas);
        printf("TaxaT: %d\n", vetor[i].taxaToroteinas);
    }
}

void imprimirPacientesDebilitados(struct Paciente *vetor, int numero)
{
    int i;
    int vetorGravidade[numero];
    

    // Receber vetor e separar condicionalmente
    for(i = 0; i < numero; i++)
    {

        // Classificar Xolesterol

        if(vetor[i].taxaXolesterol<30)
        {
            vetor[i].hipoXolesterol=1;
        }
        else
        {
            vetor[i].hipoXolesterol=0;
        }

        if(vetor[i].taxaXolesterol>50)
        {
            vetor[i].hiperXolesterol=1;
        }
        else
        {
            vetor[i].hiperXolesterol=0;
        }

        // Classificar Broteina

        if(vetor[i].taxaBroteinas<(-3))
        {
            vetor[i].hipoBroteina=1;
        }
        else
        {
            vetor[i].hiperBroteina=0;
        }

        if(vetor[i].taxaBroteinas>7)
        {
            vetor[i].hiperBroteina=1;
        }
        else
        {
            vetor[i].hiperBroteina=0;
        }

        // Classificar Toroteinas

        if(vetor[i].taxaToroteinas<6500)
        {
            vetor[i].hipoToroteinas=1;
        }
        else
        {
            vetor[i].hipoToroteinas=0;
        }

        if(vetor[i].taxaToroteinas>8000)
        {
            vetor[i].hiperToroteinas=1;
        }
        else
        {
            vetor[i].hiperToroteinas=0;
        }
    }


    // Imprimir todos debilitados

    for (i = 0; i < numero; i++)
    {
        if((vetor[i].hipoXolesterol==1)||(vetor[i].hiperXolesterol==1)||(vetor[i].hipoBroteina==1)||(vetor[i].hiperBroteina==1)||(vetor[i].hipoToroteinas==1)||(vetor[i].hiperToroteinas==1))
        {
            printf("Nome: %s\n", vetor[i].Nome);
                if(vetor[i].hipoXolesterol==1)
                {
                    printf("Apresenta: Hipoxolesterol. \n");
                }

                if(vetor[i].hiperXolesterol==1)
                {
                    printf("Apresenta: Hiperxolesterol. \n");
                }

                if(vetor[i].hipoBroteina==1)
                {
                    printf("Apresenta: Hipobroteina. \n");
                }

                if(vetor[i].hiperBroteina==1)
                {
                    printf("Apresenta: Hiperbroteina. \n");
                }

                if(vetor[i].hipoToroteinas==1)
                {
                    printf("Apresenta: Hipotoroteina. \n");
                }

                if(vetor[i].hiperToroteinas==1)
                {
                    printf("Apresenta: Hipertoroteina. \n");
                }

            vetorGravidade[i]=((vetor[i].hipoXolesterol==1)+(vetor[i].hiperXolesterol==1)+(vetor[i].hipoBroteina==1)+(vetor[i].hiperBroteina==1)+(vetor[i].hipoToroteinas==1)+(vetor[i].hiperToroteinas==1));
            if(vetorGravidade[i]==2)
            {
                printf("Caso grave. \n");
            }
            
            if(vetorGravidade[i]==3)
            {
                printf("Caso muito grave. \n");
            }
        }

    }
    
}

int buscaBinaria(struct Paciente *vetor, int numero)
{
    char nomeBuscado[50];

    printf("Digite o nome do paciente a ser buscado: ");
    scanf("%s", nomeBuscado);

    int inicio = 0;
    int fim = numero - 1;
    int meio;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;

        if (strcmp(vetor[meio].Nome, nomeBuscado) == 0)
        {
            printf("Nome: %s\n", vetor[meio].Nome);
            printf("Taxa de Xolesterol: %d\n", vetor[meio].taxaXolesterol);
            printf("Taxa de Broteinas: %d\n", vetor[meio].taxaBroteinas);
            printf("Taxa de Toroteinas: %d\n", vetor[meio].taxaToroteinas);
            return 1;
        } else
        {
            if (strcmp(vetor[meio].Nome, nomeBuscado) < 0)
            {
            inicio = meio + 1;
            }
            else
            {
            fim = meio - 1;
            }
        }
        
    }
    printf("Paciente não encontrado.\n");
    return 0;
}

void inserirPaciente(struct Paciente *vetor, int numero)
{
    struct Paciente aux;

     // Alocar espaço para o novo paciente
    vetor = (struct paciente*)realloc(vetor, (numero + 1) * sizeof(struct Paciente));

    // Ler os dados do novo paciente
    printf("\nNome do paciente: ");
    scanf("%s", vetor[numero+1].Nome);
    printf("Taxa de colesterol: ");
    scanf("%d", &vetor[numero+1].taxaXolesterol);
    printf("Taxa de proteínas: ");
    scanf("%d", &vetor[numero+1].taxaBroteinas);
    printf("Taxa de triglicerídeos: ");
    scanf("%d", &vetor[numero+1].taxaToroteinas);

    // Ordenar o vetor alfabeticamente
    int i, j;
    for (i = 0; i <= numero; i++) {
        for (j = i+1; j <= numero; j++) {
            if (strcmp(vetor[i].Nome, vetor[j].Nome) > 0) {
                // Trocando as posições
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }
        }
    }

    // Incrementar o contador
    (numero)++;
}

int main()
{
    int i, opcao, programa_inicializado=0, respBuscaDes, respBuscaBin, numero;
    struct Paciente *vetor;
    char nome[50];

  
    

    do {
        printf("\nSelecione uma opcao:\n");
        printf("1 - Inicializar programa\n");   //OK
        printf("2 - Inserir dados de novo paciente\n");  //OK
        printf("3 - Realizar busca desordenada\n"); //OK
        printf("4 - Realizar busca ordenada\n"); //OK
        printf("5 - Imprimir pacientes debilitados\n"); //OK
        printf("6 - Imprimir todos\n");    //OK
        printf("7 - Encerrar\n");   //OK
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                if(programa_inicializado == 0) {
                    printf("Inicializando programa...\n");
                    inicializarPrograma(vetor);
                    programa_inicializado = 1;

                } else {
                    printf("O programa ja foi inicializado!\n");
                }
                break;

            case 2:
            if(programa_inicializado==1)
            {
                printf("Por favor, insira um nome:  \n");
                scanf("%s", nome);

                for(i = 0; i < numero; i++)
                {
                    if(strcmp(vetor[i].Nome, nome)==0)
                    {
                        printf("Nome encontrado no vetor!");
                        break;
                    }
                    else
                    {
                    printf("Inserindo dados...\n");
                    inserirPaciente(vetor, numero);
                    break;
                    }
                }
            }
            else
            {
                printf("Necessita de inicialização do programa.");
            }
                
            case 3:
            if(programa_inicializado==1)
            {
                printf("Realizando busca desordenada...\n");
                respBuscaDes=buscaDesordenada(vetor, numero);
                if(respBuscaDes==0)
                {
                    printf("Paciente não encontrado no sistema");
                }
                else
                {
                    printf("Paciente encontrado no sistema");
                }
                break;
            }
            else
            {
                printf("Necessita de inicialização do programa.");
            }
                
            case 4:
            if(programa_inicializado==1)
            {
                printf("Realizando busca ordenada...\n");
                Ordenar(vetor, numero);
                respBuscaBin = buscaBinaria(vetor, numero);
                if(respBuscaBin==0)
                {
                    printf("Paciente não encontrado no sistema");
                }
                else
                {
                    printf("Paciente encontrado no sistema");
                }

                break;

            }
            else
            {
                printf("Necessita de inicialização do programa.");
            }
                
            case 5:
            if (programa_inicializado==1)
            {
                printf("Imprimindo pacientes debilitados...\n");
                imprimirPacientesDebilitados(vetor, numero);
                break;
            }
            else
            {
                printf("Necessita de inicialização do programa.");
            }
            
                
            case 6:
            if(programa_inicializado==1)
            {
                printf("Imprimindo todos...\n");
                Ordenar(vetor, numero);
                imprimirTodosPacientes(vetor, numero);
                break;
            }
            else
            {
                printf("Necessita de inicialização do programa.");
            }
                

            case 7:
            if(programa_inicializado==1)
            {
                printf("Encerrando programa...\n");
                programa_inicializado=0;
                break;
            }
             else
            {
                printf("Necessita de inicialização do programa.");
            }
                
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 7);
    
    return 0;

}
