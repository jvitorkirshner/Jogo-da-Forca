#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TENTATIVAS 8
#define MAX_PALAVRA 50
#define MAX_JOGADORES 10
#define LEADERBOARD_FILE "leaderboard.txt"

const char* palavras_facil[] = {
    "CASA", "GATO", "LIVRO", "MEIA", "TUMBA", "PORCO", "BOLA", "SAGAZ", "AUDAZ", "ORDEM", "FALSO",
    "VIDRO", "PLUMA", "TERRA", "CARTA", "PEDRA", "PORTA", "SALTO", "TIARA", "FOLHA", "FLOCO",
    "GRITO", "RAPTO", "LENTO", "FEIRA", "CHAVE", "RAIOS", "VENTO", "NOITE", "FESTA", "TESTA"
};
const char* palavras_medio[] = {
    "MACACO", "MANTEIGA", "CAVALO", "BOBAGEM", "TRABALHO", "COLEGA","ALTRUISMO", "GABINETE",
    "ABACATE", "ALUGUEL", "CAMARAO", "FANTASIA", "GABINETE", "HORRIVEL", "TECLADO", "ESPADA",
    "ILUMINAR", "JACARE", "LAGOSTA", "MAGNATA", "NITROGENIO", "ORGANICO", "ARMARIO", "CAIXOTE",
	"PALADINO", "RATINHO", "SAMURAI", "PERFUME", "CADERNO", "GARRAFA", "TELEVISAO", "ESCUDO"
};
const char* palavras_dificil[] = {
    "ELEFANTE", "DIAMANTE", "ESTUDANTE", "CARRAPATO", "CONTROLE", "CACHORRO", "COMPUTADOR", "INFRAESTRUTURA",
    "ABACAXIZEIRO", "BIBLIOTECA", "CIRCULATORIO", "DESENVOLVIMENTO", "ENGENHARIA", "FELICIDADE", "HIPERATIVIDADE",
    "GELADEIRA", "HIPOPOTAMO", "IMPRESSIONANTE", "JORNALISMO", "CARATECA", "LABORATORIO", "ESTETOSCOPIO", "HIDROELETRICIDADES",
    "MICROSCOPIO", "NEUROCIENCIA", "OFTALMOLOGIA", "PNEUMOLOGIA", "QUADRILATERO", "REVOLUCIONARIO", "JURISPRUDENCIA",
    "SAXOFONISTA", "TANGENCIAL", "URBANISMO", "VETERINARIO", "XENOMORFO", "ZOOLOGICO", "PNEUMOULTRAMICROSCOPICOSSILICOVULCANOCONIOTICO"
};

typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;

Jogador leaderboard[MAX_JOGADORES];
int numJogadores = 0;

int pontuacao = 0;
int nivel = 1;
char nomeJogador[50] = "";

void exibirMenu() {
    printf("\n=== JOGO DA FORCA ===\n");
    printf("1. Iniciar Jogo\n");
    printf("2. Definir/Alterar Nome do Jogador\n");
    printf("3. Remover Nome do Jogador\n");
    printf("4. Exibir Leaderboard\n");
    printf("5. Sair\n");
    printf("=====================\n");
}

void exibirForca(int tentativas) {
    switch (tentativas) {
        case 0:
            printf("  ____ \n");
            printf(" |    |\n");
            printf(" |     \n");
            printf(" |     \n");
            printf(" |     \n");
            printf("_|_\n");
            break;
        case 1:
            printf("  ____ \n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |     \n");
            printf(" |     \n");
            printf("_|_\n");
            break;
        case 2:
            printf("  ____ \n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |    |\n");
            printf(" |     \n");
            printf("_|_\n");
            break;
        case 3:
            printf("  ____ \n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |   /|\n");
            printf(" |     \n");
            printf("_|_\n");
            break;
        case 4:
            printf("  ____ \n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |     \n");
            printf("_|_\n");
            break;
        case 5:
            printf("  ____ \n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |   / \n");
            printf("_|_\n");
            break;
        case 6:
            printf("  ____ \n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |   / \\\n");
            printf("_|_\n");
            break;
        case 7:
            printf("  ____ \n");
            printf(" |    |\n");
            printf(" |     /\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |   / \\\n");
            printf("_|_\n");
            break;
        case 8:
            printf("  ____ \n");
            printf(" |    |\n");
            printf(" |   \\\ /\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |   / \\\n");
            printf("_|_\n");
            printf("Tentativas esgotadas!\n");
            break;
    }
}

