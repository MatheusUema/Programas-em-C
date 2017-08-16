
#include <stdio.h>
#include <stdarg.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif

/** Declaração de constantes, estruturas, funções e etc **/
enum terminal_const {VERMELHO, VERDE, AZUL, CIANO, MAGENTA, AMARELO, NORMAL};
void terminal_gotoxy(int x, int y);
void terminal_clear(void);
void terminal_colorPrintf(int color, char string[], ...);
void terminal_getConsoleSize(int * width, int * height);

void input_clear(void);
void input_readf(char format[], ...);

enum jogo_const {VAZIO=-1, MOSTRAR_NUM, ESCONDER_NUM};
int jogo_menu(void);
void jogo_main(void);
void jogo_inicio(int grade[3][3], int jogador_xo[2], int jogador_cor[2]);
void jogo_desenhar(int grade[3][3], int xo[2], int cores[2], int mostrar);
void jogo_vez(int grade[3][3], int jogador_xo[2], int jogador_cor[2], int jogador_id);
int jogo_resultado(int grade[3][3], int linha[3]);
void jogo_destacarVitoria(int xo, int cor, int linha[3]);

/* Main */
int main(void)
{
	int escolha;

	setlocale(LC_ALL, "");

	do
	{
		escolha = jogo_menu();

		switch(escolha)
		{
			case 1:
				jogo_main();
				break;
			case 2:
				break;
			case 0:
				terminal_clear();
				printf("Obrigado por jogar!");
				getchar();
				terminal_clear();
				break;
			default:
				break;
		}
	}while(escolha);

	return 0;
}

/* Menu */
int jogo_menu(void)
{
	int escolha, largura, altura;
	char MENU_LOGO[]=
	"\n     |  |       \\ \\     /  ____|  |      |   |     \\           |  |   "
	"\n  _  |_ |_|      \\ \\   /   __|    |      |   |    _ \\       _  |_ |  "
	"\n  _  |_ |_|       \\ \\ /    |      |      ___ |   ___ \\      _  |_ |_| "
	"\n    _| _|          \\_/    _____| _____| _|  _| _/    _\\       _| _|   ";
	char *MENU_TEXTO[] =
	{
		"1. Jogar",
		"2. Instruções",
		"0. Sair",
		"", ">> "
	};

	terminal_clear();
	terminal_colorPrintf(CIANO, "%s\n", MENU_LOGO);

	terminal_getConsoleSize(&largura, &altura);

	for(escolha=0; escolha<5; ++escolha)
	{
		terminal_gotoxy(largura/2-10, altura/2+escolha);
		printf("%s", MENU_TEXTO[escolha]);
	}

	input_readf("%d", &escolha);

	return escolha;
}

/* Função principal do jogo */
void jogo_main(void)
{
	int grade[3][3], jogador_xo[2], jogador_cor[2];
	int linha[3], turnos=0, vencedor=VAZIO;
	int semCor[2] = {NORMAL, NORMAL};

	jogo_inicio(grade, jogador_xo, jogador_cor);

	while(vencedor==VAZIO && turnos < 9)
	{
		jogo_vez(grade, jogador_xo, jogador_cor, (turnos++)%2);

		vencedor = jogo_resultado(grade, linha);
	}

	jogo_desenhar(grade, jogador_xo, semCor, ESCONDER_NUM);

	if(vencedor==VAZIO)
		printf("DEU VELHA!");
	else
		jogo_destacarVitoria(jogador_xo[vencedor], jogador_cor[vencedor], linha);

	// Vencedor.
	input_clear();
}

/* Decide o simbolo e cor de cada jogador */
void jogo_inicio(int grade[3][3], int jogador_xo[2], int jogador_cor[2])
{
	int i;

	for(i=0; i<9; ++i)
		grade[i/3][i%3] = VAZIO;

	/* O jogador pode escolher um número de 1 até 12. */
	/* (1-6) é X, (7-12) é O. */
	/* 1&7 são vermelhos, 2&8 são verdes, 3&9 são azuis e assim por diante */

	do
	{
		terminal_clear();
		printf("Escolha o simbolo e cor do segundo jogador:\n\n");
		for(i=0; i<6; ++i)
		{
			printf("%d - ", i+1);
			terminal_colorPrintf(i, "X\t");
			printf("%d - ", i+7);
			terminal_colorPrintf(i, "O\n");
		}

		printf(">> ");
		input_readf("%d", &i);
	}
	while(i<1 || i>12);

	jogador_xo[1] = (i < 7) ? 'X' : 'O';
	jogador_cor[1] = (i-1)%6;
	jogador_xo[0] = (i < 7) ? 'O' : 'X';

	/* Jogador 1 não pode escolher o mesmo simbolo ou cor que o Jogador # */
	do
	{
		terminal_clear();
		printf("Escolha a cor do primeiro jogador:\n\n");

		for(i=0; i<6; ++i)
		{
			if (i==jogador_cor[1])
				continue;

			printf("%d - ", i+1);
			terminal_colorPrintf(i, "%c\n", jogador_xo[0]);
		}
		printf(">> ");
		input_readf("%d", &i);
	}
	while(i<1 || i == jogador_cor[0]+1 || i > 6 );

	jogador_cor[0]=i-1;
}

