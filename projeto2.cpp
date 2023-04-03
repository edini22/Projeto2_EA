#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int task;
int N; // N empresas que ele esta a pensar em adicionar ao seu portfolio
int D; // coletou os valores diarios das acoes ao longo de D dias
int K; // nunca ter mais do que K acoes de cada empresa
int R; // taxa fixa

/**
 * John nunca pode ter mais do que K acoes de cada empresa
 * Em cada dia, John pode realizar no maximo uma transação(comprar ou vender quantas acoes quiser dessa empresa).
 * A bolsa que John usa/cobra uma taxa fixa R para cada acao(ex: se comprar 2 acoes em uma transacao sera 2 * R),
    nao havendo para a venda destas
 */

/** Tarefas
 * Tarefa 1 : imprimir o melhor lucro que John poderia ter com a negociacao de acoes de cada empresa.
 * Tarefa 2 : para cada empresa, imprimir o melhor lucro e imprimir a informacao de quantas acoes para
   comprar ou vender todos os dias para obter o melhor lucro(atribuir numeros positivos para compras e negativos para vendas)
 * Tarefa 3 : imprimir o melhor lucro e quantos esquemas de negociacao diferentes davam esse mesmo lucro (lucro numero)
    (a+b) mod  m = ((a mod  m)+(b mod  m)) mod  m para o numero de esquemas
 */

vector<vector<int>> V;  // vector que em cada linha representa uma empresa e cada coluna representa um dia
int profit;             // usado para imprimir o lucro total no final
vector<vector<int>> dp; // guardar a info se naquele dia comprou ou vendeu e qual o profit desse caminho

void writeVector() {
    int num;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            cin >> num;
            V[i][j] = num;
        }
    }
}

int maxProfit(int company, int day, int buy) {

    if (day == D){
        return 0;
    }
        
    if (dp[day][buy] != -1)
        return dp[day][buy];

    int prof = 0;

    if (buy) {
        prof = max(-V[company][day] * K + maxProfit(company, day + 1, 0),
                   0 + maxProfit(company, day + 1, 1)) -
               R;

    } else {
        prof = max(V[company][day] * K + maxProfit(company, day + 1, 1),
                   0 + maxProfit(company, day + 1, 0)) -
               R;
    }

    return dp[day][buy] = prof;
}

void task1() {

    for (int i = 0; i < N; i++) {
        dp = vector<vector<int>>(D, vector<int>(2, -1));
        profit = maxProfit(i, 0, 1);
        cout << profit << endl;
    }
}

void task2() {
    cout << "Nao sei :)" << endl;
}

void task3() {
    cout << "Nao sei tambem :)" << endl;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    cin >> task;

    cin >> N >> D >> K >> R;

    V = vector<vector<int>>(N, (vector<int>(D, 0)));
    profit = 0;

    writeVector();

    // fazer funcao para o ex ahah
    switch (task) {
    case 1:
        task1();

        break;
    case 2:
        task2();

        break;
    case 3:
        task3();

        break;
    default:
        break;
    }

    return 0;
}