void esconderPalavra(char* palavra, char* escondida) {
    int i;
    for (i = 0; i < strlen(palavra); i++) {
        if (palavra[i] == ' ')
            escondida[i] = ' ';
        else
            escondida[i] = '_';
    }
    escondida[i] = '\0';
}

int tentarLetra(char* palavra, char* escondida, char letra, char* letrasErradas) {
    int i, acertos = 0, encontrada = 0;
    for (i = 0; i < strlen(palavra); i++) {
        if (palavra[i] == letra) {
            escondida[i] = letra;
            acertos++;
            encontrada = 1;
        }
    }

    if (!encontrada) {
        if (!strchr(letrasErradas, letra)) {
            strncat(letrasErradas, &letra, 1);
            strncat(letrasErradas, " ", 1);
        }
    }

    return acertos;
}

int verificarVitoria(char* escondida) {
    return (strchr(escondida, '_') == NULL);
}

void exibirPalavra(char* escondida) {
    printf("%s\n", escondida);
}

void exibirPontuacao() {
    printf("\nPontuacao: %d\n", pontuacao);
}

void exibirLetrasErradas(char* letrasErradas) {
    printf("\nLetras erradas: %s\n", letrasErradas);
}

void limparTela() {
    system("cls || clear");
}

void escolherNivel() {
    printf("\nEscolha um nivel de dificuldade:\n");
    printf("1. Facil\n");
    printf("2. Medio\n");
    printf("3. Dificil\n");
    printf("=====================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &nivel);
}

const char* escolherPalavra() {
    switch (nivel) {
        case 1:
            return palavras_facil[rand() % (sizeof(palavras_facil) / sizeof(palavras_facil[0]))];
        case 2:
            return palavras_medio[rand() % (sizeof(palavras_medio) / sizeof(palavras_medio[0]))];
        case 3:
            return palavras_dificil[rand() % (sizeof(palavras_dificil) / sizeof(palavras_dificil[0]))];
        default:
            return palavras_facil[rand() % (sizeof(palavras_facil) / sizeof(palavras_facil[0]))];
    }
}

void definirNomeJogador() {
    printf("Digite seu nome: ");
    getchar();
    fgets(nomeJogador, 50, stdin);
    nomeJogador[strcspn(nomeJogador, "\n")] = '\0';
}

void removerNomeJogador() {
    nomeJogador[0] = '\0'; 
}

int compararJogadores(const void* a, const void* b) {
    Jogador* jogadorA = (Jogador*)a;
    Jogador* jogadorB = (Jogador*)b;
    return jogadorB->pontuacao - jogadorA->pontuacao;
}

void ordenarLeaderboard() {
    qsort(leaderboard, numJogadores, sizeof(Jogador), compararJogadores);
}

void atualizarLeaderboard(char* nome, int pontuacao) {
    int i;
    for (i = 0; i < numJogadores; i++) {
        if (strcmp(leaderboard[i].nome, nome) == 0) {
            if (pontuacao > leaderboard[i].pontuacao) {
                leaderboard[i].pontuacao = pontuacao;
            }
            ordenarLeaderboard();
            return;
        }
    }
    if (numJogadores < MAX_JOGADORES) {
        strcpy(leaderboard[numJogadores].nome, nome);
        leaderboard[numJogadores].pontuacao = pontuacao;
        numJogadores++;
    } else {
        if (pontuacao > leaderboard[numJogadores - 1].pontuacao) {
            strcpy(leaderboard[numJogadores - 1].nome, nome);
            leaderboard[numJogadores - 1].pontuacao = pontuacao;
        }
    }
    ordenarLeaderboard();
}

void exibirLeaderboard() {
    printf("\n=== LEADERBOARD ===\n");
    for (int i = 0; i < numJogadores; i++) {
        printf("%s: %d pontos\n", leaderboard[i].nome, leaderboard[i].pontuacao);
    }
    printf("===================\n");
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getchar();
    getchar();
}

void salvarLeaderboard() {
    FILE* file = fopen(LEADERBOARD_FILE, "w");
    if (file != NULL) {
        for (int i = 0; i < numJogadores; i++) {
            fprintf(file, "%s %d\n", leaderboard[i].nome, leaderboard[i].pontuacao);
        }
        fclose(file);
    } else {
        printf("Erro ao salvar o leaderboard!\n");
    }
}

void carregarLeaderboard() {
    FILE* file = fopen(LEADERBOARD_FILE, "r");
    if (file != NULL) {
        numJogadores = 0;
        while (fscanf(file, "%s %d", leaderboard[numJogadores].nome, &leaderboard[numJogadores].pontuacao) == 2) {
            numJogadores++;
        }
        fclose(file);
    } else {
        printf("Erro ao carregar o leaderboard!\n");
    }
    ordenarLeaderboard();
}

void darDica(char* palavra, char* escondida, int* dicasUsadas, int maxDicas) {
    if (*dicasUsadas >= maxDicas) {
        printf("Voce ja usou todas as dicas disponiveis!\n");
        return;
    }

    int indices[MAX_PALAVRA];
    int cont = 0;

    for (int i = 0; i < strlen(palavra); i++) {
        if (escondida[i] == '_') {
            indices[cont] = i;
            cont++;
        }
    }

    if (cont > 0) {
        int indiceAleatorio = indices[rand() % cont];
        escondida[indiceAleatorio] = palavra[indiceAleatorio];
        (*dicasUsadas)++;
    }
}

void iniciarJogo() {
    char palavra[MAX_PALAVRA];
    char escondida[MAX_PALAVRA];
    char letra;
    int tentativas;
    int acertos;
    int jogando = 1;
    char continuar;
    int dicasUsadas = 0;
    int maxDicas;
    char letrasErradas[MAX_PALAVRA] = "";

    if (strlen(nomeJogador) == 0) {
        strcpy(nomeJogador, "Convidado");
    }

    while (jogando) {
        escolherNivel();
        strcpy(palavra, escolherPalavra());
        esconderPalavra(palavra, escondida);
        tentativas = 0;
        dicasUsadas = 0;
        letrasErradas[0] = '\0';

        switch (nivel) {
            case 1:
                maxDicas = 1;
                break;
            case 2:
                maxDicas = 2;
                break;
            case 3:
                maxDicas = 3;
                break;
        }

        while (tentativas < MAX_TENTATIVAS) {
            limparTela();

            printf("Jogador: %s\n", nomeJogador); 

            atualizarLeaderboard(nomeJogador, pontuacao);

            exibirForca(tentativas);
            exibirPalavra(escondida);
            exibirLetrasErradas(letrasErradas); 
            exibirPontuacao();
            printf("\nTentativas restantes: %d\n", MAX_TENTATIVAS - tentativas);
            printf("Dicas usadas: %d de %d\n", dicasUsadas, maxDicas); 
            printf("\nOpcoes:\n");
            printf("1. Reiniciar a palavra\n");
            printf("2. Sair do jogo\n");
            printf("3. Pedir uma dica\n");
            printf("\nDigite uma letra ou uma opcao: ");
            scanf(" %c", &letra);
            letra = toupper(letra);

            if (letra == '1') {
                strcpy(palavra, escolherPalavra());
                esconderPalavra(palavra, escondida);
                tentativas = 0;
                dicasUsadas = 0;
                letrasErradas[0] = '\0';
                continue;
            }
            
            if (letra == '2') {
                jogando = 0;
                break;
            }

            if (letra == '3') {
                darDica(palavra, escondida, &dicasUsadas, maxDicas);
                continue;
            }

            if (strchr(letrasErradas, letra) != NULL) {
                continue;
            }

            acertos = tentarLetra(palavra, escondida, letra, letrasErradas);
            if (acertos == 0)
                tentativas++;

            if (verificarVitoria(escondida)) {
                printf("\nParabens, voce venceu! A palavra e: %s\n", palavra);
                pontuacao += (nivel * 10);
                break;
            }
        }

        if (tentativas == MAX_TENTATIVAS) {
            limparTela();
            exibirForca(tentativas);
            printf("\nVoce perdeu! A palavra era: %s\n", palavra);
        }

        if (!jogando) {
            break;
        }

        printf("\nDeseja continuar jogando? (S/N): ");
        scanf(" %c", &continuar);
        continuar = toupper(continuar);

        if (continuar == 'N') {
            jogando = 0;
        }
    }
}

int main() {
    srand(time(NULL));
    int opcao;

    carregarLeaderboard();  

    do {
        limparTela();
        exibirMenu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                iniciarJogo();
                pontuacao = 0;  
                break;
            case 2:
                definirNomeJogador();
                break;
            case 3:
                removerNomeJogador();
                break;
            case 4:
                exibirLeaderboard();
                break;
            case 5:
                printf("\nSaindo do jogo...\n");
                salvarLeaderboard();  
                break;
            default:
                printf("\nSelecione uma opcao valida.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