/* Desenha a grade na tela */
void jogo_desenhar(int grade[3][3], int xo[2], int cores[2], int mostrar)
{
	int i, pos, contagem=1;

	/* Para desenhar na terceira coluna da primeira linha use as cordenadas posicao_x[2], posicao_y[0]*/
	int posicao_x[] = {1, 5, 9};
	int posicao_y[] = {2, 5, 8};

	char desenho_grade[] =
	"\n   |   |   "
	"\n   |   |   "
	"\n___|___|___"
	"\n   |   |   "
	"\n   |   |   "
	"\n___|___|___"
	"\n   |   |   "
	"\n   |   |   "
	"\n   |   |   ";

	terminal_clear();

	printf("%s", desenho_grade);
	for(i=0; i<9; ++i)
	{
		terminal_gotoxy(posicao_x[i%3], posicao_y[i/3]);
		pos = grade[i%3][i/3];

		if(pos != VAZIO)
			terminal_colorPrintf(cores[pos], "%c", xo[pos]);
		else if(mostrar == MOSTRAR_NUM)
			printf("%d", contagem++);
	}

	terminal_gotoxy(0, 10);
}

/* Vez de cada jogador jogar */
void jogo_vez(int grade[3][3], int jogador_xo[2], int jogador_cor[2], int jogador_id)
{
	int i, jogada;

	do
	{
		jogo_desenhar(grade, jogador_xo, jogador_cor, MOSTRAR_NUM);
		terminal_colorPrintf(jogador_cor[jogador_id], "Jogador %c, escolha onde quer jogar:\n", jogador_xo[jogador_id]);
		printf(">> ");
		input_readf("%d", &jogada);

		/* Sem essa condição escolher 0 simplesmente pula seu turno */
		if (jogada==0)
			--jogada;

		for(i=0; jogada>0 && i<9; ++i)
			if (grade[i%3][i/3] == VAZIO)
				--jogada;

		if(jogada==0)
		{
			--i; /* Desfazendo o  ultimo incremento */
			if (grade[i%3][i/3]==VAZIO)
				grade[i%3][i/3] = jogador_id;
		}

	}while(jogada != 0);
}

/* Função auxiliar de jogo_resultado*/
void adicionarCordenadas(int vetor[3], int x0, int x1, int x2, int y0, int y1, int y2)
{
	vetor[0] = 3*y0 + x0;
	vetor[1] = 3*y1 + x1;
	vetor[2] = 3*y2 + x2;
}

/* Determina quem venceu o jogo, o tipo de vitória e o local onde a vitória aconteceu */
/* A coordenada é codificada como 3y+x. Note que isso funciona pois x e y são números de 0 a 2. */
int jogo_resultado(int grade[3][3], int linha[3])
{
	int i;

	for(i=0; i<3; ++i)
		if(grade[i][0] == grade[i][1] && grade[i][1]==grade[i][2])
		{
			adicionarCordenadas(linha, i, i, i, 0, 1, 2);
			return grade[i][0];
		}

	for(i=0; i<3; ++i)
		if(grade[0][i] == grade[1][i] && grade[1][i]==grade[2][i])
		{
			adicionarCordenadas(linha, 0, 1, 2, i, i, i);
			return grade[0][i];
		}

	if (grade[1][1] == grade[0][0] && grade[1][1]==grade[2][2])
	{
		adicionarCordenadas(linha, 0, 1, 2, 0, 1, 2);
		return grade[1][1];
	}

	if (grade[1][1] == grade[2][0] && grade[1][1]==grade[0][2])
	{
		adicionarCordenadas(linha, 0, 1, 2, 2, 1, 0);
		return grade[1][1];
	}

	return VAZIO;
}

/* Tela do fim do jogo */
/* Destaca a linha que o jogador vencedor fez */
void jogo_destacarVitoria(int xo, int cor, int linha[3])
{
	int i, x, y;
	/* Se estiver confuso ver jogo_desenhar() */
	int posicao_x[] = {1, 5, 9};
	int posicao_y[] = {2, 5, 8};

	for(i=0; i<3; ++i)
	{
		x = linha[i]%3;
		y = linha[i]/3;
		terminal_gotoxy(posicao_x[x], posicao_y[y]);
		terminal_colorPrintf(cor, "%c", xo);
	}

	terminal_gotoxy(0,10);
	terminal_colorPrintf(cor, "O jogador %c venceu!", xo);
}

/* Posiciona o cursor na cordenada (x,y) */
void terminal_gotoxy(int x, int y)
{
	#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos; pos.X = x; pos.Y = y;

    SetConsoleCursorPosition(hConsole, pos);
	#endif
}

/* Limpa o terminal */
void terminal_clear(void)
{
	#ifdef _WIN32
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo( hConsole, &csbi );
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter( hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten );

    GetConsoleScreenBufferInfo( hConsole, &csbi );
    FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten );
    SetConsoleCursorPosition( hConsole, coordScreen );
	#endif
}

/* Imprime uma string com cor (sem formatação) */
void terminal_colorPrintf(int color, char string[], ...)
{
	va_list format_args;
	va_start(format_args, string);

	if (color < NORMAL)
	{
		#ifdef _WIN32
		WORD colorVector[6] = { 0x04, 0x02, 0x01, 0x03, 0x05, 0x06 };
		HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );
		WORD wOldColorAttrs;
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

		GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
		wOldColorAttrs = csbiInfo.wAttributes;

		SetConsoleTextAttribute ( hConsole, colorVector[color]);

		vprintf(string, format_args);

		SetConsoleTextAttribute ( hConsole, wOldColorAttrs);
		#endif
	}
	else
		vprintf(string, format_args);

	va_end(format_args);
}

/* Dimensões do Terminal */
void terminal_getConsoleSize(int * width, int * height)
{
	#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(hConsole, &csbi);

    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	#endif
}

/* Limpa o buffer */
void input_clear(void)
{
	char c;
	do
		c=getchar();
	while(c!='\n' && c!=EOF);
}

/* Scanf que limpa o buffer automaticamente depois */
void input_readf(char format[], ...)
{
	va_list read_to;
	va_start(read_to, format);

	vscanf(format, read_to);

	input_clear();

	va_end(read_to);
}
